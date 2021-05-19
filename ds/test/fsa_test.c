
#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */

#include "fsa.h" 

static void TestSuggestSize();
static void TestInit();
static void TestAllocAndCountFreeAndFree();

int main()
{
	TestSuggestSize();
	TestAllocAndCountFreeAndFree();
	TestInit();
	
	return 0;
}

static void TestSuggestSize()
{

	size_t block_size[] = {4, 1, 6, 1, 7, 8};
	size_t num_of_blocks[] = {1, 1, 4, 6, 7, 8};
	size_t exp_size[] = {23, 23, 47, 63, 71, 79};
	size_t i = 0;
	size_t size = sizeof(exp_size)/ sizeof(exp_size[0]);
	
	for (i = 0; i < size; ++i)
	{
		if (exp_size[i] != FSASuggestSize(num_of_blocks[i], block_size[i]))
			{
				printf("TestSuggestSize->FSASuggestSize ");
				printf("error at line: %d index: %ld\n", __LINE__,i); 	
			}
	}
		
	return ;
}



static void TestInit()
{

	size_t block_size[] = {4, 16, 1, 7, 8};
	size_t pool_size[] = {100 ,100, 600, 700, 800};
	size_t exp_block_size[] = {8, 16, 8, 8, 8};
	size_t i = 0;
	size_t j = 0;
	size_t z = 1;
	size_t size = sizeof(exp_block_size)/ sizeof(exp_block_size[0]);
	fsa_t *init_res = NULL;
	 
	void *mem_pool = NULL;
	
	
	for (i = 0; i < size - 1; ++i)
	{
		mem_pool = malloc(pool_size[i]);
		init_res = FSAInit(((char *)mem_pool + i), pool_size[i], block_size[i]);
		
		if (1 == i)
		{
			
				if (*((char *)init_res) !=  (8))
				{
					printf("TestInit-> FSAInit ");
					printf("error at line: %d index: %ld, loop: %ld\n", __LINE__, j ,i);
					printf("Expected value: %d\n", 8);	
					printf("Actual result: %u\n", *((char *)init_res));	 	
				}
				
				if (*((char *)init_res + 8) !=  24)
				{
					printf("TestInit-> FSAInit ");
					printf("error at line: %d index: %ld, loop: %ld\n", __LINE__, j ,i); 
					printf("Expected value: %d\n", 24);	
					printf("Actual result: %u\n", *((char *)init_res + 8));	 	
				}

				if (*((char *)init_res + 24) !=  40)
				{
					printf("TestInit-> FSAInit ");
					printf("error at line: %d index: %ld, loop: %ld\n", __LINE__, j ,i); 
					printf("Expected value: %d\n", 40);	
					printf("Actual result: %u\n", *((char *)init_res + 24));	
				}

		}
		else
		{
			z = 1;
			for (j = 0; j < size; ++j)
			{
				if ((size_t)(*((char *)init_res + (j * exp_block_size[i]))) !=  
					(z * exp_block_size[i]))
				{
					printf("TestInit->FSAInit ");
					printf("error at line: %d index: %ld, loop: %ld\n", __LINE__,j,i);
					printf("Expected value: %lu\n", (z * exp_block_size[i]));	
					printf("Actual result: %lu\n", 
					(size_t)(*((char *)init_res + (j * exp_block_size[i]))));	
				}
				++z;
			}
		}
			free(mem_pool);	
	}
	
	mem_pool = malloc(pool_size[i]);
	
	if (mem_pool != FSAInit(mem_pool, pool_size[i], block_size[i]))
	{
		printf("TestInit->FSAInit ");
		printf("error at line: %d index: %ld\n", __LINE__,i); 	
	}
	
	free(mem_pool);	
	
	
	/* test for smaller then should retunrs NULL
	 */
	
	mem_pool = malloc(8);
	
	if (NULL != FSAInit(mem_pool, 8, block_size[0]))
	{
		printf("TestInit->FSAInit ");
		printf("error at line: %d index: %ld\n", __LINE__,i); 	
	}
	
	free(mem_pool);	
	
	return ;
}




static void TestAllocAndCountFreeAndFree()
{

	size_t block_size[] = {4, 16, 1, 7, 8};
	size_t pool_size[] = {100 ,100, 600, 700, 800};
	void *alloc_arr[] = {NULL, NULL, NULL, NULL};
	size_t exp_count_free[] = {11, 5, 74, 86, 99};
	size_t exp_alloc[] = {10, 9, 8, 7, 6};
	size_t exp_free[] = {11, 10, 9, 8, 8, 9, 10, 11};
	size_t size = sizeof(exp_count_free)/ sizeof(exp_count_free[0]);
	size_t size_for_free = sizeof(exp_free)/ sizeof(exp_free[0]);
	size_t j = 0;
	size_t i = 0;

	fsa_t *init_res = NULL;
	 
	void *mem_pool = NULL;
	
	/* test for FSACountFree
	 */
	{
		for (j = 0; j < size; ++j)
		{
			mem_pool = malloc(pool_size[j]);
			init_res = FSAInit(mem_pool, pool_size[j], block_size[j]);
			
			if (exp_count_free[j] != FSACountFree(init_res))
			{
				printf("TestAllocAndCountFreeAndFree->FSACountFree ");
				printf("error at line: %d index: %ld\n", __LINE__,j); 	
			}
			
			free(mem_pool);	
		}
	}
	
	/* test for FSAAlloc
	 */
	{
		j = 0;
		
		mem_pool = malloc(pool_size[j]);
		init_res = FSAInit(mem_pool, pool_size[j], block_size[j]);
		
		for (j = 0; j < size; ++j)
		{
			
			FSAAlloc(init_res);
		
			if (exp_alloc[j] != FSACountFree(init_res))
			{
				printf("TestAllocAndCountFreeAndFree->FSAAlloc ");
				printf("error at line: %d index: %ld\n", __LINE__,j); 	
			}
				

		}
		
		free(mem_pool);	
	}
	
	/* test for FSAFree
	 */
	{
		j = 0;
		
		mem_pool = malloc(pool_size[j]);
		init_res = FSAInit(mem_pool, pool_size[j], block_size[j]);
		
		for (j = 0; j < size_for_free / 2; ++j)
		{
			
		
			if (exp_free[j] != FSACountFree(init_res))
			{
				printf("TestAllocAndCountFreeAndFree->FSAAlloc ");
				printf("error at line: %d index: %ld\n", __LINE__,j); 	
			}
				
			alloc_arr[j] = FSAAlloc(init_res);

		}
		
		
		for (j = size_for_free / 2; j < size_for_free; ++j)
		{
			
			FSAFree(init_res, alloc_arr[i]);
		
			if (exp_free[j] != FSACountFree(init_res))
			{
				printf("TestAllocAndCountFreeAndFree->FSAFree ");
				printf("error at line: %d index: %ld\n", __LINE__,j); 	
			}
				
			++i;
		}
		
		free(mem_pool);	
	}
	
	return ;
}



