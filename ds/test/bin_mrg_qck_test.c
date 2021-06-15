#include <stdio.h>	/* printf */
#include <stdlib.h> /* time_t, rand */
#include <assert.h> /* assert */
#include <time.h>

#include "bin_mrg_qck.h"

#define SIZE (1000000)
#define RANGE_RANDOM (5000)
#define RANGE_NEGATIV (30)
#define BITS_TO_CHECK 32
#define DIGITES 9

/* helper funcs */
static int Compare(const void *data1, const void *data2);
static int *CreateRandomNegativ(size_t size, int range);
static int *CreateReversSorted(size_t size, int range);
static int *CreateSorted(size_t size, int range);
static int *CopyArr(int *arr, size_t size);
static int AreSameArr(int *arr, int *other, size_t size);
static void PrintArray(int *arr, size_t size);

/*test functions*/
static void TestIterBinSearch();
static void TestRecBinSearch();
static void TestIterBinSearch1();
static void TestRecBinSearch1();
static void TestMergeSort();
static void TestRecQsort();
static void Test();

int main()
{
    Test();

    return 0;
}

static void Test()
{
    TestIterBinSearch();
    TestIterBinSearch1();
    TestRecBinSearch();
    TestRecBinSearch1();
    TestMergeSort();
    TestRecQsort();

    return ;
}

static void TestIterBinSearch()
{
    int arr[] = {-4, 6, 7, 10, 12, 13};
    int arr_val[] = {10, 15, 2, 3, 6, -4, -5, 13};
    int arr_index_exp[] = {3, -1, -1, -1, 1, 0, -1, 5};
    int status[] = {0, 1, 1, 1, 0, 0, 1, 0};
    int status_returned = -1;

    size_t size_to_send = sizeof(arr) / sizeof(arr[0]);

    size_t size = sizeof(arr_val) / sizeof(arr_val[0]);
    size_t return_index = 0;
    size_t i = 0;

    while (0 < size)
    {
        status_returned = IterBinSearch(arr, size_to_send, arr_val[i], &return_index);
        if (status_returned != status[i])
        {
			if ((return_index != (size_t)arr_index_exp[i]) && (arr_index_exp[i] != -1))
			{
            	printf("index returned %ld\n", return_index);
            	printf("index expected %d\n", arr_index_exp[i]);
			}
            printf("Test IterBinSearch failed at line %d and at index %lu\n", __LINE__, i);
            printf("expected status %d\n", status[i]);
            printf("returned status %d\n", status_returned);
        }
		
        --size;
        ++i;
    }

    return;
}

static void TestIterBinSearch1()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 9, 10, 15, 20, 54, 56, 57, 80, 100, 108};
    int to_search[] = {6, 3, 2, 15, 56, 80, 10, 54, 108};
    size_t exp[] = {5, 2, 1, 9, 12, 14, 8, 11, 16};

    size_t size_to_send = sizeof(arr) / sizeof(arr[0]);

    size_t size = sizeof(to_search) / sizeof(to_search[0]);
    size_t return_index = 0;
    size_t i = 0;

    while (0 < size)
    {
        IterBinSearch(arr, size_to_send, to_search[i], &return_index);
        if (return_index != (size_t)exp[i])
        {
            printf("Test TestIterBinSearch1 failed at line %d and at index %lu\n", __LINE__, i);
            printf("TestIterBinSearch1 index returned %ld\n", return_index);
            printf("index expected %lu\n", exp[i]);
        }
        --size;
        ++i;
    }

    return;
}

static void TestRecBinSearch()
{
    int arr[] = {-4, 6, 7, 10, 12, 13};
    int arr_val[] = {10, 15, 2, 3, 6, -4, -5, 13};
    int arr_index_exp[] = {3, -1, -1, -1, 1, 0, -1, 5};
    int status[] = {0, 1, 1, 1, 0, 0, 1, 0};
    int status_returned = -1;

    size_t size_to_send = sizeof(arr) / sizeof(arr[0]);

    size_t size = sizeof(arr_val) / sizeof(arr_val[0]);
    size_t return_index = 0;
    size_t i = 0;

    while (0 < size)
    {
        status_returned = RecBinSearch(arr, size_to_send, arr_val[i], &return_index);
        if (status_returned != status[i])
        {
			if ((return_index != (size_t)arr_index_exp[i]) && (arr_index_exp[i] != -1))
			{
            	printf("index returned %ld\n", return_index);
            	printf("index expected %d\n", arr_index_exp[i]);
			}
            printf("Test IterBinSearch failed at line %d and at index %lu\n", __LINE__, i);
            printf("expected status %d\n", status[i]);
            printf("returned status %d\n", status_returned);
        }
        --size;
        ++i;
    }

    return;
}

static void TestRecBinSearch1()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 9, 10, 15, 20, 54, 56, 57, 80, 100, 108};
    int to_search[] = {6, 3, 2, 15, 56, 80, 10, 54, 108};
    size_t exp[] = {5, 2, 1, 9, 12, 14, 8, 11, 16};

    size_t size_to_send = sizeof(arr) / sizeof(arr[0]);

    size_t size = sizeof(to_search) / sizeof(to_search[0]);
    size_t return_index = 0;
    size_t i = 0;

    while (0 < size)
    {
        RecBinSearch(arr, size_to_send, to_search[i], &return_index);
        if (return_index != (size_t)exp[i])
        {
            printf("Test TestRecBinSearch1 failed at line %d and at index %lu\n", __LINE__, i);
            printf("TestRecBinSearch1 index returned %ld\n", return_index);
            printf("index expected %lu\n", exp[i]);
        }
        --size;
        ++i;
    }

    return;
}
/*
static void TestMergeSort()
{
    int exp[] = {-5, -4, 2, 3, 6, 10, 13, 15};
    int arr[] = {10, 15, 2, 3, 6, -4, -5, 13};
    size_t i = 0;

    size_t size = sizeof(arr) / sizeof(arr[0]);

    while (i < size)
    {
        MergeSort(arr, size);
        if (arr[i] != exp[i])
        {
            printf("Test TestMergeSort failed at line %d and at index %lu\n", __LINE__, i);
            printf("expected status %d\n", exp[i]);
            printf("returned status %d\n", arr[i]);
        }
        --size;
        ++i;
    }

    return;
}

static void TestMergeSort1()
{
    int arr[] = {108, 2, 56, 15, 5, 80, 7, 9, 100, 4, 20, 54, 3, 57, 6, 10, 1};
    int exp[] = {1, 2, 3, 4, 5, 6, 7, 9, 10, 15, 20, 54, 56, 57, 80, 100, 108};
    size_t i = 0;

    size_t size = sizeof(arr) / sizeof(arr[0]);

    while (i < size)
    {
        MergeSort(arr, size);
        if (arr[i] != exp[i])
        {
            printf("Test TestMergeSort1 failed at line %d and at index %lu\n", __LINE__, i);
            printf("expected status %d\n", exp[i]);
            printf("returned status %d\n", arr[i]);
        }
        --size;
        ++i;
    }

    return;
}
*/

static void TestRecQsort()
{
	clock_t start_time = 0;
	clock_t end_time = 0;
	int *actual = NULL;
	int *exp = NULL;
	size_t size = SIZE;

	actual = CreateRandomNegativ(size, RANGE_RANDOM);
	exp = CopyArr(actual, size);

	start_time = clock();
	qsort(exp, size, sizeof(int), Compare);
	end_time = clock();

	printf("\n");
	printf("------------------------------RecQsort Test--------------------------------\n");
	printf("\n");
	printf("Random Array\n\n");
	
	printf("qsort result: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	start_time = clock();
	RecQsort(actual, size, sizeof(int), Compare);
	end_time = clock();

	if (0 == AreSameArr(actual, exp, size))
	{
		printf("Test failed at %d\n", __LINE__);
		printf("----------------------------ACTUAL-------------------------------------\n");
		PrintArray(actual, size);
		printf("----------------------------EXP-------------------------------------\n");
		PrintArray(exp, size);
	}
	printf("My result %f\n\n\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	free(actual);
	free(exp);

	actual = CreateReversSorted(size, RANGE_RANDOM);
	exp = CopyArr(actual, size);

	start_time = clock();
	qsort(exp, size, sizeof(int), Compare);
	end_time = clock();
	printf("Revers Sorted Array\n\n");

	printf("qsort result: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	start_time = clock();
	RecQsort(actual, size, sizeof(int), Compare);
	end_time = clock();

	qsort(exp, size, sizeof(int), Compare);

	if (0 == AreSameArr(actual, exp, size))
	{
		printf("Test failed at %d\n", __LINE__);
		printf("----------------------------ACTUAL-------------------------------------\n");
		PrintArray(actual, size);
		printf("----------------------------EXP-------------------------------------\n");
		PrintArray(exp, size);
	}

	printf("My result %f\n\n\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	free(actual);
	free(exp);

	actual = CreateSorted(size, RANGE_RANDOM);
	exp = CopyArr(actual, size);

	start_time = clock();
	qsort(exp, size, sizeof(int), Compare);
	end_time = clock();
	printf("Sorted Array\n\n");

	printf("qsort result: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	start_time = clock();
	RecQsort(actual, size, sizeof(int), Compare);

    end_time = clock();

	qsort(exp, size, sizeof(int), Compare);

	if (0 == AreSameArr(actual, exp, size))
	{
		printf("Test failed at %d\n", __LINE__);
		printf("----------------------------ACTUAL-------------------------------------\n");
		PrintArray(actual, size);
		printf("----------------------------EXP-------------------------------------\n");
		PrintArray(exp, size);
	}

	printf("My result %f\n\n\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	free(actual);
	free(exp);

	return;
}




static void TestMergeSort()
{
	clock_t start_time = 0;
	clock_t end_time = 0;
	int *actual = NULL;
	int *exp = NULL;
	size_t size = SIZE;

	actual = CreateRandomNegativ(size, RANGE_RANDOM);
	exp = CopyArr(actual, size);

	start_time = clock();
	qsort(exp, size, sizeof(int), Compare);
	end_time = clock();

	printf("\n");
	printf("------------------------------MergeSort Test--------------------------------\n");
	printf("\n");
	printf("Random Array\n\n");
	
	printf("qsort result: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	start_time = clock();
    MergeSort(actual, size);
	end_time = clock();

	if (0 == AreSameArr(actual, exp, size))
	{
		printf("Test failed at %d\n", __LINE__);
		printf("----------------------------ACTUAL-------------------------------------\n");
		PrintArray(actual, size);
		printf("----------------------------EXP-------------------------------------\n");
		PrintArray(exp, size);
	}
	printf("My result %f\n\n\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	free(actual);
	free(exp);

	actual = CreateReversSorted(size, RANGE_RANDOM);
	exp = CopyArr(actual, size);

	start_time = clock();
	qsort(exp, size, sizeof(int), Compare);
	end_time = clock();
	printf("Revers Sorted Array\n\n");

	printf("qsort result: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	start_time = clock();
    MergeSort(actual, size);
	end_time = clock();

	qsort(exp, size, sizeof(int), Compare);

	if (0 == AreSameArr(actual, exp, size))
	{
		printf("Test failed at %d\n", __LINE__);
		printf("----------------------------ACTUAL-------------------------------------\n");
		PrintArray(actual, size);
		printf("----------------------------EXP-------------------------------------\n");
		PrintArray(exp, size);
	}

	printf("My result %f\n\n\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	free(actual);
	free(exp);

	actual = CreateSorted(size, RANGE_RANDOM);
	exp = CopyArr(actual, size);

	start_time = clock();
	qsort(exp, size, sizeof(int), Compare);
	end_time = clock();
	printf("Sorted Array\n\n");

	printf("qsort result: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	start_time = clock();
    MergeSort(actual, size);

    end_time = clock();

	qsort(exp, size, sizeof(int), Compare);

	if (0 == AreSameArr(actual, exp, size))
	{
		printf("Test failed at %d\n", __LINE__);
		printf("----------------------------ACTUAL-------------------------------------\n");
		PrintArray(actual, size);
		printf("----------------------------EXP-------------------------------------\n");
		PrintArray(exp, size);
	}

	printf("My result %f\n\n\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	free(actual);
	free(exp);

	return;
}

/*------------------------------helper functions------------------------------*/

static int Compare(const void *data1, const void *data2)
{
	return (*(int *)data1 - *(int *)data2);
}
/*
static int *CreateRandom(size_t size, int range)
{
	size_t i = 0;

	int *new_arr = (int *)malloc(sizeof(int) * size);

	if (NULL == new_arr)
	{
		return NULL;
	}

	for (i = 0; i < size; i++)
	{
		new_arr[i] = rand() % range;
	}

	return new_arr;
}
*/
static int *CreateRandomNegativ(size_t size, int range)
{
	size_t i = 0;

	int *new_arr = (int *)malloc(sizeof(int) * size);

	if (NULL == new_arr)
	{
		return NULL;
	}

	for (i = 0; i < size; i++)
	{
		new_arr[i] = (clock() * rand()) % range - RANGE_NEGATIV; 
	}

	return new_arr;
}


static int *CreateSorted(size_t size, int range)
{
	size_t i = 0;
	int *new_arr = (int *)malloc(sizeof(int) * size);

	(void)range;

	if (NULL == new_arr)
	{
		return NULL;
	}

	for (i = 0; i < size; i++)
	{
		new_arr[i] = i; 
	}

	return new_arr;
}

static int *CreateReversSorted(size_t size, int range)
{
	size_t i = 0;
	int *new_arr = (int *)malloc(sizeof(int) * size);
	
	(void)range;

	if (NULL == new_arr)
	{
		return NULL;
	}

	for (i = 0; i < size; i++)
	{
		new_arr[i] = size - i; 
	}

	return new_arr;
}

static int AreSameArr(int *arr, int *other, size_t size)
{
	size_t i = 0;

	for (i = 0; i < size; ++i)
	{
		if (arr[i] != other[i])
		{
			printf("Failed at index %ld at line %d\n", i, __LINE__);

			return 0;
		}
	}

	return 1;
}

static int *CopyArr(int *arr, size_t size)
{
	size_t i = 0;

	int *copy_arr = (int *)malloc(sizeof(int) * size);

	if (NULL == copy_arr)
	{
		return NULL;
	}

	for (i = 0; i < size; ++i)
	{
		copy_arr[i] = arr[i];
	}

	return copy_arr;
}

static void PrintArray(int *arr, size_t size)
{
	size_t i = 0;

	assert(NULL != arr);

	for (i = 0; i < size; ++i)
	{
		printf("%d\t", arr[i]);

		if (i % 10 == 0)
		{
			printf("\n");
		}
	}

	printf("\n");
	return;
}