/*  Developer: Shelly Shlomi;									*/
/*  Status: approved;											*/
/*  Date Of Creation:11.04.21;									*/
/*  Date Of Approval: 13.04.21;									*/
/*  Approved By: NIR 											*/
/*  Description: styatic librery of memset memcpy memmove;		*/

#include <stdio.h>  /* print */
#include <assert.h> /* assert */
#include <limits.h>	/* INT_MIN */
#include <ctype.h>	/* isspace */


#include "part2.h"     /* function declaration */

#define BASE10 10
#define ITOA_BASE36 36
#define ASCII_TABLE_SIZE 128
#define DEC_OFFSET 10
#define UNUESED(X) (void)(X)



static size_t CountChrInNum(int to_add,const size_t base);


/* Approved By: NIR */
char *ItoaBase10(int value, char *str)
{

	char *original_str = str;
	int sign = 1;
	size_t chars_in_val = 0;
	
	assert(NULL != str);
	
	if(0 > value)
	{
		sign = -sign;
		*str = '-';
		value = -value;
		++str;
	}
	
	chars_in_val = CountChrInNum(value, BASE10);
	
/* rech the lest char of num + 1 */
	str = str + chars_in_val;
	
	*str = '\0';
	
	/* hendel the 0 case*/
	do
	{
		--str;
		*str = (value % BASE10) + '0';
		value /= BASE10;
		
	}while(0 < value);
	
	return original_str;
}

/* Approved By: oahd */
char *ItoaBaseTil36(int value, char *str, int base)
{

	char *original_str = str;
	size_t chars_in_val = 0;
	
	assert(NULL != str);
	
	if (0 > value)
	{	
		value = -value;
		if (BASE10 == base)
		{
			*str = '-';
			++str;			
		}
	}
	
	chars_in_val = CountChrInNum(value, (size_t)base);
	
/* rech the lest char of num + 1 */
	str = str + chars_in_val;
	
	*str = '\0';
	
	/* hendel the 0 case*/
	do
	{
		--str;
		9 < (value % base) ? *str = (value % base) + 'a' - DEC_OFFSET :
							(*str = (value % base) + '0');
		value /= base;
		
	}while(0 < value);
	
	return original_str;
}

/* Approved By: NIR */
int AtoiBase10(const char *str)
{

	int sign = 1;
	int return_val = 0;
	
	assert(NULL != str);
	
	while (isspace(*str))
	{
		++str;
	}
	
	if ('-' == *str)
	{
		++str;
		sign = -sign;
	}

	
	while (isdigit(*str))
	{
		return_val *= BASE10;
		return_val += (int)(*str - '0');
		++str;
	}
	
	return return_val * sign;
}

/* Approved By: NIR */
int AtoiBaseTil36(const char *str, int base)
{

	int sign = 1;
	int return_val = 0;
	int alpha_val = 0;
	int isalpha_val = 0;
	
	assert(NULL != str);
	
	while (isspace(*str))
	{
		++str;
	}
	
	if ('-' == *str)
	{
		++str;
		sign = -sign;
	}

	while (isalnum(*str))
	{
		/* initiat the letter value of the courent char */
		alpha_val = (tolower(*str) -'a' + DEC_OFFSET);
		
		/* test whether the courent char is a letter or a digit */
		isalpha_val = isalpha(*str);
		
		/* test if the value of the char is biger then the base */
		if ((isalpha_val && (alpha_val > base)) || 
			(isdigit(*str) && ((*str -'0') >= base)))
		{
			break;
		}

		return_val *= base;
	 	return_val += (isalpha_val) ? alpha_val : (int)(*str - '0');
	 	
		++str;
	}
	
	return return_val * sign;
}

/* Approved By: NIR */
void PrintFirstAndSecond(const char *arr1, size_t len1, const char *arr2, 
									size_t len2, const char *arr3, size_t len3)
{
	int counter_arr[ASCII_TABLE_SIZE] = {0};
	size_t i = 0;
	
	assert(NULL != arr1);
	assert(NULL != arr2);	
	assert(NULL != arr3);
	
	for (i = 0; i < len3; ++i)
	{
		counter_arr[(size_t)arr3[i]] = -1;
	}
	
	for (i = 0; i < len1; ++i)
	{	
		if (-1 == counter_arr[(size_t)arr1[i]])
		{
			continue;
		}
		
		counter_arr[(size_t)arr1[i]] = 1;
	}
	
	for (i = 0; i < len2; ++i)
	{	
		if (-1 == counter_arr[(size_t)arr2[i]])
		{
			continue;
		}
		
		else if (1 == counter_arr[(size_t)arr2[i]])
		{
			printf("%c ", arr2[i]);
			counter_arr[(size_t)arr2[i]] = -1;
		}
		
	}
	
	printf("\n");

	return ;
}

/* Approved By: NIR */
int IsLittleEndian()
{
/* 0x00000001 */
	int one = 1;
	char *identifier = (char *)&one;

/* whether the LSB at the first addresses */
	return (*identifier);
}

/* counter func iner func */
static size_t CountChrInNum(int to_add, const size_t base)
{
	size_t count = 0;

	if (0 == to_add)
	{
		++count;
		return count;
	}

	if (0 == to_add)
	{
		++count;
		return count;
	}

	while (0 != to_add)
	{
		to_add /= base;
		++count;
	}

	return count;
}
