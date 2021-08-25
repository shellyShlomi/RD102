/*	Developer: Shelly Shlomi;		*/
/*	Status: Done;					*/
/*	Description: MAX SUB ARR		*/

#include <stdio.h>	/*	printf	*/
#include <assert.h> /*	assert	*/

/* int maxSubArray(int arr[], size_t size, size_t *start, size_t *end); */
int maxSubArray(int arr[], size_t size, size_t *g_min, size_t *g_max);
void Test();

int main()
{
	Test();

	return (0);
}
/* 
int maxSubArray(int arr[], size_t size, size_t *start, size_t *end)
{
	int max = 0;
	int curr_max = 0;

	size_t i = 0;
	size_t start_curr = 0; 

	assert(NULL != arr);
	assert(NULL != start);
	assert(NULL != end);	

	*start = 0; 
	*end = 0; 

	for(i = 0; i < size; ++i)
	{
		curr_max += arr[i];
		
		if (curr_max >= max)
		{
			max = curr_max;
			*start = start_curr;
			*end = i;
		}
		
		if (curr_max < 0)
		{
			curr_max = 0;
			start_curr = i + 1;
		}
			
	}

	return max;
} */

int maxSubArray(int arr[], size_t size, size_t *g_min, size_t *g_max)
{
	int sum = 0;
	int curr = 0;

	size_t i = 0;
	size_t i_stats = 0;

	assert(NULL != arr);
	assert(NULL != g_min);
	assert(NULL != g_max);
	sum = arr[0];
	*g_min = 0;
	*g_max = 0;
	++i;

	for (i = i; i < size; ++i)
	{

		curr += arr[i];
		if (curr < arr[i])
		{
			curr = arr[i];
			i_stats = i;
		}
		if (sum <= curr)
		{
			*g_max = i;
			*g_min = i_stats;
			sum = curr;
		}
	}

	return sum;
}
void Test()
{
	int arr[] = {-1, -2, 4, 0, -5, 6, -2, 5};
	int arr1[] = {-2, 1, -3, 4, -1, 2, 3, -5, 4};
	int arr2[] = {-5, -2, -4, -8, -5, -6, -2, -5};
	int arr3[] = {10, -2, -4, -4, -5, -6, -2, -5};
	int arr4[] = {10, -2, -4, 0, -5, -6, -2, 100};

	size_t i = 0;
	size_t start = 0;
	size_t end = 0;
	size_t size = 0;

	printf("\nfor tha array :");

	size = sizeof(arr) / sizeof(int);

	for (i = 0; i < size; ++i)
	{
		printf("%d ", arr[i]);
	}

	printf("\n");

	printf("The bast max is: %d\n", maxSubArray(arr, size, &start, &end));
	printf("the first index is: %lu\n", start);
	printf("the secound index is: %lu\n\n", end);

	size = sizeof(arr1) / sizeof(int);

	printf("for tha array :");

	for (i = 0; i < size; ++i)
	{
		printf("%d ", arr1[i]);
	}

	printf("\n");

	printf("The bast max is: %d\n", maxSubArray(arr1, size, &start, &end));
	printf("the first index is: %lu\n", start);
	printf("the secound index is: %lu\n\n", end);

	size = sizeof(arr2) / sizeof(int);

	printf("for tha array :");

	for (i = 0; i < size; ++i)
	{
		printf("%d ", arr2[i]);
	}

	printf("\n");

	printf("The bast max is: %d\n", maxSubArray(arr2, size, &start, &end));
	printf("the first index is: %lu\n", start);
	printf("the secound index is: %lu\n\n", end);

	size = sizeof(arr3) / sizeof(int);

	printf("for tha array :");

	for (i = 0; i < size; ++i)
	{
		printf("%d ", arr3[i]);
	}

	printf("\n");

	printf("The bast max is: %d\n", maxSubArray(arr3, size, &start, &end));
	printf("the first index is: %lu\n", start);
	printf("the secound index is: %lu\n\n", end);

	size = sizeof(arr4) / sizeof(int);

	printf("for tha array :");

	for (i = 0; i < size; ++i)
	{
		printf("%d ", arr4[i]);
	}

	printf("\n");

	printf("The bast max is: %d\n", maxSubArray(arr4, size, &start, &end));
	printf("the first index is: %lu\n", start);
	printf("the secound index is: %lu\n\n", end);

	return;
}
