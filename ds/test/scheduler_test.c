
#include <stdlib.h> /* exit status */
#include <stdio.h> /* printf */
#include <unistd.h> /* sleep */

#include "scheduler.h"
#include "task.h"
#include "uid.h"

#define SIEZ_UID_ARR 10


#define SUCCESS 0
#define ACTION_FUNCION_FAILURE 1
#define REPEATED 2


typedef struct param
{
	scheduler_t *scheduler;
	int counter;
	ilrd_uid_t uid;
	
}param_t;



static void Test();


static void SchedulerCreateTest();
static void SchedulerRunTest();
static void NoIntervalRunNoStopTest();
static void NoIntervalRunTest();
static void RepitesRunTest();
static void SchedulerAddRemoveTest();
static void TaskAddingSchedulerRunTest();
static void TaskErrorSchedulerRunTest();

static int SelfRemoveFuncWithInterval(void *param);
static int RemoveFuncWithInterval(void *param);
static int ActionFunc1(void *param);
static int StopFunc(void *param);
static int ActionFuncRepitChar(void *param);
static int ActionFuncRepitChar1(void *param);
static int ActionFuncChar(void *param);
static int ActionFuncRepit1(void *param);
static int ActionFuncRepit2(void *param);
static int ActionFuncRepit3(void *param);
static int ActionFuncRepit4(void *param);
static int PrintActionFuncRepit(void *param);
static int TaskAddingActionFunc(void *param);
static int ActionFuncError(void *param);

static void Red();
static void Yellow();
static void Purple();
static void Green();
static void Blue();
static void Reset();
static void Cyan();
static void YellowB();
static void PurpleB();
static void GreenB();


int main()
{

	Test();
	
	return EXIT_SUCCESS;
}


static void Test()
{
	SchedulerCreateTest();
	SchedulerAddRemoveTest();
	NoIntervalRunNoStopTest();
	NoIntervalRunTest();
	RepitesRunTest();
	SchedulerRunTest();
	TaskAddingSchedulerRunTest();
	TaskErrorSchedulerRunTest();
	
	return;

}


static void SchedulerCreateTest()
{	
	scheduler_t *scheduler = SchedulerCreate();
	
	if (NULL == scheduler)
	{
		printf("SchedulerCreateTest->SchedulerCreate error at line: %d\n", __LINE__);
		
		return ; 
	}
	
	/* test SchedulerIsEmpty on empty list */
	if (1 != SchedulerIsEmpty(scheduler))
	{
		printf("SchedulerCreateTest->SchedulerIsEmpty error at line: %d\n", __LINE__);
	}
	
	/* test SchedulerSize on empty list  */
	if (0 != SchedulerSize(scheduler))
	{
		printf("SchedulerCreateTest->SchedulerSize error at line: %d\n", __LINE__);
	}
	
	SchedulerDestroy(scheduler);
	scheduler = NULL;
	
	return ;
}

/*remove with no repites*/
static void SchedulerAddRemoveTest()
{	

	int arr[] = {1, 2, 5, 3, 1, 2};
	size_t arr_interval[] = {1, 2, 5, 3, 1, 2};
	size_t size = sizeof(arr)/ sizeof(arr[0]);
	ilrd_uid_t arr_uid[SIEZ_UID_ARR] = {0};
	size_t i = 0;
	
	scheduler_t *scheduler = SchedulerCreate();
	
	if (NULL == scheduler)
	{
		printf("SchedulerCreateTest->SchedulerCreate error at line: %d\n", __LINE__);

		
		return ; 
	}

	for (i = 0; i < size; ++i)
	{
		arr_uid[i] = SchedulerAdd(scheduler, ActionFunc1, *(arr_interval + i), (void *)(arr + i));

	}
	
	if (size != SchedulerSize(scheduler))
	{
		printf("SchedulerAddTest->SchedulerAdd error at line: %d %lu\n", __LINE__,SchedulerSize(scheduler));
	}
	
	for (i = 0; i < size; ++i)
	{
		if (0 != SchedulerRemove(scheduler, arr_uid[i]))
		{
			printf("SchedulerAddTest->SchedulerRemove ");
			printf("error at line: %d index: %ld %ld\n", __LINE__,i, SchedulerSize(scheduler)); 	
		}

	}

	if (0 != SchedulerSize(scheduler))
	{
		printf("SchedulerAddTest->SchedulerIsEmpty error at line: %d\n", __LINE__);
	}
	SchedulerDestroy(scheduler);
	scheduler = NULL;
	
	return ;

}


/*remove with repites*/
static void RepitesRunTest()
{	

	int arr[] = {1, 2, 5, 3, 1, 2};
	size_t arr_interval[] = {1, 2, 5, 3, 1, 2};
	char *str = "shelly";
	size_t size = sizeof(arr)/ sizeof(arr[0]);
	ilrd_uid_t arr_uid[SIEZ_UID_ARR] = {0};
	size_t interval = 5;
	size_t i = 0;
	
	scheduler_t *scheduler = SchedulerCreate();
	
	if (NULL == scheduler)
	{
		printf("RepitesRunTest->SchedulerCreate error at line: %d\n", __LINE__);

		
		return ; 
	}

	for (i = 0; i < size; ++i)
	{
		arr_uid[i] = SchedulerAdd(scheduler, PrintActionFuncRepit, *(arr_interval + i), (void *)(arr + i));

	}
	
	if (size != SchedulerSize(scheduler))
	{
		printf("RepitesRunTest->SchedulerAdd error at line: %d\n", __LINE__);
	}
	
	arr_uid[i] = SchedulerAdd(scheduler, StopFunc, interval, scheduler);

	arr_uid[i + 1] = SchedulerAdd(scheduler, ActionFuncRepitChar, *(arr_interval), (void *)str);

	Yellow();

	printf("\nRepitesRunTest\n \n"); 
	
	printf("\nSchedulerRun return: %d \n\n",SchedulerRun(scheduler)); 
	
	if (size + 1 != SchedulerSize(scheduler))
	{
		printf("RepitesRunTest->SchedulerAdd error at line: %d\n", __LINE__);
	}

	
	for (i = 0; i < size + 2; ++i)
	{
		if (6 == i)
		{
		
			if (1 != SchedulerRemove(scheduler, arr_uid[i]))
			{
				printf("RepitesRunTest->SchedulerRemove ");
				printf("error at line: %d index: %ld %ld\n", __LINE__,i, SchedulerSize(scheduler)); 	
			}
			
			++i;
		}

		if (0 != SchedulerRemove(scheduler, arr_uid[i]))
		{
			printf("RepitesRunTest->SchedulerRemove ");
			printf("error at line: %d index: %ld %ld\n", __LINE__,i, SchedulerSize(scheduler)); 	
		}
	}
	
	if (0 != SchedulerSize(scheduler))
	{
		printf("RepitesRunTest->SchedulerSize error at line: %d \n", __LINE__);
	}
	
	Reset();
	
	SchedulerDestroy(scheduler);
	scheduler = NULL;
	
	return ;

}


/*remove with no repites & run*/
static void NoIntervalRunNoStopTest()
{	

	int arr[] = {1, 2, 5, 3, 1, 2};
	size_t arr_interval[] = {1, 2, 5, 3, 1, 2};
	size_t size = sizeof(arr)/ sizeof(arr[0]);
	size_t i = 0;
	
	scheduler_t *scheduler = SchedulerCreate();
	
	if (NULL == scheduler)
	{
		printf("SchedulerCreateTest->SchedulerCreate error at line: %d\n", __LINE__);

		
		return ; 
	}

	for (i = 0; i < size; ++i)
	{
		SchedulerAdd(scheduler, ActionFunc1, *(arr_interval + i), (void *)(arr + i));

	}
	
	if (size != SchedulerSize(scheduler))
	{
		printf("SchedulerAddTest->SchedulerAdd error at line: %d %lu\n", __LINE__,SchedulerSize(scheduler));
	}
	
	
	Red();
	sleep(3);
	printf("\nNoIntervalRunNoStopTest delay of 3 sec\n \n"); 
	
	printf("\nSchedulerRun return: %d \n\n",SchedulerRun(scheduler)); 
	
	if (0 != SchedulerSize(scheduler))
	{
		printf("SchedulerAddTest->SchedulerIsEmpty error at line: %d\n", __LINE__);
	}
	Reset();
	
	SchedulerDestroy(scheduler);
	scheduler = NULL;
	
	return ;

}


/*remove with no repites and stop befor all taskes was executed*/
static void NoIntervalRunTest()
{	

	int arr[] = {1, 2, 10, 3, 8, 2};
	size_t arr_interval[] = {1, 2, 10, 3, 8, 2};
	char *str = "shelly";
	size_t size = sizeof(arr)/ sizeof(arr[0]);
	ilrd_uid_t arr_uid[SIEZ_UID_ARR] = {0};
	size_t interval = 5;
	size_t i = 0;
	
	scheduler_t *scheduler = SchedulerCreate();
	
	if (NULL == scheduler)
	{
		printf("NoIntervalRunTest->SchedulerCreate error at line: %d\n", __LINE__);

		
		return ; 
	}

	for (i = 0; i < size; ++i)
	{
		arr_uid[i] = SchedulerAdd(scheduler, ActionFunc1, *(arr_interval + i), (void *)(arr + i));

	}
	
	if (size != SchedulerSize(scheduler))
	{
		printf("NoIntervalRunTest->SchedulerAdd error at line: %d\n", __LINE__);
	}
	
	arr_uid[i] = SchedulerAdd(scheduler, StopFunc, interval, scheduler);

	arr_uid[i + 1] = SchedulerAdd(scheduler, ActionFuncRepitChar, *(arr_interval), (void *)str);
	
	Blue();
	printf("\nNoIntervalRunTest\n \n"); 
	
	printf("\nSchedulerRun return: %d \n\n",SchedulerRun(scheduler)); 
	
	if (size/2 != SchedulerSize(scheduler))
	{
		printf("NoIntervalRunTest->SchedulerAdd error at line: %d\n", __LINE__);
	}

	
	for (i = 0; i < size + 2; ++i)
	{
		if (6 == i || ( 2 != i && 4 != i && 7 != i))
		{
		
		/* the stop task that Destroy hearself*/
			if (1 != SchedulerRemove(scheduler, arr_uid[i]))
			{
				printf("NoIntervalRunTest->SchedulerRemove ");
				printf("error at line: %d index: %ld %ld\n", __LINE__,i, SchedulerSize(scheduler)); 	
			}
			
			continue;
		}

		if (0 != SchedulerRemove(scheduler, arr_uid[i]))
		{
			printf("NoIntervalRunTest->SchedulerRemove ");
			printf("error at line: %d index: %ld %ld\n", __LINE__,i, SchedulerSize(scheduler)); 	
		}
	}
	
	if (0 != SchedulerSize(scheduler))
	{
		printf("NoIntervalRunTest->SchedulerSize error at line: %d \n", __LINE__);
	}
	
	Reset();
	
	SchedulerDestroy(scheduler);
	scheduler = NULL;
	
	return ;

}



/*task that Destroy herself and other tasks with repites*/
static void SchedulerRunTest()
{	

	int arr[] = {1, 2, 5, 3, 1, 2};
	size_t arr_interval[] = {1, 2, 5, 3, 1, 2};
	char *str = "shelly";
	size_t size = sizeof(arr)/ sizeof(arr[0]);
	ilrd_uid_t arr_uid[SIEZ_UID_ARR] = {0};
	param_t remove = {NULL};
	size_t interval = 5;
	size_t interval1 = 2;
	size_t i = 0;
	
	scheduler_t *scheduler = SchedulerCreate();
	
	if (NULL == scheduler)
	{
		printf("SchedulerRunTest->SchedulerCreate error at line: %d\n", __LINE__);

		
		return ; 
	}

	for (i = 0; i < size; ++i)
	{
		arr_uid[i] = SchedulerAdd(scheduler, ActionFuncRepit1, *(arr_interval + i), (void *)(arr + i));

	}
	
	if (size != SchedulerSize(scheduler))
	{
		printf("SchedulerRunTest->SchedulerAdd error at line: %d %lu\n", __LINE__,SchedulerSize(scheduler));
	}
	
	arr_uid[i] = SchedulerAdd(scheduler, ActionFuncRepitChar, *(arr_interval), (void *)str);

	/*task remove herself*/
	
	++i;
	
	arr_uid[i] = SchedulerAdd(scheduler, SelfRemoveFuncWithInterval, interval1, (void *)&remove);
	
	remove.scheduler = scheduler;
	remove.uid = arr_uid[i];
	remove.counter = 0;
	
	++i;
	
	arr_uid[i] = SchedulerAdd(scheduler, StopFunc, interval * 2, scheduler);

	Purple();

	printf("\nSchedulerRunTest with task that is selfDestroy \n \n"); 
	
	printf("\nSchedulerRun return: %d \n\n",SchedulerRun(scheduler)); 
	
	if (size + 1 != SchedulerSize(scheduler))
	{
		printf("SchedulerRunTest->SchedulerAdd error at line: %d \n", __LINE__);
	}

	
	for (i = 0; !SchedulerIsEmpty(scheduler); ++i)
	{
		if (7 == i)
		{

			if (1 != SchedulerRemove(scheduler, arr_uid[i]))
			{	
				printf("SchedulerRunTest->SchedulerRemove ");
				printf("error at line: %d index: %ld %ld\n", __LINE__,i, SchedulerSize(scheduler)); 	
			}
			
			++i;
		}
		
		if (0 != SchedulerRemove(scheduler, arr_uid[i]))
		{
			printf("SchedulerRunTest->SchedulerRemove ");
			printf("error at line: %d index: %ld %ld\n", __LINE__,i, SchedulerSize(scheduler)); 	
		}
	}
	
	if (0 != SchedulerSize(scheduler))
	{
		printf("SchedulerRunTest->SchedulerSize error at line: %d \n", __LINE__);
	}
	
	Reset();
	
	SchedulerDestroy(scheduler);
	
	scheduler = SchedulerCreate();
	
	if (NULL == scheduler)
	{
		printf("SchedulerRunTest->SchedulerCreate error at line: %d\n", __LINE__);

		
		return ; 
	}

	for (i = 0; i < size; ++i)
	{
		arr_uid[i] = SchedulerAdd(scheduler, ActionFuncRepit2, *(arr_interval + i), (void *)(arr + i));

	}
	
	if (size != SchedulerSize(scheduler))
	{
		printf("SchedulerRunTest->SchedulerAdd error at line: %d %lu\n", __LINE__,SchedulerSize(scheduler));
	}
	
	arr_uid[i] = SchedulerAdd(scheduler, ActionFuncRepitChar1, *(arr_interval), (void *)str);

	/*task remove other tasks */
	
	++i;
	
	arr_uid[i] = SchedulerAdd(scheduler, RemoveFuncWithInterval, interval1, (void *)&remove);
	
	remove.scheduler = scheduler;
	remove.uid = arr_uid[i - 1]; /*removal of str*/
	remove.counter = 0;
	
	++i;
	
	arr_uid[i] = SchedulerAdd(scheduler, StopFunc, interval * 2, scheduler);

	Cyan();

	printf("\nSchedulerRunTest with task that Destroy other tasks\nshelly will be removed \n\n"); 
	
	printf("\nSchedulerRun return: %d \n\n",SchedulerRun(scheduler)); 
	
	SchedulerClear(scheduler);
	
	if (0 != SchedulerSize(scheduler))
	{
		printf("SchedulerRunTest->SchedulerAdd error at line: %d\n", __LINE__);
	}
	Reset();
	
	SchedulerDestroy(scheduler);
	scheduler = NULL;
	
	return ;

}


/*task that addes other tasks and remove herself after 2 times*/
static void TaskAddingSchedulerRunTest()
{	

	int arr[] = {1, 2, 5, 3, 1, 2};
	size_t arr_interval[] = {1, 2, 5, 3, 1, 2};
	size_t size = sizeof(arr)/ sizeof(arr[0]);
	ilrd_uid_t arr_uid[SIEZ_UID_ARR] = {0};
	param_t adding = {NULL};
	size_t interval = 5;
	size_t interval1 = 2;
	size_t i = 0;
	
	scheduler_t *scheduler = SchedulerCreate();

	
	if (NULL == scheduler)
	{
		printf("TaskAddingSchedulerRunTest->SchedulerCreate error at line: %d\n", __LINE__);

		
		return ; 
	}

	for (i = 0; i < size; ++i)
	{
		arr_uid[i] = SchedulerAdd(scheduler, ActionFuncRepit3, *(arr_interval + i), (void *)(arr + i));

	}
	
	if (size != SchedulerSize(scheduler))
	{
		printf("TaskAddingSchedulerRunTest->SchedulerAdd error at line: %d\n", __LINE__);
	}
	
	/*task that addes other tasks and remove herself after 2 times*/
	
	++i;
	
	arr_uid[i] = SchedulerAdd(scheduler, TaskAddingActionFunc, interval1, (void *)&adding);
	
	adding.scheduler = scheduler;
	adding.uid = arr_uid[i]; /*removal of herself*/
	adding.counter = 0;
		
	++i;
	
	arr_uid[i] = SchedulerAdd(scheduler, StopFunc, interval * 2, scheduler);

	Blue();

	printf("\nTaskAddingSchedulerRunTest with task that add other tasks "); 
	printf("and after 2 times remove herself \n\n"); 
	printf("\nSchedulerRun return: %d \n\n",SchedulerRun(scheduler)); 
	
	
	
	SchedulerClear(scheduler);
	
	if (0 != SchedulerSize(scheduler))
	{
		printf("TaskAddingSchedulerRunTest->SchedulerAdd error at line: %d\n", __LINE__);
	}
	Reset();
	
	SchedulerDestroy(scheduler);
	scheduler = NULL;
	
	return ;

}

/*task that returns error*/
static void TaskErrorSchedulerRunTest()
{	

	int arr[] = {1, 2, 5, 3, 1, 2};
	size_t arr_interval[] = {1, 2, 5, 3, 1, 2};
	size_t size = sizeof(arr)/ sizeof(arr[0]);
	size_t interval = 5;
	size_t i = 0;
	
	scheduler_t *scheduler = SchedulerCreate();

	
	if (NULL == scheduler)
	{
		printf("TaskErrorSchedulerRunTest->SchedulerCreate error at line: %d\n", __LINE__);

		
		return ; 
	}

	for (i = 0; i < size; ++i)
	{
		SchedulerAdd(scheduler, ActionFuncRepit4, *(arr_interval + i), (void *)(arr + i));

	}
	
	if (size != SchedulerSize(scheduler))
	{
		printf("TaskErrorSchedulerRunTest->SchedulerAdd error at line: %d\n", __LINE__);
	}
	
	SchedulerAdd(scheduler, ActionFuncError, *(arr_interval), NULL);
	
	++i;
	
	SchedulerAdd(scheduler, StopFunc, interval * 2, scheduler);

	Green();

	printf("\nTaskErrorSchedulerRunTest with task that returns error \n\n"); 
	printf("\nSchedulerRun return: %d \n\n",SchedulerRun(scheduler)); 
	
	
	
	SchedulerClear(scheduler);
	
	if (0 != SchedulerSize(scheduler))
	{
		printf("TaskErrorSchedulerRunTest->SchedulerAdd error at line: %d\n", __LINE__);
	}
	Reset();
	
	SchedulerDestroy(scheduler);
	scheduler = NULL;
	
	return ;

}




static int TaskAddingActionFunc(void *param)
{
		static int i = 0;
		char *str = "shelly";
		size_t interval = 1;
		
		PurpleB();
		
		if (2 == i)
		{		
			printf(" TaskAddingActionFunc ");
			printf("self remove now \n");
			
			return (SchedulerRemove(((param_t *)param)->scheduler, ((param_t *)param)->uid));
		}
		else
		{

			SchedulerAdd(((param_t *)param)->scheduler, ActionFuncChar, interval / 2 , (void *)str);
			printf(" TaskAddingActionFunc \n");

		}
		
		Reset();
		++i;
		
		return (REPEATED); 		
}

static int ActionFuncChar(void *param)
{
		PurpleB();
		printf("ActionFuncChar param is : %s\n", (char *)param);
		Reset();
		return (SUCCESS); 		
}

static int ActionFuncRepitChar(void *param)
{

		printf("ActionFuncRepitChar param is : %s\n", (char *)param);
		return (REPEATED); 		
}

static int ActionFuncRepitChar1(void *param)
{
		YellowB();
		printf("ActionFuncRepitChar1 interval: 1, ");
		printf("param is : %s  will be remove \n", (char *)param);
		Reset();
		return (REPEATED); 		
}



static int ActionFuncRepit1(void *param)
{
		Purple();
		printf("ActionFuncRepit1 param is : %d\n", *(int *)param);

		return (REPEATED); 		
}

static int ActionFuncRepit2(void *param)
{
		Cyan();
		printf("ActionFuncRepit2 param is : %d\n", *(int *)param);
		return (REPEATED); 		
}

static int ActionFuncRepit3(void *param)
{
		Blue();
		printf("ActionFuncRepit3 param is : %d\n", *(int *)param);
		return (REPEATED); 		
}

static int ActionFuncRepit4(void *param)
{
		Green();
		printf("ActionFuncRepit4 param is : %d\n", *(int *)param);
		return (REPEATED); 		
}
static int ActionFunc1(void *param)
{
		printf("ActionFunc1 param is : %d\n", *(int *)param);
		return (SUCCESS); 		
}

static int ActionFuncError(void *param)
{
 		(void)param;
 		YellowB();
		printf("*****ActionFuncError*****\n");

		return (ACTION_FUNCION_FAILURE); 		
}

static int PrintActionFuncRepit(void *param)
{
		printf("PrintActionFuncRepit param is : %d\n", *(int *)param);
		return (REPEATED); 		
}



static int SelfRemoveFuncWithInterval(void *param)
{
		static int i = 0;
		
		((param_t *)param)->counter = i;
		Reset();
	
		GreenB();
		if (2 == i)
		{
			printf("SelfRemoveFunc interval: 2");
			printf("self remove now \n");
			(SchedulerRemove(((param_t *)param)->scheduler, ((param_t *)param)->uid));
		}
		else
		{
			printf("SelfRemoveFunc interval: 2 ");
			printf("param counter is : %d\n", ((param_t *)param)->counter);
		}
		
		Reset();
		++i;
		
		return (REPEATED); 		
}

static int RemoveFuncWithInterval(void *param)
{
		static int i = 0;
		
		((param_t *)param)->counter = i;
		Reset();
	
		GreenB();
	
		if (2 == i)
		{
			printf("RemoveFunc interval: 2 param counter is : %d \t", ((param_t *)param)->counter);
			printf("removes shelly now\n");
			SchedulerRemove(((param_t *)param)->scheduler, ((param_t *)param)->uid);
		}
		else
		{
			printf("RemoveFunc interval: 2 ");
			printf("param counter is : %d\n", ((param_t *)param)->counter);
		}
		
		Reset();
		++i;
		return (REPEATED); 		
}



static int StopFunc(void *param)
{
		
		SchedulerStop(param);
		
		return (SUCCESS); 		
}


static void Red() 
{
  printf("\033[1;31m");
}

static void Cyan()
{
  printf("\033[0;36m");
}

static void YellowB()
{
  printf("\033[1;33m");
}

static void Yellow()
{
  printf("\033[0;33m");
}

static void Purple() 
{
  printf("\033[0;35m");
}

static void PurpleB() 
{
  printf("\033[1;35m");
}

static void Blue()
{
  printf("\033[0;34m");
}
static void Green() 
{
  printf("\033[0;32m");
}

static void GreenB() 
{
  printf("\033[1;32m");
}


static void Reset() 
{
  printf("\033[0m");
}

