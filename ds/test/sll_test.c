
#include <stdio.h> /* printf */
#include <stdlib.h> /* exit status */

#define SUCCESS 0
#define SUCCESS_BOL 1


#include "sll.h"

static int SLLManager();


static int MatchInt(const void *data,void *param);
static int PrintInt(void *data,void *param);


int main()
{
	int fail = 0;
	
	fail = SLLManager();
	
	if (fail)
	{	
		printf("SLLManager error at line: %d\n", __LINE__);
		
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}


static int SLLManager()
{

	int data = 9;
	int data1 = 19;
	int data2 = 19;


	int data3 = 1;
	int data4 = 2;
	int data5 = 3;
	int data6 = 4;
	int data7 = 5;
	int data8 = 6;
	
	s_list_t *list_for_app = SLLCreate();
	
	s_list_t *list = SLLCreate();
	s_list_iter_t iter = NULL;
	
	if (NULL == list)
	{
		printf("SLLCreate error at line: %d\n", __LINE__);
		list = NULL;
		
		return EXIT_FAILURE; 
	}
	
	/* test SLLIsSameIter on empty list */
	if (SUCCESS_BOL != SLLIsSameIter(SLLBegin(list), SLLEnd(list)))
	{
		printf("SLLCreate error at line: %d\n", __LINE__);
		 
	}
	
	/* test SLLIsEmpty on empty list  */
	if (SUCCESS_BOL != SLLIsEmpty(list))
	{
		printf("SLLIsEmpty error at line: %d\n", __LINE__);
		 
	}
	
	/* get the dummy iter - empty list -- for insert */
	iter = SLLEnd(list);
	
	iter = SLLInsert(iter, (void *)&data);
	
	
	if (SUCCESS_BOL == SLLIsEmpty(list))
	{
		printf("SLLInsert error at line: %d\n", __LINE__);
		 
	}
	
	SLLRemove(iter);
		
	if (SUCCESS_BOL != SLLIsEmpty(list))
	{
		printf("SLLRemove error at line: %d\n", __LINE__);
		 
	}
	
	iter = SLLInsert(SLLBegin(list), (void *)&data1);
	iter = SLLInsert(iter, (void *)&data3);
	iter = SLLInsert(iter, (void *)&data4);
	iter = SLLInsert(iter, (void *)&data5);

	if (SUCCESS != SLLForEach(SLLBegin(list), SLLEnd(list), PrintInt, NULL))
	{
		printf("SLLForEach error at line: %d\n", __LINE__);
	}
	
	if (4 != SLLCount(list))
	{
		printf("SLLCount error at line: %d\n", __LINE__);
	}
	
	if (data1 != *(int *)SLLGetData(
				SLLFind(SLLBegin(list), SLLEnd(list), MatchInt, (void *)&data2)))
	{
		printf("SLLFind error at line:%d \n", __LINE__);
	}
	
	iter = SLLInsert(SLLBegin(list_for_app), (void *)&data6);
	iter = SLLInsert(iter, (void *)&data7);
	iter = SLLInsert(iter, (void *)&data8);
	
	SLLAppend(list, list_for_app);
	
	if (7 != SLLCount(list) || 0 != SLLCount(list_for_app))
	{
		printf("SLLAppend error at line:%d \n", __LINE__);
	}
	
	SLLAppend(list, list_for_app);
	if (7 != SLLCount(list) || 0 != SLLCount(list_for_app))
	{
		printf("SLLAppend error at line:%d \n", __LINE__);
	}
	
	SLLAppend(list_for_app, list);
	
	if (0 != SLLCount(list) || 7 != SLLCount(list_for_app))
	{
		printf("SLLAppend error at line:%d \n", __LINE__);
	}
	
	SLLDestroy(list);
	SLLDestroy(list_for_app);
	list = NULL;
	list_for_app = NULL;
	
	iter = NULL;
	

	return EXIT_SUCCESS; 
}

static int MatchInt(const void *data,void *param)
{

	if (*(int *)data == *(int *)param)
	{
		return EXIT_SUCCESS; 		
	}
	
	return EXIT_FAILURE; 		
}




static int PrintInt(void *data,void *param)
{
	(void)param;
	
	printf("%d\n", *(int *)data);

	return EXIT_SUCCESS; 
}


