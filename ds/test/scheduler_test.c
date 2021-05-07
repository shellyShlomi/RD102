
#include <stdlib.h> /* exit status */
#include <stdio.h> /* printf */
#include <unistd.h> /* sleep */

#include "scheduler.h"
#include "task.h"
#include "uid.h"

#define SIEZ_UID_ARR 10
static void SchedulerCreateTest();
static void SchedulerRunTest();
static void SchedulerRun2Test();
static void SchedulerAddRemoveTest();
static void NoIntervalRunTest();

static int RemoveFuncWithInterval();
/*static int RemoveFunc(void *param);*/
static int ActionFunc1(void *param);
static int StopFunc(void *param);
static int ActionFuncRepit(void *param);
static int PrintActionFuncRepit(void *param);


typedef struct remove
{
	scheduler_t *scheduler;
	int counter;
	ilrd_uid_t uid;
	
}remove_t;

int main()
{

	SchedulerCreateTest();
	SchedulerAddRemoveTest();
	NoIntervalRunTest();
	SchedulerRunTest();
	SchedulerRun2Test();
	
	return EXIT_SUCCESS;
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
	ilrd_uid_t arr_uid[SIEZ_UID_ARR];
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


/*remove with no repites & run*/
static void NoIntervalRunNoStopTest()
{	

	int arr[] = {1, 2, 5, 3, 1, 2};
	size_t arr_interval[] = {1, 2, 5, 3, 1, 2};
	size_t size = sizeof(arr)/ sizeof(arr[0]);
	ilrd_uid_t arr_uid[SIEZ_UID_ARR];
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
	
	printf("NoIntervalRunTest->SchedulerRun return: %d \n",SchedulerRun(scheduler)); 
	
	if (0 != SchedulerSize(scheduler))
	{
		printf("SchedulerAddTest->SchedulerIsEmpty error at line: %d\n", __LINE__);
	}
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
	ilrd_uid_t arr_uid[SIEZ_UID_ARR];
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

	arr_uid[i + 1] = SchedulerAdd(scheduler, ActionFuncRepit, *(arr_interval), (void *)str);
	
	printf("\nNoIntervalRunTest\n \n"); 
	
	printf("NoIntervalRunTest->SchedulerRun return: %d \n",SchedulerRun(scheduler)); 
	
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
	ilrd_uid_t arr_uid[SIEZ_UID_ARR];
	remove_t remove = {NULL};
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
		arr_uid[i] = SchedulerAdd(scheduler, PrintActionFuncRepit, *(arr_interval + i), (void *)(arr + i));

	}
	
	if (size != SchedulerSize(scheduler))
	{
		printf("SchedulerRunTest->SchedulerAdd error at line: %d %lu\n", __LINE__,SchedulerSize(scheduler));
	}
	
	arr_uid[i] = SchedulerAdd(scheduler, ActionFuncRepit, *(arr_interval), (void *)str);

	/*task remove herself*/
	
	++i;
	
	arr_uid[i] = SchedulerAdd(scheduler, RemoveFuncWithInterval, interval1, (void *)&remove);
	
	remove.scheduler = scheduler;
	remove.uid = arr_uid[i];
	remove.counter = 0;
	
	++i;
	
	arr_uid[i] = SchedulerAdd(scheduler, StopFunc, interval * 2, scheduler);

	printf("\nSchedulerRunTest\n \n"); 
	
	printf("SchedulerRun return: %d \n",SchedulerRun(scheduler)); 
	
	if (size + 1 != SchedulerSize(scheduler))
	{
		printf("SchedulerRunTest->SchedulerAdd error at line: %d\n", __LINE__);
	}

	
	for (i = 0; !SchedulerIsEmpty(scheduler); ++i)
	{
		if (7 == i)
		{
		/* the stop task that Destroy hearself*/
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
	
	SchedulerDestroy(scheduler);
	scheduler = NULL;
	
	return ;

}


/*remove with repites*/
static void SchedulerRun2Test()
{	

	int arr[] = {1, 2, 5, 3, 1, 2};
	size_t arr_interval[] = {1, 2, 5, 3, 1, 2};
	char *str = "shelly";
	size_t size = sizeof(arr)/ sizeof(arr[0]);
	ilrd_uid_t arr_uid[SIEZ_UID_ARR];
	size_t interval = 5;
	size_t i = 0;
	
	scheduler_t *scheduler = SchedulerCreate();
	
	if (NULL == scheduler)
	{
		printf("SchedulSchedulerRun2TesterRunTest->SchedulerCreate error at line: %d\n", __LINE__);

		
		return ; 
	}

	for (i = 0; i < size; ++i)
	{
		arr_uid[i] = SchedulerAdd(scheduler, PrintActionFuncRepit, *(arr_interval + i), (void *)(arr + i));

	}
	
	if (size != SchedulerSize(scheduler))
	{
		printf("SchedulerRun2Test->SchedulerAdd error at line: %d\n", __LINE__);
	}
	
	arr_uid[i] = SchedulerAdd(scheduler, StopFunc, interval, scheduler);

	arr_uid[i + 1] = SchedulerAdd(scheduler, ActionFuncRepit, *(arr_interval), (void *)str);
	
	printf("\nSchedulerRun2Test\n \n"); 
	
	printf("SchedulerRun2Test->SchedulerRun return: %d \n",SchedulerRun(scheduler)); 
	
	if (size + 1 != SchedulerSize(scheduler))
	{
		printf("SchedulerRun2Test->SchedulerAdd error at line: %d\n", __LINE__);
	}

	
	for (i = 0; i < size + 2; ++i)
	{
		if (6 == i)
		{
		
		/* the stop task that Destroy hearself*/
			if (1 != SchedulerRemove(scheduler, arr_uid[i]))
			{
				printf("SchedulerRun2Test->SchedulerRemove ");
				printf("error at line: %d index: %ld %ld\n", __LINE__,i, SchedulerSize(scheduler)); 	
			}
			
			++i;
		}

		if (0 != SchedulerRemove(scheduler, arr_uid[i]))
		{
			printf("SchedulerRun2Test->SchedulerRemove ");
			printf("error at line: %d index: %ld %ld\n", __LINE__,i, SchedulerSize(scheduler)); 	
		}
	}
	
	if (0 != SchedulerSize(scheduler))
	{
		printf("SchedulerRun2Test->SchedulerSize error at line: %d \n", __LINE__);
	}
	
	SchedulerDestroy(scheduler);
	scheduler = NULL;
	
	return ;

}

static int ActionFuncRepit(void *param)
{
		
		printf("\nActionFuncRepit param is : %s\n", (char *)param);
		return (2); 		
}

static int ActionFunc1(void *param)
{
		printf("\nActionFunc1 param is : %d\n", *(int *)param);
		return (0); 		
}

static int PrintActionFuncRepit(void *param)
{
		printf("\nPrintActionFuncRepit param is : %d\n", *(int *)param);
		return (2); 		
}

static int RemoveFuncWithInterval(void *param)
{
		static int i = 0;
		
		((remove_t *)param)->counter = i;
	
		printf("\nRemoveFuncWithInterval param is : %d\n", ((remove_t *)param)->counter);
		++i;
		
		if (2 == i)
		{
			return (SchedulerRemove(((remove_t *)param)->scheduler, ((remove_t *)param)->uid));
		}
	
		return (2); 		
}

/*
static int RemoveFunc(void *param)
{
		SchedulerRemove(((remove_t *)param)->scheduler, ((remove_t *)param)->uid);
		
		return (0); 		
}


*/
static int StopFunc(void *param)
{
		
		SchedulerStop(param);
		
		return (0); 		
}


