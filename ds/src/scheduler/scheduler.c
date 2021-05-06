
/*  Developer: Shelly Shlomi;									*
 *  Status:in development;										*
 *  Date Of Creation:06.04.21;									*
 *  Date Of Approval:--.05.21;									*
 *  Approved By:												*
 *  Description:application - scheduler;						*/

#include "priority_queue.h" 
#include "scheduler.h"
#include "uid.h"

static int CmpFunc(const void *data1, const void *data2);


struct scheduler
{
	p_queue *pq;
	int run;
	task_t *task_cur;
};



scheduler_t *SchedulerCreate()
{
	scheduler_t *scheduler = (scheduler_t *)malloc(sizeof(scheduler_t));
	
	if (NULL == scheduler)
	{
		return (NULL);
	}
	
	scheduler->pq = PQueueCreate(CmpFunc);
		
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
	
	free(scheduler);
	
	return ;
}

int SchedulerRemove(scheduler_t *scheduler, ilrd_uid_t uid)
{
	int status = 1;
	task_t *task = NULL;
	
	assert(NULL != scheduler);
	assert(NULL != scheduler->pq);
	
	if (UidIsSame(uid ,TaskGetUid(scheduler->task_cur)))
	{
		return (!status);
	}
	
	task = PQueueErase(scheduler->pq, IsMatch, (void *)uid);
	
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
	
	if (NULL != task)
	{
		return (bad_uid);
	}
	
	if (0 != PQueueEnqueue(scheduler->pq, task))
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
	time_t exe_time = 0;
	unsigned int remainder = 0;
	
	assert(NULL != scheduler);
	assert(NULL != scheduler->pq);
	
	scheduler->run = 1;
	
	while (!PQueueIsEmpty(scheduler->pq) && scheduler->run)
	{
		scheduler->task_cur = PQueueDequeue(scheduler->pq);
		
		time_now = time(NULL);
	
		if ((time_t)-1 == time_now)
		{
			return (1);
		}	
		
		exe_time = TaskGetExecutionTime(scheduler->task_cur);
		
		if ((time_t)-1 == remainder)
		{
			return (1);
		}
			
		remainder = exe_time - time_now
		
		while (!remainder)
		{
			remainder = sleep((unsigned int)remainder);
		}
		
		switch(TaskExecute(scheduler->task_cur)) 
		{
			/*action_func success*/
			case 0:
			{
				TaskDestroy(scheduler->task_cur);
				scheduler->task_cur = NULL;
				break;
			}
			
			/*action_func faile - iner status */
			case 1:
			{
				TaskDestroy(scheduler->task_cur);
				scheduler->task_cur = NULL;
				
				return (2); /*action_func faile - run status*/
			}
			
			/*action_func need to be repited - iner status */
			case 2:
			{
				if(TaskUpdateExecutionTime(scheduler->task_cur))
				{
					return (1);/*TaskUpdateExecutionTime - run status of system faile */
				}
				
				if(PQueueEnqueue(scheduler->pq, scheduler->task_cur))
				{
					return (1);/*PQueueEnqueue - run status of system faile */
				}
				
				break;
			}

			default:
			{
				break;
			}

		}
	}
	
	if (!scheduler->run)
	{
		return (3); /*the stop func was activeted*/
	}
	
	scheduler->run = 0;
	
	return (0);
	
	

}
void SchedulerStop(scheduler_t *scheduler);	
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


 
static int IsMatchVoid(const void *data, const void *param)
{
	return (TaskGetUid((task_t *)data) == ((ilrd_uid_t)param)); 		
} 


static int CmpFuncVoid(const void *data1, const void *data2)
{
	return (TaskGetExecutionTime((task_t *)data1) - TaskGetExecutionTime((task_t *)data2)); 		
}

