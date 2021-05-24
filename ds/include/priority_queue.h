#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include <stddef.h> /* size_t */

typedef struct pq pq_t;


pq_t 	  *PQueueCreate (int (*cmp_func)(const void *data1, const void *data2)); 	/* O(1) */
void       PQueueDestroy(pq_t *p_queue);			         	            		/* O(n) */	

size_t     PQueueSize   (const pq_t *p_queue);       			        			/* O(n) */ 
int        PQueueIsEmpty(const pq_t *p_queue);		   			        			/* O(1) */

int        PQueueEnqueue(pq_t *p_queue, void *data);   	 				    	    /* O(n) */
void      *PQueueDequeue(pq_t *p_queue);		    		 	   				    /* O(1) */
void      *PQueuePeek   (const pq_t *p_queue);				      	    		    /* O(1) */



/*PQueueClear
 * DESCRIPTION		:	The function erase elemrnt in the priority queue and 
 *						return a pointer to the data
 * 
 * PARAMETERS    	:   p_queue - pointer to the priority queue
 *			
 *
 * RETURN VALUE   	:   non 
 * 
 * COMPLEXITY   	:   Time - O(1) 
 */

void 	   PQueueClear  (pq_t *p_queue);



/*PQueueErase
 * DESCRIPTION		:	The function erase elemrnt in the priority queue and 
 *						return a pointer to the data
 * 
 * PARAMETERS    	:   p_queue - pointer to the priority queue
 *						
 *						param -	the data looked for within the list
 *
 *						int (*is_match_func)(const void *data, const void *param)
 *						
 *							Description		:	a function wich compar to data 
 *												values of the same type
 *												
 *							Parameters		:	const data -	the data in the element
 *																of the priority queue
 *																wich compard with parta   
 *
 *												const param -	the data looked
 *			 													for within the 
 *																priority queue
 *			
 *							Return Value   	:   boolian value : 1 same data, 0 not same data
 *
 *							Complexity		: 	Time - O(n) 
 *						
 * RETURN VALUE   	:    
 * 
 * COMPLEXITY   	:   Time - O(n) 
 */					            			/* O(n) */
void 	  *PQueueErase  (pq_t *p_queue, 
						 int (*is_match_func)(const void *data, const void *param),
						 void *param); 			     					  		    /* O(n) */

#endif /* __PRIORITY_QUEUE_H__ */











