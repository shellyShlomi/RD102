
/*  Developer: Shelly Shlomi;									*
 *  Date Of Creation:11.05.21;									*
 *  Description: Memcpy Quiz ;										*/

#include <bits/wordsize.h> /* wordsize macro */
#include <assert.h> /* assert */
#include <string.h> /* memset */
#include <stdio.h> /* printf */

static void Test();

int main()
{
    Test();
    
    return 0;
}


void *MemCpy(void *dest, const void *src, size_t n)
{
    const char *ptr_s = (const char *)src;
    char *ptr_d = (char *)dest;

    assert(NULL != src);
    assert(NULL != dest);

    while (0 < n && 0 != ((size_t)ptr_s % (__WORDSIZE)))
    {
        *ptr_d = *ptr_s;
        ++ptr_s;
        ++ptr_d;
        --n;
    }

    while (0 < (n / __WORDSIZE))
    {
        *(size_t *)ptr_d = *(size_t *)ptr_s;
        ptr_s += __WORDSIZE;
        ptr_d += __WORDSIZE;
        n -= __WORDSIZE;
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




static void Test()
{

    char src_arr[] = "SHELLYSHLOMI";
    size_t size = sizeof(src_arr);
    char dest_arr[200] = {0};
    char dest_exp_arr[200] = {0};
    char *res = NULL;
    char *exp = NULL;
    size_t i = 0;

    for (i = 0; i < __WORDSIZE ; ++i)
    {

        res = (char *)MemCpy(dest_arr + i, src_arr + i, size - 1);
        exp = (char *)memcpy(dest_exp_arr + i, src_arr + i, size - 1);

        if (0 != memcmp(dest_arr, dest_exp_arr, size))
        {
            printf("Error in MemCpy when alligned to to each other\n");
            printf("at index %lu\n", i);
        }
        memset(res, 0, size);
        memset(exp, 0, size);
    }
    
    return;
}
