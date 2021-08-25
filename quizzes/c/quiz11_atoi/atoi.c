
#include <stdio.h>  /* 	print 	*/
#include <ctype.h>	/* 	isspace	 */
#include <assert.h> /* 	assert 	*/
#include <stdlib.h> /* 	atoi 	*/

#define BASE10 10


int AtoiBase10(const char *str);
void Test();

int main()
{
	Test();
	
	return 0;
}

int AtoiBase10(const char *str)
{

	int sign = 1;
	int return_val = 0;
	
	assert(NULL != str);
	
	while (isspace(*str))
	{
		++str;
	}
	
	if ('-' == *str || '+' == *str)
	{	
		if ('-' == *str)
		{
			sign = -sign;
		}
		++str;
	}
	
	while (isdigit(*str))
	{
		return_val *= BASE10;
		return_val += (int)(*str - '0');
		++str;
	}
	
	return return_val * sign;
}

void Test()
{
	char str_arr[][50] =  {
							"102554", 
							"    ++1", 
							"-100656", 
							"-10H0656", 
							"-0", 
							"0", 
							"\n\t-100656",
							"  -sh66",
							"-56j89",
							"g"
							}; 
	size_t i = 0;
	size_t size = sizeof(str_arr)/sizeof(str_arr[i]);

	for (i = 0; i < size; ++i)
	{
		if (atoi(str_arr[i]) != AtoiBase10(str_arr[i]))
		{
			printf("AtoiBase10 error at index: %ld\n", i);
		}
	}

	return; 
}

