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
	
	while ('\0' != *src)
	{
		if (c == *src)
		{
			return (char *)src;
		} 
		++src;
	}
	
	if ('\0' == c)
	{
		return (char *)src;
	}	
	
	return NULL;
}

/*aprovde by roman*/
char *StrDup(const char *str)
{
	char *new_string = NULL;
	size_t size = strlen(str) + 1;;

	assert(str);
		
	new_string = (char *)malloc(size);
		
	if (!new_string) 
	{
		printf("malloc failed\n");
		return NULL;
	}

	return (char *)strcpy(new_string, str);

}
/*aprovde by shir*/
char *StrCat(char *dest, const char *src)
{
	char *dest_oregin = dest;
	
	assert(src);
	assert(dest);
	
	dest = strchr(dest, '\0');
	
	strcpy(dest, src);
	
	return dest_oregin;

}

/*aprovde by roman*/
char *StrnCat(char *dest, const char *src, size_t n)
{
	char *dest_oregin = dest;
	
	assert(src);
	assert(dest);
	
	dest = strchr(dest, '\0');
	
	while (0 < n && '\0' != *src)
	{
		*dest = *src;
		++dest;
		++src;
		--n;
	}
	
	*dest = '\0';
		
	return dest_oregin;

}

/*aprovde by ANNA*/
char *StrStr(const char *haystack, const char *needle)
{
	char *location_first_char_needle = NULL;
	
	size_t needle_size = 0;
	
	assert(haystack);
	assert(needle);

	if (('\0' == *haystack) && ('\0' == *needle))
	{
		return  (char *)haystack;
	}

	needle_size = strlen(needle);	
	
	location_first_char_needle = (char *)haystack;
	
	while ('\0' != *location_first_char_needle)
	{
		location_first_char_needle = strchr(location_first_char_needle,
																      *needle);
		
		if(NULL == location_first_char_needle)
		{
			return location_first_char_needle;		
		}	
		
		if (strncmp(location_first_char_needle, needle, needle_size) == 0)
		{	
			return location_first_char_needle;
		}
		
		++location_first_char_needle;
	}	
	return NULL;
}
