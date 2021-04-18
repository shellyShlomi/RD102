
#include <stdio.h>  /* 	print 	*/
#include <limits.h> /*	INT_MAX	*/
#include <string.h> /* strlen */

#include "exam_c.h"	/* the function declaration */


static void Test();
static void TestFlipDigitsInNum();
static void TestByteMirror();
static void TestFlipBit();
static void TestCountBitInByte();
static void TestRotL();
static void TestStrLen();
static void TestStrCmp();
static void TestStrCpy();
static void TestStrnCpy();
static void TestStrCat();
static void TestGetNFibonacciElement();
static void TestItoa();
static void TestMultiplyBy8();
static void TestSwapPtr();
static void TestSwap();

int main()
{  
	
	Test();

	return 0;
}

static void Test()
{

	TestFlipDigitsInNum();
	TestByteMirror();
	TestFlipBit();
	TestCountBitInByte();
	TestRotL();
	TestStrLen();
	TestStrCpy();
	TestStrnCpy();
	TestStrCmp();
	TestStrCat();
	TestGetNFibonacciElement();
	TestItoa();
	TestMultiplyBy8();
	TestSwapPtr();
	TestSwap();
	
}

static void TestFlipDigitsInNum()
{
	int arr[] = {58, -520, 0, 1, -1230, 463729, 555};
	int exp_result[] = {85, -25, 0, 1, -321, 927364, 555};
	size_t size = sizeof(arr) / sizeof(arr[0]);
	size_t i = 0;

	while (i < size)
	{
		if (exp_result[i] != FlipDigitsInNum(arr[i]))
		{
		    printf("TestFlipDigitsInNum failed at index %ld\n", i);
		}

		++i;
	}

	return;	
	
}

static void TestByteMirror()
{

 	unsigned char arr[] = {88, 1, 32, 8, 36, 0, 255};
    unsigned char exp_arr[] = {26, 128, 4, 16, 36, 0, 255};
	size_t size = sizeof(arr) / (sizeof(arr[0]));
	size_t i = 0;

	while (i < size)
	{
		if (exp_arr[i] != ByteMirror(arr[i]))	
		{
			printf("ERROR at index %lu\n", i);

		}
		++i;
	}
	
	return ;

}

static void TestFlipBit()
{
	int arr[] = {~0, 0, ~0, 0, 0x7, 0x7};
	unsigned int arr_set[] = {31, 31, 0, 0, 2, 5};
	int expected_result[] = {
								0x7fffffff,
								0x80000000,
								0xfffffffe,
								0x01,
								0x03,
								0x27};
	size_t i = 0;
	size_t size = sizeof(arr) / sizeof(arr[0]);

	while (i < size)
	{
		if (FlipBit(arr[i], arr_set[i]) != expected_result[i])
		{
		    printf("Test FlipBit() failed at index %ld\n", i);

		}

		++i;
	}

	return;
}


static void TestCountBitInByte()
{
    unsigned char arr[] = {0xFF, 1, 0xbc, 0x7, 0};
    unsigned char expected_result[] = {8, 1, 5, 3, 0};
    size_t i = 0;
    size_t size = sizeof(arr) / sizeof(arr[0]);

    while (i < size)
    {
        if (CountBitInByte(arr[i]) != expected_result[i])
        {
            printf("Test CountBitInByte() failed at index %ld\n", i);
        }
        ++i;
    }

    return;
}

static void TestRotL()
{
	char arr[] = {-1, 1, -68, 0x7, ~0, 0x0F};
	unsigned int arr_rotation[] = {5000, 65, 0, 5, 8, 4};
	char expected_result[] = {
								-1,
								0x02,
								-68,
								-32,
								~0,
								-16};
	size_t i = 0;
	size_t size = sizeof(arr) / sizeof(arr[0]);

	while (i < size)
	{
		if (RotateRotL(arr[i], arr_rotation[i]) != expected_result[i])
		{
		    printf("Test RotL() failed at index %ld\n", i);
		}

		++i;
	}

    return;
}

static void TestStrLen()
{
	char *arr[] = {"", "shelly", "anna", "shelly shlomi", "shelly\0shlomi"};
	size_t i = 0;
	size_t size = sizeof(arr) / sizeof(arr[0]);

	while (i < size)
	{
		if (StrLen(arr[i]) != strlen(arr[i]))
		{
		    printf("Test StrLen() failed at index %ld\n", i);
		}

		++i;
	}

    return;
}

static void TestStrCmp()
{
	char *StrCmp_arr[] = {"", "shelly", "anna", "shelly ", "shelly\0shlomi"};
	char *strcmp_arr[] = {"", "shelly", "anna", "shelly shlomi", "shelly\0si"};
	size_t i = 0;
	size_t size = sizeof(strcmp_arr) / sizeof(strcmp_arr[0]);
	
	int StrCmp_val = 0; 
	int strcmp_val = 0;

	while (i < size)
	{	
		StrCmp_val = StrCmp(StrCmp_arr[i], strcmp_arr[i]);
		strcmp_val = strcmp(StrCmp_arr[i], strcmp_arr[i]); 
		
		if ((StrCmp_val < 0 && strcmp_val > 0)		|| 
			(StrCmp_val > 0 && strcmp_val < 0)		||
			(0 != StrCmp_val && 0 == strcmp_val)	||
			(0 == StrCmp_val && 0 != strcmp_val)		)
		{
		    printf("Test StrCmp() failed at index %ld\n", i);
		}
		++i;
	}

    return;
}

static void TestStrCpy()
{
	char *src_arr[] = {"", "shelly", "anna", "shelly shlomi", "shelly\0shlomi"};
	char dest_arr[][20] = {"", "", "", "", ""};
	char exp_dest[][20] = {"", "", "", "", ""};
	size_t i = 0;
	size_t size = sizeof(src_arr) / sizeof(src_arr[0]);

	while (i < size)
	{	
		StrCpy(dest_arr[i], src_arr[i]);
		strcpy(exp_dest[i], src_arr[i]);
		if (0 != strcmp(dest_arr[i], exp_dest[i]))
		{
		    printf("Test StrCpy() failed at index %ld\n", i);
		}
		++i;
	}

    return;
}

static void TestStrnCpy()
{
	char *src_arr[] = {"", "shelly", "anna", "shelly shlomi", "shelly\0shlomi"};
	char dest_arr[][20] = {"", "", "", "", ""};
	char exp_dest[][20] = {"", "", "", "", ""};
	size_t n_arr[] = {0, 3, 2, 10, 8};
	size_t i = 0;
	size_t size = sizeof(src_arr) / sizeof(src_arr[0]);

	while (i < size)
	{	
		StrnCpy(dest_arr[i], src_arr[i], n_arr[i]);
		strncpy(exp_dest[i], src_arr[i], n_arr[i]);
		if (0 != strncmp(dest_arr[i], exp_dest[i], n_arr[i]))
		{
		    printf("Test StrnCpy() failed at index %ld\n", i);
		}
		++i;
	}

    return;
}

static void TestStrCat()
{
    const char *src[] = {"ff", "anna", "shelly shlomi", "shelly\0shlomi"};
	char res_my_function[100] = "";
	char res_original[100] = "";
    size_t size = sizeof(src) / sizeof(src[0]);
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
    	StrCat(res_my_function, src[i]);
    	strcat(res_original, src[i]);
    	
        if (0 != strcmp(res_my_function, res_original))
        {
            printf("StrCat failed at index %ld\n", i);
        }
    }
    return;
}


static void TestGetNFibonacciElement()
{
    unsigned long fib_arr[] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
    unsigned int n[] = {1, 5, 11, 7};
    size_t i = 0;
    size_t size = sizeof(n) / sizeof(n[0]);

    while (i < size)
    {
        if (GetNFibonacciElement(n[i]) != fib_arr[n[i] -1])
        {
            printf("testGetNFibonacciElement failed at index %ld\n", i);
        }

        ++i;
    }

    return;
}

static void TestItoa()
{
	int num[] = {1024, 1, -100656 , 0};
	char *str_exp[] = {"1024", "1", "-100656", "0"}; 
	size_t i = 0;
	size_t size = sizeof(str_exp)/sizeof(str_exp[i]);
	char str_res[4][10] = {'\0'}; 
	
	for (i = 0; i < size; ++i)
	{
		Itoa(str_res[i], num[i]);
		
		if (0 != strcmp(str_res[i],str_exp[i]))
		{
			printf("Itoa error at index: %ld\n", i);
			
		}
	}

	
	return; 
}


static void TestMultiplyBy8()
{
	int arr[] = {-1, 1, 0, -7};
	int arr_exp[] = {-8, 8, 0, -56};
	size_t i = 0;
	size_t size = sizeof(arr) / sizeof(arr[0]);

	while (i < size)
	{	
		if (MultiplyBy8(arr[i]) != arr_exp[i])
		{
		    printf("Test MultiplyBy8() failed at index %ld\n", i);
		}
		++i;
	}

    return;
}


static void TestSwapPtr()
{
	
	int x = 0;
	int y = 9;
	
	int *ptr1 = &x;
	int *ptr2 = &y;
	
	SwapPtr(&ptr1, &ptr2);
	
	if (ptr1 != &y || ptr2 != &x)
	{
		printf("SwapPtr() failed\n");
	}
	
    return;
}


static void TestSwap()
{

    int a = 3;
    int b = 2;
    int *a_ptr = &a;
    int *b_ptr = &b;

    Swap(a_ptr, b_ptr);
   
    if(a != 2 || b != 3)
    {
		printf("Swap with XOR failed\n");
    }


    a = 3;
    b = 2;
    a_ptr = &a;
    b_ptr = &b;

    SwapAritmetics(a_ptr, b_ptr);
   
    if(a != 2 || b != 3)
    {
		printf("Swap Aritmetics failed\n");
    }


 	a = 3;
    b = 2;
    a_ptr = &a;
    b_ptr = &b;

    SwapTemp(a_ptr, b_ptr);
   
    if(a != 2 || b != 3)
    {
		printf("SwapTemp failed\n");
    }
  
   return ;
}

