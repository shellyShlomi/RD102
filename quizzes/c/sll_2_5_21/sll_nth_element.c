
#include <stdio.h>
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "sll.h"

s_list_iter_t SLLnthElement(s_list_t *list, size_t n);
static void Test();

int main()
{
	Test();
	
	return EXIT_SUCCESS;
}



s_list_iter_t SLLnthElement(s_list_t *list, size_t n)
{
	s_list_iter_t temp_iter = NULL;
	s_list_iter_t iter = NULL;
	
	assert(NULL != list);
	assert(SLLCount(list) >= n);
	
	temp_iter = SLLBegin(list);
	iter = temp_iter;
	
	while(0 < n)
	{
		iter = SLLNext(iter);
		--n;
	}
	
	while(NULL != SLLNext(iter))
	{
		temp_iter = SLLNext(temp_iter);
		iter = SLLNext(iter);
	}
	

	return (temp_iter);
}


static void Test()
{
	int arr[] = {4, 1, 6, 1, 7, 8};
	int arr_n[] = {1, 2, 3, 4, 5, 6};
	size_t size = sizeof(arr)/ sizeof(arr[0]);
	
	size_t i = 0;
	s_list_t *list = SLLCreate();
	s_list_iter_t iter = NULL;

	if (NULL == list)
	{
		printf("SLLCreate error at line: %d\n", __LINE__);
		list = NULL;
		
		return ; 
	}
	/* test on 1 elem list */
	{	
		iter = SLLBegin(list); 
		SLLInsert(iter, (void *)(arr + i));

		if ((arr[i]) != *(int *)SLLGetData(SLLnthElement(list, arr_n[i])))
		{
			printf("SLLnthElement error at line: ");
			printf("%d \n", __LINE__); 
		}
	}
	
	
	SLLDestroy(list);
	list = SLLCreate();
	
	/* test on empty list */	
	{	
		if (*(int *)SLLGetData(SLLBegin(list)) != *(int *)SLLGetData(SLLnthElement(list, 0)))
		{
			printf("SLLnthElement error at line: ");
			printf("%d \n", __LINE__); 
		}
	}
	
	/* test all indxes in a list list */	
	{
		iter = SLLBegin(list); 
		
		for (i = 0; i < size; ++i)
		{
			SLLInsert(iter, (void *)(arr + i));
			iter = SLLNext(iter);
			
		}


		iter = SLLBegin(list); 
			
		for (i = 0; i < size; ++i)
		{
			if ((arr[size - arr_n[i]]) != *(int *)SLLGetData(SLLnthElement(list, arr_n[i])))
			{
				printf("SLLnthElement error at line: ");
				printf("%d\n", __LINE__); 
			}
			
		}
	}
	
		

	SLLDestroy(list);
	list = NULL;	
	return ; 
}	
