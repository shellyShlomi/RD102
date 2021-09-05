#ifndef S_S_ILRD_RD102_EXT2_INER_H
#define S_S_ILRD_RD102_EXT2_INER_H

#include "print_colores.h"

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

int InerPrintFileContentDir(ext2_handle_t *ext2, char *name);
int InerPrintFileContentFile(inode_t *inode, int fd);

int GetFileDescriptor(const char *device_path);
int GetFileInode(ext2_handle_t *ext2, char *file_path);
unsigned int SearchDir(const ext2_handle_t *ext2, char *name, int falg);
int ReadInode(ext2_handle_t *ext2, int inode_num);
int ReadDataBlock(const ext2_handle_t *ext2, void *block, size_t block_size);

int InitSuperblock(super_block_t *super_block, int fd, const char *device_path);
int InitGroupDescriptor(group_desc_t *group, int fd, size_t block_size);
void InitEXT2(ext2_handle_t *ext2,
              super_block_t *super,
              group_desc_t *group,
              inode_t *inode,
              int fd);

#endif /* S_S_ILRD_RD102_EXT2_INER_H */