
/*  Developer: Shelly Shlomi;									*/
/*  Status: approved;											*/
/*  Date Of Creation:06.04.21;									*/
/*  Date Of Approval: 07.04.21;									*/
/*  Approved By: final approved (run only bit_array.c) by anna	*/
/*  Description: bit array data strctur;						*/

#include <limits.h> /* CHAR_BIT */
#include <stdint.h> /* SIZE_MAX */
#include <assert.h> /* assert */

#include "bit_array.h"

#define UNUSED(x) (void)(x)
#define WORD_SIZE sizeof(bit_arr_t) * CHAR_BIT
#define BYTE_MAX 255

/* O(1) time & space - approved by geta */
bit_arr_t SetOn(bit_arr_t bit_array, size_t index)
{
    assert(WORD_SIZE > index);

    return (bit_array | (bit_arr_t)1 << index);
}

/* O(1) time & space - approved by geta */
bit_arr_t SetOff(bit_arr_t bit_array, size_t index)
{
    assert(WORD_SIZE > index);

    return (bit_array & ~((bit_arr_t)1 << index));
}

/* O(1) time & space - approved by geta */
bit_arr_t SetAll(bit_arr_t bit_array)
{
    UNUSED(bit_array);
    return SIZE_MAX;
}

/* O(1) time & space - approved by geta */
bit_arr_t ResetAll(bit_arr_t bit_array)
{
    UNUSED(bit_array);
    return 0;
}

/* O(1) time & space - approved by geta */
bit_arr_t SetBit(bit_arr_t bit_array, size_t index, int value)
{
    assert(WORD_SIZE > index);
    assert(3 > value && value > -1);
    return ((bit_array & (~((bit_arr_t)1 << index))) |
            ((bit_arr_t)value << index));
}

/* O(n) time , O(1)space - approved by anna */

char *ToString(bit_arr_t bit_array, char *dest)
{

    char *dest_orig = dest;

    assert(NULL != dest);

    dest += 64;
    *dest = '\0';

    while (dest_orig <= dest)
    {
        --dest;
        *dest = '0' + (bit_array & 1);
        bit_array >>= 1;
    }

    return dest_orig;
}

/* O(1) time & space - approved by anna */
int GetVal(bit_arr_t bit_array, size_t index)
{
    assert(WORD_SIZE > index);

    return ((bit_array >> index) & 1);
}

/* O(1) time & space - approved by roman */
bit_arr_t FlipBit(bit_arr_t bit_array, size_t index)
{
    assert(WORD_SIZE > index);

    return bit_array ^ ((bit_arr_t)1 << index);
}

/* O(1) time & space - approved by roman */
bit_arr_t RotR(bit_arr_t bit_array, size_t shifts)
{
    size_t shift = shifts & (WORD_SIZE - 1);

    return ((bit_array >> shift) | (bit_array << ((WORD_SIZE)-shift)));
}

/* O(1) time & space - approved by roman */
bit_arr_t RotL(bit_arr_t bit_array, size_t shifts)
{
    size_t shift = shifts & (WORD_SIZE - 1);

    return ((bit_array << shift) | (bit_array >> ((WORD_SIZE)-shift)));
}

/* O(1) time & space - approved by roman */
size_t CountOn(bit_arr_t bit_array)
{
    size_t i = 0;
    size_t counter = 0;

    static unsigned char count_lut[256] =
		{
            0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
            1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
            1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
            2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
            1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
            2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
            2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
            3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
            1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
            2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
            2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
            3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
            2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
            3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
            3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
            4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
		};

    for (i = 0; i < CHAR_BIT; ++i)
    {
        counter += (bit_arr_t)count_lut[(BYTE_MAX & bit_array)];
        bit_array = bit_array >> CHAR_BIT;
    }

    return (counter);
}

/* O(n) time *when all bits are on where n is bit num - 64*, O(1) space 
	- approved by roman */
size_t CountOff(bit_arr_t bit_array)
{
    size_t counter = 0;
    bit_arr_t not_bit_array = ~bit_array;

    while (not_bit_array > 0)
    {
        not_bit_array = not_bit_array & (not_bit_array - 1);
        ++counter;
    }

    return (counter);
}

/* O(1) time & space - approved by anna */
bit_arr_t Mirror(bit_arr_t bit_array)
{
    int i = 0; /* can't be size_t - cuas a infinet loop */

    bit_arr_t mirror = 0;
    bit_arr_t return_mirror = 0;

    static unsigned char mirror_lut[256] =
		{
            0x0, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0, 0x10, 0x90,
            0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0, 0x8, 0x88, 0x48, 0xc8,
            0x28, 0xa8, 0x68, 0xe8, 0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8,
            0x78, 0xf8, 0x4, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
            0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4, 0xc, 0x8c,
            0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec, 0x1c, 0x9c, 0x5c, 0xdc,
            0x3c, 0xbc, 0x7c, 0xfc, 0x2, 0x82, 0x42, 0xc2, 0x22, 0xa2,
            0x62, 0xe2, 0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
            0xa, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea, 0x1a, 0x9a,
            0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa, 0x6, 0x86, 0x46, 0xc6,
            0x26, 0xa6, 0x66, 0xe6, 0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6,
            0x76, 0xf6, 0xe, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
            0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe, 0x1, 0x81,
            0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1, 0x11, 0x91, 0x51, 0xd1,
            0x31, 0xb1, 0x71, 0xf1, 0x9, 0x89, 0x49, 0xc9, 0x29, 0xa9,
            0x69, 0xe9, 0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
            0x5, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5, 0x15, 0x95,
            0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5, 0xd, 0x8d, 0x4d, 0xcd,
            0x2d, 0xad, 0x6d, 0xed, 0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd,
            0x7d, 0xfd, 0x3, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
            0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3, 0xb, 0x8b,
            0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb, 0x1b, 0x9b, 0x5b, 0xdb,
            0x3b, 0xbb, 0x7b, 0xfb, 0x7, 0x87, 0x47, 0xc7, 0x27, 0xa7,
            0x67, 0xe7, 0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
            0xf, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef, 0x1f, 0x9f,
            0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff
		};

    /* i = CHAR_BIT - 1 : from 7-0 includ for shifting at the corect offset */
    for (i = CHAR_BIT - 1; 0 <= i; --i)
    {
        mirror = ((bit_arr_t)mirror_lut[(unsigned char)(BYTE_MAX & bit_array)]);
        return_mirror |= mirror << CHAR_BIT * i;
        bit_array = bit_array >> CHAR_BIT;
    }

    return (return_mirror);
}

