
/*  Developer: Shelly Shlomi;									*
 *  Status:Approved ;											*
 *  Date Of Creation:04.05.21;									*
 *  Date Of Approval:00.05.21;									*
 *  Approved By: nir											*
 *  Description:priority queue data structure;					*/

#include <stdlib.h> /*	free	*/
#include <assert.h> /*	assert	*/
#include <stddef.h> /* size_t */

#include "priority_queue.h"
#include "sorted_ll.h"

struct pq
{
	sorted_list_t *pq_list; 
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
	
	pq->pq_list = SortedLLCreate(cmp_func);	
	
	if (NULL == pq->pq_list)
	{    
		free(pq);
		return (NULL);
	}
	
	return (pq);
} 	



void PQueueDestroy(pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_list);
	
	SortedLLDestroy(p_queue->pq_list);
	
	p_queue->pq_list = NULL; 
	
	free(p_queue);

	return ;

}



size_t PQueueSize(const pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_list);
	
	return (SortedLLSize(p_queue->pq_list));
}



int PQueueIsEmpty(const pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_list);
	
	return (SortedLLIsEmpty(p_queue->pq_list));
}



int PQueueEnqueue(pq_t *p_queue, void *data)
{
	sorted_list_iter_t temp = {NULL};
	
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_list);
	
	temp = SortedLLInsert(p_queue->pq_list, data);
	
	return (SortedLLIsSameIter(temp, SortedLLEnd(p_queue->pq_list)));
}


void *PQueueDequeue(pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_list);
	assert(!PQueueIsEmpty(p_queue));
	
	return (SortedLLPopFront(p_queue->pq_list));
}

void *PQueuePeek(const pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_list);
	assert(!PQueueIsEmpty(p_queue));

	return (SortedLLGetData(SortedLLBegin(p_queue->pq_list)));
}

void PQueueClear(pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_list);
	
	while (!SortedLLIsEmpty(p_queue->pq_list)) 
	{
		PQueueDequeue(p_queue);
	}
	
	return ;
}

void *PQueueErase(	pq_t *p_queue, 
					int (*is_match_func)(const void *data, const void *param),
					void *param)
{
	sorted_list_iter_t temp = {0};
	void *temp_data = NULL;
	
	
	assert(NULL != p_queue);
	assert(NULL != p_queue->pq_list);
	assert(NULL != is_match_func);
	assert(!PQueueIsEmpty(p_queue));

	temp = SortedLLFindIf(	SortedLLBegin(p_queue->pq_list), 
							SortedLLEnd(p_queue->pq_list),
							is_match_func,
							param);
		
	if (SortedLLIsSameIter(temp, SortedLLEnd(p_queue->pq_list)))									
	{
		return (NULL);
	}
	
	temp_data = SortedLLGetData(temp);											
												
	SortedLLRemove(temp);
	
	return (temp_data);

}
						 




