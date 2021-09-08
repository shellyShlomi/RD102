
/*  Developer: Shelly Shlomi;									*
 *  Status:in development;										*
 *  Date Of Creation:01.09.21;									*
 *  Date Of Approval:--.09.21;									*
 *  Approved By: Nir											*
 *  Description: Implementation of FS - EXT2					*/

#include <stdio.h>	  /*printf*/
#include <fcntl.h>	  /*open*/
#include <unistd.h>	  /*read*/
#include <string.h>	  /*memcpy*/
#include <stdlib.h>	  /*malloc*/
#include <sys/stat.h> /*S_ISDIR*/
#include <assert.h>	  /*assert*/

#include "linux_ext2.h"
#include "ilrd_ext2.h"
#include "ilrd_ext2_iner.h"

#ifndef NDEBUG
#define DEBUG if (1)
#else
#define DEBUG if (0)
#endif

#define BASE_OFFSET (1024)
#define BAD_FD (-1)
#define BAD_READ (-1)
#define BLOCK_OFFSET(block) ((block)*block_size)

/******************************* Definition *******************************/

typedef enum debug_print_of
{
	SEARCH_DIR_ENTERY,
	SEARCH_DIR_ENTRY_AND_NAME,
	DEBUG_DIR = SEARCH_DIR_ENTRY_AND_NAME,
	RESULT_DIR,
	GET_FILE_INODE,
	GET_FILE_INODE_SEARCH_DIR,
	GET_FILE_INODE_READ_INODE,
	PRINT_FILE_CONTENT,
	INIT_FD
} debug_print_of_t;

typedef struct debug_print_serch_dir
{
	unsigned int inode_n;
	char *name;
} debug_print_serch_dir_t;

/*************************** Forward Decleretion ***************************/

static size_t block_size = 0;

static void InerPrintForPrintFileContent(inode_t *inode);
static void PrintDebug(debug_print_of_t flag, void *data);
static void PrintSerchDir(debug_print_of_t flag, void *data);
static void InitDebugPrintSerchDir(debug_print_serch_dir_t *debug_print,
								   unsigned int inode_n, char *name);

/********************************** imple **********************************/

int PrintSuperblock(const char *device_path)
{
	super_block_t super_block = {0};
	int fd = BAD_FD;

	if (!device_path)
	{
		return (ERROR);
	}

	if (BAD_FD == (fd = GetFileDescriptor(device_path)))
	{
		PrintDebug(INIT_FD, (void *)device_path);
		return (ERROR);
	}

	if (SUCCESS != InitSuperblock(&super_block, fd, device_path))
	{
		return (ERROR);
	}

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
	int fd = BAD_FD;

	if (!device_path)
	{
		return (ERROR);
	}

	if (BAD_FD == (fd = GetFileDescriptor(device_path)))
	{
		PrintDebug(INIT_FD, (void *)device_path);
		return (ERROR);
	}

	if (SUCCESS != InitSuperblock(&super_block, fd, device_path) ||
		(BAD_READ == InitGroupDescriptor(&group, fd, block_size)))
	{
		return (ERROR);
	}

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
	char file_path_loc[EXT2_MAX_BLOCK_SIZE + 1] = {'\0'};

	super_block_t super = {0};
	group_desc_t group = {0};
	ext2_handle_t ext2 = {0};
	inode_t inode = {0};

	int fd = BAD_FD;
	unsigned int status = 11;

	if (!device_path || !file_path)
	{
		return (ERROR);
	}

	if (BAD_FD == (fd = GetFileDescriptor(device_path)))
	{
		PrintDebug(INIT_FD, (void *)device_path);
		return (ERROR);
	}
	if (SUCCESS != InitSuperblock(&super, fd, device_path) ||
		(BAD_READ == InitGroupDescriptor(&group, fd, block_size)))
	{
		return (ERROR);
	}

	InitEXT2(&ext2, &super, &group, &inode, fd);

	memcpy(file_path_loc, file_path, strlen(file_path) + 1);

	if (ERROR == GetFileInode(&ext2, file_path_loc))
	{
		PrintDebug(PRINT_FILE_CONTENT, NULL);
		return (ERROR);
	}

	status = S_ISDIR(inode.i_mode) ? (InerPrintFileContentDir(&ext2, file_path_loc)) : (InerPrintFileContentFile(&inode, fd));

	close(fd);
	return (status);
}

/***************************** Inner Function  *****************************/

/*----------- for print file contect ------------*/

int InerPrintFileContentDir(ext2_handle_t *ext2, char *name)
{
	InerPrintForPrintFileContent(ext2->inode);
	return !(EXT2_BAD_INO == SearchDir(ext2, name, RESULT_DIR));
}

int InerPrintFileContentFile(inode_t *inode, int fd)
{
	size_t i = 0;
	char file[EXT2_MAX_BLOCK_SIZE + 1] = {'\0'};
	InerPrintForPrintFileContent(inode);

	for (i = 0; i < inode->i_blocks; ++i)
	{
		if (inode->i_block[i])
		{
			lseek(fd, BLOCK_OFFSET(inode->i_block[i]), SEEK_SET);
			if (BAD_READ == read(fd, file, block_size))
			{
				return (ERROR);
			}
			printf("%s\n", file);
		}
	}
	return (SUCCESS);
}

/*----------- Files funcs ------------*/

int GetFileInode(ext2_handle_t *ext2, char *file_path)
{
	unsigned int inode_num = EXT2_ROOT_INO;

	assert(ext2);
	assert(file_path);

	PrintDebug(GET_FILE_INODE, file_path);
	if (BAD_READ == ReadInode(ext2, inode_num))
	{
		PrintDebug(GET_FILE_INODE_READ_INODE, file_path);
		return (ERROR);
	}

	file_path = strtok(file_path, "/");

	while (file_path != NULL)
	{
		PrintDebug(GET_FILE_INODE, file_path);
		inode_num = SearchDir(ext2, file_path, DEBUG_DIR);

		if (EXT2_BAD_INO == inode_num)
		{
			PrintDebug(GET_FILE_INODE_SEARCH_DIR, file_path);
			return (ERROR);
		}

		file_path = strtok(NULL, "/");

		if (BAD_READ == ReadInode(ext2, inode_num))
		{
			PrintDebug(GET_FILE_INODE_READ_INODE, file_path);
			return (ERROR);
		}
	}

	return (SUCCESS);
}

unsigned int SearchDir(const ext2_handle_t *ext2, char *name, int falg)
{
	void *block = NULL;
	dir_entry_t *entry = NULL;
	int inode_n = EXT2_BAD_INO;
	debug_print_serch_dir_t debug_print = {0};

	assert(ext2);
	assert(name);

	if (!S_ISDIR(ext2->inode->i_mode) || ((block = malloc(block_size)) == NULL))
	{
		DEBUG S_ISDIR(ext2->inode->i_mode) ? printf("Memory error\n") : printf("inode mode is: %u\n", S_ISDIR(ext2->inode->i_mode));
		return (EXT2_BAD_INO);
	}

	if (BAD_READ == ReadDataBlock(ext2, block, block_size))
	{
		free(block);
		return (EXT2_BAD_INO);
	}
	entry = (dir_entry_t *)block;

	while ((((char *)block + block_size) > ((char *)entry)))
	{
		InitDebugPrintSerchDir(&debug_print, entry->inode, entry->name);
		PrintSerchDir((debug_print_of_t)falg, &debug_print);

		/* if the file is found leave and return the inode num */
		if ((strlen(name) == entry->name_len) &&
			(!strncmp(entry->name, name, entry->name_len)))
		{
			inode_n = entry->inode;
			PrintDebug(SEARCH_DIR_ENTERY, NULL);
			break;
		}

		entry = (dir_entry_t *)((char *)entry + entry->rec_len);
	}

	free(block);

	return (inode_n);
}

int ReadInode(ext2_handle_t *ext2, int inode_num)
{
	assert(ext2);

	lseek(ext2->fd, BLOCK_OFFSET(ext2->group->bg_inode_table) + ((inode_num - 1) * sizeof(inode_t)), SEEK_SET);

	return read(ext2->fd, ext2->inode, sizeof(inode_t));
}

int ReadDataBlock(const ext2_handle_t *ext2, void *block, size_t block_size)
{
	assert(ext2);

	lseek(ext2->fd, BLOCK_OFFSET(ext2->inode->i_block[0]), SEEK_SET);
	return (read(ext2->fd, block, block_size));
}

/******************************** Init Func ********************************/
/*----------- Init Files funcs ------------*/
int GetFileDescriptor(const char *device_path)
{
	assert(device_path);

	return (open(device_path, O_RDONLY));
}

int InitSuperblock(super_block_t *super_block, int fd, const char *device_path)
{
	assert(super_block);
	assert(device_path);
	assert(BAD_FD != fd);

	lseek(fd, BASE_OFFSET, SEEK_SET); /* position head above super_block */
	if (BAD_READ == read(fd, super_block, sizeof(super_block_t)))
	{
		DEBUG printf("can read this file, InitSuperblock() line: %d\n", __LINE__);
		return (BAD_READ);
	}

	block_size = EXT2_BLOCK_SIZE(super_block);

	if (super_block->s_magic != EXT2_SUPER_MAGIC)
	{
		DEBUG perror("Not a Ext2 filesystem\n");
		return (ERROR);
	}

	return (SUCCESS);
}

int InitGroupDescriptor(group_desc_t *group, int fd, size_t block_size)
{
	assert(group);
	assert(BAD_FD != fd);
	assert(0 < block_size);

	lseek(fd, block_size, SEEK_SET);
	return read(fd, group, sizeof(group_desc_t));
}

void InitEXT2(ext2_handle_t *ext2,
			  super_block_t *super,
			  group_desc_t *group,
			  inode_t *inode,
			  int fd)
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

/************************** Print For DEBUG Funcs **************************/

static void InitDebugPrintSerchDir(debug_print_serch_dir_t *debug_print,
								   unsigned int inode_n, char *name)
{
	assert(inode_n != EXT2_BAD_INO);
	assert(name);
	assert(debug_print);

	debug_print->inode_n = inode_n;
	debug_print->name = name;

	return;
}

static void InerPrintForPrintFileContent(inode_t *inode)
{
	size_t i = 0;

	assert(inode);

	/*prints the offset of each datat block of the curr inode */
	DEBUG for (i = 0; i < EXT2_N_BLOCKS; i++)
	{
		if (i < EXT2_NDIR_BLOCKS)
		{
			printf("Block %2lu : %u\n", i, inode->i_block[i]);
		}
		else if (i == EXT2_IND_BLOCK)
		{
			printf("Single   : %u\n", inode->i_block[i]);
		}
		else if (i == EXT2_DIND_BLOCK)
		{
			printf("Double   : %u\n", inode->i_block[i]);
		}
		else if (i == EXT2_TIND_BLOCK)
		{
			printf("Triple   : %u\n", inode->i_block[i]);
		}
	}

	printf("%s\n", B_GREEN);
	puts("File Content:");
	printf("%s\n", RESET);

	return;
}

static void PrintSerchDir(debug_print_of_t flag, void *data)
{
	if (RESULT_DIR == flag)
	{
		printf("%10u %s \n",
			   (unsigned int)(((debug_print_serch_dir_t *)data)->inode_n),
			   (char *)(((debug_print_serch_dir_t *)data)->name));
		return;
	}

	PrintDebug(SEARCH_DIR_ENTRY_AND_NAME, data);
	return;
}

static void PrintDebug(debug_print_of_t flag, void *data)
{
	switch (flag)
	{
	case GET_FILE_INODE_READ_INODE:
	{
		DEBUG printf("%s", RED);
		DEBUG printf("ReadInode failed\n");
		DEBUG printf("%s", RESET);
		break;
	}
	case GET_FILE_INODE_SEARCH_DIR:
	{
		DEBUG printf("%s", RED);
		DEBUG printf("File not found\n");
		DEBUG printf("%s", RESET);
		break;
	}
	case SEARCH_DIR_ENTERY:
	{
		DEBUG printf("%s", GREEN);
		DEBUG printf("File found\n");
		DEBUG printf("%s", RESET);
		break;
	}
	case SEARCH_DIR_ENTRY_AND_NAME:
	{
		DEBUG printf("%s", CYAN);
		DEBUG printf("%10u %s \n",
					 (unsigned int)(((debug_print_serch_dir_t *)data)->inode_n),
					 (char *)(((debug_print_serch_dir_t *)data)->name));
		DEBUG printf("%s", RESET);
		break;
	}
	case GET_FILE_INODE:
	{
		DEBUG printf("%s", BLUE);
		DEBUG printf("file = %s\n", (char *)data);
		DEBUG printf("%s", RESET);
		break;
	}
	case PRINT_FILE_CONTENT:
	{
		DEBUG printf("%s", RED);
		DEBUG printf("GetFileInode failed\n");
		DEBUG printf("%s", RESET);
		break;
	}
	case INIT_FD:
	{
		DEBUG printf("%s", RED);
		DEBUG printf("can not open device: %s\n", (char *)data);
		DEBUG printf("%s", RESET);
	}

	default:
	{
		break;
	}
	}
	return;
}