/*  Developer: Shelly Shlomi;									*/
/*  Status: in development;										*/
/*  Date Of Creation:04.04.21;									*/
/*  Date Of Approval: --.--.--;									*/
/*  Approved By: -- ;											*/
/*  Description: styatic lybery of memset memcpy memmove;		*/

#include <assert.h> /* assert */
#include "ex.h"     /* function declaration */

void *MemSet(void *s, int c, size_t n)
{
    size_t word_size = sizeof(size_t);
    size_t mask = 0xFF;
    char original_byte_c = 0;
    char *ptr_s = NULL;

    assert(NULL != s);

    ptr_s = (char *)s;

    mask &= c;
    original_byte_c = (char)mask;

    while (0 != c)
    {
        c <<= 8;
        mask |= c;
    }
    
	mask = mask | (mask << 32);

    while (0 < n && (0 != ((size_t)s % word_size)))
    {
        *ptr_s = original_byte_c;
        ++ptr_s;
        --n;
    }

    while (0 < (n / word_size))
    {
        *(size_t *)ptr_s = mask;
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


void *MemSet(void *s, int c, size_t n)
{
    size_t word_size = sizeof(size_t);
    size_t mask = 0xFF;
    char original_byte_c = 0;
    char *ptr_s = NULL;

    assert(NULL != s);

    ptr_s = (char *)s;

    mask &= c;
    original_byte_c = (char)mask;

    while (0 != c)
    {
        c <<= 8;
        mask |= c;
    }
    
	mask = mask | (mask << 32);

    while (0 < n && (0 != ((size_t)s % word_size)))
    {
        *ptr_s = original_byte_c;
        ++ptr_s;
        --n;
    }

    while (0 < (n / word_size))
    {
        *(size_t *)ptr_s = mask;
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

