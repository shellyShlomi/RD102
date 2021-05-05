

#include <stdio.h> /* printf */
#include <stdlib.h> /* exit status */

#include "dll.h"

#define SUCCESS 0
#define SUCCESS_BOOL 1

static int DLLManager();
static int PrintInt(void *data,void *param);
static int IsMatchInt(const void *data, const void *param);

int main()
{
	int fail = 0;
	
	fail = DLLManager();
	
	if (fail)
	{	
		printf("DLLManager error at line: %d\n", __LINE__);
		
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}

 


static int DLLManager()
{
	int data = 9;
	int data1 = 19;
	int data2 = 19;

	int data3 = 1;
	int data4 = 2;
	int data5 = 3;
	int data6 = 4;
	int data7 = 5;
	
	int arr[] = {1,2,3,4,5,6};
	size_t size = sizeof(arr)/ sizeof(arr[0]);

	int arr1[] = {7,8,9,10,11,12};
	size_t size1 = sizeof(arr1)/ sizeof(arr1[0]);

	d_list_t *list_for_MultiFind = DLLCreate();
	
	d_list_t *list = DLLCreate();
	d_list_iter_t iter = NULL;
	if (NULL == list)
	{
		printf("DLLCreate error at line: %d\n", __LINE__);
		list = NULL;
		
		return EXIT_FAILURE; 
	}
	
	/* test DLLIsSameIter on empty list */
	if (SUCCESS_BOOL != DLLIsSameIter(DLLBegin(list), DLLEnd(list)))
	{
		printf("DLLCreate error at line: %d\n", __LINE__);
		 
	}
	
	/* test DLLIsEmpty on empty list  */
	if ((!SUCCESS_BOOL) != DLLSize(list))
	{
		printf("DLLSize error at line: %d\n", __LINE__);
		 
	}
	
	/* get the dummy iter - empty list -- for insert */
	iter = DLLEnd(list);
	
	iter = DLLInsert(iter, (void *)&data);
	
	
	if (SUCCESS_BOOL == DLLIsEmpty(list))
	{
		printf("DLLInsert error at line: %d\n", __LINE__);
		 
	}
	
	DLLRemove(iter);
		
	if (SUCCESS_BOOL != DLLIsEmpty(list))
	{
		printf("DLLRemove error at line: %d\n", __LINE__);
		 
	}
 	iter = DLLInsert(DLLBegin(list), (void *)&data1);
	iter = DLLInsert(iter, (void *)&data3);

	iter = DLLInsert(iter, (void *)&data4);

	iter = DLLInsert(iter, (void *)&data5);
	
	
	if (SUCCESS != DLLForEach(DLLBegin(list), DLLEnd(list), PrintInt, NULL))
	{
		printf("DLLForEach error at line: %d\n", __LINE__);
	}
	
	if (4 != DLLSize(list))
	{
		printf("DLLSize error at line: %d\n", __LINE__);
	}

	DLLPushFront(list, (void *)&data6);

	if (*(int *)DLLGetData(DLLBegin(list)) != data6)
	{
		printf("DLLPushFront error at line: %d\n", __LINE__ );
	}
	
	DLLPushBack(list, (void *)&data7);
	
	if (*(int *)DLLGetData(DLLPrev(DLLEnd(list))) != data7)
	{
		printf("DLLPushBack error at line: %d\n", __LINE__);
	}
	
	if (*(int *)DLLPopFront(list) != data6)
	{
		printf("DLLPopFront error at line: %d\n", __LINE__ );
	}
	
	if (*(int *)DLLPopBack(list) != data7)
	{
		printf("DLLPopBack error at line: %d\n", __LINE__);
	}
	
	if (data1 != *(int *)DLLGetData(
				DLLFind(DLLBegin(list), DLLEnd(list), IsMatchInt, (void *)&data2)))
	{
		printf("DLLFind error at line:%d \n", __LINE__);
	}
	
	DLLPushBack(list, (void *)&data7);
	DLLPushFront(list, (void *)&data6);
	data = data5;
	
	if (data != *(int *)DLLGetData(
				DLLFind(DLLBegin(list), DLLEnd(list), IsMatchInt, (void *)&data5)))
	{
		printf("DLLFind error at line:%d \n", __LINE__);
	}
	
	data = data6;
	
	if (data != *(int *)DLLGetData(
				DLLFind(DLLBegin(list), DLLEnd(list), IsMatchInt, (void *)&data6)))
	{
		printf("DLLFind error at line:%d \n", __LINE__);
	}

	iter = DLLInsert(DLLBegin(list), (void *)&data1);
	iter = DLLInsert(iter, (void *)&data3);

	iter = DLLInsert(iter, (void *)&data1);

	iter = DLLInsert(iter, (void *)&data1);
	iter = DLLInsert(iter, (void *)&data3);

	iter = DLLInsert(iter, (void *)&data1);

	iter = DLLInsert(DLLEnd(list), (void *)&data1);
	
	DLLMultiFind(DLLBegin(list), DLLEnd(list), IsMatchInt, (void *)&data1, list_for_MultiFind);
	
	if (6 != DLLSize(list_for_MultiFind))
	{
		printf("DLLMultiFind error at line:%d\n", __LINE__);
	}


	DLLDestroy(list_for_MultiFind);
	
	list_for_MultiFind = DLLCreate();
	
	data = 30;
	
	DLLMultiFind(DLLBegin(list), DLLEnd(list), IsMatchInt, (void *)&data, list_for_MultiFind);
	
	if (0 != DLLSize(list_for_MultiFind))
	{
		printf("DLLMultiFind error at line:%d \n", __LINE__);
	}
	
	DLLDestroy(list);
	
	list = DLLCreate();

	
	size = sizeof(arr)/ sizeof(arr[0]);
	
	while (0 < size)
	{
		DLLPushFront(list, (void *)&arr[size - 1]);
		--size;
	}
	
	DLLDestroy(list_for_MultiFind);
	
	list_for_MultiFind = DLLCreate();

	
	
	while (0 < size1)
	{
		DLLPushFront(list_for_MultiFind, (void *)&arr1[size1 - 1]);
		--size1;
	}
	

	iter = DLLFind(DLLBegin(list), DLLEnd(list), IsMatchInt, (void *)&data5);

	if (DLLPrev(DLLEnd(list_for_MultiFind)) != DLLSplice(iter, DLLBegin(list_for_MultiFind), 
								DLLEnd(list_for_MultiFind)))
	{
		printf("DLLSplice error at line: %d\n", __LINE__);
	}

	
	DLLDestroy(list);
	
	list = DLLCreate();

	
	size = sizeof(arr)/ sizeof(arr[0]);
	
	while (0 < size)
	{
		DLLPushFront(list, (void *)&arr[size - 1]);
		--size;
	}
	
	DLLDestroy(list_for_MultiFind);
	
	list_for_MultiFind = DLLCreate();

	size1 =  sizeof(arr1)/ sizeof(arr1[0]);
	
	while (0 < size1)
	{
		DLLPushFront(list_for_MultiFind, (void *)&arr1[size1 - 1]);
		--size1;
	}

	if (DLLPrev(DLLEnd(list_for_MultiFind)) != 	DLLSplice(DLLBegin(list), 													DLLBegin(list_for_MultiFind), 
												DLLEnd(list_for_MultiFind)))
	{
		printf("DLLSplice error at line: %d\n", __LINE__);
	}

	printf("\n");


	DLLDestroy(list);

	DLLDestroy(list_for_MultiFind);
	list = NULL;
	list_for_MultiFind = NULL;
	
	iter = NULL;
	

	return EXIT_SUCCESS; 
}

static int IsMatchInt(const void *data,const void *param)
{

	if (*(int *)data == *(int *)param)
	{
		return !EXIT_SUCCESS; 		
	}
	
	return !EXIT_FAILURE; 		
}



static int PrintInt(void *data,void *param)
{
	(void)param;
	
	printf("%d\n", *(int *)data);

	return EXIT_SUCCESS; 
}


