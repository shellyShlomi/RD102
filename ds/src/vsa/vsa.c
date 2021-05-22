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

struct vsa
{
	size_t pool_size;
};


typedef struct vsa_chunk_header
{
	long int c_size;
}vsa_c_h_t;/*vsa chunk header typedef*/




#define VSA_SIZE sizeof(vsa_t)
#define CHUNK_SIZE sizeof(vsa_c_h_t)
#define LONG_CHUNK_SIZE (long int)(sizeof(vsa_c_h_t))
#define WORDSIZE sizeof(size_t)

#define END_OF_CHUNK_H(X) ((vsa_c_h_t *)((char *)(X) + CHUNK_SIZE))
#define NEXT_CHUNK(X) ((vsa_c_h_t *)(((char *)(X) + \
									 (size_t)labs((X)->c_size)) + CHUNK_SIZE))
#define FIRST_CHUNK(X) (vsa_c_h_t *)((char *)(X) + VSA_SIZE)
#define MOVE_CHUNK(X, Y) (vsa_c_h_t *)(((char *)(X)) + (Y) + CHUNK_SIZE)	
#define USER_CHUNK_START(X) (void *)((char *)(X) + CHUNK_SIZE)	
#define POOLENDASCHUNKTYPE(X) ((vsa_c_h_t *)((char *)(X) + \
													VSA_SIZE + (X)->pool_size))	



static void *AllocLasy(vsa_t *vsa, size_t n_bytes);
static void VSADefragment(vsa_t *vsa); 

/* helper funcs */
static size_t GetAlinedRoundUp(size_t data);

/*------------------------------implementetion--------------------------------*/


vsa_t *VSAInit(void *mem_pool, size_t pool_size)
{
	vsa_c_h_t *chunk_header = NULL;/*vsa chunk header typedef*/
	size_t align_diff = 0;
	vsa_t *vsa_mem_pool = NULL;
	
	assert(NULL != mem_pool);
	
	align_diff = GetAlinedRoundUp((size_t)mem_pool);
	
	pool_size -= align_diff; 
	pool_size -= (pool_size & (WORDSIZE - 1));

	if (pool_size < (WORDSIZE + VSA_SIZE + CHUNK_SIZE))
	{
		return (NULL); 
	}

	/* setiing the mem_pool */
	mem_pool = (void *)((char *)mem_pool + align_diff);	
	vsa_mem_pool = (vsa_t *)mem_pool;
	
	/* setiing the vsa struct */
	vsa_mem_pool->pool_size = pool_size - VSA_SIZE;
	
	/* setiing the chunk_header */
	chunk_header = FIRST_CHUNK((vsa_t *)mem_pool);	
	chunk_header->c_size = (long int)(vsa_mem_pool->pool_size - CHUNK_SIZE);
	
	return (vsa_mem_pool);
}


void *VSAAlloc(vsa_t *vsa, size_t n_bytes)
{
	void *chunk_h = NULL;

	assert(NULL != vsa);
	assert(0 < n_bytes);

	n_bytes += GetAlinedRoundUp(n_bytes);

	chunk_h = AllocLasy(vsa, n_bytes);
	if (NULL != chunk_h)
	{
		return (chunk_h);
	}

	VSADefragment(vsa);	
	return (AllocLasy(vsa, n_bytes)); 
}

void VSAFree(void *mem_chunck)
{
	vsa_c_h_t *chunk_h = (vsa_c_h_t *)((char *)mem_chunck - CHUNK_SIZE);
	
	assert(NULL != mem_chunck);
	assert(0 > chunk_h->c_size);
	
	chunk_h->c_size *= (-1);  
	
	return ; 

}

size_t VSALargestChunkAvailable(vsa_t *vsa) /* -> here we call VSADefragment */
{
	long int temp_max = 0;
	vsa_c_h_t *chunk_header = NULL;/*vsa chunk header typedef*/
	vsa_c_h_t *vsa_end_addres = NULL;
	
	assert(NULL != vsa);
	
	VSADefragment(vsa);
	
	chunk_header = FIRST_CHUNK(vsa);
	vsa_end_addres = POOLENDASCHUNKTYPE(vsa);
	
	/* END_OF_CHUNK_H - end of chunk header */
	while (vsa_end_addres > END_OF_CHUNK_H(chunk_header))
	{
		if (temp_max < chunk_header->c_size)
		{
			temp_max = chunk_header->c_size;
		}
	
		chunk_header = NEXT_CHUNK(chunk_header);
	}
	
	return (temp_max); 

}

/*----------------------------internal functions------------------------------*/

static void VSADefragment(vsa_t *vsa)
{
	vsa_c_h_t *vsa_end_addres = NULL;
	vsa_c_h_t *chunk_h = NULL;/*vsa chunk header typedef*/
	
	assert(NULL != vsa);
	
	vsa_end_addres = POOLENDASCHUNKTYPE(vsa);

	chunk_h = FIRST_CHUNK(vsa);
	
	while (chunk_h < vsa_end_addres)
	{
		/* 
		 * will the cur chunk is free and the next one is also 
		 * free add the next chunk size to the cur one
		 * END_OF_CHUNK_H - end of chunk header 
		 */
		while ((END_OF_CHUNK_H(NEXT_CHUNK(chunk_h)) < vsa_end_addres) && 
				((chunk_h->c_size >= 0) && ((NEXT_CHUNK(chunk_h))->c_size >= 0)))
		{
			chunk_h->c_size += (NEXT_CHUNK(chunk_h))->c_size + LONG_CHUNK_SIZE;
		}

		chunk_h = NEXT_CHUNK(chunk_h);
	}
	
	return ; 

}


static void *AllocLasy(vsa_t *vsa, size_t n_bytes)
{
	vsa_c_h_t *vsa_end_addres = NULL;
	vsa_c_h_t *chunk_h = NULL;/*vsa chunk header typedef*/
	long int local_n_bytes = n_bytes;
	long int cur_c_size = 0;
	
	assert(NULL != vsa);
	assert(0 < n_bytes);
	
	vsa_end_addres = POOLENDASCHUNKTYPE(vsa);
	
	chunk_h = FIRST_CHUNK(vsa);
	
	while ((END_OF_CHUNK_H(NEXT_CHUNK(chunk_h)) < vsa_end_addres) && 
			(chunk_h->c_size < local_n_bytes))
	{
		chunk_h = NEXT_CHUNK(chunk_h);
	}
	/* if we break uot of the loop becuase chunk_h->c_size is > n_bytes
	 * need to test if we can add a new chunk header and not overflow to memory
	 * out of the bondery 
	 * END_OF_CHUNK_H - end of chunk header
	 */
	if ((END_OF_CHUNK_H(MOVE_CHUNK(chunk_h, n_bytes)) <= vsa_end_addres) && 
		(chunk_h->c_size >= local_n_bytes + LONG_CHUNK_SIZE))			
	{
		cur_c_size = chunk_h->c_size;
		chunk_h->c_size = (-1) * local_n_bytes;

	/* the new chunk head get the reminder from the old size - n_byts */
		(NEXT_CHUNK(chunk_h))->c_size = cur_c_size - LONG_CHUNK_SIZE - local_n_bytes;
		

		return (USER_CHUNK_START(chunk_h));
	}
	/*if we break uot of the loop becuase chunk_h->c_size is == n_bytes*/
	else if (chunk_h->c_size == local_n_bytes)
	{
		chunk_h->c_size = -(chunk_h->c_size);
		
		return (USER_CHUNK_START(chunk_h));
	}
	
	return (NULL);
}

/*------------------------------helper functions------------------------------*/

static size_t GetAlinedRoundUp(size_t data)
{
	size_t align_diff = 0;
	
	/* setiing data to WORDSIZE alignment */
	align_diff = (WORDSIZE - (data & (WORDSIZE - 1))); /* WORDSIZE - (% WORDSIZE) */
	/* % WORDSIZE to avoid addition of WORDSIZE when the data is aligned */
	align_diff &= (WORDSIZE - 1); 
	return (align_diff); 
}

