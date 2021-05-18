#include <bits/wordsize.h> /* wordsize macro */
#include <stddef.h> /* size_t */
#include <assert.h>

#include "fsa.h" 

struct fsa
{
	size_t next_free; 
};

typedef struct fsa_block_header
{
	size_t next_free;
}fsa_block_header_t;


fsa_t *FSAInit(void *mem_pool, size_t pool_size, size_t inner_block_size)
{
	fsa_block_header_t *block_header = mem_pool;
	size_t sum_block_offset = 0;
	size_t align_diif = 0;
	size_t num_of_blocks = 0;
	size_t i = 1;
	
	assert(NULL != mem_pool);
	
	align_diif = ((size_t)mem_pool % __WORDSIZE);
	
	mem_pool = (char *)mem_pool + align_diif;	
	inner_block_size += (inner_block_size % __WORDSIZE);
	
	num_of_blocks = (pool_size - align_diif - sizeof(fsa_t)) / inner_block_size;
	
	block_header->next_free = sizeof(fsa_t);
	sum_block_offset = block_header->next_free;
	block_header = block_header + sizeof(fsa_t);

	for(i = 1; i < num_of_blocks; ++i)
	{
		block_header->next_free = (inner_block_size) + sum_block_offset;
		sum_block_offset = block_header->next_free;
		block_header = (fsa_block_header_t *)((char *)mem_pool + sum_block_offset);
	}
	
	return ((fsa_t *)mem_pool);
}



void *FSAAlloc(fsa_t *fsa)
{
	void *temp = NULL;
	
	assert(NULL != fsa);
	
	if (0 == FSACountFree(fsa))
	{
		return (NULL);
	}
	
	temp = (void *)(fsa->next_free + (char *)fsa);
	
	fsa->next_free = ((fsa_block_header_t *)temp)->next_free;
	
	return (temp);
}


void FSAFree(fsa_t *fsa, void *mem_block)
{
	assert(NULL != mem_block);
	assert(NULL != fsa);
	
	((fsa_block_header_t *)mem_block)->next_free = fsa->next_free;
	
	fsa->next_free = ((size_t)((fsa_t *)mem_block - fsa));
	
	return ;
}

size_t FSASuggestSize(size_t num_of_blocks, size_t block_size)
{
	block_size += block_size % __WORDSIZE;
	
	return ((block_size * num_of_blocks) + sizeof(fsa_t));
	
}

size_t FSACountFree(const fsa_t *fsa)
{
	size_t count = 0;
	
	fsa_block_header_t *local_start = (fsa_block_header_t *)fsa;
	
	assert(NULL != fsa);

	while (0 != local_start->next_free)
	{
		++count;
		/* fsa->next is from type fsa_block_header_t */
		local_start = (fsa_block_header_t *)(local_start->next_free + (char *)fsa); 
	}
	
	return (count);
}


