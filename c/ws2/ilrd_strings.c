#include "ilrd_strings.h" /*the function declaration*/

int StrCmp(const char *str1, const char *str2)
{
	assert(str1);
	assert(str2);

	while (('\0' != *str1) || ('\0' != *str2))
	{
		if (*str1 != *str2)
		{
			return *str1 - *str2;
		}
		++str1;
		++str2;
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


