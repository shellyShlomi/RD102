
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
	
	temp_iter = SLLBegin(list);
	iter = temp_iter;
	
	while(0 < n)
	{
		iter = SLLNext(iter);
		--n;
	}
	
	while(NULL != SLLNext(iter))
	{
		iter = SLLNext(iter);
		temp_iter = SLLNext(temp_iter);
	}
	

	return (temp_iter);
}


static void Test()
{
	int arr[] = {4, 1, 6, 1, 7, 8};
	size_t size = sizeof(arr)/ sizeof(arr[0]);
	
	size_t i = 0;
	size_t n = 3;
	s_list_t *list = SLLCreate();
	s_list_iter_t iter = NULL;

	if (NULL == list)
	{
		printf("SLLCreate error at line: %d\n", __LINE__);
		list = NULL;
		
		return ; 
	}
	iter = SLLBegin(list); 
	for (i = 0; i < size; ++i)
	{
		SLLInsert(iter, (void *)(arr + i));
		iter = SLLNext(iter);
		
	}
	
	iter = SLLBegin(list); 
	
	if ((arr[size - n]) != *(int *)SLLGetData(SLLnthElement(list, n)))
		{
			printf("SLLnthElement error at line: ");
			printf("%d \n", __LINE__); 
		}

	SLLDestroy(list);
	list = NULL;	
	return ; 
}	
