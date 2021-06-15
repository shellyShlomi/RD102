#ifndef OL_102_BIN_MRG_QCK_H
#define OL_102_BIN_MRG_QCK_H
#include <stddef.h> /* size_t */

/* O (log n)*/
int IterBinSearch(int *arr_to_srch, size_t arr_size, int num, size_t *output_idx);
/* O (log n)*/
int RecBinSearch(int *arr_to_srch, size_t arr_size, int num, size_t *output_idx);
/* O (n log n)*/
int MergeSort(int *arr_to_sort, size_t arr_size);

/* base is the start of the array*/
/* O (n log n) avg*/
void RecQsort(void *base, size_t arr_size, size_t element_size, 
					  int (*compar)(const void *, const void *));

#endif /* OL_102_BIN_MRG_QCK_H */
