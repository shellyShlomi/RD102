
/*  Developer: Shelly Shlomi;									*
 *  Status:Approved by nir;										*
 *  Date Of Creation:28.04.21;									*
 *  Date Of Approval:02.05.21;									*
 *  Approved By:nir; Last Reviewer tests - Anna Pest;			*
 *  Description:priority queue doubly link list data structure;			*/

#include <stdlib.h> /*	free	*/
#include <assert.h> /*	assert	*/
#include "priority_queue.h"

#define SORTED_

struct pq
{
	sorted_list_t *pq;
};



pq_t *PQueueCreate(int (*cmp_func)(const void *data1, const void *data2))
{
	pq_t *pq = NULL;
	
	assert(NULL != cmp_func);	

	pq = (pq_t *)malloc(sizeof(pq_t));
	
	if (NULL == pq)
	{    
		return (NULL);
	}
	
	pq->pq = SortedLLCreate(cmp_func);	
	
	if (NULL == pq->pq)
	{    
		free(pq);
		return (NULL);
	}
	
	return (pq);
} 	



void PQueueDestroy(pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq);
	
	SortedLLDestroy(p_queue->pq);
	
	p_queue->p_queue = NULL;
	
	free(p_queue);

	return ;

}



size_t PQueueSize(const pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq);
	
	return (SortedLLSize(p_queue->pq));
}



int PQueueIsEmpty(const pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq);
	
	return (SortedLLIsEmpty(p_queue->pq));
}



int PQueueEnqueue(pq_t *p_queue, void *data)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq);
	
	sorted_list_iter_t temp = SortedLLInsert(p_queue->pq, data);
	
	return (!SortedLLIsSameIter(temp, SortedLLEnd(p_queue->pq)));
}


void *PQueueDequeue(pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq);
	assert(!PQueueIsEmpty(p_queue->pq));
	
	return (SortedLLPopFront(p_queue->pq));
}

void *PQueuePeek(const pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq);
	assert(!PQueueIsEmpty(p_queue->pq));

	return (SortedLLGetData(SortedLLBegin(p_queue->pq)));
}

void PQueueClear(pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq);
	assert(!PQueueIsEmpty(p_queue->pq));
	
	while (!SortedLLIsEmpty(p_queue->pq)) 
	{
		PQueueDequeue(p_queue);
	}
	
	return ;
}

void *PQueueErase(pq_t *p_queue, 
						 int (*is_match_func)(const void *data, const void *param),
						 void *param)
{
	sorted_list_iter_t temp = {0};
	void *temp_data = NULL;
	
	
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq);
	assert(!PQueueIsEmpty(p_queue->pq));

	temp = SortedLLFindIf(	SortedLLBegin(p_queue->pq), 
							SortedLLEnd(p_queue->pq),
							is_match_func,
							param);
		
	if (SortedLLIsSameIter(temp, SortedLLEnd(p_queue->pq)))									
	{
		return (param);
	}
	
	temp_data = SortedLLGetData(temp);											
												
	SortedLLRemove(temp);
	
	return (temp_data);

}
						 




