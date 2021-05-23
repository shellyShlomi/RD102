#include <stdlib.h> /* malloc */
#include <stdio.h> /* printf */

#include "vsa.h"

#define HUGH_BLOCK 10000
#define HUGH_BLOCK 10000

#define VSA_SIZE 8
#define CHUNK_SIZE 8
#define WORDSIZE sizeof(size_t)


static void VSATests();
static void TestInit();
static void TestAlloc();
static void TestAllocAndFree();
static void TestAllocAndFreeWithDefragment();
static void TestDefragment();



int main()
{
	VSATests();
	
	return (0);
}

static void VSATests()
{
	
	TestInit();
	TestAlloc();
	TestAllocAndFree();
	TestAllocAndFreeWithDefragment();
	TestDefragment();
	
	return;
}


static void TestInit()
{

	size_t pool_size[] = {100 , 4000, 800};
	size_t exp_pool_size_unaligned[] = {80, 3984, 784};
	long int exp_first_chunk_size_unalign[] = {72, 3976, 776};
	size_t i = 0;
	size_t j = 0;
	size_t size = sizeof(pool_size)/ sizeof(pool_size[0]);
	vsa_t *init_res = NULL;
	void *mem_pool = NULL;
 	size_t pool_size_aligned = 3992;
 	long int first_chunk_size_aligned = 3984;
	
	/*not alingd*/
	for (i = 1; j < size; ++i, ++j)
	{
		mem_pool = (void *)malloc(pool_size[j]);
		if(NULL == mem_pool)
		{
			return ;
		}
		
		init_res = VSAInit(((char *)mem_pool + i * 3), pool_size[j]);
		if(NULL == init_res)
		{
			return ;
		}
		/* test the addreses of the vsa struct */
		if (0 == j)
		{
			if ((size_t)((char *)mem_pool + VSA_SIZE) != (size_t)init_res)
			{
				printf("TestInit->VSAInit ");
				printf("error at line: %d index: %ld\n", __LINE__,i); 
				printf("expected addres : %lu\n", (size_t)((char *)mem_pool + i * 3));
				printf("Actual result : %lu\n", (size_t)init_res); 		
			}
		}
		else if ((size_t)((char *)mem_pool + (j * VSA_SIZE)) != (size_t)init_res)
		{
			printf("TestInit->VSAInit ");
			printf("error at line: %d index: %ld\n", __LINE__,i); 
			printf("expected addres : %lu\n", (size_t)((char *)mem_pool + i * 3));
			printf("Actual result : %lu\n", (size_t)init_res); 		
		}
		/* test the pool size of the vsa struct */
		if (exp_pool_size_unaligned[j] != *(size_t *)init_res)
		{
			printf("TestInit->VSAInit \n");
			printf("error at line: %d \n", __LINE__);
			printf("expected pool size : %lu\n", pool_size_aligned);
			printf("Actual result : %lu\n", *(size_t *)init_res); 	
		}
		/* test the first chunk size of the chunk struct */
		if (exp_first_chunk_size_unalign[j] != *(long int *)((char *)init_res + VSA_SIZE))
		{
			printf("TestInit->VSAInit \n");
			printf("error at line: %d \n", __LINE__);
			printf("expected chunk size : %lu\n", first_chunk_size_aligned);
			printf("Actual result : %lu\n",*(long int *)((char *)init_res + VSA_SIZE)); 	
		}
		
		free(mem_pool);	
	}
	
	mem_pool = (void *)malloc(pool_size[1]);
	if(NULL == mem_pool)
	{
		return ;
	}
	
	init_res = VSAInit(mem_pool, pool_size[1]);
	if(NULL == init_res)
	{
		return ;
	}
		
	if (mem_pool != init_res)
	{
		printf("TestInit->VSAInit ");
		printf("error at line: %d index: %ld\n", __LINE__,i); 	
	}
	
	if (pool_size_aligned != *(size_t *)init_res)
	{
		printf("TestInit->VSAInit Pool size don't mach \n");
		printf("error at line: %d \n", __LINE__);
		printf("expected pool size : %lu\n", pool_size_aligned);
		printf("Actual result : %lu\n", *(size_t *)init_res); 	
	}
	
	if (first_chunk_size_aligned != *(long int *)((char *)init_res + VSA_SIZE))
	{
		printf("TestInit->VSAInit Pool size don't mach \n");
		printf("error at line: %d \n", __LINE__);
		printf("expected chunk size: %lu\n", first_chunk_size_aligned);
		printf("Actual result : %lu\n", *(long int *)((char *)init_res + VSA_SIZE)); 	
	}
	
	
	free(mem_pool);	
	
	
	/* test for pool size which is to small for vsa to manage -  should retunrs NULL
	 */
	mem_pool = (void *)malloc(8);
	if(NULL == mem_pool)
	{
		return ;
	}
	
	if (NULL != VSAInit(mem_pool, 8))
	{
		printf("TestInit->VSAInit Pool size small for vsa to manage");
		printf("error at line: %d index: %ld\n", __LINE__,i);
		printf("expected result : NULL\n");
		printf("Actual result : %p \n", (void *)VSAInit(mem_pool, 8)); 
	}
	
	free(mem_pool);	
	
	return ;
}




static void TestAlloc()
{
	vsa_t *init_res = NULL;
	void *res_first_chunk = NULL;
	void *mem_pool = NULL;
	size_t pool_size = 100;
 	size_t pool_size_aligned = 88;
 	long int first_chunk_size_aligned = 80;
	long int exp_first_chunk_size = -56;
	
	mem_pool = (void *)malloc(pool_size);
	if(NULL == mem_pool)
	{
		return ;
	}
	
	init_res = VSAInit(mem_pool, pool_size);
	if(NULL == init_res)
	{
		return ;
	}
		
	if (mem_pool != init_res)
	{
		printf("TestAlloc->VSAInit ");
		printf("error at line: %d \n", __LINE__); 	
	}
	
	if (pool_size_aligned != *(size_t *)init_res)
	{
		printf("TestAlloc->VSAInit  \n");
		printf("error at line: %d \n", __LINE__);
		printf("expected pool size : %lu\n", pool_size_aligned);
		printf("Actual result : %lu\n", *(size_t *)init_res); 	
	}
	
	if (first_chunk_size_aligned != *(long int *)((char *)init_res + VSA_SIZE))
	{
		printf("TestAlloc->VSAInit befor alloc\n");
		printf("error at line: %d \n", __LINE__);
		printf("expected chunk size : %lu\n", first_chunk_size_aligned);
		printf("Actual result : %lu\n", *(long int *)((char *)init_res + VSA_SIZE)); 	
	}
	
	res_first_chunk = VSAAlloc(init_res, 52);
	
	if ((long int)exp_first_chunk_size != *(long int *)((char *)res_first_chunk - CHUNK_SIZE))
	{
		printf("TestAlloc->VSAAlloc After alloc \n");
		printf("error at line: %d \n", __LINE__);
		printf("expected chunk size : %ld\n", exp_first_chunk_size);
		printf("Actual result : %ld\n", *(long int *)((char *)res_first_chunk - CHUNK_SIZE)); 	
	}
	
	if (16 != *(long int *)((char *)res_first_chunk + (-1 * exp_first_chunk_size)))
	{
		printf("TestAlloc->VSAAlloc After alloc \n");
		printf("error at line: %d \n", __LINE__);
		printf("expected chunk size : %d\n", 16);
		printf("Actual result : %ld\n", *(long int *)((char *)res_first_chunk + 56)); 	
	}
	
	
	free(mem_pool);	
	
	return ;
}




static void TestAllocAndFree()
{
	vsa_t *init_res = NULL;
	void *mem_pool = NULL;
	
	size_t alloc_c[] = {80 , 4000, 800, 104, 104, 5000};
	long int exp_alloc_c[] = {-80, -4000, -800, -104, -104, 5000};
	long int exp_next_free_alloc[] = {
										(HUGH_BLOCK - 88 - VSA_SIZE - CHUNK_SIZE), 
										(HUGH_BLOCK - 4096 - VSA_SIZE - CHUNK_SIZE), 
										(HUGH_BLOCK - 4904 - VSA_SIZE - CHUNK_SIZE),
										(HUGH_BLOCK - 5016 - VSA_SIZE - CHUNK_SIZE),
										(HUGH_BLOCK - 5128 - VSA_SIZE - CHUNK_SIZE),
									};
	void *ptr_alloc_c[] = {NULL, NULL, NULL, NULL, NULL, NULL};
	size_t i = 0;
	size_t size = sizeof(alloc_c)/ sizeof(alloc_c[0]);
	
	
		mem_pool = (void *)malloc(HUGH_BLOCK);
		if(NULL == mem_pool)
		{
			return ;
		}
		
		init_res = VSAInit(mem_pool, HUGH_BLOCK);
		if(NULL == init_res)
		{
			return ;
		}
			
		if (mem_pool != init_res)
		{
			printf("TestAllocAndFree->VSAInit ");
			printf("error at line: %d index: %ld\n", __LINE__,i);
		}
		
		if (HUGH_BLOCK - VSA_SIZE!= *(size_t *)init_res)
		{
			printf("TestAllocAndFree->VSAInit  \n");
			printf("error at line: %d index: %ld\n", __LINE__,i);
			printf("expected pool size : %u\n", HUGH_BLOCK- VSA_SIZE);
			printf("Actual result : %lu\n", *(size_t *)init_res); 	
		}
		
		if (HUGH_BLOCK - CHUNK_SIZE - VSA_SIZE != 
			*(long int *)((char *)init_res + VSA_SIZE))
		{
			printf("TestAllocAndFree->VSAInit befor alloc\n");
			printf("error at line: %d index: %ld\n", __LINE__,i);
			printf("expected chunk size : %d\n", HUGH_BLOCK - CHUNK_SIZE- VSA_SIZE);
			printf("Actual result : %ld\n", *(long int *)((char *)init_res + VSA_SIZE)); 	
		}
		
	for (i = 0; i < size - 1; ++i)
	{
		
		
		ptr_alloc_c[i] = VSAAlloc(init_res, alloc_c[i]);
		
		if ((long int)exp_alloc_c[i] != *(long int *)((char *)ptr_alloc_c[i] - CHUNK_SIZE))
		{
			printf("TestAllocAndFree->VSAAlloc After alloc \n");
			printf("error at line: %d index: %ld\n", __LINE__,i);
			printf("expected chunk size : %ld\n", exp_alloc_c[i]);
			printf("Actual result : %ld\n", *(long int *)((char *)ptr_alloc_c[i] - CHUNK_SIZE)); 	
		}
		
		if (exp_next_free_alloc[i] != 
			*(long int *)((char *)ptr_alloc_c[i] + alloc_c[i]))
		{
			printf("TestAllocAndFree->VSAAlloc next free size \n");
			printf("error at line: %d index: %ld\n", __LINE__,i);
			printf("expected chunk size : %ld\n", (long int)exp_next_free_alloc[i]);
			printf("Actual result : %ld\n", 
						*(long int *)((char *)ptr_alloc_c[i] + alloc_c[i])); 	
		}
		
		/*	printf("\n");
			printf("alloc size : %lu\n", alloc_c[i]);
			printf("alloced chunk addreses : %lu\n", (size_t)ptr_alloc_c[i]);
			printf("next chunk addreses not alloced : %lu\n", 
			(size_t)((char *)ptr_alloc_c[i] + alloc_c[i])); 	
			printf("the diff size is: %lu\n",  (size_t)((char *)ptr_alloc_c[i] + alloc_c[i]) - (size_t)ptr_alloc_c[i]);
			printf("\n");
		*/

	}
	for (i = 0; i < size - 1; ++i)
	{
		
		
		VSAFree(ptr_alloc_c[i]);
		
		if ((long int)alloc_c[i] != *(long int *)((char *)ptr_alloc_c[i] - CHUNK_SIZE))
		{
			printf("TestAllocAndFree->VSAAlloc After alloc \n");
			printf("error at line: %d index: %ld\n", __LINE__,i);
			printf("expected chunk size : %ld\n", (long int)alloc_c[i]);
			printf("Actual result : %ld\n", *(long int *)((char *)ptr_alloc_c[i] - CHUNK_SIZE)); 	
		}
	}
	
	free(mem_pool);	
	
	return ;
}





static void TestAllocAndFreeWithDefragment()
{
	vsa_t *init_res = NULL;
	vsa_t *vsa_ptr = NULL;
	void *mem_pool = NULL;
	void *ptr_alloc_c[] = {NULL, NULL, NULL, NULL, NULL, NULL};
	size_t size = sizeof(ptr_alloc_c)/ sizeof(ptr_alloc_c[0]);
	size_t i = 0;


	mem_pool = (void *)malloc(120);/*112 pool size*/
	if(NULL == mem_pool)
	{
		return ;
	}
	
	init_res = VSAInit(mem_pool, 120);
	if(NULL == init_res)
	{
		return ;
	}
	
	if (120 - VSA_SIZE != *(size_t *)init_res)
	{
		printf("TestAllocAndFreeWithDefragment->VSAInit  \n");
		printf("error at line: %d \n", __LINE__);
		printf("expected pool size : %u\n",120 - VSA_SIZE);
		printf("Actual result : %lu\n", *(size_t *)init_res); 	
	}
	
	ptr_alloc_c[0] = VSAAlloc(init_res, 104);
	if(NULL == ptr_alloc_c[0])
	{
		printf("VSAAlloc failed line: %d \n", __LINE__ );
		return ;
	}
	vsa_ptr = init_res;
	init_res = (vsa_t *)((char *)init_res + VSA_SIZE + CHUNK_SIZE);
	for (i = 0; i < 104; ++i)
	{
		*((char *)init_res + i) = 8;
	}

	VSAFree(ptr_alloc_c[0]);
	ptr_alloc_c[0] = VSAAlloc(vsa_ptr, 16);
	if(NULL == ptr_alloc_c[0])
	{
		printf("TestAllocAndFreeWithDefragment->VSAAlloc failed line: %d \n", __LINE__ );
		return ;
	}
	ptr_alloc_c[1] = VSAAlloc(vsa_ptr, 16);
	if(NULL == ptr_alloc_c[1])
	{
		printf("TestAllocAndFreeWithDefragment->VSAAlloc failed line: %d \n", __LINE__ );
		return ;
	}
	
	ptr_alloc_c[2] = VSAAlloc(vsa_ptr, 16);
	if(NULL == ptr_alloc_c[1])
	{
		printf("TestAllocAndFreeWithDefragment->VSAAlloc failed line: %d \n", __LINE__ );
		return ;
	}
	ptr_alloc_c[3] = VSAAlloc(vsa_ptr, 24);
	if(NULL == ptr_alloc_c[3])
	{
		printf("TestAllocAndFreeWithDefragment->VSAAlloc failed line: %d \n", __LINE__ );
		return ;
	}

	/* there is no room to make this allocation expect NULL */
	ptr_alloc_c[4] = VSAAlloc(vsa_ptr, 32);
	if(NULL != ptr_alloc_c[4])
	{
		printf("TestAllocAndFreeWithDefragment->VSAAlloc failed line: %d \n", __LINE__ );

	}
	/* there is no room to make anoder allocation expext - 0 */
	i = VSALargestChunkAvailable(vsa_ptr);
	printf("%ld \n", i);
	
	for (i = 1; i < size - 3; ++i)
	{
		VSAFree(ptr_alloc_c[i]);
		
		if (0 > *(long int *)((char *)ptr_alloc_c[i] - CHUNK_SIZE))
		{
			printf("TestAllocAndFreeWithDefragment->VSAAlloc \n");
			printf("error at line: %d index: %ld\n", __LINE__,i);
			printf("Actual result : %ld\n", *(long int *)((char *)ptr_alloc_c[i] - CHUNK_SIZE)); 	
		}
	}
	
	printf("%ld size after\n", *(long int *)((char *)ptr_alloc_c[1] - CHUNK_SIZE));

	/*i = VSALargestChunkAvailable(vsa_ptr);*/
	/*printf("%ld \n", i);
	printf("%ld \n", *(long int *)((char *)ptr_alloc_c[1] - CHUNK_SIZE));*/
	ptr_alloc_c[1] = VSAAlloc(vsa_ptr, 32);
	if(NULL == ptr_alloc_c[1])
	{
		printf("TestAllocAndFreeWithDefragment->VSAAlloc failed line: %d \n", __LINE__ );

	}
	
	ptr_alloc_c[2] = VSAAlloc(vsa_ptr, 8);
	if(NULL == ptr_alloc_c[1])
	{
		printf("TestAllocAndFreeWithDefragment->VSAAlloc failed line: %d \n", __LINE__ );

	}
	/*i = VSALargestChunkAvailable(vsa_ptr);
	printf("%ld \n", i);*/
	ptr_alloc_c[3] = VSAAlloc(vsa_ptr, 8);
	if(NULL == ptr_alloc_c[3])
	{
		printf("TestAllocAndFreeWithDefragment->VSAAlloc failed line: %d \n", __LINE__ );
	}
	
	free(mem_pool);			
	return ;
}

static void TestDefragment()
{
	vsa_t *init_res = NULL;
	void *mem_pool = NULL;
	size_t pool_size = 120;
	size_t alloc_c[] = {16, 16, 16, 8, 8};
	void *ptr_alloc_c[] = {NULL, NULL, NULL, NULL, NULL};
	size_t i = 0;
	size_t size = sizeof(alloc_c)/ sizeof(alloc_c[0]);
	
	
		mem_pool = (void *)malloc(pool_size);
		if(NULL == mem_pool)
		{
			return ;
		}
		
		init_res = VSAInit(mem_pool, pool_size);
		if(NULL == init_res)
		{
			return ;
		}
			
		if (mem_pool != init_res)
		{
			printf("TestDefragment->VSAInit ");
			printf("error at line: %d index: %ld\n", __LINE__,i);
		}
		
		if (pool_size - VSA_SIZE!= *(size_t *)init_res)
		{
			printf("TestDefragment->VSAInit  \n");
			printf("error at line: %d index: %ld\n", __LINE__,i);
			printf("expected pool size : %lu\n", pool_size- VSA_SIZE);
			printf("Actual result : %lu\n", *(size_t *)init_res); 	
		}
		
		if ((long int)(pool_size - CHUNK_SIZE - VSA_SIZE) != 
			*(long int *)((char *)init_res + (long int)VSA_SIZE))
		{
			printf("TestDefragment->VSAInit befor alloc\n");
			printf("error at line: %d index: %ld\n", __LINE__,i);
			printf("expected chunk size : %ld\n", pool_size - CHUNK_SIZE- VSA_SIZE);
			printf("Actual result : %ld\n", *(long int *)((char *)init_res + VSA_SIZE)); 	
		}
		
	for (i = 0; i < size; ++i)
	{
		
		ptr_alloc_c[i] = VSAAlloc(init_res, alloc_c[i]);
		
		if ((long int)-(alloc_c[i]) != *(long int *)((char *)ptr_alloc_c[i] - CHUNK_SIZE))
		{
			printf("TestDefragment->VSAAlloc After alloc \n");
			printf("error at line: %d index: %ld\n", __LINE__,i);
			printf("expected chunk size : %ld\n", -(alloc_c[i]));
			printf("Actual result : %ld\n", *(long int *)((char *)ptr_alloc_c[i] - CHUNK_SIZE)); 	
		}
		
	}
	/*a header chunk 8 block is sepos to be at the end*/
	for (i = 0; i < size; ++i)
	{
		
		
		VSAFree(ptr_alloc_c[i]);
		
		if ((long int)alloc_c[i] != *(long int *)((char *)ptr_alloc_c[i] - CHUNK_SIZE))
		{
			printf("TestDefragment->VSAAlloc After alloc \n");
			printf("error at line: %d index: %ld\n", __LINE__,i);
			printf("expected chunk size : %ld\n", (long int)alloc_c[i]);
			printf("Actual result : %ld\n", *(long int *)((char *)ptr_alloc_c[i] - CHUNK_SIZE)); 	
		}
	}
	
	
	if (pool_size - CHUNK_SIZE - VSA_SIZE  != VSALargestChunkAvailable(init_res))
	{
		printf("TestDefragment->VSALargestChunkAvailable \n");
		printf("error at line: %d index\n", __LINE__);
		printf("expected LargestChunkAvailable : %ld\n", pool_size - CHUNK_SIZE - VSA_SIZE);
		printf("Actual result : %ld\n", VSALargestChunkAvailable(init_res)); 	
	}
	
	
	
	free(mem_pool);	
	
	return ;
}

