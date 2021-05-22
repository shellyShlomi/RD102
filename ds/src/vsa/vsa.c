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
#define LONG_CHUNK_SIZE (long int)(sizeof(vsa_c_h_t))
#define WORDSIZE sizeof(size_t)



struct vsa
{
	size_t pool_size;
};


typedef struct vsa_chunk_header
{
	long int c_size;
}vsa_c_h_t;/*vsa chunk header typedef*/


static void *GetPtrLazy(vsa_t *vsa, size_t n_bytes);
static void VSADefragment(vsa_t *vsa); 

/* helper funcs */
static size_t GetAlinedRoundUp(size_t data);
vsa_c_h_t *NextChunk(vsa_c_h_t *chunk);
vsa_c_h_t *EndOfPoolAsChunkType(vsa_t *vsa);
vsa_c_h_t *	MoveChunk(vsa_c_h_t *chunk, size_t n_bytes);
vsa_c_h_t *FirstChunk(vsa_t *vsa);
void *UserChunkStart(vsa_c_h_t *chunk);

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
	chunk_header = FirstChunk((vsa_t *)mem_pool);	
	chunk_header->c_size = (long int)(vsa_mem_pool->pool_size - CHUNK_SIZE);
	
	return (vsa_mem_pool);
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
	
	chunk_header = FirstChunk(vsa);
	vsa_end_addres = EndOfPoolAsChunkType(vsa);
	
	while (vsa_end_addres > chunk_header)
	{
		if (temp_max < chunk_header->c_size)
		{
			temp_max = chunk_header->c_size;
		}
	
		chunk_header = NextChunk(chunk_header);
	}
	
	return (temp_max); 

}

/*----------------------------internal functions------------------------------*/

static void VSADefragment(vsa_t *vsa)
{
	vsa_c_h_t *vsa_end_addres = NULL;
	vsa_c_h_t *chunk_h = NULL;/*vsa chunk header typedef*/
	
	assert(NULL != vsa);
	
	vsa_end_addres = EndOfPoolAsChunkType(vsa);

	chunk_h = FirstChunk(vsa);
	
	while (chunk_h < vsa_end_addres)
	{
		/* 
		 * will the cur chunk is free and the next one is also 
		 * free add the next chunk size to the cur one 
		 */
		while ((NextChunk(chunk_h) < vsa_end_addres) && 
				((chunk_h->c_size >= 0) && (NextChunk(chunk_h)->c_size >= 0)))
		{
			chunk_h->c_size += NextChunk(chunk_h)->c_size + LONG_CHUNK_SIZE;
		}

		chunk_h = NextChunk(chunk_h);
	}
	
	return ; 

}


static void *GetPtrLazy(vsa_t *vsa, size_t n_bytes)
{
	vsa_c_h_t *vsa_end_addres = NULL;
	vsa_c_h_t *chunk_h = NULL;/*vsa chunk header typedef*/
	long int local_n_bytes = n_bytes;
	long int cur_c_size = 0;
	
	assert(NULL != vsa);
	assert(0 < n_bytes);
	
	vsa_end_addres = EndOfPoolAsChunkType(vsa);
	
	chunk_h = FirstChunk(vsa);
	
	while ((NextChunk(chunk_h) < vsa_end_addres) && (chunk_h->c_size < local_n_bytes))
	{
		chunk_h = NextChunk(chunk_h);
		
	}
	/* if we break uot of the loop becuase chunk_h->c_size is > n_bytes
	 * need to test if we can add a new chunk header and not overflow to memory
	 * out of the bondery 
	 */
	if ((MoveChunk(chunk_h, n_bytes) < vsa_end_addres) && 
		(chunk_h->c_size + LONG_CHUNK_SIZE >= local_n_bytes))			
	{
		cur_c_size = chunk_h->c_size;
		chunk_h->c_size = (-1) * local_n_bytes;

	/* the new chunk head get the reminder from the old size - n_byts */
		NextChunk(chunk_h)->c_size = cur_c_size - LONG_CHUNK_SIZE - local_n_bytes;
		

		return (UserChunkStart(chunk_h));
	}
	/*if we break uot of the loop becuase chunk_h->c_size is == n_bytes*/
	else if (chunk_h->c_size == local_n_bytes)
	{
		chunk_h->c_size = -(chunk_h->c_size);
		
		return (UserChunkStart(chunk_h));
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

vsa_c_h_t *NextChunk(vsa_c_h_t *chunk)
{
	assert(NULL != chunk);
	return ((vsa_c_h_t *)((char *)chunk + (size_t)labs(chunk->c_size) + CHUNK_SIZE));
}

vsa_c_h_t *FirstChunk(vsa_t *vsa)
{
	assert(NULL != vsa);
	return ((vsa_c_h_t *)((char *)vsa + VSA_SIZE));
}

vsa_c_h_t *	MoveChunk(vsa_c_h_t *chunk, size_t n_bytes)
{
	assert(NULL != chunk);
	return ((vsa_c_h_t *)((char *)chunk + n_bytes + CHUNK_SIZE));
}

void *UserChunkStart(vsa_c_h_t *chunk)
{
	assert(NULL != chunk);
	return ((void *)((char *)chunk + CHUNK_SIZE));
}

vsa_c_h_t *EndOfPoolAsChunkType(vsa_t *vsa)
{
	assert(NULL != vsa);
	return ((vsa_c_h_t *)((char *)vsa + VSA_SIZE + vsa->pool_size));
}

