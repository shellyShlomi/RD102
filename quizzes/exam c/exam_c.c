#include <stdio.h> 	/*	sprintf	*/

#include <stdlib.h> /*	fopen	*/
#include <assert.h> /*	assert	*/
#include <string.h> /*	strchr	*/

#include "exam_c.h"	/*	the function declaration	*/

#define BITS_IN_BYTE 8
#define BASE10 10

int FlipDigitsInNum(int num)
{
	
	int sign = 1;
	int flip_num = 0;
	
	if (num < 0)
	{
		sign = -sign;
		num = -num;
	}	
	
	while (num > 0)
	{
		flip_num *= BASE10;
		flip_num += (num % BASE10);
		num /= BASE10;
	}
	
	return (sign * flip_num);	
}


unsigned char ByteMirror(unsigned char num)
{
	
	unsigned char byte_mirror = 0;
	size_t i = 0;	

	
	for (i = 0; i < BITS_IN_BYTE; ++i)
	{
		byte_mirror <<= 1;
		byte_mirror |= (num & 1);
		num >>= 1;
	}
	
	return byte_mirror;	
}


int FlipBit(int val, unsigned int n)
{
	return (val ^ (1 << n));	
}


size_t CountBitInByte(unsigned char byte)	
{
	size_t counter = 0;

    while (byte > 0)
    {
       	byte &= (byte - 1);
        ++counter;
    }

    return (counter);

}

char RotateRotL(char byte, unsigned int nbits)
{
	unsigned char rotation = (unsigned char)byte;
	nbits &= (BITS_IN_BYTE - 1);

    return ((rotation << nbits) | (rotation >> ((BITS_IN_BYTE) - nbits)));
}

size_t StrLen(const char *str)
{

	size_t counter = 0;
	
	assert(NULL != str);
	
	while ('\0' != *str)
	{
		++counter;
		++str;
	}
	
	return counter;
}


int StrCmp(const char *str1, const char *str2)
{
	
	assert(NULL != str1);
	assert(NULL != str2);

	while (('\0' != *str1) || ('\0' != *str2))
	{
		if (*str1 != *str2)
		{
			return (*str1 - *str2);
		}
		++str1;
		++str2;
	}

	return 0;
}

char *StrCpy(char *dest, const char *src)
{

	const char * const origenal_dest = dest;
	
	assert(NULL != src);
	assert(NULL != dest);
	
	while ('\0' != *src)
	{
		*dest = *src;
		++src;
		++dest;
	}
	
	*dest = '\0';
	
	return (char *)origenal_dest;
}

char *StrnCpy(char *dest, const char *src, size_t n)
{
	const char * const origenal_dest = dest;
	
	assert(NULL != src);
	assert(NULL != dest);
	
	while (n > 0)
	{
		*dest = *src;
		--n;
		
		if ('\0' == *src)
		{
			break;
		}
		
		++src;
		++dest;
	}
	
	while (n > 0)
	{
		++dest;
		*dest = '\0';
		--n;
	}
	
	return (char *)origenal_dest;
}

char *StrCat(char *dest, const char *src)
{

	const char * const dest_oregin = dest;
	
	assert(NULL != src);
	assert(NULL != dest);
	
	dest = strchr(dest, '\0');
	
	strcpy(dest, src);
	
	return (char *)dest_oregin;

}

unsigned long GetNFibonacciElement(unsigned int n)
{
	size_t i = 1;	
	unsigned long fib = 1;
	unsigned long num = 0;
	
	assert(0 != n); /* based on the exam request */
	
	while (i < n)
	{
		fib = fib + num;
		num = fib - num;
		++i;
	}
	return fib;
}

char *Itoa(char *dest, int num)
{
	assert(NULL != dest);

	if (0 > sprintf(dest, "%d", num))
	{
		return NULL;
	}

    return dest;
}

long MultiplyBy8(int num)
{
	return (long)num << 3;
}

void SwapPtr(int **ptr1, int **ptr2)
{
	size_t temp = 0;	
	
	assert(NULL != ptr1);
	assert(NULL != ptr2);
	
	temp = (size_t)*ptr1;
	*ptr1 = *ptr2;
	*ptr2 = (int *)temp;

	return;	
}	


void Swap(int *x, int *y)
{
	assert(NULL != x);
	assert(NULL != y);

    if (x != y)
    {
        *x = *y ^ *x;
        *y = *y ^ *x;
        *x = *y ^ *x;
    }
    return ;		
}

void SwapAritmetics(int *x, int *y)
{
   	assert(NULL != x);
	assert(NULL != y);
	
    if (x != y)
    {
        *x = *x + *y;
        *y = *x - *y;
        *x = *x - *y;
    }
    return ;		
}

void SwapTemp(int *x, int *y)
{	
	int temp = 0;

	assert(NULL != x);
	assert(NULL != y);
	
	temp = *x;
	*x = *y;
	*y = temp; 
    
    return ;		
}

