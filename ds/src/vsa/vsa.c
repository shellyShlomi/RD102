#include <assert.h>
#include <stdlib.h>

#include "vsa.h" 

#define WORD_SIZE sizeof(size_t)
#define NEXT_CHUNK_SIZE ((vsa_block_header_t *)((char *)chunk_header + \
      sizeof(vsa_block_header_t) + labs(chunk_header->chunk_size)))->chunk_size
#define CHUNK_SIZE(x) ((x)->chunk_size)
#define NEXT_CHUNK (vsa_block_header_t *)((char *)chunk_header + \
                    sizeof(vsa_block_header_t) + labs(chunk_header->chunk_size))
#define FIRST_CHUNK (vsa_block_header_t *)((char *)vsa + sizeof(vsa_t)) 

/*#define VSA_SIZE sizeof(vsa_t)*/

struct vsa
{
	size_t pool_size;
};

typedef struct vsa_chunk_header
{
	long int chunk_size;
} vsa_block_header_t;

static void VSADefragment(vsa_t *vsa);
static void *VSAAllocLasy(vsa_t *vsa, size_t n_bytes);

vsa_t *VSAInit(void *mem_pool, size_t pool_size)
{
	size_t align_address = 0;
	vsa_block_header_t *chunk_header = NULL;
	
	assert(NULL != mem_pool);
	
	align_address = (WORD_SIZE - ((size_t)mem_pool & (WORD_SIZE - 1)));
	align_address &= (WORD_SIZE - 1);	
	
	pool_size -= align_address;
	
	/* pool_size mudolo WORD_SIZE */
	pool_size -= pool_size & (WORD_SIZE - 1);
	
	if (pool_size < (WORD_SIZE + sizeof(vsa_block_header_t) + sizeof(vsa_t)))
	{
		return (NULL);
	}     
	
	mem_pool = (vsa_t *)((char *)mem_pool + align_address);
    ((vsa_t *)mem_pool)->pool_size = pool_size - sizeof(vsa_t); 
	 
	chunk_header = (vsa_block_header_t *)((char *)mem_pool + sizeof(vsa_t));
	
	chunk_header->chunk_size = pool_size - sizeof(vsa_t) - sizeof(vsa_block_header_t); 		 	
		
	return (mem_pool);	
}

void VSAFree(void *mem_chunck)
{
	assert(NULL != mem_chunck);
	
	mem_chunck = (void *)((char *)mem_chunck - sizeof(vsa_block_header_t));
	
	/*assert(0 > ((vsa_block_header_t *)mem_chunck)->chunk_size);*/
	
	((vsa_block_header_t *)mem_chunck)->chunk_size *= -1;  	

	return;
}

size_t VSALargestChunkAvailable(vsa_t *vsa)
{
	size_t largest_chunk = 0;
	size_t positive_chunk = 0;
	size_t sum =  sizeof(vsa_block_header_t);
	
	vsa_block_header_t *chunk_header = NULL;
	  
	assert(NULL != vsa);
	
	VSADefragment(vsa);
	
	chunk_header = (vsa_block_header_t *)((char *)vsa + sizeof(vsa_t));  
	
	while (sum < vsa->pool_size)
	{
		if ((long int)largest_chunk < chunk_header->chunk_size)
		{
			largest_chunk = chunk_header->chunk_size;
		} 
		
		positive_chunk = labs(chunk_header->chunk_size);	  
		
		sum += positive_chunk + sizeof(vsa_block_header_t);
		
		chunk_header = (vsa_block_header_t *)
		   ((char *)chunk_header + positive_chunk + sizeof(vsa_block_header_t));	   						
	}
	
	return (largest_chunk);
}

void *VSAAlloc(vsa_t *vsa, size_t n_bytes)
{
	void *alloc_block = NULL;
	
	assert(NULL != vsa);
	
	/* same as line 28 - 29 */
	n_bytes += ((WORD_SIZE - (n_bytes & (WORD_SIZE - 1))) & (WORD_SIZE - 1));
	
	alloc_block = VSAAllocLasy(vsa, n_bytes);
	
	if (NULL != alloc_block)
	{
		return alloc_block;
	}
	
	VSADefragment(vsa);
	
	return (VSAAllocLasy(vsa, n_bytes)); 
		
}

static void *VSAAllocLasy(vsa_t *vsa, size_t n_bytes)
{
	size_t sum = 0;
	size_t positive_chunk = 0;
	
	vsa_block_header_t *chunk_header = NULL;
	
	assert(NULL != vsa);
	
	/* same as line 28 - 29 */
	/*n_bytes += ((WORD_SIZE - (n_bytes & (WORD_SIZE - 1))) & (WORD_SIZE - 1));*/
	
	chunk_header = (vsa_block_header_t *)((char *)vsa + sizeof(vsa_t)); 
	
	while ((sum < vsa->pool_size) && (chunk_header->chunk_size < (long int)n_bytes))
	{
		positive_chunk = labs(chunk_header->chunk_size);
		
		chunk_header = (vsa_block_header_t *)
		  ((char *)chunk_header + positive_chunk + sizeof(vsa_block_header_t));
		   	
		sum += positive_chunk + sizeof(vsa_block_header_t);
	}
	
	if ((sum >= vsa->pool_size))
	{
		return (NULL);
	}
	
	if ((long int)n_bytes < chunk_header->chunk_size /*+ (long int)sizeof(vsa_block_header_t)*/)
	{
		/*chunk_header = (vsa_block_header_t *)((char *)chunk_header - sizeof(vsa_block_header_t) - positive_chunk)*/;
		
		((vsa_block_header_t *)((char *)chunk_header + n_bytes + 
		  sizeof(vsa_block_header_t)))->chunk_size = chunk_header->chunk_size - (long int)n_bytes - (long int)sizeof(vsa_block_header_t);
		  
		chunk_header->chunk_size = -(long int)n_bytes; 
		
		return (void *)((char *)chunk_header + sizeof(vsa_block_header_t));          						
	}
	
	chunk_header->chunk_size *= (long int)-1;
		
	return (void *)((char *)chunk_header + sizeof(vsa_block_header_t));  					
}


static void VSADefragment(vsa_t *vsa)
{
	size_t sum = 0;
	
	vsa_block_header_t *chunk_header = NULL;
	
	assert(NULL != vsa);	

	chunk_header = FIRST_CHUNK; 
	
	while (sum < vsa->pool_size)
	{
		sum += labs(CHUNK_SIZE(chunk_header)) + sizeof(vsa_block_header_t);
		
		while ((sum < vsa->pool_size) && (0 < chunk_header->chunk_size && 0 < NEXT_CHUNK_SIZE))
		{
			CHUNK_SIZE(chunk_header) = sizeof(vsa_block_header_t) + NEXT_CHUNK_SIZE;
								
     		sum += NEXT_CHUNK_SIZE + sizeof(vsa_block_header_t);
		}
		 	
		chunk_header = (vsa_block_header_t *)((char *)chunk_header + labs(CHUNK_SIZE(chunk_header)) + sizeof(vsa_block_header_t));
	}
	
	return;
} 


