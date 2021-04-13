/*  Developer: Shelly Shlomi;									*/
/*  Status: approved;											*/
/*  Date Of Creation:04.04.21;									*/
/*  Date Of Approval: 05.04.21;									*/
/*  Approved By: NIR 											*/
/*  Description: styatic librery of memset memcpy memmove;		*/

#include <assert.h> /* assert */
#include "ex.h"     /* function declaration */

#define WORD_SIZE sizeof(size_t)

/* Approved By: NIR */
void *MemSet(void *s, int c, size_t n)
{
    size_t word_size = sizeof(size_t);
    size_t word = 0xFF;
    char original_byte_c = 0;
    char *ptr_s = (char *)s;

    assert(NULL != s);

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

    while (0 <= (n / word_size))
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
    const size_t word_size = sizeof(size_t);
    const char *ptr_s = (const char *)src;
    char *ptr_d = (char *)dest;

    assert(NULL != src);
    assert(NULL != dest);

    while (0 < n && 0 != ((size_t)ptr_s % (word_size)))
    {
        *ptr_d = *ptr_s;
        ++ptr_s;
        ++ptr_d;
        --n;
    }

    while (0 < n / word_size)
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

/* Approved By: NIR */
void *MemMove(void *dest, const void *src, size_t n)
{
    const char *ptr_s = (const char *)src;
    char *ptr_d = (char *)dest;

    assert(NULL != src);
    assert(NULL != dest);

    if ((ptr_s - ptr_d) > 0 || (size_t)(ptr_d - ptr_s) > n)
   
    {
        return MemCpy(dest, src, n);
    }

    while (0 < n)
    {
        *(ptr_d + n - 1) = *(ptr_s + n - 1);
        --n;
    }

    return dest;
}

