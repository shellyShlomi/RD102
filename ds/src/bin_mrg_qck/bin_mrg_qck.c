/*  Developer: Shelly Shlomi;									*
 *  Status:Approved;				        					*
 *  Date Of Creation:13.06.21;									*
 *  Date Of Approval:15.06.21;									*
 *  Approved By: Getta;	            							*
 *  Description: Recursive Merge Sort & Quick Sort &            *
 *   binary search (both recutsive and iterativ)                */

#include <stddef.h>  /* size_t */
#include <stdlib.h> /* malloc */
#include <assert.h>/*  assert */

#include "bin_mrg_qck.h"
/*
typedef int (*compar_t)(const void *, const void *);

static int Merge(int *arr_to_sort, size_t left, size_t mid, size_t right);
static int FindLefAndRitghMergeSort(int *arr_to_sort, size_t left, size_t right);

static void HelperQuickSort(void *arr, long int low, long int high, size_t element_size, compar_t compar);
static size_t PartitionQsort(void *arr, long int low, long int high, size_t element_size, compar_t compar);
static void Swap(void *elem1, void *elem2, size_t element_size);
*/
int IterBinSearch(int *arr_to_srch, size_t arr_size, int num, size_t *output_idx)
{
    long int top = arr_size - 1; /*for arr size 10 the mid is 4 (0-9 indexses) && lower rang val of index*/
    long int down = 0;
    size_t mid = (arr_size) / 2;

    assert(arr_to_srch);
    assert(output_idx);

    while (top - down >= 0)
    {
        if (arr_to_srch[mid] == num)
        {
            *output_idx = mid;
            return (0);
        }

        else if (arr_to_srch[mid] < num)
        {
            down = mid + 1;
        }
        else
        {
            top = mid - 1;
        }

        mid = down + ((top - down) / 2);
    }

    return (1);
}



int RecBinSearch(int *arr_to_srch, size_t arr_size, int num, size_t *output_idx)
{
    int status = -1;
    size_t mid = (arr_size) / 2;
    int is_odd = 0;

    assert(arr_to_srch);
    assert(output_idx);

    is_odd = (arr_size & 1);

    if (arr_to_srch[mid] == num)
    {
        *output_idx = mid;
        return (0);
    }
    if (mid == 0)
    {
        return (1);
    }
    if (arr_to_srch[mid] > num)
    {
        status = RecBinSearch(arr_to_srch, mid, num, output_idx);
    }
    if (arr_to_srch[mid] < num)
    {
        status = RecBinSearch(arr_to_srch + mid, mid + is_odd, num, output_idx);
        *output_idx += mid;
    }

    return (status);
}
/*
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
            Swap((char *)arr + (i * element_size),
                 (char *)arr + (low * element_size), element_size);
        }
        ++low;
    }

    Swap((char *)arr + ((i + 1) * element_size),
         (char *)arr + (high * element_size), element_size);

    return ((size_t)(i + 1));
}

static void Swap(void *elem1, void *elem2, size_t element_size)
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
*/

/* vers_2
static int HelperRecBinSearch(int *arr_to_srch, long int left, long int rigth, int num, size_t *output_idx); */
/* vers 2
int RecBinSearch(int *arr_to_srch, size_t arr_size, int num, size_t *output_idx)
{
    assert(arr_to_srch);
    assert(output_idx);

    return (HelperRecBinSearch(arr_to_srch, 0, arr_size - 1, num, output_idx));
}

int HelperRecBinSearch(int *arr_to_srch, long int left, long int rigth, int num, size_t *output_idx)
{
    size_t mid = (rigth + left) / 2;

    if (rigth < left)qsort result: 0.000462
My result 0.002775



    if (arr_to_srch[mid] < num)
    {
        return (HelperRecBinSearch(arr_to_srch, mid + 1, rigth, num, output_idx));
    }
    else if (arr_to_srch[mid] > num)
    {
        return (HelperRecBinSearch(arr_to_srch, left, mid - 1, num, output_idx));
    }
    else
    {
        *output_idx = mid;
        return (0);
    }
}
*/