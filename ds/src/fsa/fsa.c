/*  Developer: Shelly Shlomi;									*
 *  Status:approved;											*
 *  Date Of Creation:18.05.21;									*
 *  Date Of Approval:19.05.21;									*
 *  Approved By: approved by eden.w.;							*
 *  Description: fixed-size blocks allocation;					*/
 


#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#include "fsa.h" 

#define FSA_SIZE sizeof(fsa_t)
#define WORDSIZE sizeof(size_t)

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
	fsa_block_header_t *block_header = NULL;
	fsa_t *pool = NULL;
	size_t sum_block_offset = 0;
	size_t align_diif = 0;
	size_t num_of_blocks = 0;
	size_t modulo_res = (inner_block_size % WORDSIZE);
	size_t modulo_align = ((size_t)mem_pool % WORDSIZE);
	size_t i = 0;
	
	assert(NULL != mem_pool);
	
	align_diif = (WORDSIZE * (!!modulo_align)) - modulo_align;
	inner_block_size += (WORDSIZE * (!!modulo_res)) - modulo_res;
	
	num_of_blocks = (pool_size - align_diif - FSA_SIZE) / inner_block_size;
	
	if(0 == num_of_blocks)
	{
		return (NULL);
	}
	
	mem_pool = (void *)((char *)mem_pool + align_diif);	
	*(void **)&block_header = mem_pool;
	*(void **)&pool = mem_pool;
	
	pool->next_free = FSA_SIZE;
	sum_block_offset = FSA_SIZE;
	block_header = (fsa_block_header_t *)((char *)block_header + FSA_SIZE);
	
	for(i = 0; i < num_of_blocks - 1; ++i)
	{
		block_header->next_free = (inner_block_size) + sum_block_offset;
		sum_block_offset = block_header->next_free;
		block_header = (fsa_block_header_t *)((char *)mem_pool + sum_block_offset);
	}

	block_header->next_free = 0;
	
	return (pool);
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
	fsa->next_free = ((size_t)((char *)mem_block - (char *)fsa));
	
	return ;
}

size_t FSASuggestSize(size_t num_of_blocks, size_t block_size)
{
	size_t modulo_res = (block_size % WORDSIZE);
	block_size += (WORDSIZE * (!!modulo_res)) - modulo_res;
	
	return ((block_size * num_of_blocks) + FSA_SIZE);
	
}

size_t FSACountFree(const fsa_t *fsa)
{
	size_t count = 0;
	
	fsa_block_header_t *local_start = (fsa_block_header_t *)fsa;
	
	assert(NULL != fsa);
	
	/* for the logically correct of the types and to ensure it will 
	 * work even if the fsa manager struct will change
	 */
	if (0 == fsa->next_free)
	{
		return (count);
	}
	
	do
	{
		++count;
		/* fsa->next is from type fsa_block_header_t */
		local_start = (fsa_block_header_t *)(local_start->next_free + (char *)fsa); 
	}while (0 != local_start->next_free);
	
	return (count);
}



