#ifndef __BIT_ARR_H__
#define __BIT_ARR_H__

#include <stddef.h>  /*size_t*/

typedef size_t bit_arr_t;

bit_arr_t BitArrSetOn		(bit_arr_t bit_array, size_t index);
bit_arr_t BitArrSetOff		(bit_arr_t bit_array, size_t index);
bit_arr_t BitArrSetAll		(bit_arr_t bit_array);
bit_arr_t BitArrResetAll	(bit_arr_t bit_array);
bit_arr_t BitArrSetBit		(bit_arr_t bit_array, size_t index, int value);
int 	  BitArrGetVal		(bit_arr_t bit_array, size_t index);
bit_arr_t BitArrFlipBit		(bit_arr_t bit_array, size_t index);
bit_arr_t BitArrRotR		(bit_arr_t bit_array, size_t shifts);
bit_arr_t BitArrRotL		(bit_arr_t bit_array, size_t shifts);
bit_arr_t BitArrMirror		(bit_arr_t bit_array);
size_t BitArrCountOn		(bit_arr_t bit_array);
size_t BitArrCountOff		(bit_arr_t bit_array);
char *BitArrToString		(bit_arr_t bit_array, char *dest);

#endif /*__BIT_ARR_H__*/
