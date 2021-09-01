#include <stdio.h>    /*printf*/
#include <fcntl.h>    /*open*/
#include <unistd.h>   /*read*/
#include <string.h>   /*memcpy*/
#include <stdlib.h>   /*malloc*/
#include <sys/stat.h> /*S_ISDIR*/
#include <assert.h>   /*assert*/

#include "linux_ext2.h"
#include "ilrd_ext2.h"
#include "ilrd_ext2_iner.h"

#ifndef NDEBUG
#define DEBUG if (1)
#else
#define DEBUG if (0)
#endif

/* 
mke2fs 1.45.5 (07-Jan-2020)
Creating filesystem with 26214 4k blocks and 26240 inodes

Allocating group tables: done                            
Writing inode tables: done                            
Writing superblocks and filesystem accounting information: done
*/

static size_t block_size = 0;

#define BASE_OFFSET (1024)
#define BLOCK_OFFSET(block) ((block)*block_size)

int PrintSuperblock(const char *device_path)
{
  super_block_t super_block = {0};
  int fd = InitSuperblock(&super_block, device_path);

  printf("Reading super block from device %s: \n"
         "Inodes count            : %u\n"
         "Blocks count            : %u\n"
         "Reserved blocks count   : %u\n"
         "Free blocks count       : %u\n"
         "Free inodes count       : %u\n"
         "First data block        : %u\n"
         "Block size              : %lu\n"
         "Blocks per group        : %u\n"
         "Inodes per group        : %u\n"
         "Creator OS              : %u\n"
         "First non-reserved inode: %u\n"
         "Size of inode structure : %hu\n",
         device_path,
         super_block.s_inodes_count,
         super_block.s_blocks_count,
         super_block.s_r_blocks_count,
         super_block.s_free_blocks_count,
         super_block.s_free_inodes_count,
         super_block.s_first_data_block,
         block_size,
         super_block.s_blocks_per_group,
         super_block.s_inodes_per_group,
         super_block.s_creator_os,
         super_block.s_first_ino,
         super_block.s_inode_size);

  close(fd);

  return (SUCCESS);
}

int PrintGroupDescriptor(const char *device_path)
{
  super_block_t super_block = {0};
  group_desc_t group = {0};
  int fd = InitSuperblock(&super_block, device_path);

  assert(device_path);

  InitGroupDescriptor(&group, fd, block_size);

  printf("Reading first group-descriptor from device %s:\n"
         "Blocks bitmap block: %u\n"
         "Inodes bitmap block: %u\n"
         "Inodes table block : %u\n"
         "Free blocks count  : %u\n"
         "Free inodes count  : %u\n"
         "Directories count  : %u\n",
         device_path,
         group.bg_block_bitmap,
         group.bg_inode_bitmap,
         group.bg_inode_table,
         group.bg_free_blocks_count,
         group.bg_free_inodes_count,
         group.bg_used_dirs_count);

  close(fd);

  return (SUCCESS);
}

int PrintFileContent(const char *device_path, const char *file_path)
{
  char file_path_loc[EXT2_MAX_BLOCK_SIZE + 1] = {0};
  super_block_t super = {0};
  group_desc_t group = {0};
  ext2_handle_t ext2 = {0};
  inode_t inode = {0};
  size_t i = 0;
  int fd = -1;

  assert(device_path);

  fd = InitSuperblock(&super, device_path);

  InitGroupDescriptor(&group, fd, block_size);
  InitEXT2(&ext2, &super, &group, &inode, fd);

  memcpy(file_path_loc, file_path, strlen(file_path));

  GetFileInode(&ext2, file_path_loc);

  DEBUG
  {
    /*prints the offset of each datat block of the curr inode */
    for (i = 0; i < EXT2_N_BLOCKS; i++)
    {
      if (i < EXT2_NDIR_BLOCKS)
      {
        printf("Block %2lu : %u\n", i, inode.i_block[i]);
      }
      else if (i == EXT2_IND_BLOCK)
      {
        printf("Single   : %u\n", inode.i_block[i]);
      }
      else if (i == EXT2_DIND_BLOCK)
      {
        printf("Double   : %u\n", inode.i_block[i]);
      }
      else if (i == EXT2_TIND_BLOCK)
      {
        printf("Triple   : %u\n", inode.i_block[i]);
      }
    }
  }

  for (i = 0; i < EXT2_N_BLOCKS; i++)
  {
    char file[EXT2_MAX_BLOCK_SIZE + 1];

    if (inode.i_block[i])
    {
      lseek(fd, BLOCK_OFFSET(inode.i_block[i]), SEEK_SET);
      if (-1 == read(fd, file, block_size))
      {
        return (ERROR);
      }
      printf("%s\n", file);
    }
  }

  close(fd);

  return (SUCCESS);
}

static void GetFileInode(ext2_handle_t *ext2, char *file_path)
{
  int inode_num = EXT2_ROOT_INO;
  inode_t curr_inode = {0};
  ext2_handle_t ext2_loc = {0};
  char *curr_file = file_path;

  memcpy(&ext2_loc, ext2, sizeof(ext2_handle_t));

  DEBUG printf("  file = %s\n", curr_file);

  ext2_loc.inode = &curr_inode;

  ReadInode(&ext2_loc, inode_num);

  DEBUG printf("%d\n", curr_inode.i_size);
  curr_file = strtok(curr_file, "/");

  while (curr_file != NULL)
  {
    DEBUG printf("file = %s\n", curr_file);
    inode_num = SearchDir(&ext2_loc, curr_file);
    DEBUG printf("file = %s\n", curr_file);

    if (-1 == inode_num)
    {
      DEBUG printf("File not found");
      return;
    }
    curr_file = strtok(NULL, "/");
    ReadInode(&ext2_loc, inode_num);
  }

  memcpy(ext2->inode, &curr_inode, sizeof(inode_t));

  return;
}

static int SearchDir(ext2_handle_t *ext2, char *name)
{
  dir_entry_t *entry = NULL;
  void *block = NULL;
  int inode_n = -1;
  size_t size = 0;

  if (!S_ISDIR(ext2->inode->i_mode))
  {
    return (inode_n);
  }

  if ((block = malloc(block_size)) == NULL)
  {
    DEBUG perror("Memory error\n");
    return (-1);
  }

  lseek(ext2->fd, BLOCK_OFFSET(ext2->inode->i_block[0]), SEEK_SET);
  if (-1 == read(ext2->fd, block, block_size))
  {
    return (-1);
  }
  entry = (dir_entry_t *)block;

  while ((size < ext2->inode->i_size) && entry->inode)
  {
    char file_name[EXT2_MAX_BLOCK_SIZE];
    memcpy(file_name, entry->name, entry->name_len);
    file_name[entry->name_len] = '\0';

    /*prints the dir content*/
    DEBUG printf("%10u %s\n", entry->inode, file_name);

    /*if the file is found leave and return the inode num */
    if (!strncmp(file_name, name, strlen(name) + 1))
    {
      DEBUG printf("File found\n");
      inode_n = entry->inode;
      break;
    }

    entry = (dir_entry_t *)((char *)entry + entry->rec_len);
    size += entry->rec_len;
  }

  free(block);

  return (inode_n);
}

static int ReadInode(ext2_handle_t *ext2, int inode_num)
{
  lseek(ext2->fd, BLOCK_OFFSET(ext2->group->bg_inode_table) + ((inode_num - 1) * sizeof(inode_t)), SEEK_SET);

  return read(ext2->fd, ext2->inode, sizeof(inode_t));
}

int InitSuperblock(super_block_t *super_block, const char *device_path)
{
  int fd = -1;
  assert(super_block);
  assert(device_path);

  if (((fd = open(device_path, O_RDONLY)) < 0))
  {
    DEBUG printf("can not open device: %s\n", device_path);
    return (fd);
  }

  lseek(fd, BASE_OFFSET, SEEK_SET); /* position head above super_block */
  if (-1 == read(fd, super_block, sizeof(super_block_t)))
  {
    return (-1);
  }

  block_size = EXT2_BLOCK_SIZE(super_block);

  if (super_block->s_magic != EXT2_SUPER_MAGIC)
  {
    DEBUG perror("Not a Ext2 filesystem\n");
  }

  return (fd);
}

int InitGroupDescriptor(group_desc_t *group, int fd, size_t block_size)
{
  assert(group);
  assert(0 < fd);
  assert(0 < block_size);

  lseek(fd, block_size, SEEK_SET);
  return read(fd, group, sizeof(group_desc_t));
}

void InitEXT2(ext2_handle_t *ext2, super_block_t *super, group_desc_t *group, inode_t *inode, int fd)
{
  assert(ext2);
  assert(group);
  assert(super);
  assert(inode);
  assert(0 < fd);

  ext2->super = super;
  ext2->group = group;
  ext2->inode = inode;
  ext2->fd = fd;

  return;
}
