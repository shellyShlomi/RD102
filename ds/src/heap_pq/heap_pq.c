
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

struct pq
{
	heap_t *pq_heap; 
};



pq_t *HeapPQueueCreate(int (*cmp_func)(const void *data1, const void *data2))
{
	pq_t *pq = NULL;
	
	assert(NULL != cmp_func);	

	pq = (pq_t *)malloc(sizeof(pq_t));
	
	if (NULL == pq)
	{    
		return (NULL);
	}
	
	pq->pq_heap = HeapCreate(cmp_func);	
	
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

	return ;

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
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_heap);
	
	return (HeapPush(p_queue->pq_heap, data));
}


void *HeapPQueueDequeue(pq_t *p_queue)
{
	void *peek = NULL;

	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_heap);
	assert(!HeapPQueueIsEmpty(p_queue));

	peek = HeapPeek(p_queue->pq_heap);
	HeapPop(p_queue->pq_heap);

	return (peek);
}

void *HeapPQueuePeek(const pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_heap);
	assert(!HeapPQueueIsEmpty(p_queue));

	return (HeapPeek(p_queue->pq_heap));
}

void HeapPQueueClear(pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_heap);
	
	while (!HeapIsEmpty(p_queue->pq_heap)) 
	{
		HeapPop(p_queue->pq_heap);
	}
	
	return ;
}

void *HeapPQueueErase(	pq_t *p_queue, 
					int (*is_match_func)(const void *data, const void *param),
					void *param)
{

	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_heap);
	assert(NULL != is_match_func);
	assert(!HeapPQueueIsEmpty(p_queue));

	return (HeapRemove(p_queue->pq_heap, is_match_func, param));

}
						 




