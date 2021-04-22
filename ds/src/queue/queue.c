
/*  Developer: Shelly Shlomi;									*
 *  Status:Approved ;										*
 *  Date Of Creation:21.04.21;									*
 *  Date Of Approval:22.04.21;									*
 *  Approved By: final approved by maor;												*
 *  Description: queue implementation as a client of 			*
 *				 singly link list data structure;				*/

#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "sll.h"
#include "queue.h"

#define FAILE 1

struct queue
{
	s_list_t *queue_list;
};                    			

/* nir approved */
queue_t *QueueCreate(void)
{
	queue_t *queue = (queue_t *)malloc(sizeof(queue_t));

	if (NULL == queue)
	{    
		return NULL;
	}
	
	queue->queue_list = SLLCreate();
	
	if (NULL == queue->queue_list)
	{    
		queue->queue_list = NULL;
		free(queue);
		
		return NULL;
	}
	
	return queue;
}

/* nir approved */
void QueueDestroy(queue_t *queue)
{
	assert(NULL != queue);
	assert(NULL != queue->queue_list);	
		
	SLLDestroy(queue->queue_list);
	
	queue->queue_list = NULL;
	
	free(queue);
	
	return ;
}				              	

/* eden boy approved */
size_t QueueSize(const queue_t *queue)
{
	assert(NULL != queue);
	assert(NULL != queue->queue_list);	
		
	return SLLCount(queue->queue_list);
}

/* eden boy approved */
int  QueueIsEmpty(const queue_t *queue)
{
	assert(NULL != queue);
	assert(NULL != queue->queue_list);	
		
	return SLLIsEmpty(queue->queue_list);

}

/* eden boy approved */
int QueueEnqueue(queue_t *queue, void *data)
{
	assert(NULL != queue);
	assert(NULL != queue->queue_list);	

	return (SLLIsSameIter(SLLEnd(queue->queue_list), 
			SLLInsert(SLLEnd(queue->queue_list), data)));

}

/* eden boy approved */
void QueueDequeue(queue_t *queue)
{
	assert(NULL != queue);
	assert(NULL != queue->queue_list);	

	SLLRemove(SLLBegin(queue->queue_list));

	return ;
}

/* eden boy approved */
void *QueuePeek(const queue_t *queue)
{
	assert(NULL != queue->queue_list);	
	
	return SLLGetData(SLLBegin(queue->queue_list));         
}

/* eden boy approved */
void QueueAppend(queue_t *dest, queue_t *src)
{
	assert(NULL != dest);
	assert(NULL != src);

	assert(NULL != dest->queue_list);	
	assert(NULL != src->queue_list);
	
	SLLAppend(dest->queue_list, src->queue_list);

	return ;         

}
