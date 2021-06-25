
#include <stdio.h>	/* printf */
#include <stdlib.h> /* exit status */

#include "Heap_PQ.h"

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
	pq_t *p_queue = HPQueueCreate(CmpFunc);

	if (NULL == p_queue)
	{
		printf("CreateQueueTest->HPQueueCreate error at line: %d\n", __LINE__);
		p_queue = NULL;

		return;
	}

	/* test SortedLLIsSameIter on empty list */
	if (1 != HPQueueIsEmpty(p_queue))
	{
		printf("CreateQueueTest->HPQueueIsEmpty error at line: %d\n", __LINE__);
	}

	/* test HPQueueSize on empty list  */
	if (0 != HPQueueSize(p_queue))
	{
		printf("CreateQueueTest->HPQueueSize error at line: %d\n", __LINE__);
	}

	HPQueueDestroy(p_queue);
	p_queue = NULL;

	return;
}

static void EnDeQueueTest()
{

	int arr[] = {4, 1, 6, 1, 7, 8};
	int arr_exp[] = {1, 1, 4, 6, 7, 8};
	size_t size = sizeof(arr) / sizeof(arr[0]);

	size_t i = 0;
	pq_t *p_queue = HPQueueCreate(CmpFunc);

	int *remove = NULL;

	if (NULL == p_queue)
	{
		printf("EnDeQueueTest->HPQueueCreate error at line: %d\n", __LINE__);
		p_queue = NULL;

		return;
	}

	for (i = 0; i < size; ++i)
	{
		HPQueueEnqueue(p_queue, (void *)(arr + i));
	}

	if (size != HPQueueSize(p_queue))
	{
		printf("EnDeQueueTest->HPQueueEnqueue error at line: %d\n", __LINE__);
	}

	for (i = size - 1; 0 <= (long)i; --i)
	{
		remove = (int *)HPQueueDequeue(p_queue);

		if (arr_exp[i] != *remove)
		{
			printf("EnDeQueueTest->HPQueueEnqueue ");
			printf("error at line: %d index: %ld\n", __LINE__, i);
			printf("elem: %d\n", *remove);
			printf("exp elem: %d\n", arr_exp[i]);
		}
	}

	if (!HPQueueIsEmpty(p_queue))
	{
		printf("EnDeQueueTest->HPQueueIsEmpty error at line: %d\n", __LINE__);
	}

	HPQueueDestroy(p_queue);
	p_queue = NULL;

	return;
}

static void PeekClearEraseQueueTest()
{

	int arr[] = {4, 1, 6, 1, 7, 8};
	int arr_exp[] = {1, 1, 4, 6, 7, 8};
	size_t size = sizeof(arr) / sizeof(arr[0]);

	int arr_erase[] = {1, 4, 8};
	int arr_erase_cmp[] = {1, 4, 8};
	int remaining_after_erase[] = {1, 6, 7};
	size_t size_erase = sizeof(arr_erase) / sizeof(arr_erase[0]);

	int erase = 10;
	size_t i = 0;
	pq_t *p_queue = HPQueueCreate(CmpFunc);

	if (NULL == p_queue)
	{
		printf("PeekClearEraseQueueTest->HPQueueCreate error at line: %d\n", __LINE__);
		p_queue = NULL;

		return;
	}

	for (i = 0; i < size; ++i)
	{
		HPQueueEnqueue(p_queue, (void *)(arr + i));
	}

	if (size != HPQueueSize(p_queue))
	{
		printf("PeekClearEraseQueueTest->HPQueueEnqueue error at line: %d\n", __LINE__);
	}

	HPQueueClear(p_queue);

	if (0 != HPQueueSize(p_queue))
	{
		printf("PeekClearEraseQueueTest->HPQueueClear error at line: %d\n", __LINE__);
	}

	for (i = 0; i < size; ++i)
	{
		HPQueueEnqueue(p_queue, (void *)(arr + i));
	}

	if (size != HPQueueSize(p_queue))
	{
		printf("PeekClearEraseQueueTest->HPQueueEnqueue error at line: %d\n", __LINE__);
	}

	for (i = size - 1; 0 <= (long)i; --i)
	{
		if (arr_exp[i] != *(int *)HPQueuePeek(p_queue))
		{
			printf("PeekClearEraseQueueTest->HPQueuePeek ");
			printf("error at line: %d index: %ld\n", __LINE__, i);
		}

		HPQueueDequeue(p_queue);
	}

	if (1 != HPQueueIsEmpty(p_queue))
	{
		printf("PeekClearEraseQueueTest->HPQueueIsEmpty error at line: %d\n", __LINE__);
	}

	for (i = 0; i < size; ++i)
	{
		HPQueueEnqueue(p_queue, (void *)(arr + i));
	}

	if (size != HPQueueSize(p_queue))
	{
		printf("PeekClearEraseQueueTest->HPQueueEnqueue error at line: %d\n", __LINE__);
	}

	if (NULL != HPQueueErase(p_queue, IsMatchInt, (void *)&erase))
	{
		printf("PeekClearEraseQueueTest->HPQueueErase ");
		printf("error at line: %d index: %ld\n", __LINE__, i);
	}

	for (i = 0; i < size_erase; ++i)
	{
		if (arr_erase_cmp[i] != *(int *)HPQueueErase(p_queue, IsMatchInt, (void *)(arr_erase + i)))
		{
			printf("PeekClearEraseQueueTest->HPQueueErase ");
			printf("error at line: %d index: %ld\n", __LINE__, i);
		}
	}

	if (size_erase != HPQueueSize(p_queue))
	{
		printf("PeekClearEraseQueueTest->HPQueueEnqueue error at line: %d\n", __LINE__);
	}

	for (i = size_erase - 1; 0 <= (long)i; --i)
	{
		if (remaining_after_erase[i] != *(int *)HPQueuePeek(p_queue))
		{
			printf("PeekClearEraseQueueTest->HPQueuePeek ");
			printf("error at line: %d index: %ld\n", __LINE__, i);
		}

		HPQueueDequeue(p_queue);
	}

	HPQueueDestroy(p_queue);
	p_queue = NULL;

	return;
}

static int IsMatchInt(const void *data, const void *param)
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
