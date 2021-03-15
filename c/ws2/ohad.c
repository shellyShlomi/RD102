#include "ilrd_strings.h"

size_t StrLen(const char *str)
{
	const char *temp = str;
	
	assert (NULL != str);
	
	while ('\0' != *temp)
	{
		++temp;
	}
	
	return (temp - str);
}

int StrCmp(const char *str1, const char *str2)
{
	assert (NULL != str1 && str2);
	
	while ('\0' != *str1 || '\0' != *str2 )
	{
		if (*str1 != *str2)
		{
			return (*str1 - *str2);
		}
		
		++str1;
		++str2;
	}
	
	return (0);	 
}   

char *StrCpy(char *dest, const char *src)
{
	char *temp = dest;
	
	assert (NULL != src);
	assert (NULL != dest);
	
	while ('\0' != *src)
	{
		*dest = *src;
		++src;
		++dest;
	} 
	
	*dest = '\0';
	
	return (temp);
}

char *StrnCpy(char *dest, const char *src, size_t n)
{
	char *dest_original = dest;
	
	assert(NULL != src);
	assert(NULL != dest);
	
	while (0 < n && '\0' != *src)
	{
		*dest = *src;
		++src;
		++dest;
		--n;
	}
	
	while (0 < n)
	{
		*dest = '\0';
		++dest;
		--n;
	}
	
	return (dest_original);	
}

int StrCaseCmp(const char *str1, const char *str2)
{
	assert(NULL != str1); 
	assert(NULL != str2);

	while ('\0' != *str1 || '\0' != *str2)
	{
			
		if (tolower(*str1) != tolower(*str2))
		{
			return tolower(*str1) - tolower(*str2);
		}
		
		++str1;
		++str2;
	}

	return ((tolower(*str1) - tolower(*str2)));
} 

char *StrChr(const char *s, int c)
{
	assert(NULL != s);	
	
	while ('\0' != *s)
	{
		if (c == *s)
		{
			return ((char *)s);
		}
		
		++s;
	}
	
	if (c == *s)
	{
		return ((char *)s);
	}
	
	return NULL;
}

char *StrDup(const char *s)
{
	char *duplicate = NULL;
	size_t len = 0;
	
	assert(NULL != s);
	
	len = strlen(s);
	
	duplicate = (char *)malloc((len + 1) * sizeof(char));
	
	if (NULL == duplicate)
	{
		return NULL;
	}
	
	return (strcpy(duplicate, s));
}

char *StrCat(char *dest, const char *src)
{
	char *dest_original = dest;
	size_t len_dest = 0;
	
	assert(NULL != src);
	assert(NULL != dest);
	
	len_dest = strlen(dest);
	dest = dest + len_dest;
	
	while ('\0' != *src)
	{
		*dest = *src;
		++dest;
		++src;
	}
	
	*dest = '\0';
	
	return dest_original;
}

char *StrnCat(char *dest, const char *src, size_t n)
{
	char *dest_original = dest;
	size_t len_dest = 0;
	
	assert(NULL != src);
	assert(NULL != dest);
	
	len_dest = strlen(dest);
	dest = dest + len_dest;
	
	while ('\0' != *src && 0 != n)
	{
		*dest = *src;
		++src;
		++dest;
		--n;
	}
	
	*dest = '\0';
	
	return dest_original;
}

/* Approved by Shir */
char *StrStr(const char *haystack, const char *needle)
{
	size_t needle_len = 0;
	char *ptr = (char *)haystack;
	
	assert (NULL != haystack);
	assert (NULL != needle);
	
	needle_len = strlen(needle);
	
	while (NULL != (ptr = strchr(haystack, *needle)))
	{
		if (0 == strncmp(ptr, needle, needle_len))
		{
			return (ptr); 
		}
		
		++ptr;
	}

	return NULL;
}

/* Approved by Eden Samama */
size_t StrSpn(const char *s, const char *accept)
{
	char *original_s = NULL;
	
	assert(NULL != accept);
	assert(NULL != s);
	
	original_s = (char *)s;
	
	while ('\0' != *s && NULL != strchr(accept, *s))
	{
		s++;
	}
	
	return (s - original_s);
}





