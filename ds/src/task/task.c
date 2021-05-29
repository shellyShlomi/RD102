
/*  Developer: Shelly Shlomi;									*
 *  Status:in development;										*
 *  Date Of Creation:06.04.21;									*
 *  Date Of Approval:--.05.21;									*
 *  Approved By:												*
 *  Description:application - task;								*/
 
#include <sys/types.h> /* time_t */
#include <stdlib.h>	/* malloc */
#include <stddef.h> /* size_t */
#include <assert.h> /* assret */
#include <time.h>	/* time_t */

#include "uid.h"
#include "task.h"


struct task
{
	time_t execution_time;
	size_t interval;
	int (*action_func)(void *param);
	void *param;
	ilrd_uid_t uid;
};


task_t *TaskCreate(	int (*action_func)(void *param), 
					size_t interval_in_sec,
					void *param)
{

	ilrd_uid_t task_uid = {0};
	task_t *task = NULL;
	time_t time_now = time(NULL);

	assert(NULL != action_func);	
	
	if (((time_t)-1) == time_now)
	{
		return (NULL);
	}	
	
	task_uid = UidCreate();

	if (UidIsSame(GetBadUid(), task_uid))
	{
		return (NULL);
	}
	
	task = (task_t *)malloc(sizeof(task_t));
	
	if (NULL == task)
	{	
		return (NULL);
	}
	
	task->uid = task_uid;
	task->action_func = action_func;
	task->param = param;
	task->interval = interval_in_sec;
	task->execution_time = time_now + interval_in_sec;
	
	return (task);

}


void TaskDestroy(task_t *task)
{
	assert(NULL != task);	
	
	task->action_func = NULL;
	task->param = NULL;
	task->execution_time = ((time_t)-1);
	
	free(task);
	
	return ; 
}


ilrd_uid_t TaskGetUid(const task_t *task)
{
	assert(NULL != task);	
	
	return (task->uid); 
}


int TaskUpdateExecutionTime(task_t *task)
{
	time_t time_now = time(NULL);

	assert(NULL != task);	
	
	if (((time_t)-1) == time_now)
	{
		return (1);
	}	
	
	task->execution_time = time_now + task->interval;
	
	return (0); 
}



time_t TaskGetExecutionTime(task_t *task)
{
	assert(NULL != task);	
	
	return (task->execution_time); 
}


int TaskExecute(task_t *task)
{
	assert(NULL != task);	
	assert(NULL != task->action_func);	
	
	return (task->action_func(task->param)); 
}




