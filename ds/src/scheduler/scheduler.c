
/*  Developer: Shelly Shlomi;									*
 *  Status:Reviewed by anna;									*
 *  Date Of Creation:06.05.21;									*
 *  End Date: 08.05.21;											*
 *  Date Of Approval:09.05.21;									*
 *  Approved By:anna											*
 *  Description: application - scheduler;						*/
 
#include <sys/types.h> /* time_t */
#include <stdlib.h>	/* uid */
#include <stddef.h> /* size_t */
#include <assert.h> /* assret */
#include <time.h>	/* time_t */
#include <unistd.h> /* sleep */

#include "scheduler.h"
#include "priority_queue.h" 
#include "task.h"
#include "uid.h"

/* run return status */
#define SUCCESS 0
#define SYSTEM_FAILURE 1
#define ACTION_FUNC_FAILURE 2
#define STOPED 3

/* opartion func return status for swich */

#define OPARTION_FUNCION_FAILURE 1
#define	REPEATED 2

static int CmpFunc(const void *data1, const void *data2);
static int IsMatch(const void *data, const void *param);

struct scheduler
{
	pq_t *pq;
	task_t *task_cur;
	int is_running;
};


scheduler_t *SchedulerCreate()
{
	scheduler_t *scheduler = (scheduler_t *)malloc(sizeof(scheduler_t));
	
	if (NULL == scheduler)
	{
		return (NULL);
	}
	
	scheduler->pq = PQueueCreate(CmpFunc);
	scheduler->is_running = 0;
	scheduler->task_cur = NULL;
	
		
	if (NULL == scheduler->pq)
	{
		free(scheduler);
		scheduler = NULL;
		
		return (NULL);
	}
	
	return (scheduler);

}

void SchedulerDestroy(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	assert(NULL != scheduler->pq);	

	SchedulerClear(scheduler);
	
	PQueueDestroy(scheduler->pq);
	
	scheduler->pq = NULL;
	scheduler->task_cur = NULL;
	
	free(scheduler);
	
	return ;
}



int SchedulerRemove(scheduler_t *scheduler, ilrd_uid_t uid)
{
	int status = 1;
	task_t *task_to_remove = NULL;
	
	assert(NULL != scheduler);
	assert(NULL != scheduler->pq);
	
	/* for task that remove hemself at run and the NULL cheke is for remove not at run */
	if ((NULL != scheduler->task_cur) && UidIsSame(uid ,TaskGetUid(scheduler->task_cur)))
	{
		TaskDestroy(scheduler->task_cur);
		
		scheduler->task_cur = NULL;		

		return (!status);
	}
	
	task_to_remove = (task_t *)(PQueueErase(scheduler->pq, IsMatch, (void *)&uid));
	
	if (NULL != task_to_remove)
	{
		TaskDestroy(task_to_remove);

		status = 0;
	}
	
	return (status);
}	


size_t SchedulerSize(const scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	assert(NULL != scheduler->pq);

	return (PQueueSize(scheduler->pq) + (!!scheduler->task_cur));
}


int SchedulerIsEmpty(const scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	assert(NULL != scheduler->pq);
	

	return (PQueueIsEmpty(scheduler->pq) - (!!scheduler->task_cur));
}


ilrd_uid_t SchedulerAdd(scheduler_t *scheduler, int (*action_func)(void *param), 
											size_t interval_in_sec, void *param)
{
	task_t *task = NULL;
	
	assert(NULL != scheduler);
	assert(NULL != scheduler->pq);
	assert(NULL != action_func); 
	
	task = TaskCreate(action_func, interval_in_sec, param);
	
	if (NULL == task)
	{
		return (GetBadUid());
	}
	
	if (PQueueEnqueue(scheduler->pq, (void *)task))
	{
		TaskDestroy(task);
		task = NULL;

		return (GetBadUid());
	}
	
	return (TaskGetUid(task));
}




int SchedulerRun(scheduler_t *scheduler)
{
	time_t time_now = 0;
	int remainder = 0;
	
	assert(NULL != scheduler);
	assert(NULL != scheduler->pq);
	
	scheduler->is_running = 1;

	while (!PQueueIsEmpty(scheduler->pq) && scheduler->is_running)
	{
		time_now = time(NULL);
	
		scheduler->task_cur = PQueueDequeue(scheduler->pq);
		
		remainder = (int)TaskGetExecutionTime(scheduler->task_cur) - time_now;
		
		while (0 < remainder)
		{
			remainder = sleep((unsigned int)remainder);
		}
		
		switch(TaskExecute(scheduler->task_cur)) 
		{
			/* action_func success/ stop/ or 
			 * task that is self remove (0)
			 */
			case SUCCESS:
			{
				/* for task that remove hemself at run
				 * time with a success (0)status do Destroy 
				 * and now the scheduler->task_cur == null
				 */
				if (NULL != scheduler->task_cur)
				{
					TaskDestroy(scheduler->task_cur);
					scheduler->task_cur = NULL;
				}
				
				break;
			}
			
			/* action_func faile - iner status (1) 
			*/
			case OPARTION_FUNCION_FAILURE:
			{
				TaskDestroy(scheduler->task_cur);
				scheduler->task_cur = NULL;
				
				/*action_func faile - run status (2)
				*/
				return (ACTION_FUNC_FAILURE); 
			}
			
			/* action_func need to be repeated - 
			 * [iner status (2)]
			 */
			case REPEATED:
			{
				/* for task that remove hemself at run 
				 * time with a repit status 
				 */
				if (NULL == scheduler->task_cur)
				{
					break;
				}

				/* TaskUpdateExecutionTime or PQueueEnqueue - 
				 * run status of system faile (1)
				 */
				
				TaskUpdateExecutionTime(scheduler->task_cur); 
		
				if (PQueueEnqueue(scheduler->pq, scheduler->task_cur))
				{
					TaskDestroy(scheduler->task_cur);
					scheduler->task_cur = NULL;
					
					return (SYSTEM_FAILURE);
				}
			}
			
			default:
			{
				break;
			}

		}
	}	

	if (!scheduler->is_running)
	{
		/*the stop func was activeted - 
		 *run status (3)
		 */
		return (STOPED); 
	}

	scheduler->task_cur = NULL;
		
	return (SUCCESS);

}
void SchedulerStop(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	scheduler->is_running = 0;
	
	return ;
}


void SchedulerClear(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	assert(NULL != scheduler->pq);
	
	while (!PQueueIsEmpty(scheduler->pq))
	{
		TaskDestroy(PQueueDequeue(scheduler->pq));
	}
	
	return ; 
}


 
static int IsMatch(const void *data, const void *param)
{
	return (UidIsSame(TaskGetUid((task_t *)data), (*((ilrd_uid_t *)param)))); 		
} 


static int CmpFunc(const void *data1, const void *data2)
{
	return (TaskGetExecutionTime((task_t *)data1) - TaskGetExecutionTime((task_t *)data2)); 		
}

