#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include <stddef.h> /* size_t */

#include "sorted_ll.h"

typedef struct pq pq_t;


pq_t 	  *PQueueCreate (int (*cmp_func)(const void *data1, const void *data2)); 	/* O(1) */
void       PQueueDestroy(pq_t *p_queue);			         	            		/* O(n) */	

size_t     PQueueSize   (const pq_t *p_queue);       			        			/* O(n) */ 
int        PQueueIsEmpty(const pq_t *p_queue);		   			        			/* O(1) */

int        PQueueEnqueue(pq_t *p_queue, void *data);   	 				    	    /* O(n) */
void      *PQueueDequeue(pq_t *p_queue);		    		 	   				    /* O(1) */
void      *PQueuePeek   (const pq_t *p_queue);				      	    		    /* O(1) */
  
void 	   PQueueClear  (pq_t *p_queue);					            			/* O(n) */
void 	  *PQueueErase  (pq_t *p_queue, 
						 int (*is_match_func)(const void *data, const void *param),
						 void *param); 			     					  		    /* O(n) */

#endif /* __PRIORITY_QUEUE_H__ */












