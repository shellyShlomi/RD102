#ifndef __BIT_ARR_H__
#define __BIT_ARR_H__

#include <stddef.h>  /*size_t*/

typedef size_t bit_arr_t;

bit_arr_t SetOn		(bit_arr_t bit_array, size_t index);
bit_arr_t SetOff	(bit_arr_t bit_array, size_t index);
bit_arr_t SetAll	(bit_arr_t bit_array);
bit_arr_t ResetAll	(bit_arr_t bit_array);
bit_arr_t SetBit	(bit_arr_t bit_array, size_t index, int value);
int 	  GetVal	(bit_arr_t bit_array, size_t index);
bit_arr_t FlipBit	(bit_arr_t bit_array, size_t index);
bit_arr_t RotR		(bit_arr_t bit_array, size_t shifts);
bit_arr_t RotL		(bit_arr_t bit_array, size_t shifts);
bit_arr_t Mirror	(bit_arr_t bit_array);
size_t CountOn		(bit_arr_t bit_array);
size_t CountOff		(bit_arr_t bit_array);

char *ToString		(bit_arr_t bit_array, char *dest);

#endif /*__BIT_ARR_H__*/
