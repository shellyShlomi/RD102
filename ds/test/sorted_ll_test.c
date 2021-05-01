
#include <stdlib.h> /* exit status */
#include <stdio.h>	/* printf */

#include "sorted_ll.h"

static void SortedLLManager();
static int CreateEndBeginTest();
static int InsertNextPrevLLTest();
static int ForEachFindIfTest();
static int PopBackPopFrontTest();
static int MergeTest();

static int CmpFunc(const void *data1, const void *data2);

static int IsMatchInt(const void *data, const void *param);
static int Add(void *data,void *param);
#ifdef DEBUG
static int IsSameAddrese(d_list_iter_t data, d_list_iter_t param);

#else
	
#endif	


int main()
{
	SortedLLManager();


	return EXIT_SUCCESS;
}

static void SortedLLManager()
{
	CreateEndBeginTest();
	InsertNextPrevLLTest();
	ForEachFindIfTest();
	PopBackPopFrontTest();
	MergeTest();

	return;
}

static int CreateEndBeginTest()
{	
	sorted_list_t *list = SortedLLCreate(CmpFunc);
	
	if (NULL == list)
	{
		printf("CreateEndBeginTest->SortedLLCreate error at line: %d\n", __LINE__);
		list = NULL;
		
		return EXIT_FAILURE; 
	}
	
	/* test SortedLLIsSameIter on empty list */
	if (1 != SortedLLIsEmpty(list))
	{
		printf("CreateEndBeginTest->SotedLLIsEmpty error at line: %d\n", __LINE__);
	}
	
	/* test SortedLLIsEmpty on empty list  */
	if (0 != SortedLLSize(list))
	{
		printf("CreateEndBeginTest->SortedLLSize error at line: %d\n", __LINE__);
	}
	
	if (1 != SortedLLIsSameIter(SortedLLBegin(list), SortedLLEnd(list)))
	{
		printf("CreateEndBeginTest->SortedLLIsSameIter, ");
		printf("CreateEndBeginTest->SortedLLBegin and SortedLLEnd ");
		printf("error at line: %d\n", __LINE__);
	}
	
	SortedLLDestroy(list);
	list = NULL;
	
	return EXIT_SUCCESS;
}


static int PopBackPopFrontTest()
{	

	int arr[] = {4, 1, 6, 1, 7, 8};
	int arr_exp[] = {1, 1, 4, 6, 7, 8};
	size_t size = sizeof(arr)/ sizeof(arr[0]);
	
	size_t i = 0;
	sorted_list_t *list = SortedLLCreate(CmpFunc);

	if (NULL == list)
	{
		printf("PopBackPopFrontTest->SorteLLCreate error at line: %d\n", __LINE__);
		list = NULL;
		
		return EXIT_FAILURE; 
	}


	for (i = 0; i < size; ++i)
	{
		SortedLLInsert(list, (void *)(arr + i));
	}
	
	if (size != SortedLLSize(list))
	{
		printf("PopBackPopFrontTest->SortedLLInsert error at line: %d\n", __LINE__);
	}
		
	
	for (i = 0; i < size; ++i)
	{
		if (arr_exp[i] != *(int *)SortedLLPopFront(list))
		{
			printf("PopBackPopFrontTest->SortedLLPopFront ");
			printf("error at line: %d index: %ld\n", __LINE__, i); 	
		}
	}
	
	if (1 != SortedLLIsEmpty(list))
	{
		printf("PopBackPopFrontTest->SortedLLPopFront error at line: %d\n", __LINE__);
	}
	for (i = 0; i < size; ++i)
	{
		SortedLLInsert(list, (void *)(arr + i));
	}
	
	if (size != SortedLLSize(list))
	{
		printf("PopBackPopFrontTest->SortedLLInsert error at line: %d\n", __LINE__);
	}
		
	
	for (i = size; 0 < i; --i)
	{
		if (arr_exp[i - 1] != *(int *)SortedLLPopBack(list))
		{
			printf("PopBackPopFrontTest->SortedLLPopBack ");
			printf("error at line: %d index: %ld\n", __LINE__, i); 	
		}
	}
	
	if (1 != SortedLLIsEmpty(list))
	{
		printf("PopBackPopFrontTest->SortedLLPopBack error at line: %d\n", __LINE__);
	}
	
	SortedLLDestroy(list);
	list = NULL;
	
	return EXIT_SUCCESS;

}



static int InsertNextPrevLLTest()
{	
	int arr[] = {4, 1, 6, 1, 7, 8};
	int arr_exp[] = {1, 1, 4, 6, 7, 8};
	size_t size = sizeof(arr)/ sizeof(arr[0]);
	
	size_t i = 0;
	sorted_list_t *list = SortedLLCreate(CmpFunc);
	sorted_list_iter_t iter1 = {NULL};
	sorted_list_iter_t iter2 = {NULL};

	if (NULL == list)
	{
		printf("InsertNextPrevLLTest->SorteLLCreate error at line: %d\n", __LINE__);
		list = NULL;
		
		return EXIT_FAILURE; 
	}

	/* test Insert */
	for (i = 0; i < size; ++i)
	{
		iter1 = SortedLLInsert(list, (void *)(arr + i));
	
		if (1 == SortedLLIsSameIter(iter1, SortedLLEnd(list)))
		{
			printf("InsertNextPrevLLTest->SortedLLInsert error at line: ");
			printf("%d index: \n", __LINE__); 
		}
		
	}
	
	
		/* test GetData && Next Prev */
	{		
		iter1 = SortedLLBegin(list); 

		for (i = 0; i < size; ++i)
		{
			if (arr_exp[i] != *(int *)SortedLLGetData(iter1))
			{
				printf("InsertNextPrevLLTest->SortedLLInsert and SortedLLGetData ");
				printf("error at line: %d index: %ld\n", __LINE__, i); 	
			}
			
			iter2 = iter1;
			iter1 = SortedLLNext(iter1);
			
			if (1 == SortedLLIsSameIter(iter1, iter2))
			{
				printf("InsertNextPrevLLTest->SortedLLNext ");
				printf("error at line: %d index: %ld\n", __LINE__, i); 
			}
		}
			
		iter1 = SortedLLPrev(SortedLLEnd(list)); 

		for (i = size; 0 < i; --i)
		{
			if (arr_exp[i - 1] != *(int *)SortedLLGetData(iter1))
			{
				printf("InsertNextPrevLLTest->SortedLLPrev ");
				printf("error at line: %d index: %ld\n", __LINE__, i); 	
			}
			
			iter2 = iter1;
			iter1 = SortedLLPrev(iter1);
			
			if (1 == SortedLLIsSameIter(iter1, iter2))
			{
				printf("InsertNextPrevLLTest->SortedLLPrev ");
				printf("error at line: %d index: %ld\n", __LINE__, i); 
			}
		}
	}
	
	/* test Remove*/
	
	for (i = 0; i < size; ++i)
	{
		iter1 = SortedLLNext(SortedLLBegin(list));
		
		if (!SortedLLIsSameIter(iter1, SortedLLRemove(SortedLLBegin(list))))
		{
			printf("InsertNextPrevLLTest->SortedLLRemove ");
			printf("error at line: %d index: %ld\n", __LINE__, i); 
		}
	}
	
	SortedLLDestroy(list);
	list = NULL;
	
	return EXIT_SUCCESS;
}


static int ForEachFindIfTest()
{	

	int arr[] = {4, 1, 6, 1, 7, 8};
	int arr_exp[] = {1, 1, 4, 6, 7, 8};
	size_t size = sizeof(arr)/ sizeof(arr[0]);
	
	int addition = 10;
	int reducing = -10;
	
	size_t i = 0;
	sorted_list_t *list = SortedLLCreate(CmpFunc);
	sorted_list_iter_t iter1 = {NULL};

	if (NULL == list)
	{
		printf("ForEachFindIfTest->SorteLLCreate error at line: %d\n", __LINE__);
		list = NULL;
		
		return EXIT_FAILURE; 
	}


	for (i = 0; i < size; ++i)
	{
		SortedLLInsert(list, (void *)(arr + i));
	}
	
	
	if (EXIT_SUCCESS != SortedLLForEach(SortedLLBegin(list), SortedLLEnd(list), 
														Add, (void *)&addition))
	{
		printf("ForEachFindIfTest->SortedLLForEach error at line: %d\n", __LINE__);
	}
	
	iter1 = SortedLLBegin(list); 
	
	for (i = 0; i < size; ++i)
	{
		if (arr_exp[i] + addition != *(int *)SortedLLGetData(iter1))
		{
			printf("ForEachFindIfTest->SortedLLForEach ");
			printf("error at line: %d index: %ld\n", __LINE__, i); 	
		}
		
		iter1 = SortedLLNext(iter1);
	}

	
	if (EXIT_SUCCESS != SortedLLForEach(SortedLLBegin(list), SortedLLEnd(list), 
														Add, (void *)&reducing))
	{
			printf("ForEachFindIfTest->SortedLLForEach ");
			printf("error at line: %d index: %ld\n", __LINE__, i); 	
	}

	
	iter1 = SortedLLNext(SortedLLBegin(list)); 
	
	for (i = 2; i < size; ++i)
	{
		iter1 = SortedLLNext(iter1);
		
		if (!SortedLLIsSameIter(
								SortedLLFindIf(SortedLLBegin(list),
								SortedLLEnd(list), IsMatchInt, 
								(void *)(arr_exp + i)), iter1)
																			)
		{
			printf("ForEachFindIfTest->SortedLLFindIf ");
			printf("error at line: %d index: %ld\n", __LINE__, i); 	
		}
	
	
	}
	
	SortedLLDestroy(list);
	list = NULL;
	
	return EXIT_SUCCESS;
}
static int MergeTest()
{		
	int arr[] = {4, 1, 6, 1, 7, 8, 8, 10};
	size_t size = sizeof(arr)/ sizeof(arr[0]);
	
	int arr1[] = {4, 5, 4, 2, 7, 5, 20, 8, 10};
	size_t size1 = sizeof(arr1)/ sizeof(arr1[0]);

	int merg_exp1[] = {1, 1, 2, 4, 4, 4, 5, 5, 6, 7, 7, 8, 8, 8, 10, 10, 20};
	size_t size_exp1 = sizeof(merg_exp1)/ sizeof(merg_exp1[0]);

	int merg_exp2[] = {1, 1, 4, 6, 7, 8, 8, 10};
	size_t size_exp2 = sizeof(merg_exp2)/ sizeof(merg_exp2[0]);

	int merg_exp3[] = {2, 4, 4, 5, 5, 7, 8, 10, 20};
	size_t size_exp3 = sizeof(merg_exp3)/ sizeof(merg_exp3[0]);
	
	size_t i = 0;
	
	sorted_list_t *src = SortedLLCreate(CmpFunc);
	sorted_list_t *dest = NULL;
	
	sorted_list_iter_t find_iter_orig_d = {NULL};
	sorted_list_iter_t find_iter_orig_d1 = {NULL};
	sorted_list_iter_t find_iter_merg = {NULL};
	sorted_list_iter_t find_iter_merg1 = {NULL};
	
	if (NULL == src)
	{
		printf("MergeTest->SortedLLCreate src error at line: %d\n", __LINE__);
		src = NULL;
		
		SortedLLDestroy(dest);
		return EXIT_FAILURE; 
	}
	dest = SortedLLCreate(CmpFunc);

	if (NULL == dest)
	{
		printf("MergeTest->SortedLLCreate dest error at line: %d\n", __LINE__);
		dest = NULL;
		
		SortedLLDestroy(src);
		return EXIT_FAILURE; 
	}
	
	
	for (i = 0; i < size; ++i)
	{
		SortedLLInsert(src, (void *)(arr + i));
	}
	
	if (size != SortedLLSize(src))
	{
		printf("MergeTest->SortedLLInsert src error at line: %d\n", __LINE__);
	}
	
	for (i = 0; i < size1; ++i)
	{
		SortedLLInsert(dest, (void *)(arr1 + i));
	}
	
	if (size1 != SortedLLSize(dest))
	{
		printf("MergeTest->SortedLLInsert dest error at line: %d\n", __LINE__);
	}
	
	/* to full lists */	
	{
		/* test if the original iter in the dest list is the first iter and the 
			duplication of the same data was inserted after the original dest iter */
		find_iter_orig_d = SortedLLPrev(SortedLLEnd(dest));
		
		find_iter_orig_d1 = SortedLLPrev(SortedLLPrev(SortedLLEnd(dest)));

		SortedLLMerge(dest, src);
		
		
		find_iter_merg = SortedLLFindIf(SortedLLBegin(dest),SortedLLEnd(dest), IsMatchInt,
		 								SortedLLGetData(find_iter_orig_d));
		

		 														
		if (1 != SortedLLIsSameIter(find_iter_merg, find_iter_orig_d))
		{
			printf("MergeTest->SortedLLMerge error at line: %d\n", __LINE__);
		}
		
		find_iter_merg1 = SortedLLFindIf(SortedLLBegin(dest),SortedLLEnd(dest), IsMatchInt,
		 								SortedLLGetData(find_iter_orig_d1));
			
		if (1 != SortedLLIsSameIter(find_iter_merg1, find_iter_orig_d1))
		{
			printf("MergeTest->SortedLLMerge error at line: %d\n", __LINE__);
		}
	
	}

	for (i = 0; i < size_exp1; ++i)
	{
		if (merg_exp1[i] != *(int *)SortedLLPopFront(dest))
			{
				printf("MergeTest->SortedLLMerge ");
				printf("error at line: %d index: %ld\n", __LINE__, i); 	
			}
	}
	
	if (0 != SortedLLSize(src))
	{
		printf("MergeTest->SortedLLMerge src error at line: %d\n", __LINE__);
	}

	{
		SortedLLDestroy(src);
		
		src = SortedLLCreate(CmpFunc);

		
		for (i = 0; i < size; ++i)
		{
			SortedLLInsert(src, (void *)(arr + i));
		}
		
		if (size != SortedLLSize(src))
		{
			printf("MergeTest->SortedLLInsert src error at line: %d\n", __LINE__);
		}
		
		
		SortedLLDestroy(dest);
		
		dest = SortedLLCreate(CmpFunc);

		/* to dest where dest is empty list */	
		SortedLLMerge(dest, src);


		for (i = 0; i < size_exp2; ++i)
		{
			if (merg_exp2[i] != *(int *)SortedLLPopFront(dest))
				{
					printf("MergeTest->SortedLLMerge ");
					printf("error at line: %d index: %ld\n", __LINE__, i); 	
				}
		}
		
	}		
	
	{	
		SortedLLDestroy(src);
		
		src = SortedLLCreate(CmpFunc);
		
		SortedLLDestroy(dest);
		
		dest = SortedLLCreate(CmpFunc);

		for (i = 0; i < size1; ++i)
		{
			SortedLLInsert(dest, (void *)(arr1 + i));
		}
		
		if (size1 != SortedLLSize(dest))
		{
			printf("MergeTest->SortedLLInsert dest error at line: %d\n", __LINE__);
		}
		
		/* to dest where src is empty list */	
		SortedLLMerge(dest, src);
		
		for (i = 0; i < size_exp3; ++i)
		{
			if (merg_exp3[i] != *(int *)SortedLLPopFront(dest))
				{
					printf("MergeTest->SortedLLMerge ");
					printf("error at line: %d index: %ld\n", __LINE__, i); 	
				}
		}
	}



	SortedLLDestroy(src);
	src = NULL;
	
	SortedLLDestroy(dest);
	dest = NULL;
	
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


static int CmpFunc(const void *data1, const void *data2)
{
		return (*(int *)data1 - *(int *)data2); 		
}



static int Add(void *data,void *param)
{

	*(int *)data = *(int *)data + *(int *)param;

	return EXIT_SUCCESS; 
}
#ifdef DEBUG
static int IsSameAddrese(d_list_iter_t data, d_list_iter_t param)
{
	return (data == param); 
}
#else
	
#endif	



