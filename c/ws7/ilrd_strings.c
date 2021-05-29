#include <errno.h> 	/*strdup function*/
#include "ilrd_strings.h" /*the function declaration*/

/* Developer: Shelly Shlomi 
   Status: aproved by ohad;   
   Description: strings libery*/

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

/*aprovde by tal*/
char *StrCpy(char *dest, const char *src)
{
	char *dest_oregin = dest;			/*saving the original location*/
										/*of the destanetion pointer*/
	assert(src);
	assert(dest);

	while ('\0' != *src)
	{
		*dest = *src;
		++dest;
		++src;
	}
	*dest = '\0';

	return dest_oregin;
}

char *StrnCpy(char *dest, const char *src, size_t n)
{
	char *dest_oregin = dest;
	
	assert(src);
	assert(dest);
	
	while ('\0' != *src && 0 < n )
	{
		*dest = *src;
		++dest;
		++src;
		--n;
	}
	
	while ( 0 < n )
	{
		*dest = '\0';
		++dest;
		--n;
	}
	
	return dest_oregin;
}

