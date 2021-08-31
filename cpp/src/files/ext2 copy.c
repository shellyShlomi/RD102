#include <stdio.h>  /*printf*/
#include <fcntl.h>  /*open*/
#include <unistd.h> /*read*/
#include <string.h> /*memcpy*/

#include "linux_ext2.h"
#include "ilrd_ext2.h"

/*mke2fs 1.45.5 (07-Jan-2020)
Creating filesystem with 262144 4k blocks and 65536 inodes
Filesystem UUID: feefdd51-2e6f-44cb-96b0-314ffcaa5f59
Superblock backups stored on blocks: 
        32768, 98304, 163840, 229376

Allocating group tables: done                            
Writing inode tables: done                            
Writing superblocks and filesystem accounting information: done*/

enum errors
{
  SECCSUS,
  ERROR
};

typedef struct ext2_super_block super_block_t;
typedef struct ext2_group_desc group_desc_t;
int InitSuperBlock(super_block_t *super, const char *device_path);
int GetFileDicriptor(const char *device_path);

void PrintSuperblock(const char *device_path)
{

  super_block_t super_block;

  InitSuperBlock(&super_block, device_path);

  printf("Inodos count: %d \n", super_block.s_inodes_count);
  printf("Blocks count: %d \n", super_block.s_blocks_count);
  printf("Blocks per group: %d \n", super_block.s_blocks_per_group);
  printf("NM: %p\n", super_block.s_magic);

  return;
}

void PrintGroupDescriptor(const char *device_path)
{
  struct ext2_super_block super_block;
  size_t s_block_size = 0;

  struct ext2_group_desc group;
  int fd;

  fd = open(device_path, O_RDONLY);

  if (super_block.s_magic != EXT2_SUPER_MAGIC)
  {
    fprintf(stderr, "Not a Ext2 filesystem\n");
    return;
  }

  lseek(fd, EXT2_MIN_BLOCK_SIZE, SEEK_SET); /* position head above super_block-block */
  read(fd, &super_block, sizeof(struct ext2_super_block));
  s_block_size = super_block.s_log_block_size;

  lseek(fd, EXT2_MIN_BLOCK_SIZE + s_block_size, SEEK_SET);
  read(fd, &group, sizeof(group));

  printf("Reading first group-descriptor from device  %s:\n"
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
}
/* void PrintFileContent(const char *device_path, const char *file_path);
 */

int InitSuperBlock(super_block_t *super, const char *device_path)
{
  int fd;
  fd = GetFileDicriptor(device_path);

  lseek(fd, EXT2_BLOCK_SIZE(super), SEEK_SET); /* position head above super_block */
  read(fd, super, sizeof(super_block_t));

  if (super->s_magic != EXT2_SUPER_MAGIC)
  {
    fprintf(stderr, "Not a Ext2 filesystem\n");
    return (ERROR);
  }

  return (SECCSUS);
}

int GetFileDicriptor(const char *device_path)
{
  int fd;

  fd = open(device_path, O_RDONLY);

  return (fd);
}

/* int InitBlockGroup(group_desc_t *g_desc, const char *device_path)
{
  struct ext2_super_block super_block;
  size_t s_block_size = 0;

  int fd = -2;

  if (ERROR == InitSuperBlock(&super_block, device_path))
  {
    return (ERROR);
  }

  lseek(fd, EXT2_BLOCK_SIZE(super_block) + EXT2_BLOCK_SIZE(super_block), SEEK_SET);
  read(fd, g_desc, sizeof(super_block_t));

  return (SECCSUS);
} */