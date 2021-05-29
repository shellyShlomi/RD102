#include <stdio.h> /* printd */
#include <unistd.h>/* sleep */

#include "task.h"
#include "uid.h"

static int Print(void *param);
static void TestTask();
static void PrintUid(ilrd_uid_t uid);

/* My Iner func (at task and uid) to test the task module */
extern size_t TaskGetInterval(const task_t *task);
extern size_t GetUidCount(const ilrd_uid_t uid);
extern time_t GetUidTimeStamp(const ilrd_uid_t uid);
extern pid_t GetUidPID(const ilrd_uid_t uid);
/*static void PrintInterval(const task_t *task);*/


int main()
{
	TestTask();
	
	return 0;
}


static void TestTask()
{
	size_t interval = 5;
	int param = 1;
	int param1 = 2;
	time_t ExecutionTime = 0;
	time_t ExecutionTime1 = 0;
	time_t update_ExecutionTime = 0;
	time_t update_ExecutionTime1 = 0;
	
	ilrd_uid_t task_uid = {0};
	ilrd_uid_t task_uid1 = {0};
	ilrd_uid_t bad_uid = GetBadUid();
	
	task_t *task = TaskCreate(Print, interval, (void *)&param); 		
	task_t *task1 = TaskCreate(Print, interval, (void *)&param1); 		
	task_uid = TaskGetUid(task);
	task_uid1 = TaskGetUid(task1);
	
	if (UidIsSame(task_uid, bad_uid))
	{
		printf("test1 failed at line: %d\n", __LINE__);
	}
	
	printf("\n");
	printf("Uid :");	
	PrintUid(task_uid);
	
	ExecutionTime = TaskGetExecutionTime(task);
	
	printf("task ExecutionTime: %ld\n", ExecutionTime);
	
	TaskExecute(task);
	
	sleep(5);

	if (TaskUpdateExecutionTime(task))
	{
		printf("test1 failed at line: %d\n", __LINE__);
	} 
	
	update_ExecutionTime = TaskGetExecutionTime(task);
	
	printf("task TaskUpdateExecutionTime after sleep 5 sec: %ld\n",
		   update_ExecutionTime);
		 
		 

	if (UidIsSame(task_uid1, bad_uid))
	{
		printf("test2 failed at line: %d\n", __LINE__);
	}


	printf("\n");
	printf("Uid1 :");	
	PrintUid(task_uid1);
	
	ExecutionTime1 = TaskGetExecutionTime(task1);
	
	printf("task1 ExecutionTime: %ld\n", ExecutionTime1);
	
	TaskExecute(task1);
	
	sleep(5);

	if (TaskUpdateExecutionTime(task1))
	{
		printf("test2 failed at line: %d\n", __LINE__);
	} 
	
	update_ExecutionTime1 = TaskGetExecutionTime(task1);
	
	printf("task1 TaskUpdateExecutionTime after sleep 5 sec: %ld\n",
		   update_ExecutionTime1);
	printf("\n");
		 
	TaskDestroy(task);
	TaskDestroy(task1);

	return;
}

static int Print(void *param)
{
	printf("the parameter is: %d\n", *((int *)param)); 

	return 0;
}
/*
static void PrintInterval(const task_t *task)
{
    printf("Interval: %lu\n Uid:\n", TaskGetInterval(task));
	PrintUid(TaskGetUid(task));
    return;
}
*/

static void PrintUid(ilrd_uid_t uid)
{
	
    printf("\ncount:%ld\nprocess_id: %d\ntime_stamp: %ld\n", 
    	  GetUidCount(uid), GetUidPID(uid), GetUidTimeStamp(uid));

    return;
}
