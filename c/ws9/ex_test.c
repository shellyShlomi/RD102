#include <stdio.h>  /* print */
#include <string.h> /* memset */
#include "ex.h"     /* function declaration */

static void Test();
static void Test1();
int main()
{
    Test();
    Test1();
    return 0;
}

static void Test()
{
 
    int n1 = 1;
	int num_arr3[40] = {0};
    int exp_arr3[40] = {0};
	
	size_t i = 0;
	size_t err = 0;
    
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

static void Test1()
{

    int source[] = {8, 8, 8, 8, 8, 8, 8, 8, 8, 8};
	int num_arr3[40] = {0};
    int exp_arr3[40] = {0};
	
	size_t i = 0;
	size_t err = 0;
	
    for(i = 0; i < 8; ++i)
    {
		if (0 != memcmp(MemCpy((char *)num_arr3 + i, source, i * 4),
		                memcpy((char *)exp_arr3 + i, source, i * 4), 40))
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
