#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <time.h> 		/* struct tm */
#include <stddef.h> 	/* size_t */

#include "uid.h" 

typedef struct scheduler scheduler_t;

scheduler_t *HSchedulerCreate	(void); 						 	 /* time complexity:  O(1) */
void 		 HSchedulerDestroy	(scheduler_t *scheduler); 			 /* time complexity:  O(n) */
ilrd_uid_t 	 HSchedulerAdd		(scheduler_t *scheduler, 
								int (*action_func)(void *param), 
								size_t interval_in_sec, void *param);/* 
								0 - seccses and stop func need to be 
							  	1 -  error at action_func		  		
							  	2- repited func							
							  	
action can be either periodical and run each x seconds, or a single instance to be executed
in x seconds.														
																		time complexity: O(n) */	   
int 		 HSchedulerRemove	(scheduler_t *scheduler,            
								ilrd_uid_t uid);	  				 /* time complexity: O(n) */
size_t 	 	 HSchedulerSize		(const scheduler_t *scheduler); 	 /* time complexity: O(n) */
int 		 HSchedulerIsEmpty	(const scheduler_t *scheduler); 	 /* time complexity: O(1) */
int 		 HSchedulerRun		(scheduler_t *scheduler); 			 /* time complexity: O(1) */
void    	 HSchedulerStop		(scheduler_t *scheduler);			 /* stops the scheduler, should be
																	 *	entered as a task to be scheduled in 
																	 * interval seconds
																	 *	 time complexity: O(1) 
																	 */
void 		 HSchedulerClear		(scheduler_t *scheduler);			 /* time complexity: O(n) */

#endif /* __SCHEDULER_H__ */



