#ifndef S_S_ILRD_RD102_EXT2_INER_H
#define S_S_ILRD_RD102_EXT2_INER_H

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

static void GetFileInode(ext2_handle_t *ext2, char *file_path);
static int SearchDir(ext2_handle_t *ext2, char *name);
static void ReadInode(ext2_handle_t *ext2, int inode_num);


int InitSuperblock(super_block_t *super_block, const char *device_path);
void InitGroupDescriptor(group_desc_t *group, int fd, size_t block_size);
void InitEXT2(ext2_handle_t *ext2, super_block_t *super, group_desc_t *group, inode_t *inode, int fd);

#endif /* S_S_ILRD_RD102_EXT2_INER_H */