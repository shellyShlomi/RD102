
#include <stdio.h> /* printf */
#include <stdlib.h> /* exit status */

#include "heap_pq.h"



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
	pq_t *p_queue = HeapPQueueCreate(CmpFunc);
	
	if (NULL == p_queue)
	{
		printf("CreateQueueTest->HeapPQueueCreate error at line: %d\n", __LINE__);
		p_queue = NULL;
		
		return ; 
	}
	
	/* test SortedLLIsSameIter on empty list */
	if (1 != HeapPQueueIsEmpty(p_queue))
	{
		printf("CreateQueueTest->HeapPQueueIsEmpty error at line: %d\n", __LINE__);
	}
	
	/* test HeapPQueueSize on empty list  */
	if (0 != HeapPQueueSize(p_queue))
	{
		printf("CreateQueueTest->HeapPQueueSize error at line: %d\n", __LINE__);
	}
	
	HeapPQueueDestroy(p_queue);
	p_queue = NULL;
	
	return ;
}


static void EnDeQueueTest()
{	

	int arr[] = {4, 1, 6, 1, 7, 8};
	int arr_exp[] = {1, 1, 4, 6, 7, 8};
	size_t size = sizeof(arr)/ sizeof(arr[0]);
	
	size_t i = 0;
	pq_t *p_queue = HeapPQueueCreate(CmpFunc);

	if (NULL == p_queue)
	{
		printf("EnDeQueueTest->HeapPQueueCreate error at line: %d\n", __LINE__);
		p_queue = NULL;
		
		return ; 
	}


	for (i = 0; i < size; ++i)
	{
		HeapPQueueEnqueue(p_queue, (void *)(arr + i));
	}
	
	if (size != HeapPQueueSize(p_queue))
	{
		printf("EnDeQueueTest->HeapPQueueEnqueue error at line: %d\n", __LINE__);
	}
		
	
	for (i = 0; i < size; ++i)
	{
		if (arr_exp[i] != *(int *)HeapPQueueDequeue(p_queue))
		{
			printf("EnDeQueueTest->HeapPQueueEnqueue ");
			printf("error at line: %d index: %ld\n", __LINE__, i); 	
		}
	}
	
	if (1 != HeapPQueueIsEmpty(p_queue))
	{
		printf("EnDeQueueTest->HeapPQueueIsEmpty error at line: %d\n", __LINE__);
	}

	HeapPQueueDestroy(p_queue);
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
	pq_t *p_queue = HeapPQueueCreate(CmpFunc);

	if (NULL == p_queue)
	{
		printf("PeekClearEraseQueueTest->HeapPQueueCreate error at line: %d\n", __LINE__);
		p_queue = NULL;
		
		return ; 
	}


	for (i = 0; i < size; ++i)
	{
		HeapPQueueEnqueue(p_queue, (void *)(arr + i));
	}
	
	if (size != HeapPQueueSize(p_queue))
	{
		printf("PeekClearEraseQueueTest->HeapPQueueEnqueue error at line: %d\n", __LINE__);
	}
	
	HeapPQueueClear(p_queue);
	
	
	if (0 != HeapPQueueSize(p_queue))
	{
		printf("PeekClearEraseQueueTest->HeapPQueueClear error at line: %d\n", __LINE__);
	}
	
	
	for (i = 0; i < size; ++i)
	{
		HeapPQueueEnqueue(p_queue, (void *)(arr + i));
	}
	
	if (size != HeapPQueueSize(p_queue))
	{
		printf("PeekClearEraseQueueTest->HeapPQueueEnqueue error at line: %d\n", __LINE__);
	}
	
	
	for (i = 0; i < size; ++i)
	{
		if (arr_exp[i] != *(int *)HeapPQueuePeek(p_queue))
		{
			printf("PeekClearEraseQueueTest->HeapPQueuePeek ");
			printf("error at line: %d index: %ld\n", __LINE__, i); 	
		}
		
		HeapPQueueDequeue(p_queue);
	}
	
	if (1 != HeapPQueueIsEmpty(p_queue))
	{
		printf("PeekClearEraseQueueTest->HeapPQueueIsEmpty error at line: %d\n", __LINE__);
	}


	for (i = 0; i < size; ++i)
	{
		HeapPQueueEnqueue(p_queue, (void *)(arr + i));
	}
	
	if (size != HeapPQueueSize(p_queue))
	{
		printf("PeekClearEraseQueueTest->HeapPQueueEnqueue error at line: %d\n", __LINE__);
	}
	
	if (NULL != HeapPQueueErase(p_queue, IsMatchInt, (void *)&erase))
	{
		printf("PeekClearEraseQueueTest->HeapPQueueErase ");
		printf("error at line: %d index: %ld\n", __LINE__, i); 	
	}
	
	for (i = 0; i < size_erase; ++i)
	{
		if (arr_erase_cmp[i] != *(int *)HeapPQueueErase(p_queue, IsMatchInt, (void *)(arr_erase + i)))
		{
			printf("PeekClearEraseQueueTest->HeapPQueueErase ");
			printf("error at line: %d index: %ld\n", __LINE__, i); 	
		}
		
	}
	
	if (size_erase != HeapPQueueSize(p_queue))
	{
		printf("PeekClearEraseQueueTest->HeapPQueueEnqueue error at line: %d\n", __LINE__);
	}
	
	for (i = 0; i < size_erase; ++i)
	{
		if (remaining_after_erase[i] != *(int *)HeapPQueuePeek(p_queue))
		{
			printf("PeekClearEraseQueueTest->HeapPQueuePeek ");
			printf("error at line: %d index: %ld\n", __LINE__, i); 	
		}
		
		HeapPQueueDequeue(p_queue);
	}
	
	HeapPQueueDestroy(p_queue);
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


