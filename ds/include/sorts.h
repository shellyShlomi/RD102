#ifndef __OL102_SORTS_H__
#define __OL102_SORTS_H__

#include <stddef.h> /* size_t */

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


#endif /* __OL102_SORTS_H__*/
