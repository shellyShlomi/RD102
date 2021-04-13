#include <stdio.h>  /* print */
#include <string.h> /* memset */
#include "ex.h"     /* function declaration */

static void Test();
static void Test1();
static void Test2();

static size_t err = 0;

int main()
{
    Test();
    Test1();
    Test2();
    return 0;
}

static void Test()
{

    int n1 = 1;
    int num_arr3[40] = {0};
    int exp_arr3[40] = {0};

    size_t i = 0;

    for (i = 0; i < 8; ++i)
    {
        if (0 != memcmp(MemSet((char *)num_arr3 + i, n1 + i, 7),
                        memset((char *)exp_arr3 + i, n1 + i, 7), 24))
        {
            printf("Error in MemSet at index %ld\n", i);
            ++err;
        }
    }

    return;
}

static void Test1()
{

    char src_arr[] = "abcdefghijklmnopqrstuvwxyz";
    size_t size = sizeof(src_arr);
    char dest_arr[sizeof(src_arr)] = {0};
    char dest_exp_arr[sizeof(src_arr)] = {0};
    char *res = NULL;
    char *exp = NULL;
    size_t i = 0;

    for (i = 0; i < sizeof(size_t); ++i)
    {

        res = (char *)MemCpy(dest_arr + i, src_arr + i, size - 1);
        exp = (char *)memcpy(dest_exp_arr + i, src_arr + i, size - 1);

        if (0 != memcmp(dest_arr, dest_exp_arr, size))
        {
            printf("Error in MemCpy when alligned to to each other\n");
            printf("at index %ld\n", i);
            ++err;
        }
        memset(res, 0, size);
        memset(exp, 0, size);
    }
    return;
}

static void Test2()
{
    char src_arr[] = "abcdefghijklmnopqrstuvwxyz";
    char src_arr1[] = "abcdefghijklmnopqrstuvwxyz";
    char src_arr2[] = "abcdefghijklmnopqrstuvwxyz";
    char src_arr3[] = "abcdefghijklmnopqrstuvwxyz";

    size_t i = 0;
    size_t size = sizeof(src_arr);

    char *res = NULL;
    char *exp = NULL;

    for (i = 0; (sizeof(size_t) + i) < size ; ++i)
    {
        MemMove(src_arr + i, src_arr + (sizeof(size_t) + i), 6);
        memmove(src_arr1 + i, src_arr1 + (sizeof(size_t) + i), 6);

        if (0 != memcmp(src_arr, src_arr1, size))
        {
            printf("Error in MemMove when alligned to to each other\n");
            printf(" & overlaps, error at index %ld\n", i);
            ++err;
        }

        MemMove(src_arr + (sizeof(size_t) + i), src_arr + i, 8);
        memmove( src_arr1 + (sizeof(size_t) + i), src_arr1 + i, 8);

        if (0 != memcmp(src_arr, src_arr1, size))
        {
            printf("Error in MemMove when alligned to to each other\n");
            printf(" & overlaps, error at index %ld\n", i);
            ++err;
        }
    }

	memcpy(src_arr, src_arr3, size);
	memcpy(src_arr1, src_arr3, size);
	
    res = MemMove(src_arr, src_arr1, 10);
    exp = memmove(src_arr2, src_arr3, 10);
    
    if (0 != memcmp(res, exp, size))
    {
        printf("Error in MemMove when alligned to each other\n");
        ++err;
    }

    if (0 == err)
    {
        printf("All good\n");
    }

    return;
}
