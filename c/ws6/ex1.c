
/* Developer: Shelly Shlomi         */
/* Status: final approved by anna;  */
/* Description: bit exercies        */
   
#include <stdio.h>  /*print*/
#include "ex1.h" /*function declaration*/

#define SIZE 256
#define BYTE_ON 0xFF
#define BIT_IN_BYTE 8
#define BIT_IN_int 32

static unsigned char *ByteMirrorArrLut();
static unsigned int *CountBitsNoLoopArrLut();


/*approved by shir*/
long Pow2(unsigned int x, unsigned int y)
{
	return ((long)x << y);
}

/*approved by avital*/
int IsPow2Loop(unsigned int n)
{
	unsigned int i = 1;
	
	while(i < n)
	{
		i = i << 1;
	}
	
	if (i == n)
	{
		return 1;
	}
	
	return 0;
}

/*approved by avital*/
int IsPow2NoLoop(unsigned int n)
{
	unsigned int minus1 = n - 1;
	
	if(0 == (minus1 & n) && 0 != n)
	{
		return 1;
	} 
	return 0;
}

/*approved by ohad*/
int Add1(int n)
{
	unsigned int i = 1;
	
	while (0 != (i & n))
	{
		n = n ^ i;
		i = i << 1;
	}
	return (n ^ i);
}



/*approved by avital*/
void PrintThreeOn(unsigned int nums[], size_t length)
{	
	unsigned int bits_on_equle_num = 0;
	unsigned int bits_on = 1;
	size_t i = 0;
	size_t counter = 0;
	
	if(NULL == nums)
	{
		return ;
	} 
	
	for(i = 0; i < length - 1 ; ++i)
	{
/*ending the loop when reaching the tested number*/
		while (bits_on_equle_num != nums[i]) 
		{				
			if (0 != (bits_on & nums[i]))
			{
				bits_on_equle_num += bits_on;
				++counter;
			}
			
			bits_on = bits_on << 1;
		}
		
		if (3 == counter)
		{
			printf("this number %u has 3 bit on \n", nums[i]);	
		}
		
		counter = 0;
		bits_on_equle_num = 0;
		bits_on = 1;
	}
	return ;
}


/*approved by anna*/
unsigned char ByteMirrorLoop(unsigned char byte)
{
	size_t index = 0;
	unsigned char mirror = '\0';
	unsigned char mirror_add = '\0';
	
	for (index = 0 ; index < 8; ++index)
	{							
		mirror = mirror << 1;
		mirror_add = byte & 1;
		mirror = mirror | mirror_add;
		byte = byte >>1;
	}
	return mirror;
}

/*approved by anna*/
static unsigned char *ByteMirrorArrLut()
{
	static unsigned char arr_mirror[SIZE] = {'\0'};
	size_t i = 0;

	if ('\0' == arr_mirror[1]) /*expected to be 128*/
	{
		for (i = 0 ; i < SIZE; ++i)
		{		
			arr_mirror[i] = ByteMirrorLoop(i);
		}
	}	
	return arr_mirror;
}

/*approved by anna*/
unsigned char ByteMirrorNoLoop(unsigned char byte)
{   
	return ByteMirrorArrLut()[byte];
}

/*approved by anna*/
int IsBit2And6On(unsigned char byte)
{
	return (68 == (byte & 68));
}

/*approved by anna*/
int IsBit2Or6On(unsigned char byte)
{
	return ((64 == (byte & 64)) || (4 == (byte & 4)));
}

/*approved by ohad*/
unsigned char Swap3And5(unsigned char byte)
{
	unsigned char a = '\0';
	unsigned char b = '\0';
	unsigned char mirror_byte = '\0';
	b =  (byte >> 5) & 1;
	a = (byte >> 3) & 1;
	mirror_byte = a ^ b; /*to test if the 3 & 5 bit are the same*/
	mirror_byte = ( mirror_byte << 3 ) | (mirror_byte << 5);

	return (byte ^ mirror_byte); /*to flip the 3 & 5 bit or do nothing*/
}

/*approved by ohad*/
unsigned int DivideBy16(unsigned int num)
{
	return ((num >> 4) << 4);/*when there is no smallest num div by 16 return 0*/	
}


/*approved by anna*/
void Swap(unsigned int *x, unsigned int *y)
{
    if (NULL != x && NULL != y)
    {
        *x = *y ^ *x;
        *y = *y ^ *x;
        *x = *y ^ *x;
    }
    return ;
}

/*approved by ohad*/
unsigned int CountBitsLoop(int num)
{	
    unsigned int num_local = (unsigned int)num;
	unsigned int counter = 0;

    while (0 < num_local)
    {
        counter += (num_local & 1);
        num_local = num_local >> 1;
    }

    return counter;
}

/*approved by ohad*/
static unsigned int *CountBitsNoLoopArrLut()
{
	static unsigned int arr_count[SIZE] = {0};
	size_t i = 0;
	
	if ('\0' == arr_count[1]) /*expected to be 1*/
	{
		for (i = 0 ; i < SIZE; ++i)
		{		
			arr_count[i] = CountBitsLoop(i);
		}
	}	
	return arr_count;
}

/*approved by ohad*/
unsigned int CountBitsNoLoop(int num)
{  
	unsigned int count_bits = 0;
	unsigned char all_bit_one_byte = BYTE_ON;
	
	count_bits = CountBitsNoLoopArrLut()[(num & all_bit_one_byte)];
	num = num >> BIT_IN_BYTE; /*taking the next byte*/
	
	count_bits += CountBitsNoLoopArrLut()[(num & all_bit_one_byte)];
	num = num >> BIT_IN_BYTE;
	
	count_bits += CountBitsNoLoopArrLut()[(num & all_bit_one_byte)];
	num = num >> BIT_IN_BYTE;
	
	return (count_bits + CountBitsNoLoopArrLut()[num & all_bit_one_byte]);
}


/*approved by roman*/
void PrintFloatBits(float f)
{
 	unsigned int temp = 0;
	unsigned int *local_float = (unsigned int *)&f;
	int count_loop = 0;
	
	printf("the number is: %.2f\n\t\t\t\t", f);
			
	for(count_loop = 31; 0 <= count_loop; --count_loop)
	{	
		temp = *local_float & (1 << count_loop);/*taking bits starts from last*/
		switch(temp >> count_loop)		/*chenging it to be the first (0 or 1)*/
		{	
			case 1:
			{	
				printf("1");
				break;
			}
			case 0:
			{	
				printf("0");
				break;			
			}
			default:
			{
				break;
			}
		}	
	}
	
	printf("\n");
	
	return ;
}




