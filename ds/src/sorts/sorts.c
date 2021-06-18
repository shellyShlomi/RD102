
/*  Developer: Shelly Shlomi;									*
 *  Status: Approved;											*
 *  Date Of Creation:25.05.21;									*
 *  End Date: 27.05.21;											*
 *  Date Of Approval:29.05.21;									*
 *  Approved By: anna											*
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
static void FindMinAndMax(int arr[], size_t size, int *min, int *max);
static int CountSortHelper(int arr[], size_t size, size_t param, size_t (*index_val)(int arr_val, int param), size_t range);
static size_t GetCount(int arr_val, int param);
static size_t GetRadixBits(int arr_val, int param);
static size_t GetRadixDigits(int arr_val, int param);

static int Merge(int *arr_to_sort, size_t left, size_t mid, size_t right);
static int FindLefAndRitghMergeSort(int *arr_to_sort, size_t left, size_t right);
static void SwapM(void *elem1, void *elem2, size_t element_size);
static void HelperQuickSort(void *arr, long int low, long int high,
                                    size_t element_size, compar_t compar);
static size_t PartitionQsort(void *arr, long int low, long int high,
                             size_t element_size, compar_t compar);
static void HelperQuickSort(void *arr, long int low, long int high,
                                    size_t element_size, compar_t compar);							 
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
		for (j = i - 1; (0 <= j) && (arr[j] > curr); --j)
		{
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = curr;
	}
	
	return; 
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
	
	return; 
}


void BubbleSort(int arr[], size_t size)
{

	size_t i = 0;
	size_t j = 0;
	size_t is_unsort = BOOL_TRUE;
	
	assert(arr);
	assert(0 < size);
	
	for (i = 0; i < size - 1 && is_unsort; ++i)
	{
		is_unsort = BOOL_FALUT;
		
		for (j = 0; j < size - i - 1; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				Swap((arr + j), (arr + j + 1));	
				is_unsort = BOOL_TRUE;
			}
		}
	}
	
	return; 
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
			return (EXIT_FAILURE);
		}
		expo *= BASE10;
	}
	
	return (EXIT_SUCCESS);
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


int MergeSort(int *arr_to_sort, size_t arr_size)
{
    return (FindLefAndRitghMergeSort(arr_to_sort, 0, arr_size - 1));
}

static int FindLefAndRitghMergeSort(int *arr_to_sort, size_t left, size_t right)
{
    size_t mid = 0;
    int status = -1;

    assert(arr_to_sort);

    if (left < right)
    {
        mid = (right + left) / 2;
        FindLefAndRitghMergeSort(arr_to_sort, left, mid);
        FindLefAndRitghMergeSort(arr_to_sort, mid + 1, right);
        status = Merge(arr_to_sort, left, mid, right);
    }

    return (status);
}

static int Merge(int *arr_to_sort, size_t left, size_t mid, size_t right)
{
    size_t j = mid + 1;
    size_t i = left;
    size_t k = 0;

    int *arr = (int *)malloc(sizeof(int) * ((right - left) + 1));
    assert(arr_to_sort);

    if (!arr)
    {
        return (1);
    }

    while (i <= mid && j <= right)
    {
        if (arr_to_sort[i] < arr_to_sort[j])
        {
            arr[k] = arr_to_sort[i];
            ++i;
            ++k;
        }
        else
        {

            arr[k] = arr_to_sort[j];
            ++j;
            ++k;
        }
    }

    while (i <= mid)
    {
        arr[k] = arr_to_sort[i];
        ++i;
        ++k;
    }

    while (j <= right)
    {
        arr[k] = arr_to_sort[j];
        ++j;
        ++k;
    }

    for (i = left, k = 0; i <= right; ++i, ++k)
    {
        arr_to_sort[i] = arr[k];
    }

    free(arr);

    return (0);
}

void RecQsort(void *base, size_t arr_size, size_t element_size, compar_t compar)
{
    HelperQuickSort(base, 0, arr_size - 1, element_size, compar);
}

static void HelperQuickSort(void *arr, long int low, long int high,
                                    size_t element_size, compar_t compar)
{
    long int pivot = 0;
    assert(arr);

    if (low < high)
    {
        pivot = PartitionQsort(arr, low, high, element_size, compar);

        HelperQuickSort(arr, low, (pivot - 1), element_size, compar);
        HelperQuickSort(arr, (pivot + 1), high, element_size, compar);
    }
}

static size_t PartitionQsort(void *arr, long int low, long int high,
                             size_t element_size, compar_t compar)
{
    long int i = low - 1;
    assert(arr);

    while (low < high)
    {
        if (0 > compar((char *)arr + (low * element_size),
                       (char *)arr + (high * element_size)))
        {
            ++i;
            SwapM((char *)arr + (i * element_size),
                 (char *)arr + (low * element_size), element_size);
        }
        ++low;
    }

    SwapM((char *)arr + ((i + 1) * element_size),
         (char *)arr + (high * element_size), element_size);

    return ((size_t)(i + 1));
}

static void SwapM(void *elem1, void *elem2, size_t element_size)
{
    char temp = '\0';

    assert(element_size > 0);
    assert(elem1);
    assert(elem2);

    while (0 < element_size)
    {
        temp = *(char *)elem1;
        *(char *)elem1 = *(char *)elem2;
        *(char *)elem2 = temp;
        ++(*(char *)&elem1);
        ++(*(char *)&elem2);
        --element_size;
    }

    return;
}



/*------------------------------helper functions------------------------------*/


static int CountSortHelper(int arr[], size_t size, size_t param, size_t (*index_val)(int arr_val, int param), size_t range)
{
	int *counts_arr = NULL;
	int *sort_arr = NULL;
	long int i = 0;
	
	assert(arr);
	assert(index_val);
	assert(0 < size);
	
	sort_arr = (int *)calloc(size, sizeof(int));
	if (NULL == sort_arr)
	{	
		return (EXIT_FAILURE);
	}
	
	counts_arr = (int *)calloc(range, sizeof(int));
	if (NULL == counts_arr)
	{
		free(sort_arr);
		return (EXIT_FAILURE);
	}
	
	for (i = 0; (size_t)i < size; ++i)
	{
		++counts_arr[index_val(arr[i], param)];
	}	
	
	for (i = 1; (size_t)i < range; ++i)
	{
		counts_arr[i] += counts_arr[i  - 1];
	}
	
	for (i = size - 1; i >= 0 ; --i)
	{
		sort_arr[counts_arr[index_val(arr[i], param)] - 1] = arr[i];
		--counts_arr[index_val(arr[i], param)];
	}
	
	memcpy(arr, sort_arr, size * sizeof(int));
	
	free(sort_arr);
	free(counts_arr);
		
	return (EXIT_SUCCESS);
}

static size_t GetCount(int arr_val, int param)
{
	return(arr_val - param);
}


static size_t GetRadixBits(int arr_val, int param)
{
	return((arr_val >> (size_t)param) & 1);
}


static size_t GetRadixDigits(int arr_val, int param)
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



