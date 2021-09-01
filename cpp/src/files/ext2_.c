#include <stdio.h>    /*printf*/
#include <fcntl.h>    /*open*/
#include <unistd.h>   /*read*/
#include <string.h>   /*memcpy*/
#include <stdlib.h>   /*malloc*/
#include <sys/stat.h> /*S_ISDIR*/

#include "linux_ext2.h"
#include "ilrd_ext2.h"

/* 
mke2fs 1.45.5 (07-Jan-2020)
Creating filesystem with 262144 4k blocks and 65536 inodes
Filesystem UUID: 8243b37e-ade7-474b-9a1c-6860c5fd7f4e
Superblock backups stored on blocks: 
	32768, 98304, 163840, 229376

Allocating group tables: done                            
Writing inode tables: done                            
Writing superblocks and filesystem accounting information: done

*/
typedef struct ext2_inode inode_t;
typedef struct ext2_super_block super_block_t;
typedef struct ext2_group_desc group_desc_t;
typedef struct ext2_handle ext2_handle_t;
typedef struct ext2_dir_entry_2 dir_entry_t;

struct ext2_handle
{
  super_block_t *super;
  group_desc_t *group;
  inode_t *inode;
  int fd;
};

enum errors
{
  SUCCESS,
  ERROR
};

static size_t block_size = 0;

#define BASE_OFFSET (1024)
#define BLOCK_OFFSET(block) ((block)*block_size)

static void GetFileInode(ext2_handle_t *ext2, char *file_path);

static int SearchDir(ext2_handle_t *ext2, char *name);

int PrintSuperblock(const char *device_path)
{

  super_block_t super_block = {0};
  int fd = 0;

  fd = open(device_path, O_RDONLY);
  lseek(fd, BASE_OFFSET, SEEK_SET); /* position head above super_block */
  read(fd, &super_block, sizeof(super_block_t));

  block_size = EXT2_BLOCK_SIZE(&super_block);

  if (super_block.s_magic != EXT2_SUPER_MAGIC)
  {
    fprintf(stderr, "Not a Ext2 filesystem\n");
    close(fd);

    return (ERROR);
  }

  printf("Reading super block from device %s: \n"

         "Inodes count            : %u\n"
         "Blocks count            : %u\n"
         "Reserved blocks count   : %u\n"
         "Free blocks count       : %u\n"
         "Free inodes count       : %u\n"
         "First data block        : %u\n"
         "Block size              : %u\n"
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
  struct ext2_super_block super_block;
  struct ext2_group_desc group;
  int fd;

  if (((fd = open(device_path, O_RDONLY)) < 0))
  {
    fprintf(stderr, "Not a Ext2 filesystem\n");
    close(fd);
    return (ERROR);
  }

  lseek(fd, BASE_OFFSET, SEEK_SET); /* position head above super_block */
  read(fd, &super_block, sizeof(struct ext2_super_block));

  block_size = EXT2_BLOCK_SIZE(&super_block);

  if (super_block.s_magic != EXT2_SUPER_MAGIC)
  {
    fprintf(stderr, "Not a Ext2 filesystem\n");
    close(fd);
    return (ERROR);
  }

  lseek(fd, block_size, SEEK_SET); /*get the offset in bytes*/
  read(fd, &group, sizeof(group));

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

static void ReadInode(int fd, int inode_no, group_desc_t *group, inode_t *inode)
{
  lseek(fd, BLOCK_OFFSET(group->bg_inode_table) + ((inode_no) * sizeof(inode_t)), SEEK_SET);
  read(fd, inode, sizeof(inode_t));
}

int PrintFileContent(const char *device_path, const char *file_path)
{
  inode_t inode;
  super_block_t super;
  group_desc_t group;
  int fd;
  int i;
  char file[4243456];

  ext2_handle_t ext2 = {0};

  if ((fd = open(device_path, O_RDONLY)) < 0)
  {
    perror(device_path);
  }

  lseek(fd, BASE_OFFSET, SEEK_SET);
  read(fd, &super, sizeof(super));

  if (super.s_magic != EXT2_SUPER_MAGIC)
  {
    fprintf(stderr, "Not a Ext2 filesystem\n");
  }

  lseek(fd, EXT2_BLOCK_SIZE(&super), SEEK_SET);
  read(fd, &group, sizeof(group));

  ext2.super = &super;
  ext2.group = &group;
  ext2.inode = &inode;
  ext2.fd = fd;

  GetFileInode(&ext2, (char *)file_path);

  for (i = 0; i < EXT2_N_BLOCKS; i++)
  {
    if (inode.i_block[i])
    {
      lseek(fd, BLOCK_OFFSET(inode.i_block[i] + 1), SEEK_SET);

      read(fd, file, block_size);
      printf("%s\n", file);
    }
  }

  close(fd);
}

static void GetFileInode(ext2_handle_t *ext2, char *file_path)
{
  size_t inode_num = EXT2_ROOT_INO;
  size_t size = 0;
  inode_t curr_inode = {0};
  ext2_handle_t ext2_loc = {0};

  char *curr_file = strtok(file_path, "/");

  memcpy(&ext2_loc, ext2, sizeof(ext2_handle_t));

  printf("file = %s\n", curr_file);

  ReadInode(ext2_loc.fd, inode_num, ext2_loc.group, &curr_inode);

/*   printf("%d\n", curr_inode.i_size);
 */
  while (curr_file != NULL)
  {
    ext2_loc.inode = &curr_inode;
    inode_num = SearchDir(&ext2_loc, curr_file);

    if (0 == inode_num)
    {
      puts("File not found");
      return;
    }

    printf("inode is = %ld\n", inode_num);
    curr_file = strtok(NULL, "/");

    ReadInode(ext2_loc.fd, inode_num, ext2_loc.group, &curr_inode);
  }

  memcpy(ext2->inode, &curr_inode, sizeof(inode_t));

  puts("File found");

  return;
}

static int SearchDir(ext2_handle_t *ext2, char *name)
{
  void *block;

  if (S_ISDIR(ext2->inode->i_mode))
  {
    dir_entry_t *entry;
    size_t size = 0;

    if ((block = malloc(block_size)) == NULL)
    {
      perror("Memory error\n");
      close(ext2->fd);
      return (ERROR);
    }

    lseek(ext2->fd, BLOCK_OFFSET(ext2->inode->i_block[0]), SEEK_SET);
    read(ext2->fd, block, block_size);

    entry = (dir_entry_t *)block;

    while ((size < ext2->inode->i_size) && entry->inode)
    {
      char file_name[EXT2_NAME_LEN + 1];
      memcpy(file_name, entry->name, entry->name_len);
      file_name[entry->name_len] = '\0';

      /*                              //prints the dir content
      printf("%u", entry->rec_len);
      printf("%10u %s\n", entry->inode, file_name); 
      */

      if (!strcmp(file_name, name))
      {
        return (entry->inode);
      }

      entry = (dir_entry_t *)((char *)entry + entry->rec_len);
      size += entry->rec_len;
    }

    free(block);
  }
  return (SUCCESS);
}