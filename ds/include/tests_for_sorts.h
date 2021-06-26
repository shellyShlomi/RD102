

#ifndef OL_102_SORTS_TESTS_LIB_H
#define OL_102_SORTS_TESTS_LIB_H

#include <stddef.h> /* size_t */

#define SIZE (200)
#define RANGE_RANDOM (5000)
#define RANGE_NEGATIV (30)
#define BITS_TO_CHECK 32
#define DIGITES 9
/*
#define INTARRCMP(arr1, arr2) \
    Test((arr1), sizeof(arr1), (arr2), sizeof(arr2))

void (*sort)(void *, size_t);
void TestSorts();*/

/* FOR INTS !!!!*/
/* the commperision for the qsort and generic sorts data1 - data2 - comper for ints !!!!*/
int Compare(const void *data1, const void *data2);

int *CreateRandomNegativ(size_t size, int range);

int *CreateReversSorted(size_t size, int range);

int *CreateSorted(size_t size, int range);

int *CopyArr(int *arr, size_t size);

int AreSameArr(int *arr, int *other, size_t size);

void PrintArray(int *arr, size_t size);

#endif /* OL_102_SORTS_TESTS_LIB_H */
