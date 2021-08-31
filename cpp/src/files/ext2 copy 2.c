#include <stdio.h>  /*printf*/
#include <fcntl.h>  /*open*/
#include <unistd.h> /*read*/
#include <string.h> /*memcpy*/

#include "linux_ext2.h"
#include "ilrd_ext2.h"

/* 
 * mke2fs 1.45.5 (07-Jan-2020)
 * Creating filesystem with 262144 4k blocks and 65536 inodes
 * Filesystem UUID: feefdd51-2e6f-44cb-96b0-314ffcaa5f59
 * Superblock backups stored on blocks: 
 *      32768, 98304, 163840, 229376
 *
 * Allocating group tables: done                            
 * Writing inode tables: done                            
 * Writing superblocks and filesystem accounting information: done 
*/

enum errors
{
  SECCSUS,
  ERROR
};

static size_t block_size = 0;

#define BASE_OFFSET (1024)
#define BLOCK_OFFSET(block) (BASE_OFFSET + (block - 1) * block_size)

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

  printf("Reading super block from device %s: \n", device_path);
  printf("Inodos count: %d \n", super_block.s_inodes_count);
  printf("Blocks count: %d \n", super_block.s_blocks_count);
  printf("Blocks per group: %d \n", super_block.s_blocks_per_group);
  printf("NM: %x\n", super_block.s_magic);
  printf("size: %d\n", block_size);

/*   close(fd);
 */
  return (SECCSUS);
}

int PrintGroupDescriptor(const char *device_path)
{
  struct ext2_super_block super_block;
  struct ext2_group_desc group;
  int fd;


  if (((fd = open(device_path, O_RDONLY)) < 0))
  {
    fprintf(stderr, "Not a Ext2 filesystem\n");
/*     close(fd);
 */    return (ERROR);
  }

  lseek(fd, BASE_OFFSET, SEEK_SET); /* position head above super_block */
  read(fd, &super_block, sizeof(struct ext2_super_block));
  block_size = EXT2_BLOCK_SIZE(&super_block);

  if (super_block.s_magic != EXT2_SUPER_MAGIC)
  {
    fprintf(stderr, "Not a Ext2 filesystem\n");
/*     close(fd);
 */    return (ERROR);
  }

  lseek(fd, BASE_OFFSET + block_size, SEEK_SET);
  read(fd, &group, sizeof(group));

  printf("Reading first group-descriptor from device %s:\n"
         "Free blocks count  : %u\n"
         "Free inodes count  : %u\n"
         "Directories count  : %u\n",
         device_path,
         group.bg_free_blocks_count,
         group.bg_free_inodes_count,
         group.bg_used_dirs_count);

  close(fd);

  return (SECCSUS);
}
/* 
int PrintFileContent(const char *device_path, const char *file_path)
{
  struct ext2_inode inode;
  struct ext2_super_block super;
  struct ext2_group_desc group;
  int fd;
  int i;


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



  lseek(fd, BASE_OFFSET + block_size, SEEK_SET);
  read(fd, &group, sizeof(group));



  printf("Reading root inode\n"
         "File mode: %hu\n"
         "Owner UID: %hu\n"
         "Size     : %u bytes\n"
         "Blocks   : %u\n",
         inode.i_mode,
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

  close(fd);
  EXT2_ROOT_INO;
}
 */