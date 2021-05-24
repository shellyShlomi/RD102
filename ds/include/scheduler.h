#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <time.h> 		/* struct tm */
#include <stddef.h> 	/* size_t */

#include "uid.h" 

typedef struct scheduler scheduler_t;

scheduler_t *SchedulerCreate	(void); 						 	 /* time complexity:  O(1) */
void 		 SchedulerDestroy	(scheduler_t *scheduler); 			 /* time complexity:  O(n) */
ilrd_uid_t 	 SchedulerAdd		(scheduler_t *scheduler, 
								int (*action_func)(void *param), 
								size_t interval_in_sec, void *param);/* 
								0 - seccses and stop func need to be 
							  	1 -  error at action_func		  		
							  	2- repited func							
							  	
action can be either periodical and run each x seconds, or a single instance to be executed
in x seconds.														
																		time complexity: O(n) */	   
int 		 SchedulerRemove	(scheduler_t *scheduler,            
								ilrd_uid_t uid);	  				 /* time complexity: O(n) */
size_t 	 	 SchedulerSize		(const scheduler_t *scheduler); 	 /* time complexity: O(n) */
int 		 SchedulerIsEmpty	(const scheduler_t *scheduler); 	 /* time complexity: O(1) */
int 		 SchedulerRun		(scheduler_t *scheduler); 			 /* time complexity: O(1) */
void    	 SchedulerStop		(scheduler_t *scheduler);			 /* stops the scheduler, should be
																	 *	entered as a task to be scheduled in 
																	 * interval seconds
																	 *	 time complexity: O(1) 
																	 */
void 		 SchedulerClear		(scheduler_t *scheduler);			 /* time complexity: O(n) */

#endif /* __SCHEDULER_H__ */



