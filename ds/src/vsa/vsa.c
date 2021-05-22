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
/*#define LONGINT(X) (long int)(X)
#define CHUNK_H_P(X) (vsa_c_h_t *)(X)
#define CHUNK_H_SIZE(X) (X)->c_size*/


struct vsa
{
	size_t pool_size;
};


typedef struct vsa_chunk_header
{
	long int c_size;
}vsa_c_h_t;/*vsa chunk header typedef*/


static void *GetPtrLazy(vsa_t *vsa, size_t n_bytes);
static size_t GetAlinedRoundUp(size_t data);
static void VSADefragment(vsa_t *vsa); 



/*------------------------------implementetion--------------------------------*/


vsa_t *VSAInit(void *mem_pool, size_t pool_size)
{
	vsa_c_h_t *chunk_header = NULL;/*vsa chunk header typedef*/
	size_t align_diff = 0;
	
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
	
	/* setiing the vsa struct */
	((vsa_t *)mem_pool)->pool_size = pool_size - VSA_SIZE;
	
	/* setiing the chunk_header */
	chunk_header = (vsa_c_h_t *)((char *)mem_pool + VSA_SIZE);	
	chunk_header->c_size = (long int)((vsa_t *)mem_pool)->pool_size - CHUNK_SIZE;
	
	return ((vsa_t *)mem_pool);
}


void *VSAAlloc(vsa_t *vsa, size_t n_bytes)
{
	void *chunk_h = NULL;

	assert(NULL != vsa);
	assert(0 < n_bytes);

	n_bytes += GetAlinedRoundUp(n_bytes);

	chunk_h = GetPtrLazy(vsa, n_bytes);
	if (NULL != chunk_h)
	{
		return (chunk_h);
	}

	VSADefragment(vsa);	
	return (GetPtrLazy(vsa, n_bytes)); 
}

void VSAFree(void *mem_chunck)
{

	assert(NULL != mem_chunck);
	assert(0 > (((vsa_c_h_t *)((char *)mem_chunck - CHUNK_SIZE))->c_size));
	
	((vsa_c_h_t *)((char *)mem_chunck - CHUNK_SIZE))->c_size *= -1;  
	
	return ; 

}

size_t VSALargestChunkAvailable(vsa_t *vsa) /* -> here we call VSADefragment */
{
	size_t positive_c_size = 0;
	long int temp_max = 0;
	vsa_c_h_t *chunk_header = NULL;/*vsa chunk header typedef*/
	size_t vsa_end_addres = 0;
	
	assert(NULL != vsa);
	
	VSADefragment(vsa);
	
	chunk_header = (vsa_c_h_t *)((char *)vsa + VSA_SIZE);
	vsa_end_addres = (size_t)((char *)vsa + VSA_SIZE + vsa->pool_size);
	
	while (vsa_end_addres > (size_t)(chunk_header))
	{
		if (temp_max < chunk_header->c_size)
		{
			temp_max = chunk_header->c_size;
		}
	
		positive_c_size = labs(chunk_header->c_size);
		
		chunk_header = (vsa_c_h_t *)((char *)chunk_header + positive_c_size + CHUNK_SIZE);
	}
	
	return (temp_max); 

}

/*----------------------------internal functions------------------------------*/

static void VSADefragment(vsa_t *vsa)
{
	size_t vsa_end_addres = 0;
	size_t chunk_end_addres = 0;
	size_t positive_c_size = 0;
	vsa_c_h_t *chunk_h = NULL;/*vsa chunk header typedef*/
	
	assert(NULL != vsa);
	
	vsa_end_addres = (size_t)((char *)vsa + VSA_SIZE + vsa->pool_size);

	chunk_h = (vsa_c_h_t *)((char *)vsa + VSA_SIZE);
	positive_c_size = (size_t)labs(chunk_h->c_size);
	
	while ((size_t)((char *)chunk_h + positive_c_size + CHUNK_SIZE) < vsa_end_addres)
	{

			/* 
			 * will the cur chunk is free and the next one is also 
			 * free add the next chunk size to the cur one 
			 */
			 
			while ((((size_t)((char *)chunk_h + positive_c_size + CHUNK_SIZE)) <
					 vsa_end_addres ) && 
					 
					((chunk_h->c_size >= 0) &&
					(((vsa_c_h_t *)((char *)chunk_h + CHUNK_SIZE +
							positive_c_size))->c_size >= 0)))
			{
				chunk_h->c_size += ((vsa_c_h_t *)((char *)chunk_h + 
									positive_c_size))->c_size + (long int)CHUNK_SIZE;
				positive_c_size = (size_t)labs(chunk_h->c_size);
			}

		chunk_h = (vsa_c_h_t *)((char *)chunk_h + (size_t)labs(chunk_h->c_size) + CHUNK_SIZE);
		
		if ((size_t)((char *)chunk_h + positive_c_size + CHUNK_SIZE) >= vsa_end_addres)
		{
			break;
		}
		positive_c_size = (size_t)labs(chunk_h->c_size);
		
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
	vsa_c_h_t *chunk_h = NULL;/*vsa chunk header typedef*/
	long int positive_c_size = 0;
	
	assert(NULL != vsa);
	assert(0 < n_bytes);
	
	chunk_h = (vsa_c_h_t *)((char *)vsa + VSA_SIZE);
	positive_c_size = labs(chunk_h->c_size);
	
	while (((size_t)((size_t)positive_c_size + CHUNK_SIZE + (char *)chunk_h) < 
					(size_t)((char *)vsa + VSA_SIZE + vsa->pool_size))
					 && (chunk_h->c_size < (long int)(n_bytes)))
	{
		chunk_h = (vsa_c_h_t *)((char *)chunk_h + (size_t)positive_c_size + CHUNK_SIZE);
		positive_c_size = labs(chunk_h->c_size);
		
	}
	
	/* if we break uot of the loop becuase chunk_h->c_size is > n_bytes
	 * need to test if we can add a new chunk header and not overflow to memory
	 * out of the bondery 
	 */
	if ((	(size_t)(n_bytes + CHUNK_SIZE + (char *)chunk_h) < 
			(size_t)((char *)vsa + VSA_SIZE + vsa->pool_size)			) && 
			chunk_h->c_size + (long int)CHUNK_SIZE >= (long int)(n_bytes))
	{
	/* the new chunk head get the reminder from the old size - n_byts*/
		((vsa_c_h_t *)((char *)chunk_h + n_bytes + CHUNK_SIZE))->c_size =
								chunk_h->c_size - CHUNK_SIZE - (long int)(n_bytes);
		
		chunk_h->c_size = -1 * ((long int)(n_bytes));

		return (void *)((char *)chunk_h + CHUNK_SIZE);
	}
	/*if we break uot of the loop becuase chunk_h->c_size is == n_bytes*/
	else if (/*((size_t)(positive_c_size + CHUNK_SIZE + (char *)chunk_h) <= 
			(size_t)((char *)vsa + VSA_SIZE + vsa->pool_size)			) &&*/
			(chunk_h->c_size == (long int)(n_bytes)))
	{
		chunk_h->c_size = -(chunk_h->c_size);
		return (void *)((char *)chunk_h + (long int)CHUNK_SIZE);
	}
	
	return (NULL);
}

