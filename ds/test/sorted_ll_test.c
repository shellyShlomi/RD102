
#include <stdlib.h> /* exit status */
#include <stdio.h>
#include "sorted_ll.h"

static void SortedLLManager();
static int CreateTest();
/*
static int NextPrevEndBeginTest();
static int InsertLLTest();
*/
static int IsMatchInt(const void *data,const void *param);
/*
static int PrintInt(void *data,void *param);
*/

int main()
{
	SortedLLManager();


	return EXIT_SUCCESS;
}

static void SortedLLManager()
{
	CreateTest();

}

static int CreateTest()
{	

	sorted_list_t *list = SortedLLCreate(IsMatchInt);
	
	if (NULL == list)
	{
		printf("CreateTest->SortedLLCreate error at line: %d\n", __LINE__);
		list = NULL;
		
		return EXIT_FAILURE; 
	}
	
	/* test SortedLLIsSameIter on empty list */
	if (1 != SotedLLIsEmpty(list))
	{
		printf("CreateTest->SotedLLIsEmpty error at line: %d\n", __LINE__);
		 
	}
	
	/* test SortedLLIsEmpty on empty list  */
	if (0 != SortedLLSize(list))
	{
		printf("CreateTest->SortedLLSize error at line: %d\n", __LINE__);
		 
	}
	
	if (1 != SortedLLIsSameIter(SortedLLBegin(list), SortedLLEnd(list)))
	{
		printf("CreateTest->SortedLLIsSameIter error at line: %d\n", __LINE__);
		 
	}
	
	SortedLLDestroy(list);
	list = NULL;
	
	return EXIT_SUCCESS;
}
/*
static int NextPrevEndBeginTest()
{	

	sorted_list_t *list = SortedLLCreate(IsMatchInt);
	
	if (NULL == list)
	{
		printf("NextPrevEndBeginTest->SorteLLCreate error at line: %d\n", __LINE__);
		list = NULL;
		
		return EXIT_FAILURE; 
	}
	
	
	

	SortedLLDestroy(list);
	list = NULL;
	
	return EXIT_SUCCESS;
}

static int InsertLLTest()
{	

		sorted_list_t *list = SortedLLCreate(IsMatchInt);
	
	if (NULL == list)
	{
		printf("NextPrevEndBeginTest->SorteLLCreate error at line: %d\n", __LINE__);
		list = NULL;
		
		return EXIT_FAILURE; 
	}
	
	
	

	SortedLLDestroy(list);
	list = NULL;
}


*/

static int IsMatchInt(const void *data,const void *param)
{

	if (*(int *)data == *(int *)param)
	{
		return !EXIT_SUCCESS; 		
	}
	
	return !EXIT_FAILURE; 		
}
/*


static int PrintInt(void *data,void *param)
{
	(void)param;
	
	printf("%d\n", *(int *)data);

	return EXIT_SUCCESS; 
}

*/
