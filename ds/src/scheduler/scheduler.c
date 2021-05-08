
/*  Developer: Shelly Shlomi;									*
 *  Status:in development;										*
 *  Date Of Creation:06.04.21;									*
 *  Date Of Approval:--.05.21;									*
 *  Approved By:												*
 *  Description:application - scheduler;						*/
#include <sys/types.h> /* time_t */
#include <stdlib.h>	/* uid */
#include <stddef.h> /* size_t */
#include <assert.h> /* assret */
#include <time.h>	/* time_t */
#include <unistd.h> /* sleep */

#include "scheduler.h"
#include "priority_queue.h" 
#include "task.h"

static int CmpFunc(const void *data1, const void *data2);
static int IsMatch(const void *data, const void *param);

struct scheduler
{
	pq_t *pq;
	int run;
	task_t *task_cur;
};

enum exit_satus_run
{
	SUCCESS,
	SYSTEM_FAILURE,
	ACTION_FUNC_FAILURE,
	STOPED

};

enum exit_satus_action_func
{
	ACTION_FUNCION_FAILURE = 1,
	REPEATED
};

scheduler_t *SchedulerCreate()
{
	scheduler_t *scheduler = (scheduler_t *)malloc(sizeof(scheduler_t));
	
	if (NULL == scheduler)
	{
		return (NULL);
	}
	
	scheduler->pq = PQueueCreate(CmpFunc);
	scheduler->run = 1;
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
	task_t *task = NULL;
	
	assert(NULL != scheduler);
	assert(NULL != scheduler->pq);
	
	if (NULL != scheduler->task_cur)
	{	
		if (UidIsSame(uid ,TaskGetUid(scheduler->task_cur)))
		{
			return (!status);
		}
	}
	
	task = (task_t *)(PQueueErase(scheduler->pq, IsMatch, (void *)&uid));
	
	if (NULL != task)
	{
		TaskDestroy(task);
		task = NULL;

		status = 0;
	}
	
	return (status);
}	
								
size_t SchedulerSize(const scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	assert(NULL != scheduler->pq);

	return (PQueueSize(scheduler->pq));
}


int SchedulerIsEmpty(const scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	assert(NULL != scheduler->pq);
	
	return (PQueueIsEmpty(scheduler->pq));
}

ilrd_uid_t SchedulerAdd(scheduler_t *scheduler, int (*action_func)(void *param), 
											size_t interval_in_sec, void *param)
{
	task_t *task = NULL;
	
	ilrd_uid_t bad_uid = GetBadUid();
	
	assert(NULL != scheduler);
	assert(NULL != scheduler->pq);
	assert(NULL != action_func);
	
	task = TaskCreate(action_func, interval_in_sec, param);
	
	if (NULL == task)
	{
		return (bad_uid);
	}
	
	if (0 != PQueueEnqueue(scheduler->pq, (void *)task))
	{
		TaskDestroy(task);
		task = NULL;

		return (bad_uid);
	}
	
	return (TaskGetUid(task));
}




int SchedulerRun(scheduler_t *scheduler)
{
	time_t time_now = 0;
	unsigned int remainder = 0;
	
	assert(NULL != scheduler);
	assert(NULL != scheduler->pq);
	
	while (!PQueueIsEmpty(scheduler->pq) && scheduler->run)
	{
		time_now = time(NULL);
	
		if ((time_t)-1 == time_now)
		{
			return (SYSTEM_FAILURE);
		}	
		
		scheduler->task_cur = PQueueDequeue(scheduler->pq);
		
		remainder = TaskGetExecutionTime(scheduler->task_cur) - time_now;
		
		while (remainder)
		{
			remainder = sleep((unsigned int)remainder);
		}
		
		switch(TaskExecute(scheduler->task_cur)) 
		{
			/*action_func need to be repeated - iner status */
			case REPEATED:
			{
	
			/*TaskUpdateExecutionTime - run status of system faile */
				if(TaskUpdateExecutionTime(scheduler->task_cur))
				{
					TaskDestroy(scheduler->task_cur);
					
					scheduler->task_cur = NULL;
					
					return (SYSTEM_FAILURE);
				}
				
				if(PQueueEnqueue(scheduler->pq, scheduler->task_cur))
				{
					TaskDestroy(scheduler->task_cur);
					
					scheduler->task_cur = NULL;
					
					return (SYSTEM_FAILURE);/*PQueueEnqueue - run status of system faile */
				}
				
				break;
			}
			
			/*action_func faile - iner status */
			case ACTION_FUNCION_FAILURE:
			{
				TaskDestroy(scheduler->task_cur);
				
				scheduler->task_cur = NULL;
				
				return (ACTION_FUNC_FAILURE); /*action_func faile - run status*/
			}
			/*action_func success/ stop/ or task that is self remove*/
			default:
			{
				TaskDestroy(scheduler->task_cur);
				
				scheduler->task_cur = NULL;
				
				break;
			}

		}
	}
	
	if (!scheduler->run)
	{
		scheduler->run = 1;
		
		return (STOPED); /*the stop func was activeted*/
	}
	
	return (SUCCESS);

}
void SchedulerStop(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	scheduler->run = 0;
	
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


 
int IsMatch(const void *data, const void *param)
{
	return (UidIsSame(TaskGetUid((task_t *)data), (*((ilrd_uid_t *)param)))); 		
} 


static int CmpFunc(const void *data1, const void *data2)
{
	return (TaskGetExecutionTime((task_t *)data1) - TaskGetExecutionTime((task_t *)data2)); 		
}

