/*  Developer: Shelly Shlomi;									*
 *  Status:in development;										*
 *  Date Of Creation:20.05.21;									*
 *  Date Of Approval:--.05.21;									*
 *  Approved By: 												*
 *  Description: Variable-size blocks allocation;				*/

#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdlib.h> /* labs */
#include "vsa.h" 

#define VSA_SIZE sizeof(vsa_t)
#define CHUNK_SIZE sizeof(vsa_c_h_t)
#define WORDSIZE sizeof(size_t)
#define LONGINT(X) (long int)(X)
#define CHUNK_H_P(X) (vsa_c_h_t *)(X)
#define CHUNK_H_SIZE(X) (X)->c_size


struct vsa
{
	size_t pool_size;
};


typedef struct vsa_chunk_header
{
	long int c_size;
}vsa_c_h_t;


static void *GetPtrLazy(vsa_t *vsa, size_t n_bytes);
static size_t GetAlinedRoundUp(size_t data);
static void VSADefragment(vsa_t *vsa); 



/*------------------------------implementetion--------------------------------*/


vsa_t *VSAInit(void *mem_pool, size_t pool_size)
{
	vsa_c_h_t *chunk_header = NULL;
	size_t align_diff = 0;
	
	assert(NULL != mem_pool);

	/* setiing the mem_pool offset to alignment & the pool_size to aligned size */
	/*align_diff = (WORDSIZE - ((size_t)mem_pool & (WORDSIZE - 1))); /* WORDSIZE - (% WORDSIZE) */
	/* % WORDSIZE to avoid addition of WORDSIZE when the addres is aligned */
	/*align_diff &= (WORDSIZE - 1); */
	
	align_diff = GetAlinedRoundUp((size_t)mem_pool);
	
	pool_size -= align_diff; 
	pool_size -= (pool_size & (WORDSIZE - 1));

	if (pool_size < (WORDSIZE + VSA_SIZE + CHUNK_SIZE))
	{
		return (NULL); 
	}

	/* setiing the mem_pool */
	mem_pool = (void *)((char *)mem_pool + align_diff);	
	
	/* setiing the vsa struct */
	((vsa_t *)mem_pool)->pool_size = pool_size - VSA_SIZE;
	
	/* setiing the chunk_header */
	chunk_header = CHUNK_H_P((char *)mem_pool + ((vsa_t *)mem_pool)->pool_size);	
	chunk_header->c_size = ((vsa_t *)mem_pool)->pool_size - CHUNK_SIZE;
	
	return ((vsa_t *)mem_pool);
}


void *VSAAlloc(vsa_t *vsa, size_t n_bytes)
{
	void *chunk_h = NULL;

	assert(NULL != vsa);
	assert(0 < n_bytes);

	n_bytes += GetAlinedRoundUp(n_bytes);

	chunk_h = GetPtrLazy(vsa, n_bytes);
	if (NULL == chunk_h)
	{
		VSADefragment(vsa);
		return (GetPtrLazy(vsa, n_bytes));
	}
	
	return (chunk_h); 
}

void VSAFree(void *mem_chunck)
{

	assert(NULL != mem_chunck);
	assert(0 < ((CHUNK_H_P(mem_chunck) - CHUNK_SIZE)->c_size));
	
	(CHUNK_H_P(mem_chunck)- CHUNK_SIZE)->c_size *= -1;  
	
	return ; 

}

size_t VSALargestChunkAvailable(vsa_t *vsa) /* -> here we call VSADefragment */
{
	size_t sum_size = 0;
	size_t positive_c_size = 0;
	size_t temp_max = 0;
	vsa_c_h_t *chunk_header = NULL;
	
	assert(NULL != vsa);
	
	VSADefragment(vsa);
	
	chunk_header = CHUNK_H_P((char *)vsa + VSA_SIZE);
	
	while (vsa->pool_size > sum_size)
	{
		if (LONGINT(temp_max) < chunk_header->c_size)
		{
			temp_max = chunk_header->c_size;
		}
	
		positive_c_size = labs(chunk_header->c_size);
		
		sum_size += positive_c_size + CHUNK_SIZE;
		chunk_header = CHUNK_H_P((char *)chunk_header + positive_c_size + CHUNK_SIZE);
	}
	
	return (temp_max); 

}

/*----------------------------internal functions------------------------------*/

static void VSADefragment(vsa_t *vsa)
{
	size_t sum_size = 0;
	size_t positive_c_size = 0;
	long int next_chunk_size = 0;
	vsa_c_h_t *chunk_h = NULL;
	
	assert(NULL != vsa);
	
	VSADefragment(vsa);
	
	chunk_h = CHUNK_H_P((char *)vsa + VSA_SIZE);
	
	while (vsa->pool_size > sum_size)
	{
		next_chunk_size = (CHUNK_H_P((char *)chunk_h + CHUNK_SIZE + chunk_h->c_size))->c_size;
	/* 
	 * will the cur chunk is free and the next one is also 
	 * free add the next chunk size to the cur one 
	 */
		while (((chunk_h->c_size + CHUNK_SIZE + sum_size) < vsa->pool_size) &&
			  ((chunk_h->c_size >= 0) && (next_chunk_size >= 0)))
		{
			chunk_h->c_size += next_chunk_size + CHUNK_SIZE;
			next_chunk_size = (CHUNK_H_P((char *)chunk_h + CHUNK_SIZE + 
													chunk_h->c_size))->c_size;
		}
		
		positive_c_size = labs(chunk_h->c_size);
		
		sum_size += positive_c_size + CHUNK_SIZE;
		chunk_h = CHUNK_H_P((char *)chunk_h + positive_c_size + CHUNK_SIZE);
	}
	
	return ; 

}

static size_t GetAlinedRoundUp(size_t data)
{
	size_t align_diff = 0;
	
	/* setiing data to WORDSIZE alignment */
	align_diff = (WORDSIZE - (data & (WORDSIZE - 1))); /* WORDSIZE - (% WORDSIZE) */
	/* % WORDSIZE to avoid addition of WORDSIZE when the data is aligned */
	align_diff &= (WORDSIZE - 1); 
	return (align_diff); 
}

static void *GetPtrLazy(vsa_t *vsa, size_t n_bytes)
{
	vsa_c_h_t *chunk_h = NULL;
	size_t sum_size = 0;	
	size_t positive_c_size = 0;
	
	assert(NULL != vsa);
	assert(0 < n_bytes);
	
	chunk_h = (vsa_c_h_t *)((char *)vsa + VSA_SIZE);
	
	while ((chunk_h->c_size < LONGINT(n_bytes)) && (vsa->pool_size > sum_size))
	{
		positive_c_size = labs(chunk_h->c_size);
		
		sum_size += positive_c_size + CHUNK_SIZE;
		chunk_h = (vsa_c_h_t *)((char *)chunk_h + positive_c_size + CHUNK_SIZE);
	}
	
	if (chunk_h->c_size + LONGINT(CHUNK_SIZE) >= LONGINT(n_bytes))
	{
	/* the new chunk head get the reminder from the old size - n_byts*/
		((vsa_c_h_t *)((char *)chunk_h + n_bytes + CHUNK_SIZE))->c_size =
								chunk_h->c_size - n_bytes - CHUNK_SIZE;
		
		chunk_h->c_size = -(chunk_h->c_size);
		return (void *)(chunk_h + CHUNK_SIZE);
	}
	else if (chunk_h->c_size == LONGINT(n_bytes))
	{
		chunk_h->c_size = -(chunk_h->c_size);
		return (void *)(chunk_h + CHUNK_SIZE);
	}
	
	return (NULL);
	
}



