/*  Developer: Shelly Shlomi;									*/
/*  Status: in development;										*/
/*  Date Of Creation:04.04.21;									*/
/*  Date Of Approval: --.--.--;									*/
/*  Approved By: -- ;											*/
/*  Description: styatic lybery of memset memcpy memmove;		*/

#include <assert.h> /* assert */
#include "ex.h"     /* function declaration */
/* Approved By: NIR */
void *MemSet(void *s, int c, size_t n)
{
    size_t word_size = sizeof(size_t);
    size_t word = 0xFF;
    char original_byte_c = 0;
    char *ptr_s = NULL;

    assert(NULL != s);

    ptr_s = (char *)s;

    word &= c;
    original_byte_c = (char)word;

    while (0 != c)
    {
        c <<= 8;
        word |= c;
    }
    
	word = word | (word << 32);

    while (0 < n && (0 != ((size_t)ptr_s % word_size)))
    {
        *ptr_s = original_byte_c;
        ++ptr_s;
        --n;
    }

    while (0 < (n / word_size))
    {
        *(size_t *)ptr_s = word;
        ptr_s += word_size;
        n -= word_size;
    }

    while (0 < n)
    {
        *ptr_s = original_byte_c;
        ++ptr_s;
        --n;
    }

    return s;
}

/* approved by Ohad */
void *MemCpy(void *dest, const void *src, size_t n)
{
	char *ptr_s = NULL;
	char *ptr_d = NULL;
    size_t word_size = sizeof(size_t);
    
	assert(NULL != src);
	assert(NULL != dest);

	ptr_s = (char *)src;
	ptr_d = (char *)dest;
	
	while (0 < n && (0 != ((size_t)ptr_s % word_size)))
	{
		*ptr_d = *ptr_s;
		++ptr_s;
		++ptr_d;
		--n;
	}

	while (0 < (n / word_size))
	{
		*(size_t *)ptr_d = *(size_t *)ptr_s;
		ptr_s += word_size;
		ptr_d += word_size;
		n -= word_size;
	}

	while (0 < n)
	{
		*ptr_d = *ptr_s;
		++ptr_s;
		++ptr_d;
		--n;
	}

	return dest;
}

