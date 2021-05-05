
#include <stdio.h> /* printf */
#include <stdlib.h> /* exit status */

#include "priority_queue.h"



static void QueueManager();
static void CreateQueueTest();
static void EnDeQueueTest();
static void PeekClearEraseQueueTest();

static int CmpFunc(const void *data1, const void *data2);

static int IsMatchInt(const void *data, const void *param);
	


int main()
{
	QueueManager();


	return EXIT_SUCCESS;
}

static void QueueManager()
{
	CreateQueueTest();
	EnDeQueueTest();
	PeekClearEraseQueueTest();
	return;
}

static void CreateQueueTest()
{	
	pq_t *p_queue = PQueueCreate(CmpFunc);
	
	if (NULL == p_queue)
	{
		printf("CreateQueueTest->PQueueCreate error at line: %d\n", __LINE__);
		p_queue = NULL;
		
		return ; 
	}
	
	/* test SortedLLIsSameIter on empty list */
	if (1 != PQueueIsEmpty(p_queue))
	{
		printf("CreateQueueTest->PQueueIsEmpty error at line: %d\n", __LINE__);
	}
	
	/* test PQueueSize on empty list  */
	if (0 != PQueueSize(p_queue))
	{
		printf("CreateQueueTest->PQueueSize error at line: %d\n", __LINE__);
	}
	
	PQueueDestroy(p_queue);
	p_queue = NULL;
	
	return ;
}


static void EnDeQueueTest()
{	

	int arr[] = {4, 1, 6, 1, 7, 8};
	int arr_exp[] = {1, 1, 4, 6, 7, 8};
	size_t size = sizeof(arr)/ sizeof(arr[0]);
	
	size_t i = 0;
	pq_t *p_queue = PQueueCreate(CmpFunc);

	if (NULL == p_queue)
	{
		printf("EnDeQueueTest->PQueueCreate error at line: %d\n", __LINE__);
		p_queue = NULL;
		
		return ; 
	}


	for (i = 0; i < size; ++i)
	{
		PQueueEnqueue(p_queue, (void *)(arr + i));
	}
	
	if (size != PQueueSize(p_queue))
	{
		printf("EnDeQueueTest->PQueueEnqueue error at line: %d\n", __LINE__);
	}
		
	
	for (i = 0; i < size; ++i)
	{
		if (arr_exp[i] != *(int *)PQueueDequeue(p_queue))
		{
			printf("EnDeQueueTest->PQueueEnqueue ");
			printf("error at line: %d index: %ld\n", __LINE__, i); 	
		}
	}
	
	if (1 != PQueueIsEmpty(p_queue))
	{
		printf("EnDeQueueTest->PQueueIsEmpty error at line: %d\n", __LINE__);
	}

	PQueueDestroy(p_queue);
	p_queue = NULL;
	
	return ;

}

static void PeekClearEraseQueueTest()
{	

	int arr[] = {4, 1, 6, 1, 7, 8};
	int arr_exp[] = {1, 1, 4, 6, 7, 8};
	size_t size = sizeof(arr)/ sizeof(arr[0]);
	
	int arr_erase[] = {1, 4, 8};
	int arr_erase_cmp[] = {1, 4, 8};
	int remaining_after_erase[] = {1, 6, 7};
	size_t size_erase = sizeof(arr_erase)/ sizeof(arr_erase[0]);

	
	int erase = 10;	
	size_t i = 0;
	pq_t *p_queue = PQueueCreate(CmpFunc);

	if (NULL == p_queue)
	{
		printf("PeekClearEraseQueueTest->PQueueCreate error at line: %d\n", __LINE__);
		p_queue = NULL;
		
		return ; 
	}


	for (i = 0; i < size; ++i)
	{
		PQueueEnqueue(p_queue, (void *)(arr + i));
	}
	
	if (size != PQueueSize(p_queue))
	{
		printf("PeekClearEraseQueueTest->PQueueEnqueue error at line: %d\n", __LINE__);
	}
	
	PQueueClear(p_queue);
	
	
	if (0 != PQueueSize(p_queue))
	{
		printf("PeekClearEraseQueueTest->PQueueClear error at line: %d\n", __LINE__);
	}
	
	
	for (i = 0; i < size; ++i)
	{
		PQueueEnqueue(p_queue, (void *)(arr + i));
	}
	
	if (size != PQueueSize(p_queue))
	{
		printf("PeekClearEraseQueueTest->PQueueEnqueue error at line: %d\n", __LINE__);
	}
	
	
	for (i = 0; i < size; ++i)
	{
		if (arr_exp[i] != *(int *)PQueuePeek(p_queue))
		{
			printf("PeekClearEraseQueueTest->PQueuePeek ");
			printf("error at line: %d index: %ld\n", __LINE__, i); 	
		}
		
		PQueueDequeue(p_queue);
	}
	
	if (1 != PQueueIsEmpty(p_queue))
	{
		printf("PeekClearEraseQueueTest->PQueueIsEmpty error at line: %d\n", __LINE__);
	}


	for (i = 0; i < size; ++i)
	{
		PQueueEnqueue(p_queue, (void *)(arr + i));
	}
	
	if (size != PQueueSize(p_queue))
	{
		printf("PeekClearEraseQueueTest->PQueueEnqueue error at line: %d\n", __LINE__);
	}
	
	if (NULL != PQueueErase(p_queue, IsMatchInt, (void *)&erase))
	{
		printf("PeekClearEraseQueueTest->PQueueErase ");
		printf("error at line: %d index: %ld\n", __LINE__, i); 	
	}
	
	for (i = 0; i < size_erase; ++i)
	{
		if (arr_erase_cmp[i] != *(int *)PQueueErase(p_queue, IsMatchInt, (void *)(arr_erase + i)))
		{
			printf("PeekClearEraseQueueTest->PQueueErase ");
			printf("error at line: %d index: %ld\n", __LINE__, i); 	
		}
		
	}
	
	if (size_erase != PQueueSize(p_queue))
	{
		printf("PeekClearEraseQueueTest->PQueueEnqueue error at line: %d\n", __LINE__);
	}
	
	for (i = 0; i < size_erase; ++i)
	{
		if (remaining_after_erase[i] != *(int *)PQueuePeek(p_queue))
		{
			printf("PeekClearEraseQueueTest->PQueuePeek ");
			printf("error at line: %d index: %ld\n", __LINE__, i); 	
		}
		
		PQueueDequeue(p_queue);
	}
	
	PQueueDestroy(p_queue);
	p_queue = NULL;
	
	return ;

}


static int IsMatchInt(const void *data,const void *param)
{

	if (*(int *)data == *(int *)param)
	{
		return !EXIT_SUCCESS; 		
	}
	
	return !EXIT_FAILURE; 		
}


static int CmpFunc(const void *data1, const void *data2)
{
		return (*(int *)data1 - *(int *)data2); 		
}


