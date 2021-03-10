#include <stdio.h>			/*printf function*/
#include <string.h>			/*strlen function*/
#include <assert.h>			/*assret function*/
#include "ilrd_strings.h"	/*the function declaration*/


int main ()
{
	TestFunction();
	return 0;
}

int StrCmp(const char *str1, const char *str2)
{

	int ret = 0; 			/*the return value */ 
	assert(str1);
	assert(str2);
	
	while (('\0' != *str1 ) && ('\0' != *str2))
	{
		if (*str1 > *str2)
		{
			ret = (*str1) - (*str2);
			return ret;
		}
		else if (*str1 < *str2)
		{
			ret = (*str1) - (*str2);
			return ret;
		} 
		++str1;
		++str2;
	}
	if (('\0' == *str1 ) && ('\0' != *str2))
	{
		ret = -((int)*str2);
		return  ret;		
	}
	else if (('\0' != *str1 ) && ('\0' == *str2))
	{			
		return  (int)*str1;				
	}	
	return 0;
}


size_t StrLen(const char *str)
{
	size_t counter = 0; /*counter to count the charecters in the string*/
	
	assert(str);

	while ('\0' != str[counter])
	{
		++counter;
	}
	

	return counter;
}



