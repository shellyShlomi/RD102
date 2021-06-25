
/*  Developer: Shelly Shlomi;									*
 *  Status: ;													*
 *  Date Of Creation:25.06.21;									*
 *  Date Of Approval:--.06.21;									*
 *  Approved By: 												*
 *  Description:priority queue data structure beasd on heap;	*/

#include <stdlib.h> /*	free	*/
#include <assert.h> /*	assert	*/
#include <stddef.h> /* size_t */

#include "Heap_PQ.h"
#include "heap.h"

struct pq
{
	heap_t *pq_heap; 
};



pq_t *HPQueueCreate(int (*cmp_func)(const void *data1, const void *data2))
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



void HPQueueDestroy(pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_heap);
	
	HeapDestroy(p_queue->pq_heap);
	
	p_queue->pq_heap = NULL; 
	
	free(p_queue);

	return ;

}



size_t HPQueueSize(const pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_heap);
	
	return (HeapSize(p_queue->pq_heap));
}



int HPQueueIsEmpty(const pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_heap);
	
	return (HeapIsEmpty(p_queue->pq_heap));
}



int HPQueueEnqueue(pq_t *p_queue, void *data)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_heap);
	
	return (HeapPush(p_queue->pq_heap, data));
}


void *HPQueueDequeue(pq_t *p_queue)
{
	void *peek = NULL;

	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_heap);
	assert(!HPQueueIsEmpty(p_queue));

	peek = HeapPeek(p_queue->pq_heap);
	HeapPop(p_queue->pq_heap);

	return (peek);
}

void *HPQueuePeek(const pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_heap);
	assert(!HPQueueIsEmpty(p_queue));

	return (HeapPeek(p_queue->pq_heap));
}

void HPQueueClear(pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_heap);
	
	while (!HeapIsEmpty(p_queue->pq_heap)) 
	{
		HeapPop(p_queue->pq_heap);
	}
	
	return ;
}

void *HPQueueErase(	pq_t *p_queue, 
					int (*is_match_func)(const void *data, const void *param),
					void *param)
{

	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_heap);
	assert(NULL != is_match_func);
	assert(!HPQueueIsEmpty(p_queue));

	return (HeapRemove(p_queue->pq_heap, is_match_func, param));

}
						 




