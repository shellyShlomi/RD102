#ifndef __BIT_ARRAY_H__
#define __BIT_ARRAY_H__

#include <stddef.h> /* size_t */

typedef size_t bit_arr_t;

bit_arr_t BitArrSetOn		(bit_arr_t bit_arr, size_t index);
bit_arr_t BitArrSetOff	    (bit_arr_t bit_arr, size_t index);
bit_arr_t BitArrSetBit	    (bit_arr_t bit_arr, size_t index, int value);
bit_arr_t BitArrSetAll	    (bit_arr_t bit_arr);
bit_arr_t BitArrResetAll	(bit_arr_t bit_arr);
char *    BitArrToString	(bit_arr_t bit_arr, char *dest);
int 	  BitArrGetVal	    (bit_arr_t bit_arr, size_t index);
bit_arr_t BitArrFlipBit	    (bit_arr_t bit_arr, size_t index);
bit_arr_t BitArrMirror	    (bit_arr_t bit_arr);
bit_arr_t BitArrRotR		(bit_arr_t bit_arr, size_t shifts);
bit_arr_t BitArrRotL		(bit_arr_t bit_arr, size_t shifts);
size_t 	  BitArrCountOn		(bit_arr_t bit_arr);
size_t    BitArrCountOff	(bit_arr_t bit_arr);
bit_arr_t BitArrMirrorLUT	(bit_arr_t bit_arr);
size_t 	  BitArrCountOnLUT	(bit_arr_t bit_arr);

#endif /* __BIT_ARRAY_H__ */

