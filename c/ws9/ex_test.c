#include <stdio.h>  /* print */
#include <string.h> /* memset */
#include "ex.h"     /* function declaration */

static void Test();

int main()
{
    Test();
    return 0;
}

static void Test()
{
    char dest1[26] = {0x0};
    char dest2[26] = {0x0};
    char source = 'a';

    int num_arr1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int exp_arr1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int n1 = 1;

    int num_arr2[] = {8, 8, 8, 8, 8, 8, 8, 8, 8, 8};
    int exp_arr2[] = {8, 8, 8, 8, 8, 8, 8, 8, 8, 8};
    int n2 = 10;
    int n3 = 10;
	
	int num_arr3[40] = {0};
    					
    int exp_arr3[40] = {0};
	
	size_t i = 0;
	size_t err = 0;
	
    
    if (0 != memcmp(MemSet(dest1, source, 26), memset(dest2, source, 26), 26))
    {
		++err;
        printf("test failed 1\n");
    }

    if (0 != memcmp(MemSet(num_arr1, n1, 5), memset(exp_arr1, n1, 5), 5))
    {
		++err;
        printf("test failed 2\n");
    }

    if (0 != memcmp(MemSet(num_arr2, n2, 15), memset(exp_arr2, n2, 15), 10))
    {
		++err;
        printf("test failed 3\n");
    }

    if (0 != memcmp(MemSet(&n2, source, 6), memset(&n3, source, 6), 4))
    {
    	++err;
        printf("test failed 4\n");
    }
    
    for(i = 0; i < 8; ++i)
    {
		if (0 != memcmp(MemSet((char *)num_arr3 + i, n1 + i, 7),
		                memset((char *)exp_arr3 + i, n1 + i, 7), 7))
		{
			++err;
		    printf("%lu loop test failed \n", i);
		}
	}
	
    if (0 == err)
    {
        printf("All good\n");
    }

    return;
}
