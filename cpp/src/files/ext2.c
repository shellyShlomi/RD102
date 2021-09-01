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

enum errors
{
  SUCCESS,
  ERROR
};

static size_t block_size = 0;

#define BASE_OFFSET (1024)
#define BLOCK_OFFSET(block) ((block)*block_size)

int PrintSuperblock(const char *device_path)
{

  struct ext2_super_block super_block;
  int fd;

  fd = open(device_path, O_RDONLY);
  lseek(fd, BASE_OFFSET, SEEK_SET); /* position head above super_block */
  read(fd, &super_block, sizeof(struct ext2_super_block));

  block_size = EXT2_BLOCK_SIZE(&super_block);

  if (super_block.s_magic != EXT2_SUPER_MAGIC)
  {
    fprintf(stderr, "Not a Ext2 filesystem\n");
    close(fd);

    return (ERROR);
  }

  /*    printf("Reading super block from device %s: \n", device_path);
  printf("Inodos count: %d \n", super_block.s_inodes_count);
  printf("Blocks count: %d \n", super_block.s_blocks_count);
  printf("Blocks per group: %d \n", super_block.s_blocks_per_group);
  printf("NM: %x\n", super_block.s_magic);
  printf("size: %d\n", block_size); */

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

static void read_inode(int fd, int inode_no, struct ext2_group_desc *group, struct ext2_inode *inode)
{
  lseek(fd, BLOCK_OFFSET(group->bg_inode_table) + ((inode_no) * sizeof(struct ext2_inode)), SEEK_SET);
  read(fd, inode, sizeof(struct ext2_inode));
}

static void read_dir(int fd, struct ext2_inode *inode, struct ext2_group_desc *group)
{
  void *block;
  if (S_ISDIR(inode->i_mode))
  {
    struct ext2_dir_entry_2 *entry;
    unsigned int size = 0;

    if ((block = malloc(block_size)) == NULL)
    {
      fprintf(stderr, "Memory error\n");
      close(fd);
      exit(1);
    }

    lseek(fd, BLOCK_OFFSET(inode->i_block[0]), SEEK_SET);
    read(fd, block, block_size);

    entry = (struct ext2_dir_entry_2 *)block;

    while ((size < inode->i_size) && entry->inode)
    {
      char file_name[EXT2_NAME_LEN + 1];
      memcpy(file_name, entry->name, entry->name_len);
      file_name[entry->name_len] = 0;
      printf("%u", entry->rec_len);
      printf("%10u %s\n", entry->inode, file_name);

      entry = (struct ext2_dir_entry_2 *)((char *)entry + entry->rec_len);
      size += entry->rec_len;
    }

    free(block);
  }
  return;
}

int PrintFileContent(const char *device_path, const char *file_path)
{
  struct ext2_inode inode;
  struct ext2_inode inode2;
  struct ext2_super_block super;
  struct ext2_group_desc group;
  int fd;
  int i;
  char file[4243456];

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

  read_inode(fd, 2, &group, &inode);
  read_dir(fd, &inode, &group);

  printf("\nReading root inode\n"
         "File mode: %hu\n"
         "File mode: %u\n"
         "Owner UID: %hu\n"
         "Size     : %u bytes\n"
         "Blocks   : %u\n",
         inode.i_mode,
         S_ISREG(inode.i_mode),
         inode.i_uid,
         inode.i_size,
         inode.i_blocks);

  for (i = 0; i < EXT2_N_BLOCKS; i++)
    if (i < EXT2_NDIR_BLOCKS)
      printf("Block %2u : %u\n", i, inode.i_block[i]);
    else if (i == EXT2_IND_BLOCK)
      printf("Single   : %u\n", inode.i_block[i]);
    else if (i == EXT2_DIND_BLOCK)
      printf("Double   : %u\n", inode.i_block[i]);
    else if (i == EXT2_TIND_BLOCK)
      printf("Triple   : %u\n", inode.i_block[i]);

  read_inode(fd, 12, &group, &inode2);

  printf("\nReading 12 inode\n"
         "File mode: %hu\n"
         "File mode: %u\n"
         "Owner UID: %hu\n"
         "Size     : %u bytes\n"
         "Blocks   : %u\n",
         inode2.i_mode,
         S_ISREG(inode2.i_mode),
         inode2.i_uid,
         inode2.i_size,
         inode2.i_blocks);

  for (i = 0; i < EXT2_N_BLOCKS; i++)
  {

    if (i < EXT2_NDIR_BLOCKS)
    {
      printf("Block %2u : %u\n", i, inode2.i_block[i]);
      lseek(fd, BLOCK_OFFSET(inode2.i_block[i] + 1), SEEK_SET);
      read(fd, file, block_size);
      printf("%s\n", file);

    }
    else if (i == EXT2_IND_BLOCK)
    {
      printf("Single   : %u\n", inode2.i_block[i]);
      lseek(fd, BLOCK_OFFSET(inode2.i_block[i] + 1), SEEK_SET);
      read(fd, file, block_size);
      printf("%s\n", file);

    }
    else if (i == EXT2_DIND_BLOCK)
    {
      printf("Double   : %u\n", inode2.i_block[i]);
      lseek(fd, BLOCK_OFFSET(inode2.i_block[i] + 1), SEEK_SET);
      read(fd, file, block_size);
      printf("%s\n", file);

    }
    else if (i == EXT2_TIND_BLOCK)
    {
      printf("Triple   : %u\n", inode2.i_block[i]);
      lseek(fd, BLOCK_OFFSET(inode2.i_block[i] + 1), SEEK_SET);
      read(fd, file, block_size);
      printf("%s\n", file);
    }
    /* 
    lseek(fd, BLOCK_OFFSET(584 + 1), SEEK_SET);

    read(fd, file, block_size);

    printf("%s\n", file); */
  }

  close(fd);
}


static void GetFileInode(ext2_handle_t *ext2, char *file_path)
{
    size_t inode_num = EXT2_ROOT_INO;
    size_t size = 0;
    inode_t curr_inode = {0};
    char *curr_file = strtok(file_path, "/");

    printf("file = %s\n", curr_file);
    ReadInode(ext2, inode_num, ext2->groups, &curr_inode);

    printf("%d\n", curr_inode.i_size);

    while (curr_file != NULL)
    {
        inode_num = SearchDir(ext2, &curr_inode, file_path);

        if (0 == inode_num)
        {
            puts("File not found");
            return;
        }

        printf("inode is = %ld\n", inode_num);
        curr_file = strtok(NULL, "/");
        ReadInode(ext2, inode_num, ext2->groups, &curr_inode);
    }

    puts("File found");

    return;
}