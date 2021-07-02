
/*  Developer: Shelly Shlomi;									*
 *  Status: ;													*
 *  Date Of Creation:25.06.21;									*
 *  Date Of Approval:--.06.21;									*
 *  Approved By: 												*
 *  Description:priority queue data structure beasd on heap;	*/

#include <stdlib.h> /*	free	*/
#include <assert.h> /*	assert	*/
#include <stddef.h> /* size_t */

#include "heap_pq.h"
#include "heap.h"
typedef int (*pq_heap_t)(const void *, const void *);

typedef struct data_func
{
	void *data;
	pq_heap_t func;
} data_func_t;

struct pq
{
	pq_heap_t cmp_func;
	heap_t *pq_heap;
};

int CmpFunc(const void *data1, const void *data2);
int IsMatch(const void *data, const void *param);

pq_t *HeapPQueueCreate(int (*cmp_func)(const void *data1, const void *data2))
{
	pq_t *pq = NULL;

	assert(NULL != cmp_func);

	pq = (pq_t *)malloc(sizeof(pq_t));

	if (NULL == pq)
	{
		return (NULL);
	}

	pq->cmp_func = cmp_func;

	pq->pq_heap = HeapCreate(CmpFunc);
	if (NULL == pq->pq_heap)
	{
		free(pq);
		return (NULL);
	}

	return (pq);
}

void HeapPQueueDestroy(pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_heap);

	HeapDestroy(p_queue->pq_heap);

	p_queue->pq_heap = NULL;

	free(p_queue);

	return;
}

size_t HeapPQueueSize(const pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_heap);

	return (HeapSize(p_queue->pq_heap));
}

int HeapPQueueIsEmpty(const pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_heap);

	return (HeapIsEmpty(p_queue->pq_heap));
}

int HeapPQueueEnqueue(pq_t *p_queue, void *data)
{
	data_func_t *data_func_to_push = (data_func_t *)malloc(sizeof(data_func_t));

	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_heap);

	data_func_to_push->data = data;
	data_func_to_push->func = p_queue->cmp_func;

	return (HeapPush(p_queue->pq_heap, data_func_to_push));
}

void *HeapPQueueDequeue(pq_t *p_queue)
{
	void *peek_data = NULL;
	data_func_t *data_func = NULL;

	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_heap);
	assert(!HeapPQueueIsEmpty(p_queue));

	data_func = (data_func_t *)HeapPeek(p_queue->pq_heap);
	peek_data = data_func->data;

	HeapPop(p_queue->pq_heap);

	free(data_func);

	return (peek_data);
}

void *HeapPQueuePeek(const pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_heap);
	assert(!HeapPQueueIsEmpty(p_queue));

	return (((data_func_t *)HeapPeek(p_queue->pq_heap))->data);
}

void HeapPQueueClear(pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_heap);

	while (!HeapPQueueIsEmpty(p_queue))
	{
		HeapPQueueDequeue(p_queue);
	}

	return;
}

void *HeapPQueueErase(pq_t *p_queue,
					  int (*is_match_func)(const void *data, const void *param),
					  void *param)
{
	void *data = NULL;
	data_func_t *data_func = (data_func_t *)malloc(sizeof(data_func_t));
	data_func_t *data_func_to_remove = NULL;

	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_heap);
	assert(NULL != is_match_func);
	assert(!HeapPQueueIsEmpty(p_queue));

	data_func->func = is_match_func;
	data_func->data = param;
	data_func_to_remove = HeapRemove(p_queue->pq_heap, IsMatch, data_func);

	if (NULL != data_func_to_remove)
	{
		data = data_func_to_remove->data;
		free(data_func_to_remove);
	}

	free(data_func);

	return (data);
}

int CmpFunc(const void *data1, const void *data2)
{
	return ((-1) * ((data_func_t *)data2)->func(((data_func_t *)data1)->data, ((data_func_t *)data2)->data));
}

int IsMatch(const void *data, const void *param)
{
	return ((data_func_t *)param)->func(((data_func_t *)data)->data, ((data_func_t *)param)->data);
}


