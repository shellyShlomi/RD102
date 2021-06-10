
/*  Developer: Shelly Shlomi;									*
 *  Status:; done												*
 *  Date Of Creation:25.05.21;									*
 *  End Date: 27.05.21;											*
 *  Date Of Approval:--.05.21;									*
 *  Approved By:												*
 *  Description: sorting functions - algorithms ws				*/
 
 
#include <assert.h> /*assert*/
#include <stdint.h> /*SIZE_MAX*/
#include <stdlib.h> /*malloc*/
#include <string.h> /* memcpy */

#include "sorts.h"

#define BASE10 (10)
#define BOOL_TRUE (1)
#define BOOL_FALUT (0)
#define BASE2 (2)

/* helper funcs */
static void Swap(int *x, int *y);
static void FindMinAndMax(int arr[], size_t size,int *min, int *max);
static int CountSortHelper(int arr[], size_t size, size_t param, size_t (*Index)(int arr_val, int param), size_t range);
size_t GetCount(int arr_val, int param);
size_t GetRadixBits(int arr_val, int param);
size_t GetRadixDigits(int arr_val, int param);

/*------------------------------implementetion--------------------------------*/

void InsertionSort(int arr[], size_t size)
{
	size_t i = 0;
	long int j = 0;/*cuse of the condition at 140*/
	int curr = 0;
	
	assert(arr);
	assert(0 < size);
	
	for (i = 1; i < size; ++i)
	{
		curr =  arr[i];
		for (j = i - 1; 0 <= j && arr[j] > curr; --j)
		{
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = curr;
	}
	
	return ; 

}


void SelectionSort(int arr[], size_t size)
{

	size_t i = 0;
	size_t j = 0;
	size_t min_idx = 0;
	
	assert(arr);
	assert(0 < size);
	
	for (i = 0; i < size - 1; ++i)
	{
		min_idx = i;
		for (j = i + 1; j < size; ++j)
		{
			min_idx = arr[j] < arr[min_idx] ? j : min_idx; 
		}
			Swap((arr + i), (arr + min_idx));
		
	}
	
	return ; 
}


void BubbleSort(int arr[], size_t size)
{

	size_t i = 0;
	size_t j = 0;
	size_t is_sort = BOOL_FALUT;
	
	assert(arr);
	assert(0 < size);
	
	for (i = 0; i < size - 1; ++i)
	{
		for (j = 0; j < size - i - 1; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				Swap((arr + j), (arr + j + 1));	
				is_sort = BOOL_TRUE;
			}
		
		}
		
		if (BOOL_FALUT == is_sort)
		{
				return ; 		
		}
	}
	
	return ; 
}


int CountSort(int arr[], size_t size)
{
	size_t range_size = 0;
	int min = 0;
	int max = 0;

	assert(0 < size);
	assert(arr);
	
	FindMinAndMax(arr, size, &min, &max);
	range_size = max - min + 1;

	return (CountSortHelper(arr, size, min, GetCount, range_size));
}


int RadixDigitsSort(int arr[], size_t size, size_t n_digits)
{
	size_t i = 0;
	size_t expo = 1;

	assert(arr);
	assert(0 < size);
	assert(0 < n_digits);
	
	for (i = 0; i < n_digits; ++i)
	{
		if (CountSortHelper(arr, size, expo, GetRadixDigits, BASE10))
		{
			return (1);
		}
	}
	return (0);
}

int RadixBitsSort(int arr[], size_t size, size_t n_bits)
{
	size_t i = 0;

	assert(arr);
	assert(0 < size);
	assert(0 < n_bits);
	
	for (i = 0; i < n_bits; ++i)
	{
		if (CountSortHelper(arr, size, i, GetRadixBits, BASE2))
		{
			return (EXIT_FAILURE);
		}
	}

	return (EXIT_SUCCESS);
}

/*------------------------------helper functions------------------------------*/


static int CountSortHelper(int arr[], size_t size, size_t param, size_t (*Index)(int arr_val, int param), size_t range)
{
	int *temp_arr = NULL;
	int *sort_arr = NULL;
	long int i = 0;
	
	assert(arr);
	assert(Index);
	assert(0 < size);
	
	sort_arr = (int *)calloc(size, sizeof(int));
	if (NULL == sort_arr)
	{	
		return (1);
	}
	
	temp_arr = (int *)calloc(range, sizeof(int));
	if (NULL == temp_arr)
	{
		free(sort_arr);
		return (1);
	}
	
	for (i = 0; (size_t)i < size; ++i)
	{
		++temp_arr[Index(arr[i], param)];
	}	
	
	for (i = 1; (size_t)i < range; ++i)
	{
		temp_arr[i] += temp_arr[i  - 1];
	}
	
	for (i = size - 1; i >= 0 ; --i)
	{
		sort_arr[temp_arr[Index(arr[i], param)] - 1] = arr[i];
		--temp_arr[Index(arr[i], param)];
	}
	
	memcpy(arr, sort_arr, size * sizeof(int));
	
	free(sort_arr);
	free(temp_arr);
		
	return (0);
}

size_t GetCount(int arr_val, int param)
{
	return(arr_val - param);
}


size_t GetRadixBits(int arr_val, int param)
{
	return(((size_t)arr_val >> (size_t)param) & 1);
}


size_t GetRadixDigits(int arr_val, int param)
{
	assert(0 < param);
	
	return((arr_val / (size_t)param) % BASE10);
}


static void FindMinAndMax(int arr[], size_t size, int *min, int *max)
{
	size_t j = 0;
	
	assert(max);
	assert(min);
	assert(arr);
	assert(0 < size);
	
	*max = arr[0];
	*min = arr[0];
	
	for (j = 1; j < size; ++j)
	{
		*min = arr[j] < *min ? arr[j] : *min;
		*max = arr[j] > *max ? arr[j] : *max; 
	}

	return ;
}

static void Swap(int *x, int *y)
{	
	int temp = 0;

	assert(x);
	assert(y);
	
	temp = *x;
	*x = *y;
	*y = temp; 
    
    return ;		
}


