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


int StrCaseCmp(const char *str1, const char *str2)
{
	assert(str1);
	assert(str2);

	while (('\0' != *str1) || ('\0' != *str2))
	{
	
		if (tolower(*str1) != tolower(*str2))
		{
			return tolower(*str1) - tolower(*str2);
		}
		++str1;
		++str2;
	}
	return 0;
}



char *StrChr(const char *src, int c)
{
	assert(src);
	
	while ( (char)'\0' <= *src )
	{
		if ((char)c == *src)
		{
			return (char *)src;
		} 
		++src;
	}
	
	return NULL;
}

char *StrDup(const char *str)
{
		char *new_string = NULL;
		size_t size = strlen(str) + 1;;
		
		assert(str);
		
		new_string = (char *)malloc(size);
		
		if (new_string == NULL) 
		{
			/*fprintf(errno, "malloc failed\n");*/
			return NULL;
		}

return (char *)strcpy(new_string, str);

}


