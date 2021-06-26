#ifndef __OL102_SORTS_H__
#define __OL102_SORTS_H__

#include <stddef.h> /* size_t */
typedef int (*compar_t)(const void *, const void *);

/* O(n^2) */
void InsertionSort(int arr[], size_t size);

/* O(n^2) */
void SelectionSort(int arr[], size_t size);

/* O(n^2) */
void BubbleSort(int arr[], size_t size);

/* O(n + k), k - range of input */
int CountSort(int arr[], size_t size);

/* O(n * k), k - num of digits */
int RadixDigitsSort(int arr[], size_t size, size_t n_digits);

/* O(n * k), k - num of bits */
int RadixBitsSort(int arr[], size_t size, size_t n_bits);

int MergeSort(int *arr_to_sort, size_t arr_size);

void RecQsort(void *base, size_t arr_size, size_t element_size, compar_t compar);


#endif /* __OL102_SORTS_H__*/
