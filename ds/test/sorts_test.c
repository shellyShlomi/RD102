#include <stdio.h>	/* printf */
#include <stdlib.h> /* time_t, rand */
#include <assert.h> /* assert */
#include <time.h>

#include "sorts.h"

#define SIZE (200)
#define RANGE_RANDOM (5000)
#define RANGE_NEGATIV (300)
#define COUNT_RANGE (2000)
#define BITS_TO_CHECK 32
#define DIGITES 9

/* helper funcs */
static int Compare(const void *data1, const void *data2);
static int *CreateRandom(size_t size, int range);
static int *CreateRandomNegativ(size_t size, int range);
static int *CreateReversSorted(size_t size, int range);
static int *CreateSorted(size_t size, int range);
static int *CopyArr(int *arr, size_t size);
static int AreSameArr(int *arr, int *other, size_t size);
static void PrintArray(int *arr, size_t size);
/*test functions*/
static void TestBubbleSort();
static void TestSelectionSort();
static void TestInsertionSort();
static void TestCountSort();
static void TestRadixDigitsSort();
static void TestRadixBitsSort();
static void TestMergeSort();
static void TestRecQsort();


int main()
{
	TestBubbleSort();
	TestSelectionSort();
	TestInsertionSort();
	TestCountSort();
	TestRadixDigitsSort();
	TestRadixBitsSort();
    TestMergeSort();
    TestRecQsort();

	return 0;
}

static void TestBubbleSort()
{
	clock_t start_time = 0;
	clock_t end_time = 0;

	int *actual = NULL;
	int *exp = NULL;

	size_t size = SIZE;

	actual = CreateRandom(size, RANGE_RANDOM);
	exp = CopyArr(actual, size);

	start_time = clock();
	qsort(exp, size, sizeof(int), Compare);
	end_time = clock();
	printf("\n");
	printf("-----------------------------BubbleSort Test--------------------------------\n");
	printf("\n");
	printf("Random Array\n\n");

	printf("qsort result: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	start_time = clock();
	BubbleSort(actual, size);
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
	
	actual = CreateReversSorted(size, RANGE_RANDOM);
	exp = CopyArr(actual, size);

	start_time = clock();
	qsort(exp, size, sizeof(int), Compare);
	end_time = clock();
	printf("Revers Sorted Array\n\n");

	printf("qsort result: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	start_time = clock();
	BubbleSort(actual, size);
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
	BubbleSort(actual, size);
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

static void TestSelectionSort()
{
	clock_t start_time = 0;
	clock_t end_time = 0;
	int *actual = NULL;
	int *exp = NULL;

	size_t size = SIZE;

	actual = CreateRandom(size, RANGE_RANDOM);
	exp = CopyArr(actual, size);

	printf("\n");
	printf("----------------------------SelectionSort Test------------------------------\n");
	printf("\nRandom Array\n");

	start_time = clock();
	qsort(exp, size, sizeof(int), Compare);
	end_time = clock();

	printf("\n");
	printf("qsort result: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	start_time = clock();
	SelectionSort(actual, size);
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
	SelectionSort(actual, size);
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
	SelectionSort(actual, size);
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

static void TestInsertionSort()
{
	clock_t start_time = 0;
	clock_t end_time = 0;

	int *actual = NULL;
	int *exp = NULL;

	size_t size = SIZE;

	actual = CreateRandom(size, RANGE_RANDOM);
	exp = CopyArr(actual, size);

	start_time = clock();
	qsort(exp, size, sizeof(int), Compare);
	end_time = clock();

	printf("\n");
	printf("----------------------------InsertionSort Test------------------------------\n");
	printf("\n");
	printf("Random Array\n\n");
	
	printf("qsort result: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	start_time = clock();
	InsertionSort(actual, size);
	end_time = clock();

	if (0 == AreSameArr(actual, exp, size))
	{
		printf("Test failed at %d\n", __LINE__);
		printf("----------------------------ACTUAL-------------------------------------\n");
		PrintArray(actual, size);
		printf("----------------------------EXP-------------------------------------\n");
		printf("exp:\n");
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
	InsertionSort(actual, size);
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
	InsertionSort(actual, size);
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

static void TestCountSort()
{
	clock_t start_time = 0;
	clock_t end_time = 0;
	int *actual = NULL;
	int *exp = NULL;
	size_t size = SIZE;

	actual = CreateRandomNegativ(size, COUNT_RANGE);
	exp = CopyArr(actual, size);

	start_time = clock();
	qsort(exp, size, sizeof(int), Compare);
	end_time = clock();

	printf("\n");
	printf("------------------------------CountSort Test--------------------------------\n");
	printf("\n");
	printf("Random Array\n\n");
	
	printf("qsort result: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	start_time = clock();
	CountSort(actual, size);
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
	CountSort(actual, size);
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
	CountSort(actual, size);
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

static void TestRadixDigitsSort()
{
	clock_t start_time = 0;
	clock_t end_time = 0;
	int *actual = NULL;
	int *exp = NULL;

	size_t size = SIZE;

	actual = CreateRandom(size, RANGE_RANDOM);
	exp = CopyArr(actual, size);

	start_time = clock();
	qsort(exp, size, sizeof(int), Compare);
	end_time = clock();

	printf("\n");
	printf("----------------------------RadixDigitsSort Test----------------------------\n");
	printf("\n");
	printf("Random Array\n\n");
	
	printf("qsort result: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	start_time = clock();
	RadixDigitsSort(actual, size, DIGITES);
	end_time = clock();

	if (0 == AreSameArr(actual, exp, size))
	{
		printf("RadixDigitsSort Test failed at %d\n", __LINE__);
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
	RadixDigitsSort(actual, size, DIGITES);
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
	RadixDigitsSort(actual, size, DIGITES);
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

static void TestRadixBitsSort()
{
	clock_t start_time = 0;
	clock_t end_time = 0;
	int *actual = NULL;
	int *exp = NULL;

	size_t size = SIZE;

	actual = CreateRandom(size, RANGE_RANDOM);
	exp = CopyArr(actual, size);

	start_time = clock();
	qsort(exp, size, sizeof(int), Compare);
	end_time = clock();

	printf("\n");
	printf("----------------------------RadixBitsSort Test------------------------------\n");
	printf("\n");
	printf("Random Array\n\n");

	printf("qsort result: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

	start_time = clock();
	RadixBitsSort(actual, size, BITS_TO_CHECK);
	end_time = clock();

	if (0 == AreSameArr(actual, exp, size))
	{
		printf("RadixDigitsSort Test failed at %d\n", __LINE__);
		printf("----------------------------ACTUAL-------------------------------------\n");
		PrintArray(actual, size);
		printf("----------------------------EXP-------------------------------------\n");
		PrintArray(exp, size);
	}
	printf("My result %f\n\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);
	printf("\n");

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
	RadixBitsSort(actual, size, BITS_TO_CHECK);
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

	printf("My result %f\n\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

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
	RadixBitsSort(actual, size, BITS_TO_CHECK);
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
		new_arr[i] = (clock() * rand()) % range - RANGE_NEGATIV; /*range between -100 to 400*/
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
