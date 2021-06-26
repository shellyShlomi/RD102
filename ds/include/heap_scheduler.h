#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <time.h> 		/* struct tm */
#include <stddef.h> 	/* size_t */

#include "uid.h" 

typedef struct scheduler scheduler_t;

scheduler_t *HeapSchedulerCreate	(void); 						 	 /* time complexity:  O(1) */
void 		 HeapSchedulerDestroy	(scheduler_t *scheduler); 			 /* time complexity:  O(n) */
ilrd_uid_t 	 HeapSchedulerAdd		(scheduler_t *scheduler, 
								int (*action_func)(void *param), 
								size_t interval_in_sec, void *param);/* 
								0 - seccses and stop func need to be 
							  	1 -  error at action_func		  		
							  	2- repited func							
							  	
action can be either periodical and run each x seconds, or a single instance to be executed
in x seconds.														
																		time complexity: O(n) */	   
int 		 HeapSchedulerRemove	(scheduler_t *scheduler,            
								ilrd_uid_t uid);	  				 /* time complexity: O(n) */
size_t 	 	 HeapSchedulerSize		(const scheduler_t *scheduler); 	 /* time complexity: O(n) */
int 		 HeapSchedulerIsEmpty	(const scheduler_t *scheduler); 	 /* time complexity: O(1) */
int 		 HeapSchedulerRun		(scheduler_t *scheduler); 			 /* time complexity: O(1) */
void    	 HeapSchedulerStop		(scheduler_t *scheduler);			 /* stops the scheduler, should be
																	 *	entered as a task to be scheduled in 
																	 * interval seconds
																	 *	 time complexity: O(1) 
																	 */
void 		 HeapSchedulerClear		(scheduler_t *scheduler);			 /* time complexity: O(n) */

#endif /* __SCHEDULER_H__ */



