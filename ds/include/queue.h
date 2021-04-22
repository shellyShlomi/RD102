/* 20.4.21 14:00 version_1 */

#ifndef __OL102_QUEUE_H__
#define __OL102_QUEUE_H__

#include <stddef.h> /* size_t */

typedef struct queue queue_t;

queue_t *QueueCreate(void);                    				  /* O(1) */
void QueueDestroy(queue_t *queue);				              /* O(n) */	

size_t QueueSize(const queue_t *queue);         			  /* O(n) */ 
int  QueueIsEmpty(const queue_t *queue);		              /* O(1) */

int  QueueEnqueue(queue_t *queue, void *data);	              /* O(1) */
void *QueuePeek(const queue_t *queue);						  /* O(1) */
void QueueDequeue(queue_t *queue);							  /* O(1) */

void QueueAppend(queue_t *dest, queue_t *src);            /* O(1) */
 
#endif /* __OL102_QUEUE_H__ */


