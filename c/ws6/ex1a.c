/* Developer: Anna Pest
   Status: writing stage
   Date: 25.03.21
   Description: bitwise functions */
#include <stdio.h>		/* printf */
#include <assert.h>		/* assert */
#include "ex1.h"


static int IsOnlyThree(unsigned int num);
static unsigned char *CountBitsLut();
static int bit_return(int a, int loc);


/* aprroved by roman */
long Pow2(unsigned int x, unsigned int y)
{
	return (long)x << y;
}

/* aprroved by Yakov */
int IsPow2Loop(unsigned int n)
{
	unsigned int is_power = 1;
	
	if (n == 0)
	{
		return 0;
	}
	
	while(is_power < n)
	{
		is_power <<= 1;	
	}
	
	return (is_power == n) ? 1 : 0;
}

/* aprroved by Yakov */
int IsPow2NoLoop(unsigned int n)
{
	if (n == 0)
	{
		return 0;
	}
	
	if (n & (n-1))
		return 0;
	else
		return 1;
}

/* aprroved by Roman */
int Add1(int n)
{
	unsigned int mask = 1;
	
	while (n & mask)
	{
		n = n ^ mask;
		mask <<= 1;
	}
    
	n = n ^ mask;
    
	return n;
}

/* aprroved by Roman */
void PrintThreeOn(unsigned int nums[], size_t length)
{
	size_t i = 0;
	
	for(i = 0; i < length; i++)
	{
		if (IsOnlyThree(nums[i]))
		{
			printf("%u ",nums[i]);
		}
	}
	printf("\n");
}

/* aprroved by Roman */
static int IsOnlyThree(unsigned int num)
{
	int counter = 3;
	
	while (0 < num && 0 <= counter)
	{
		if (num & 1)
		{
			counter--;
		}
		
		num >>= 1;
	}
	
	return (0 == counter) ? 1 : 0;
}

/* aprroved by Nir */
unsigned char ByteMirrorLoop(unsigned char byte)
{
	unsigned char low = 0x01; 
	unsigned char high = 0x80;
	unsigned char res = 0;
	int i = 0;
	int size  = 8;
	
	while (i < size)
	{
		if (byte & low)
		{
			res |= high;	
		}
		
		low <<= 1;
		high >>= 1;
		i++;
	}
	return res; 
}

/* aprroved by Nir */
unsigned char ByteMirrorNoLoop(unsigned char byte) 
{
	unsigned char res1 = 0;
	unsigned char res2 = 0;
	
	res1 = (byte & 0xF0) >> 4;	/* swap nibbles */
	res2 = (byte & 0x0F) << 4;
	byte = res1 | res2;
	
	res1 = (byte & 0xCC) >> 2;	/* swap half nibbles inside the nibble  */
	res2 = (byte & 0x33) << 2;
	byte = res1 | res2;
	
	res1 = (byte & 0xAA) >> 1;	/* swap each pair of bits inside the nibble */
	res2 = (byte & 0x55) << 1;
	byte = res1 | res2;

	return byte;
}

/* approved by Nir*/
int IsBit2And6On(unsigned char byte)
{
	unsigned char mask = 0x40;
	
	mask = mask & byte;
	mask >>= 4;
	mask = mask & byte;
	
	return mask >> 2; 
}

/* approved by Nir*/
int IsBit2Or6On(unsigned char byte)
{
	unsigned char mask = 0x00;
	
	mask = mask | byte;
	mask >>= 4;
	mask = mask | byte;
	
	return (mask >> 2) & 0x01; 
}

/* approved by Nir*/
unsigned char Swap3And5(unsigned char byte)
{
	unsigned char bit3 = 0;
	unsigned char bit5 = 0;
	unsigned char xor_res; 
	unsigned char mask = 1;
	
	bit3 = byte >> 3;
	bit5 = bit3 >> 2;
	
	bit3 = bit3 & mask;
	bit5 = bit5 & mask;
	
	xor_res = bit3^bit5;
	
	bit3 = xor_res << 3;
	bit5 = bit3 << 2;
	
	xor_res = bit3 | bit5;
	
	return byte ^ xor_res;
}

/* approved by Roman */
unsigned int DivideBy16(unsigned int num)
{
	num >>= 4;
	
	return num <<= 4;
}

/* approved by Nir */
void Swap(unsigned int *x, unsigned int *y)
{
	assert(NULL != x);
	assert(NULL != y);
	
	*y = *x ^ *y;
	*x = *x ^ *y;
	*y = *x ^ *y;
	
	return;
}

/* approved by Shelly */
unsigned int CountBitsLoop(int num)
{
	int counter = 0;
	
	while (0 < num)
	{
		if (num & 1)
		{
			counter++;
		}
		num >>= 1;
	}
	return counter;
}

/* approved by Ohad */
unsigned int CountBitsNoLoop(int num)
{
	unsigned int mask = 0x000000FF;
	int counter = 0;
	
	counter += CountBitsLut()[num & mask];
	
	num >>= 8;								/* second byte */
	counter += CountBitsLut()[num & mask];
	
	num >>= 8;								/* third byte */
	counter += CountBitsLut()[num & mask];
	
	num >>= 8;								/* fourth byte */
	counter += CountBitsLut()[num & mask];

	return counter;
}

/* approved by Ohad */
static unsigned char *CountBitsLut()
{
    static unsigned char arr_count_bits[256] = {0};
    static int init = 0;
    size_t i = 0;

    if (!init)
    {
    	init = 1;
    	
        for (i = 0; i < 256; ++i)
        {
            arr_count_bits[i] = CountBitsLoop(i);
        }
    }

    return arr_count_bits;
}


/* approved by Ohad */
void PrintFloatBits(float f)
{
    /* 
     * 1 sign bit (30)
     * 8 exponent bit (23-30)
     * 23 fraction bits (0-22)
     */
    int *ptr_to_float = NULL;
    int i = 0;
    
    ptr_to_float = (int *)&f;
   
    for (i = 31; i >= 0; i--)
    {	
    	if (i == 30 || i == 22)
    	{
    		printf(" ");
    	}
        printf("%d", bit_return(*ptr_to_float, i));	/* print from 31 bit to 0 */
    }
    printf("\n");

    return;
}

/* approved by Ohad */
static int bit_return(int num, int num_of_shifts)   
{
    int buf = num & (1 << num_of_shifts);

    if (buf == 0) 
    {
    	return 0;
    }
    else
    { 
    	return 1;
    } 
}













