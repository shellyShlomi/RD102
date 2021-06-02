#include <stdio.h>	/* printf */
#include <stdlib.h> /* exit status */

#include "bst.h"

#define UNUSED(x) (void)(x)
#define SIZE 10

/*---------------helper iner func-----------------*/

static int Compare(void *data1, void *data2, void *param);
static int AddOne(void *data1, void *data2);

/*---------------test func-----------------*/

static void Test();
static void TestBST();
static void TestInsertBST();
static void TestFindAndForEachBST();
static void TestLeftSubTreeTwoBST();
static void TestLeftSubTreeOneBST();
static void TestRightSubTreeOneBST();

/*------------------------------test for impl---------------------------------*/

int main()
{
	Test();

	return (0);
}
static void Test()
{
	TestBST();
	TestInsertBST();
	TestFindAndForEachBST();
	TestLeftSubTreeTwoBST();
	TestLeftSubTreeOneBST();
	TestRightSubTreeOneBST();
}
static void TestBST()
{
	bst_t *bst = BstCreate(Compare, NULL);
	if (NULL == bst)
	{
		printf("TestBST BstCreate failed %d", __LINE__);
	}

	if (1 != BstIsEmpty(bst))
	{
		printf("TestBST BstIsEmpty failed at line: %d", __LINE__);
	}

	/*if (0 != BstSize(bst))
	{
		printf("TestBST BstSize failed at line: %d", __LINE__);
	}*/

	BstDestroy(bst);
	return;
}

static void TestInsertBST()
{
	int array[] = {1, 10, 4, 7, 3, 2, 8, 9, 5, 6};
	int sorted[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	size_t size = sizeof(array) / sizeof(array[0]);
	bst_iter_t iter = NULL;
	bst_iter_t arr[sizeof(array) / sizeof(array[0])] = {NULL};
	size_t i = 0;
	size_t res_size = size;
	bst_t *bst = BstCreate(Compare, NULL);

	if (NULL == bst)
	{
		printf("TestBST BstCreate failed %d", __LINE__);
	}

	if (1 != BstIsEmpty(bst))
	{
		printf("TestBST BstIsEmpty failed at line: %d", __LINE__);
	}

	if (1 != BstIterIsEqual(BstEnd(bst), BstBegin(bst)))
	{
		printf("TestBST BstIterIsEqual failed at line: %d", __LINE__);
	}

	for (i = 0; i < size; ++i)
	{
		arr[i] = BstInsert(bst, (void *)(array + i));
	}
	if (size != BstSize(bst))
	{
		printf("TestBST BstInsert failed at line: %d %lu\n", __LINE__, BstSize(bst));
	}

	iter = BstPrev(BstEnd(bst));

	for (i = 0; i < size; ++i)
	{
		if (sorted[i] != *(int *)BstGetData(iter))
		{
			printf("TestBST BstPrev & BstGetData failed at line:%d %d %d\n", __LINE__, sorted[i], *(int *)BstGetData((iter)));
		}
		iter = BstPrev(iter);
	}

	iter = BstPrev(BstEnd(bst));
	for (i = 0; i < size / 2 - 1; ++i)
	{
		BstRemove(arr[i * 2]);
		if (--res_size != BstSize(bst))
		{
			printf("TestBST BstRemove failed at line:%d %lu %lu\n", __LINE__, BstSize(bst), i);
		}
		iter = BstPrev(iter);
	}

	BstDestroy(bst);
	return;
}

static void TestFindAndForEachBST()
{
	int array[] = {1, 10, 4, 7, 3, 2, 8, 9, 5, 6};
	int sorted[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	size_t size = sizeof(array) / sizeof(array[0]);
	bst_iter_t iter = NULL;
	bst_iter_t arr[SIZE * 2] = {NULL};
	size_t i = 0;
	int data_val = 100;
	int *data = &data_val;
	bst_t *bst = BstCreate(Compare, NULL);

	if (NULL == bst)
	{
		printf("TestBST BstCreate failed %d", __LINE__);
	}

	if (1 != BstIsEmpty(bst))
	{
		printf("TestBST BstIsEmpty failed at line: %d", __LINE__);
	}

	for (i = 0; i < size; ++i)
	{
		arr[i] = BstInsert(bst, (void *)(array + i));
	}
	if (size != BstSize(bst))
	{
		printf("TestBST BstInsert failed at line: %d %lu\n", __LINE__, BstSize(bst));
	}

	iter = BstBegin(bst);

	for (i = 0; i < size; ++i)
	{
		if (sorted[i] != *(int *)BstGetData(iter))
		{
			printf("TestBST BstNext & BstBegin failed at line:%d %d %d\n", __LINE__, sorted[i], *(int *)BstGetData((iter)));
		}
		iter = BstNext(iter);
	}

	if ((BstEnd(bst)) != BstFind(bst, (void *)(data)))
	{
		printf("TestBST BstFind failed at line:%d\n", __LINE__);
	}
	data_val = 9;
	arr[size] = BstFind(bst, (void *)(data));
	if (data_val != *(int *)BstGetData(arr[size]))
	{
		printf("TestBST BstFind failed at line: %d\n", __LINE__);
	}

	if (EXIT_SUCCESS != BstForEach(BstBegin(bst), BstEnd(bst), AddOne, (void *)data))
	{
		printf("TestBST BstFind failed at line:%d %d %d\n", __LINE__, sorted[9], *(int *)BstGetData(arr[size]));
	}

	iter = BstBegin(bst);
	for (i = 0; i < size; ++i)
	{
		if ((sorted[i] + *data) != *(int *)BstGetData(iter))
		{
			printf("TestBST BstNext & BstBegin failed at line:%d %d %d\n", __LINE__, sorted[i] + *data, *(int *)BstGetData((iter)));
		}
		iter = BstNext(iter);
	}

	BstDestroy(bst);
	return;
}

static void TestLeftSubTreeTwoBST()
{
	int array[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	int sorted[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	size_t size = sizeof(array) / sizeof(array[0]);
	bst_iter_t iter = NULL;
	size_t i = 0;
	int *data = (sorted + 1);
	bst_t *bst = BstCreate(Compare, NULL);

	if (NULL == bst)
	{
		printf("TestBST BstCreate failed %d", __LINE__);
	}

	if (1 != BstIsEmpty(bst))
	{
		printf("TestBST BstIsEmpty failed at line: %d", __LINE__);
	}

	if (1 != BstIterIsEqual(BstEnd(bst), BstBegin(bst)))
	{
		printf("TestBST BstIterIsEqual failed at line: %d", __LINE__);
	}

	for (i = 0; i < size; ++i)
	{
		BstInsert(bst, (void *)(array + i));
	}
	if (size != BstSize(bst))
	{
		printf("TestBST BstInsert failed at line: %d %lu\n", __LINE__, BstSize(bst));
	}

	iter = BstPrev(BstEnd(bst));

	for (i = 0; i < size; ++i)
	{
		if (sorted[size - 1 - i] != *(int *)BstGetData(iter))
		{
			printf("TestBST BstPrev & BstGetData failed at line:%d %d %d\n", __LINE__, sorted[i], *(int *)BstGetData((iter)));
		}
		iter = BstPrev(iter);
	}

	iter = BstBegin(bst);
	for (i = 0; i < size; ++i)
	{
		if ((sorted[i]) != *(int *)BstGetData(iter))
		{
			printf("TestBST BstNext & BstBegin failed at line:%d %d %d\n", __LINE__, sorted[i] + *data, *(int *)BstGetData((iter)));
		}
		iter = BstNext(iter);
	}

	BstDestroy(bst);
	return;
}

static void TestLeftSubTreeOneBST()
{
	int array[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	int sorted[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	size_t size = sizeof(array) / sizeof(array[0]);
	bst_iter_t iter = NULL;
	bst_iter_t arr[SIZE * 2] = {NULL};
	size_t i = 0;
	int *data = (sorted + 1);
	bst_t *bst = BstCreate(Compare, NULL);

	if (NULL == bst)
	{
		printf("TestBST BstCreate failed %d", __LINE__);
	}

	if (1 != BstIsEmpty(bst))
	{
		printf("TestBST BstIsEmpty failed at line: %d", __LINE__);
	}

	for (i = 0; i < size; ++i)
	{
		arr[i] = BstInsert(bst, (void *)(array + i));
	}
	if (size != BstSize(bst))
	{
		printf("TestBST BstInsert failed at line: %d %lu\n", __LINE__, BstSize(bst));
	}

	iter = BstBegin(bst);

	for (i = 0; i < size; ++i)
	{
		if (sorted[i] != *(int *)BstGetData(iter))
		{
			printf("TestBST BstNext & BstBegin failed at line:%d %d %d\n", __LINE__, sorted[i], *(int *)BstGetData((iter)));
		}
		iter = BstNext(iter);
	}

	arr[size] = BstFind(bst, (void *)(data));
	if (sorted[1] != *(int *)BstGetData(arr[size]))
	{
		printf("TestBST BstFind failed at line:%d %d %d\n", __LINE__, sorted[1], *(int *)BstGetData(arr[size]));
	}

	data = (sorted + 9);
	arr[size] = BstFind(bst, (void *)(data));
	if (sorted[9] != *(int *)BstGetData(arr[size]))
	{
		printf("TestBST BstFind failed at line:%d %d %d\n", __LINE__, sorted[9], *(int *)BstGetData(arr[size]));
	}

	if (EXIT_SUCCESS != BstForEach(BstBegin(bst), BstEnd(bst), AddOne, (void *)data))
	{
		printf("TestBST BstFind failed at line:%d %d %d\n", __LINE__, sorted[9], *(int *)BstGetData(arr[size]));
	}

	iter = BstBegin(bst);
	for (i = 0; i < size; ++i)
	{
		if ((sorted[i] + *data) != *(int *)BstGetData(iter))
		{
			printf("TestBST BstNext & BstBegin failed at line:%d %d %d\n", __LINE__, sorted[i] + *data, *(int *)BstGetData((iter)));
		}
		iter = BstNext(iter);
	}

	BstDestroy(bst);
	return;
}

static void TestRightSubTreeOneBST()
{
	int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int sorted[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	size_t size = sizeof(array) / sizeof(array[0]);
	bst_iter_t iter = NULL;
	bst_iter_t arr[SIZE * 2] = {NULL};
	size_t i = 0;
	int *data = (sorted + 1);
	bst_t *bst = BstCreate(Compare, NULL);

	if (NULL == bst)
	{
		printf("TestBST BstCreate failed %d", __LINE__);
	}

	if (1 != BstIsEmpty(bst))
	{
		printf("TestBST BstIsEmpty failed at line: %d", __LINE__);
	}

	for (i = 0; i < size; ++i)
	{
		arr[i] = BstInsert(bst, (void *)(array + i));
	}
	if (size != BstSize(bst))
	{
		printf("TestBST BstInsert failed at line: %d %lu\n", __LINE__, BstSize(bst));
	}

	iter = BstBegin(bst);

	for (i = 0; i < size; ++i)
	{
		if (sorted[i] != *(int *)BstGetData(iter))
		{
			printf("TestBST BstNext & BstBegin failed at line:%d %d %d\n", __LINE__, sorted[i], *(int *)BstGetData((iter)));
		}
		iter = BstNext(iter);
	}

	arr[size] = BstFind(bst, (void *)(data));
	if (sorted[1] != *(int *)BstGetData(arr[size]))
	{
		printf("TestBST BstFind failed at line:%d %d %d\n", __LINE__, sorted[1], *(int *)BstGetData(arr[size]));
	}

	data = (sorted + 9);
	arr[size] = BstFind(bst, (void *)(data));
	if (sorted[9] != *(int *)BstGetData(arr[size]))
	{
		printf("TestBST BstFind failed at line:%d %d %d\n", __LINE__, sorted[9], *(int *)BstGetData(arr[size]));
	}

	if (EXIT_SUCCESS != BstForEach(BstBegin(bst), BstEnd(bst), AddOne, (void *)data))
	{
		printf("TestBST BstFind failed at line:%d %d %d\n", __LINE__, sorted[9], *(int *)BstGetData(arr[size]));
	}

	iter = BstBegin(bst);
	for (i = 0; i < size; ++i)
	{
		if ((sorted[i] + *data) != *(int *)BstGetData(iter))
		{
			printf("TestBST BstNext & BstBegin failed at line:%d %d %d\n", __LINE__, sorted[i] + *data, *(int *)BstGetData((iter)));
		}
		iter = BstNext(iter);
	}

	BstDestroy(bst);
	return;
}
/*------------------------------helper func--------------------------------*/

static int Compare(void *data1, void *data2, void *param)
{
	UNUSED(param);

	return (*(int *)data1 - *(int *)data2);
}
static int AddOne(void *data1, void *data2)
{
	*(int *)data1 = *(int *)data1 + *(int *)data2;
	return (EXIT_SUCCESS);
}
