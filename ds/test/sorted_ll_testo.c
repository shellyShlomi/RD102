#include <stdio.h> /* printf */

#include "sorted_ll.h"


static int Match(const void * data, const void *param);
static int Compare(const void *data1, const void *data2);
static int PrintList(void * data, void *param);
static int Max(const void *data1, const void *data2);

#define UNUSED(x) (void)(x)

int main()
{
	int arr_src[] = {12, 1 ,2};/*for Merge*/
	int arr_dest[] = {4, 1, 6 , 1, 7, 8};
	int arr_dest_expeted[] = {1, 1, 4, 6, 7, 8}; 
	size_t i = 0;
	size_t size_src = sizeof(arr_src) / sizeof(arr_src[0]); 
	size_t size_dest = sizeof(arr_dest) / sizeof(arr_dest[0]); 
	sorted_list_iter_t iter_src = {NULL};
	sorted_list_iter_t iter_dest = {NULL};
	
	sorted_list_t *list_src = SortedLLCreate(Compare);
	sorted_list_t *list_dest = SortedLLCreate(Compare);
	
	if (1 != SortedLLIsEmpty(list_src))
	{
		printf("SortedLLIsEmpty function failed at line: %d\n", __LINE__); 
	}
		
	if (0 != SortedLLSize(list_src))
	{
			printf("SortedLLIsEmpty function failed at line: %d\n", __LINE__); 
	}
	
	if (1 != SortedLLIsEmpty(list_dest))
	{
		printf("SortedLLIsEmpty function failed at line: %d\n", __LINE__); 
	}
		
	if (0 != SortedLLSize(list_dest))
	{
			printf("SortedLLIsEmpty function failed at line: %d\n", __LINE__); 
	}
	
	
	for (i = 0; i < size_src; ++i)
	{
		SortedLLInsert(list_src, (void *)(arr_src + i));
	}
	
	for (i = 0; i < size_dest; ++i)
	{
		SortedLLInsert(list_dest, (void *)(arr_dest + i));
	}
	
	iter_dest = SortedLLBegin(list_dest); 
	
	for (i = 0; i < size_dest; ++i)
	{
		if (arr_dest_expeted[i] != *(int *)SortedLLGetData(iter_dest))
		{
			printf("SortedLLGetData function failed at line: %d in index: %ld\n", __LINE__, i); 	
		}
		
		iter_dest = SortedLLNext(iter_dest);
	}
	
	iter_dest = SortedLLEnd(list_dest);
	iter_dest = SortedLLPrev(iter_dest);
	
	for (i = 0; i < size_dest; ++i)
	{
		if (arr_dest_expeted[size_dest - i - 1] != *(int *)SortedLLGetData(iter_dest))
		{
			printf("SortedLLGetData function failed at line: %d in index: %ld\n", __LINE__, i); 	
		}
		
		iter_dest = SortedLLPrev(iter_dest);	
	}
	
	for (i = 0; i < size_dest; ++i)
	{
		if (arr_dest_expeted[size_dest - i - 1] != *(int *)SortedLLPopBack(list_dest))
		{
			printf("SortedLLPopBack function failed at line: %d in index: %ld\n", __LINE__, i); 	
		}
		
	}
	
	if (1 != SortedLLIsEmpty(list_dest))
	{
		printf("SortedLLIsEmpty function failed at line: %d\n", __LINE__); 
	}
	
	for (i = 0; i < size_dest; ++i)
	{
		SortedLLInsert(list_dest, (void *)(arr_dest + i));
	}
	
	
	for (i = 0; i < size_dest; ++i)
	{
		if (arr_dest_expeted[i] != *(int *)SortedLLPopFront(list_dest))
		{
			printf("SortedLLPopFront function failed at line: %d in index: %ld\n", __LINE__, i); 	
		}
	}
	
	iter_dest = SortedLLBegin(list_dest); 
	
	if (1 != SortedLLIsEmpty(list_dest))
	{
		printf("SortedLLIsEmpty function failed at line: %d\n", __LINE__); 
	}
	
	if (1 != SortedLLIsSameIter(SortedLLBegin(list_dest), SortedLLEnd(list_dest)))
	{
		printf("SortedLLIsEmpty function failed at line: %d\n", __LINE__); 
	}
	
	for (i = 0; i < size_dest; ++i)
	{
		SortedLLInsert(list_dest, (void *)(arr_dest + i));
	}
	
	for (i = 0; i < size_dest; ++i)
	{
		iter_dest = SortedLLRemove(SortedLLBegin(list_dest));
	}
	
	if (1 != SortedLLIsEmpty(list_dest))
	{
		printf("SortedLLIsEmpty function failed at line: %d\n", __LINE__); 
	}
	
	if (1 != SortedLLIsSameIter(iter_dest, SortedLLEnd(list_dest)))
	{
		printf("SortedLLIsEmpty function failed at line: %d\n", __LINE__); 
	}
	for (i = 0; i < size_dest; ++i)
	{
		SortedLLInsert(list_dest, (void *)(arr_dest + i));
	}
	
	
	printf("list_src before Merge function: \n");	
	SortedLLForEach(SortedLLBegin(list_src), SortedLLEnd(list_src), PrintList, NULL);
	printf("\nlist_dest before Merge function: \n");
	SortedLLForEach(SortedLLBegin(list_dest), SortedLLEnd(list_dest), PrintList, NULL);
	printf("\n");	

	SortedLLMerge(list_dest, list_src);
	
	printf("list_src after Merge function: \n");
	SortedLLForEach(SortedLLBegin(list_src), SortedLLEnd(list_src), PrintList, NULL);
	printf("\nlist_dest after Merge function: \n");
	SortedLLForEach(SortedLLBegin(list_dest), SortedLLEnd(list_dest), PrintList, NULL);
	printf("\n");
	
	if (0 != SortedLLIsEmpty(list_dest))
	{
		printf("SortedLLIsEmpty function failed at line: %d\n", __LINE__); 
	}
	
	if (size_src + size_dest != SortedLLSize(list_dest))
	{
		printf("SortedLLSize function failed at line: %d\n", __LINE__); 
	}
	
	
	SortedLLDestroy(list_src);
	SortedLLDestroy(list_dest);
	return 0;
}





static int Match(const void * data, const void *param)
{
	return (*(int *)data == *(int *)param);
}

static int Compare(const void *data1, const void *data2)
{
    return ((*(int*)data1 > *((int*)data2)) ? 1 : 0);
}

static int PrintList(void * data, void *param)
{
	UNUSED(param);
	
	printf("%d ", *(int *)data); 
	
	return 0;
}

static int Max(const void *data1, const void *data2)
{
	 return ((*(int*)data1 > *((int*)data2)) ? 1 : 0);	
} 

/*static int Compare(const void *data1, const void *data2)
{
    return  (*(int *)data1 - *(int *)data2);
} */ 


