
#include <stdio.h> /* printf */
#include <stdlib.h> /* exit status */

#define SUCCESS 0
#define SUCCESS_BOL 1

typedef struct s_list_node *s_list_node_ptr_t;	

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
	
	s_list_t *list = SLLCreate();
	s_list_node_ptr_t iter = NULL;
	
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
	
	iter = SLLInsert(SLLBegin(list), (void *)&data);
	iter = SLLInsert(iter, (void *)&data1);
	iter = SLLInsert(iter, (void *)&data);
	iter = SLLInsert(iter, (void *)&data);

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
	
	SLLDestroy(list);
	list = NULL;

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


