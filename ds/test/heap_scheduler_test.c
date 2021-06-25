
#include <stdlib.h> /* exit status */
#include <stdio.h> /* printf */
#include <unistd.h> /* sleep */

#include "heap_scheduler.h"
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


static void HSchedulerCreateTest();
static void HSchedulerRunTest();
static void NoIntervalRunNoStopTest();
static void NoIntervalRunTest();
static void RepitesRunTest();
static void HSchedulerAddRemoveTest();
static void TaskAddingHSchedulerRunTest();
static void TaskErrorHSchedulerRunTest();

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
	HSchedulerCreateTest();
	HSchedulerAddRemoveTest();
	NoIntervalRunNoStopTest();
	NoIntervalRunTest();
	RepitesRunTest();
	HSchedulerRunTest();
	TaskAddingHSchedulerRunTest();
	TaskErrorHSchedulerRunTest();
	
	return;

}


static void HSchedulerCreateTest()
{	
	scheduler_t *scheduler = HSchedulerCreate();
	
	if (NULL == scheduler)
	{
		printf("HSchedulerCreateTest->HSchedulerCreate error at line: %d\n", __LINE__);
		
		return ; 
	}
	
	/* test HSchedulerIsEmpty on empty list */
	if (1 != HSchedulerIsEmpty(scheduler))
	{
		printf("HSchedulerCreateTest->HSchedulerIsEmpty error at line: %d\n", __LINE__);
	}
	
	/* test HSchedulerSize on empty list  */
	if (0 != HSchedulerSize(scheduler))
	{
		printf("HSchedulerCreateTest->HSchedulerSize error at line: %d\n", __LINE__);
	}
	
	HSchedulerDestroy(scheduler);
	scheduler = NULL;
	
	return ;
}

/*remove with no repites*/
static void HSchedulerAddRemoveTest()
{	

	int arr[] = {1, 2, 5, 3, 1, 2};
	size_t arr_interval[] = {1, 2, 5, 3, 1, 2};
	size_t size = sizeof(arr)/ sizeof(arr[0]);
	ilrd_uid_t arr_uid[SIEZ_UID_ARR] = {0};
	size_t i = 0;
	
	scheduler_t *scheduler = HSchedulerCreate();
	
	if (NULL == scheduler)
	{
		printf("HSchedulerCreateTest->HSchedulerCreate error at line: %d\n", __LINE__);

		
		return ; 
	}

	for (i = 0; i < size; ++i)
	{
		arr_uid[i] = HSchedulerAdd(scheduler, ActionFunc1, *(arr_interval + i), (void *)(arr + i));

	}
	
	if (size != HSchedulerSize(scheduler))
	{
		printf("HSchedulerAddTest->HSchedulerAdd error at line: %d %lu\n", __LINE__,HSchedulerSize(scheduler));
	}
	
	for (i = 0; i < size; ++i)
	{
		if (0 != HSchedulerRemove(scheduler, arr_uid[i]))
		{
			printf("HSchedulerAddTest->HSchedulerRemove ");
			printf("error at line: %d index: %ld %ld\n", __LINE__,i, HSchedulerSize(scheduler)); 	
		}

	}

	if (0 != HSchedulerSize(scheduler))
	{
		printf("HSchedulerAddTest->HSchedulerIsEmpty error at line: %d\n", __LINE__);
	}
	HSchedulerDestroy(scheduler);
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
	
	scheduler_t *scheduler = HSchedulerCreate();
	
	if (NULL == scheduler)
	{
		printf("RepitesRunTest->HSchedulerCreate error at line: %d\n", __LINE__);

		
		return ; 
	}

	for (i = 0; i < size; ++i)
	{
		arr_uid[i] = HSchedulerAdd(scheduler, PrintActionFuncRepit, *(arr_interval + i), (void *)(arr + i));

	}
	
	if (size != HSchedulerSize(scheduler))
	{
		printf("RepitesRunTest->HSchedulerAdd error at line: %d\n", __LINE__);
	}
	
	arr_uid[i] = HSchedulerAdd(scheduler, StopFunc, interval, scheduler);

	arr_uid[i + 1] = HSchedulerAdd(scheduler, ActionFuncRepitChar, *(arr_interval), (void *)str);

	Yellow();

	printf("\nRepitesRunTest\n \n"); 
	
	printf("\nHSchedulerRun return: %d \n\n",HSchedulerRun(scheduler)); 
	
	if (size + 1 != HSchedulerSize(scheduler))
	{
		printf("RepitesRunTest->HSchedulerAdd error at line: %d\n", __LINE__);
	}

	
	for (i = 0; i < size + 2; ++i)
	{
		if (6 == i)
		{
		
			if (1 != HSchedulerRemove(scheduler, arr_uid[i]))
			{
				printf("RepitesRunTest->HSchedulerRemove ");
				printf("error at line: %d index: %ld %ld\n", __LINE__,i, HSchedulerSize(scheduler)); 	
			}
			
			++i;
		}

		if (0 != HSchedulerRemove(scheduler, arr_uid[i]))
		{
			printf("RepitesRunTest->HSchedulerRemove ");
			printf("error at line: %d index: %ld %ld\n", __LINE__,i, HSchedulerSize(scheduler)); 	
		}
	}
	
	if (0 != HSchedulerSize(scheduler))
	{
		printf("RepitesRunTest->HSchedulerSize error at line: %d \n", __LINE__);
	}
	
	Reset();
	
	HSchedulerDestroy(scheduler);
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
	
	scheduler_t *scheduler = HSchedulerCreate();
	
	if (NULL == scheduler)
	{
		printf("HSchedulerCreateTest->HSchedulerCreate error at line: %d\n", __LINE__);

		
		return ; 
	}

	for (i = 0; i < size; ++i)
	{
		HSchedulerAdd(scheduler, ActionFunc1, *(arr_interval + i), (void *)(arr + i));

	}
	
	if (size != HSchedulerSize(scheduler))
	{
		printf("HSchedulerAddTest->HSchedulerAdd error at line: %d %lu\n", __LINE__,HSchedulerSize(scheduler));
	}
	
	
	Red();
	sleep(3);
	printf("\nNoIntervalRunNoStopTest delay of 3 sec\n \n"); 
	
	printf("\nHSchedulerRun return: %d \n\n",HSchedulerRun(scheduler)); 
	
	if (0 != HSchedulerSize(scheduler))
	{
		printf("HSchedulerAddTest->HSchedulerIsEmpty error at line: %d\n", __LINE__);
	}
	Reset();
	
	HSchedulerDestroy(scheduler);
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
	
	scheduler_t *scheduler = HSchedulerCreate();
	
	if (NULL == scheduler)
	{
		printf("NoIntervalRunTest->HSchedulerCreate error at line: %d\n", __LINE__);

		
		return ; 
	}

	for (i = 0; i < size; ++i)
	{
		arr_uid[i] = HSchedulerAdd(scheduler, ActionFunc1, *(arr_interval + i), (void *)(arr + i));

	}
	
	if (size != HSchedulerSize(scheduler))
	{
		printf("NoIntervalRunTest->HSchedulerAdd error at line: %d\n", __LINE__);
	}
	
	arr_uid[i] = HSchedulerAdd(scheduler, StopFunc, interval, scheduler);

	arr_uid[i + 1] = HSchedulerAdd(scheduler, ActionFuncRepitChar, *(arr_interval), (void *)str);
	
	Blue();
	printf("\nNoIntervalRunTest\n \n"); 
	
	printf("\nHSchedulerRun return: %d \n\n",HSchedulerRun(scheduler)); 
	
	if (size/2 != HSchedulerSize(scheduler))
	{
		printf("NoIntervalRunTest->HSchedulerAdd error at line: %d\n", __LINE__);
	}

	
	for (i = 0; i < size + 2; ++i)
	{
		if (6 == i || ( 2 != i && 4 != i && 7 != i))
		{
		
		/* the stop task that Destroy hearself*/
			if (1 != HSchedulerRemove(scheduler, arr_uid[i]))
			{
				printf("NoIntervalRunTest->HSchedulerRemove ");
				printf("error at line: %d index: %ld %ld\n", __LINE__,i, HSchedulerSize(scheduler)); 	
			}
			
			continue;
		}

		if (0 != HSchedulerRemove(scheduler, arr_uid[i]))
		{
			printf("NoIntervalRunTest->HSchedulerRemove ");
			printf("error at line: %d index: %ld %ld\n", __LINE__,i, HSchedulerSize(scheduler)); 	
		}
	}
	
	if (0 != HSchedulerSize(scheduler))
	{
		printf("NoIntervalRunTest->HSchedulerSize error at line: %d \n", __LINE__);
	}
	
	Reset();
	
	HSchedulerDestroy(scheduler);
	scheduler = NULL;
	
	return ;

}



/*task that Destroy herself and other tasks with repites*/
static void HSchedulerRunTest()
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
	
	scheduler_t *scheduler = HSchedulerCreate();
	
	if (NULL == scheduler)
	{
		printf("HSchedulerRunTest->HSchedulerCreate error at line: %d\n", __LINE__);

		
		return ; 
	}

	for (i = 0; i < size; ++i)
	{
		arr_uid[i] = HSchedulerAdd(scheduler, ActionFuncRepit1, *(arr_interval + i), (void *)(arr + i));

	}
	
	if (size != HSchedulerSize(scheduler))
	{
		printf("HSchedulerRunTest->HSchedulerAdd error at line: %d %lu\n", __LINE__,HSchedulerSize(scheduler));
	}
	
	arr_uid[i] = HSchedulerAdd(scheduler, ActionFuncRepitChar, *(arr_interval), (void *)str);

	/*task remove herself*/
	
	++i;
	
	arr_uid[i] = HSchedulerAdd(scheduler, SelfRemoveFuncWithInterval, interval1, (void *)&remove);
	
	remove.scheduler = scheduler;
	remove.uid = arr_uid[i];
	remove.counter = 0;
	
	++i;
	
	arr_uid[i] = HSchedulerAdd(scheduler, StopFunc, interval * 2, scheduler);

	Purple();

	printf("\nHSchedulerRunTest with task that is selfDestroy \n \n"); 
	
	printf("\nHSchedulerRun return: %d \n\n",HSchedulerRun(scheduler)); 
	
	if (size + 1 != HSchedulerSize(scheduler))
	{
		printf("HSchedulerRunTest->HSchedulerAdd error at line: %d \n", __LINE__);
	}

	
	for (i = 0; !HSchedulerIsEmpty(scheduler); ++i)
	{
		if (7 == i)
		{

			if (1 != HSchedulerRemove(scheduler, arr_uid[i]))
			{	
				printf("HSchedulerRunTest->HSchedulerRemove ");
				printf("error at line: %d index: %ld %ld\n", __LINE__,i, HSchedulerSize(scheduler)); 	
			}
			
			++i;
		}
		
		if (0 != HSchedulerRemove(scheduler, arr_uid[i]))
		{
			printf("HSchedulerRunTest->HSchedulerRemove ");
			printf("error at line: %d index: %ld %ld\n", __LINE__,i, HSchedulerSize(scheduler)); 	
		}
	}
	
	if (0 != HSchedulerSize(scheduler))
	{
		printf("HSchedulerRunTest->HSchedulerSize error at line: %d \n", __LINE__);
	}
	
	Reset();
	
	HSchedulerDestroy(scheduler);
	
	scheduler = HSchedulerCreate();
	
	if (NULL == scheduler)
	{
		printf("HSchedulerRunTest->HSchedulerCreate error at line: %d\n", __LINE__);

		
		return ; 
	}

	for (i = 0; i < size; ++i)
	{
		arr_uid[i] = HSchedulerAdd(scheduler, ActionFuncRepit2, *(arr_interval + i), (void *)(arr + i));

	}
	
	if (size != HSchedulerSize(scheduler))
	{
		printf("HSchedulerRunTest->HSchedulerAdd error at line: %d %lu\n", __LINE__,HSchedulerSize(scheduler));
	}
	
	arr_uid[i] = HSchedulerAdd(scheduler, ActionFuncRepitChar1, *(arr_interval), (void *)str);

	/*task remove other tasks */
	
	++i;
	
	arr_uid[i] = HSchedulerAdd(scheduler, RemoveFuncWithInterval, interval1, (void *)&remove);
	
	remove.scheduler = scheduler;
	remove.uid = arr_uid[i - 1]; /*removal of str*/
	remove.counter = 0;
	
	++i;
	
	arr_uid[i] = HSchedulerAdd(scheduler, StopFunc, interval * 2, scheduler);

	Cyan();

	printf("\nHSchedulerRunTest with task that Destroy other tasks\nshelly will be removed \n\n"); 
	
	printf("\nHSchedulerRun return: %d \n\n",HSchedulerRun(scheduler)); 
	
	HSchedulerClear(scheduler);
	
	if (0 != HSchedulerSize(scheduler))
	{
		printf("HSchedulerRunTest->HSchedulerAdd error at line: %d\n", __LINE__);
	}
	Reset();
	
	HSchedulerDestroy(scheduler);
	scheduler = NULL;
	
	return ;

}


/*task that addes other tasks and remove herself after 2 times*/
static void TaskAddingHSchedulerRunTest()
{	

	int arr[] = {1, 2, 5, 3, 1, 2};
	size_t arr_interval[] = {1, 2, 5, 3, 1, 2};
	size_t size = sizeof(arr)/ sizeof(arr[0]);
	ilrd_uid_t arr_uid[SIEZ_UID_ARR] = {0};
	param_t adding = {NULL};
	size_t interval = 5;
	size_t interval1 = 2;
	size_t i = 0;
	
	scheduler_t *scheduler = HSchedulerCreate();

	
	if (NULL == scheduler)
	{
		printf("TaskAddingHSchedulerRunTest->HSchedulerCreate error at line: %d\n", __LINE__);

		
		return ; 
	}

	for (i = 0; i < size; ++i)
	{
		arr_uid[i] = HSchedulerAdd(scheduler, ActionFuncRepit3, *(arr_interval + i), (void *)(arr + i));

	}
	
	if (size != HSchedulerSize(scheduler))
	{
		printf("TaskAddingHSchedulerRunTest->HSchedulerAdd error at line: %d\n", __LINE__);
	}
	
	/*task that addes other tasks and remove herself after 2 times*/
	
	++i;
	
	arr_uid[i] = HSchedulerAdd(scheduler, TaskAddingActionFunc, interval1, (void *)&adding);
	
	adding.scheduler = scheduler;
	adding.uid = arr_uid[i]; /*removal of herself*/
	adding.counter = 0;
		
	++i;
	
	arr_uid[i] = HSchedulerAdd(scheduler, StopFunc, interval * 2, scheduler);

	Blue();

	printf("\nTaskAddingHSchedulerRunTest with task that add other tasks "); 
	printf("and after 2 times remove herself \n\n"); 
	printf("\nHSchedulerRun return: %d \n\n",HSchedulerRun(scheduler)); 
	
	
	
	HSchedulerClear(scheduler);
	
	if (0 != HSchedulerSize(scheduler))
	{
		printf("TaskAddingHSchedulerRunTest->HSchedulerAdd error at line: %d\n", __LINE__);
	}
	Reset();
	
	HSchedulerDestroy(scheduler);
	scheduler = NULL;
	
	return ;

}

/*task that returns error*/
static void TaskErrorHSchedulerRunTest()
{	

	int arr[] = {1, 2, 5, 3, 1, 2};
	size_t arr_interval[] = {1, 2, 5, 3, 1, 2};
	size_t size = sizeof(arr)/ sizeof(arr[0]);
	size_t interval = 5;
	size_t i = 0;
	
	scheduler_t *scheduler = HSchedulerCreate();

	
	if (NULL == scheduler)
	{
		printf("TaskErrorHSchedulerRunTest->HSchedulerCreate error at line: %d\n", __LINE__);

		
		return ; 
	}

	for (i = 0; i < size; ++i)
	{
		HSchedulerAdd(scheduler, ActionFuncRepit4, *(arr_interval + i), (void *)(arr + i));

	}
	
	if (size != HSchedulerSize(scheduler))
	{
		printf("TaskErrorHSchedulerRunTest->HSchedulerAdd error at line: %d\n", __LINE__);
	}
	
	HSchedulerAdd(scheduler, ActionFuncError, *(arr_interval), NULL);
	
	++i;
	
	HSchedulerAdd(scheduler, StopFunc, interval * 2, scheduler);

	Green();

	printf("\nTaskErrorHSchedulerRunTest with task that returns error \n\n"); 
	printf("\nHSchedulerRun return: %d \n\n",HSchedulerRun(scheduler)); 
	
	
	
	HSchedulerClear(scheduler);
	
	if (0 != HSchedulerSize(scheduler))
	{
		printf("TaskErrorHSchedulerRunTest->HSchedulerAdd error at line: %d\n", __LINE__);
	}
	Reset();
	
	HSchedulerDestroy(scheduler);
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
			
			return (HSchedulerRemove(((param_t *)param)->scheduler, ((param_t *)param)->uid));
		}
		else
		{

			HSchedulerAdd(((param_t *)param)->scheduler, ActionFuncChar, interval / 2 , (void *)str);
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
			(HSchedulerRemove(((param_t *)param)->scheduler, ((param_t *)param)->uid));
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
			HSchedulerRemove(((param_t *)param)->scheduler, ((param_t *)param)->uid);
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
		
		HSchedulerStop(param);
		
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

