
#include <stdio.h>	/* printf */
#include <stdint.h>	/* SIZE_MAX */
#include <string.h>	/* memcmp */

#include "bit_array.h"


static void Test();
static void TestSetOff();
static void TestSetOn();
static void TestSetBit();
static void TestSetAll();
static void TestResetAll();
static void TestToString();
static void TestGetVal();
static void TestFlipBit();
static void TestRotR();
static void TestRotL();
static void TestCountOn();
static void TestCountOff();
static void TestMirror();
static void TestIndicator();

static size_t err = 0;

int main()
{
	Test();
	
	return 0;

}
static void Test()
{
	TestSetOn();
	TestSetOff();
	TestSetBit();
	TestSetAll();
	TestResetAll();
	TestToString();
	TestGetVal();
	TestFlipBit();
	TestRotR();
	TestRotL();
	TestCountOn();
	TestCountOff();
	TestMirror();
	
	TestIndicator();
	
    return;
}

/* lest bit when on, first bit when on, and a rendom midel bit */
static void TestSetOff()
{

    size_t arr[] = {0x8000000000000000, 0, 0xf};
    size_t arr_set[] = {63, 0, 3};
    size_t expected_result[] = {0, 0, 0x7};
    size_t i = 0;
    size_t size = sizeof(arr) / sizeof(arr[0]); 

    while (i < size)
    {
        if (SetOff(arr[i], arr_set[i]) != expected_result[i])
        {
            printf("Test SetOff() failed at index %ld\n", i);
            ++err;
        } 

        ++i;
    }

    return;
}

/* lest bit when off ,first bit when off, and a rendom midel bit */
static void TestSetOn()
{

    size_t arr[] = {0x0000000000000000, 1, 0, 0x7};
    size_t arr_set[] = {63, 0, 0, 3};
    size_t expected_result[] = {0x8000000000000000, 1, 1, 0xf};
    size_t i = 0;
    size_t size = sizeof(arr) / sizeof(arr[0]); 

    while (i < size)
    {
        if (SetOn(arr[i], arr_set[i]) != expected_result[i])
        {
            printf("Test SetOn() failed at index %ld\n", i);
            ++err;
        } 

        ++i;
    }

    return;
}


/* lest bit when on and off, first bit when on and off, and a rendom midel bit */
static void TestSetBit()
{

    size_t arr[] = {0, 0, 0x7};
    size_t arr_set[] = {63, 0, 3};
    size_t expected_result[] = {0x8000000000000000, 1, 0xf};
    size_t i = 0;
    size_t size = sizeof(arr) / sizeof(arr[0]); 

    while (i < size)
    {
        if (SetBit(arr[i], arr_set[i], 1) != expected_result[i])
        {
            printf("Test SetBit() with 1 failed to tern on at index %ld\n", i);
            ++err;
        }

        ++i;
    }
    
	i = 0;
	
	while (i < size)
	{
		if (SetBit(expected_result[i], arr_set[i], 0) != arr[i])
		{
			printf("Test SetBit() failed to tern off at index %ld\n", i);
			++err;
		}

		++i;
	}


    return;
}
/* all bits on, all bits off, random numbers */
static void TestSetAll()
{
    size_t arr[] = {SIZE_MAX, 0, 0x7};
    size_t expected_result[] = {SIZE_MAX, SIZE_MAX, SIZE_MAX};
    size_t i = 0;
    size_t size = sizeof(arr) / sizeof(arr[0]); 

    while (i < size)
    {
        if (SetAll(arr[i]) != expected_result[i])
        {
            printf("Test SetAll() failed at index %ld\n", i);
            ++err;
        } 

        ++i;
    }
	return;
}
  
/* all bits on, all bits off, random numbers */
static void TestResetAll()
{
    size_t arr[] = {SIZE_MAX, 0, 0x7, 1};
    size_t expected_result[] = {0, 0, 0, 0};
    size_t i = 0;
    size_t size = sizeof(arr) / sizeof(arr[0]); 

    while (i < size)
    {
        if (ResetAll(arr[i]) != expected_result[i])
        {
            printf("Test ResetAll() failed at index %ld\n", i);
            ++err;
        } 

        ++i;
    }
	return;
}
 
/* all bits on, all bits off, random numbers */
static void TestToString()
{
    size_t i = 0;
    char dest[65] = {'\0'};
    size_t arr[] = {SIZE_MAX, 0, 0x7, 0x8000000000000000, 68467311635};
    size_t size = sizeof(arr) / sizeof(arr[0]); 
    char *expected_result[] = 
    {	
		"1111111111111111111111111111111111111111111111111111111111111111", 
		"0000000000000000000000000000000000000000000000000000000000000000",
		"0000000000000000000000000000000000000000000000000000000000000111",
		"1000000000000000000000000000000000000000000000000000000000000000",
		"0000000000000000000000000000111111110000111110000100010000010011"
    };

    while (i < size)
    {
        if (0 != strcmp(ToString(arr[i], dest) ,expected_result[i]))
        {
            printf("Test ToString() failed at index %ld\n", i);
            ++err;
        } 

        ++i;
    }
    return;

}

/* lest bit when on and off, first bit when on and off, and a rendom midel bit */
static void TestGetVal()
{
    size_t arr[] = {SIZE_MAX, 0, SIZE_MAX, 0, 0x7, 0x7};
    size_t arr_set[] = {63, 63, 0, 0, 2, 5};
    int expected_result[] = {1, 0, 1, 0, 1, 0};
    size_t i = 0;
    size_t size = sizeof(arr) / sizeof(arr[0]); 

    while (i < size)
    {
        if (GetVal(arr[i], arr_set[i]) != expected_result[i])
        {
            printf("Test GetVal() failed at index %ld\n", i);
            ++err;
        }

        ++i;
    }
    
	return;
}

/* lest bit when on and off, first bit when on and off, and a rendom midel bit */
static void TestFlipBit()
{
    size_t arr[] = {SIZE_MAX, 0, SIZE_MAX, 0, 0x7, 0x7};
    size_t arr_set[] = {63, 63, 0, 0, 2, 5};
    size_t expected_result[] = {
    							 0x7fffffffffffffff, 
    							 0x8000000000000000, 
    							 0xfffffffffffffffe, 
    							 0x01, 
    							 0x03, 
    							 0x27
    							};
    size_t i = 0;
    size_t size = sizeof(arr) / sizeof(arr[0]); 

    while (i < size)
    {
        if (FlipBit(arr[i], arr_set[i]) != expected_result[i])
        {
            printf("Test FlipBit() failed at index %ld\n", i);
            ++err;
        }

        ++i;
    }
    
	return;
}
/* shift with larg val the 64, whit exsectly 64, less then 64, & 0 */
static void TestRotR()
{
    size_t arr[] = {0xFF0F84413, 1, 0xbc, 0x7, SIZE_MAX};
    size_t arr_rotation[] = {5000, 65, 0, 5, 63};
    size_t expected_result[] = {
									0x130000000FF0F844, 
									0x8000000000000000,
									0xbc,
									0x3800000000000000, 
									SIZE_MAX
    							};
    size_t i = 0;
    size_t size = sizeof(arr) / sizeof(arr[0]); 

    while (i < size)
    {
        if (RotR(arr[i], arr_rotation[i]) != expected_result[i])
        {
            printf("Test RotR()failed at index %ld\n", i);
            ++err;
        }

        ++i;
    }
    
	return;
}

/* shift with larg val the 64, whit exsectly 64, less then 64, & 0 */
static void TestRotL()
{
    size_t arr[] = {0xFF0F84413, 1, 0xbc, 0x7, SIZE_MAX};
    size_t arr_rotation[] = {5000, 65, 0, 5, 64};
    size_t expected_result[] = {
									0xFF0F8441300, 
									0x02,
									0xbc,
									0xe0, 
									SIZE_MAX
    							};
    size_t i = 0;
    size_t size = sizeof(arr) / sizeof(arr[0]); 

    while (i < size)
    {
        if (RotL(arr[i], arr_rotation[i]) != expected_result[i])
        {
            printf("Test RotL() failed at index %ld\n", i);
            ++err;
        }

        ++i;
    }
    
	return;
}

/* all bits on, no bits on, 1 bit on, rendom num */
static void TestCountOn()
{
    size_t arr[] = {0xFF0F84413, 1, 0xbc, 0x7, 0, SIZE_MAX};
    size_t expected_result[] = {18, 1, 5, 3, 0, 64};
    size_t i = 0;
    size_t size = sizeof(arr) / sizeof(arr[0]); 

    while (i < size)
    {
        if (CountOn(arr[i]) != expected_result[i])
        {
            printf("Test CountOn() failed at index %ld\n", i);
            ++err;
        }

        ++i;
    }
    
	return;
}

/* all bits on, no bits on, 1 bit on, rendom num */
static void TestCountOff()
{
    size_t arr[] = {0xFF0F84413, 1, 0xbc, 0x7, SIZE_MAX};
    size_t expected_result[] = {46, 63, 59, 61, 0};
    size_t i = 0;
    size_t size = sizeof(arr) / sizeof(arr[0]); 

    while (i < size)
    {
        if (CountOff(arr[i]) != expected_result[i])
        {
            printf("Test CountOff() failed at index %ld\n", i);
            ++err;
        }

        ++i;
    }
    
	return;
}
/* all bits on, no bits on, 1 bit on, rendom num */
static void TestMirror()
{
    size_t i = 0;
    size_t arr[] = {0xFF0F84413, 1, 0xbc, SIZE_MAX, 0};
    size_t size = sizeof(arr) / sizeof(arr[0]); 
    size_t expected_result[] = {
									0xC8221F0FF0000000, 
									0x8000000000000000, 
									0x3d00000000000000, 
									SIZE_MAX,
									0
    							};

    while (i < size)
    {
        if (Mirror(arr[i]) != expected_result[i])
        {
            printf("Test Mirror() failed at index %ld %lu\n", i,Mirror(arr[i]));
            ++err;
        }

        ++i;
    }
    
	return;
}

static void TestIndicator()
{
	if (0 == err)
    {
        printf("All good\n");
    }
    
    return;
}


