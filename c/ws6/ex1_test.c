#include <stdio.h>  /*print*/
#include <math.h>	/*pow*/
#include "ex1.h" /*function declaration*/

static void TestPow2();/*test for Pow2 func*/
static void TestIsPow2Loop();
static void TestIsPow2NoLoop();
static void TestAdd1();
static void TestPrintThreeOn();
static void TestCountBitsLoop();
static void TestSwap();
static void TestIsBit2And6On();
static void TestIsBit2Or6On();
static void TestSwap3And5();
static void TestByteMirrorLoop();
static void TestByteMirrorNoLoop();
static void TestDivideBy16();
static void TestCountBitsNoLoop();
static void TestPrintFloatBits();


int main()
{  
	
	printf("\nTest Pow2: \n\n");
	TestPow2();
	
	printf("\nTest Pow2: \n\n");
	TestIsPow2Loop();
	
	printf("\nTest Pow2 Without Loop:\n\n");	
	TestIsPow2NoLoop();
	
	printf("\nTest Add1: \n\n");
	TestAdd1();
	
	printf("\nTest Print Three On: \n\n");	
	TestPrintThreeOn();
	
	printf("\n\nTest Count Bits Loop:\n\n");	
	TestCountBitsLoop();
	
	printf("\nTest Swap: \n\n");	
	TestSwap();
	
	printf("\nTest Is Bit 2 And 6 On: \n\n");	
	TestIsBit2And6On();
	
	printf("\nTest Is Bit 2 Or 6 On: \n\n");	
	TestIsBit2Or6On();
	
	printf("\nTest Swap 3 And 5: \n\n");	
	TestSwap3And5();
	
	printf("\nTest Byte Mirror Loop: \n\n");	
	TestByteMirrorLoop();
	
	printf("\nTest Byte Mirror No Loop: \n\n");	
	TestByteMirrorNoLoop();
	
	printf("\nTest Divide By 16: \n\n");	
	TestDivideBy16();
	
	printf("\nTest Count Bits No Loop: \n\n");	
	TestCountBitsNoLoop();
	
	printf("\nTest Print Float Bits: \n\n");	
	TestPrintFloatBits();
	return 0;
}

static void TestPow2()
{	

	int err = 0;
	
	if (Pow2(5, 3) != (5*pow(2, 3)))	
	{
		printf("ERROR with %d & %d\n", 5, 3);
		err = 1;
	}
	
	if (Pow2(2, 5) != (2*pow(2, 5)))	
	{
		printf("ERROR with %d & %d\n", 2, 5);
		err = 1;
	}
	
	if (Pow2(8, 32) != (8*pow(2, 32)))	
	{
		printf("ERROR with %d & %d\n", 8, 32);
		err = 1;
	}
	
	if (Pow2(0, 3) != (0*pow(2, 3)))	
	{
		printf("ERROR with %d & %d\n", 0, 3);
		err = 1;
	}
	
	if (Pow2(7, 0) != (7*pow(2, 0)))	
	{
		printf("ERROR with %d & %d\n", 7, 0);
		err = 1;
	}
	if(0 == err)
	{
		printf("All good\n");
	}	
	return ;	
}

static void TestIsPow2Loop()
{	
	unsigned int num_arr[] = {8, 0, 16, 20, 9, 127, 0x8000000};
	int exp_arr[] = {1, 0, 1, 0, 0, 0, 1};
	size_t i = 0;
	size_t size = sizeof(exp_arr) / (sizeof(exp_arr[i]));
	int err = 0;
		
	while (i < size)
	{	
		if (exp_arr[i] != IsPow2Loop(num_arr[i]))	
		{
			printf("ERROR at index %lu\n", i);
			err = 1;
		}
		++i;
	}
	
	if(0 == err)
	{
		printf("All good\n");
	}
	return ;		
}

static void TestIsPow2NoLoop()
{	
	unsigned int num_arr[] = {8, 12, 16, 20, 9, 127, 120, 0};
	int exp_arr[] = {1, 0, 1, 0, 0, 0, 0, 0};
	size_t i = 0;
	size_t size = sizeof(exp_arr) / (sizeof(exp_arr[i]));
	int err = 0;
	
	while (i < size)
	{	
		if (exp_arr[i] != IsPow2NoLoop(num_arr[i]))	
		{
			printf("ERROR at index %lu\n", i);
			err = 1;
		}
		++i;
	}
	
	if(0 == err)
	{
		printf("All good\n");
	}
	
	return ;		
}

static void TestAdd1()
{	
	int num_arr[] = {8, 12, 3, 20, 9, 127, 0, -1};
	int exp_arr[] = {9, 13, 4, 21, 10, 128, 1, 0};
	size_t i = 0;
	size_t size = sizeof(exp_arr) / (sizeof(exp_arr[i]));
	int err = 0;
		
	while (i < size)
	{	
		if (exp_arr[i] != Add1(num_arr[i]))	
		{
			printf("ERROR at index %lu\n", i);
			err = 1;
		}
		++i;
	}
	
	if(0 == err)
	{
		printf("All good\n");
	}
	
	return;
}

static void TestPrintThreeOn()
{	
	unsigned int nums[] = {8, 11, 3, 7, 9, 127, 0};
	size_t length = sizeof(nums) / (sizeof(nums[0]));
	size_t i = 0;
	
	while (i < length - 1)
	{
		printf("%u  ", nums[i]);
		++i;
	}
	printf("0\n\n");
	PrintThreeOn(nums, 7);
	
	return ;	
}


static void TestCountBitsLoop()
{	
	unsigned int num_arr[] = {8, 12, 3, 20, 20453, 127, 659, 0, -2};
	unsigned int exp_arr[] = {1, 2, 2, 2, 10, 7, 5, 0, 31};
	size_t i = 0;
	size_t size = sizeof(exp_arr) / (sizeof(exp_arr[i]));
	int err = 0;
	
	while (i < size)
	{	
		if (exp_arr[i] != CountBitsLoop(num_arr[i]))	
		{
			printf("ERROR at index %lu\n", i);
			err = 1;
		}
		++i;
	}
	
	if(0 == err)
	{
		printf("All good\n");
	}
	
	return;
}
static void TestSwap()
{	
	unsigned int arr[] = {8, 12, 3, 20, 20453, 127, 659, 0};
	unsigned int num[] = {1, 2, 2, 2, 10, 7, 5, 0};
	unsigned int exp_num[] = {8, 12, 3, 20, 20453, 127, 659, 0};
	unsigned int exp_arr[] = {1, 2, 2, 2, 10, 7, 5, 0};
	size_t i = 0;
	size_t size = sizeof(exp_arr) / (sizeof(exp_arr[i]));
	int err = 0;
	
	while (i < size)
	{	
		Swap((num + i), (arr + i));
		if (exp_arr[i] != arr[i] && exp_num[i] != num[i])	
		{
			printf("ERROR at index %lu\n", i);
			err = 1;
		}
		++i;
	}
	
	if(0 == err)
	{
		printf("All good\n");
	}
	return;
}

static void TestIsBit2And6On()
{
	unsigned char arr[] = {'8', 'z', '7', 'Z', '_', '~', '/', '0'};
	int exp_arr[] = {0, 0, 0, 0, 1, 1, 0, 0};
	size_t i = 0;
	size_t size = sizeof(arr) / (sizeof(arr[i]));
	int err = 0;
		
	while (i < size)
	{
		if (exp_arr[i] != IsBit2And6On(arr[i]))	
		{
			printf("ERROR at index %lu\n", i);
			err = 1;
		}
		++i;
	}
	
	if(0 == err)
	{
		printf("All good\n");
	}
	
	return ;	
}

static void TestIsBit2Or6On()
{
	unsigned char arr[] = {'8', 'z', '7', 'Z', '_', '~', '/', '0'};
	int exp_arr[] = {0, 1, 1, 1, 1, 1, 1, 0};
	size_t i = 0;
	size_t size = sizeof(arr) / (sizeof(arr[i]));
	int err = 0;
	
	while (i < size)
	{
		if (exp_arr[i] != IsBit2Or6On(arr[i]))	
		{
			printf("ERROR at index %lu\n", i);
			err = 1;
		}
		++i;
	}
	
	if(0 == err)
	{
		printf("All good\n");
	}
	
	return ;		
}

static void TestSwap3And5()
{
    unsigned char arr[] = {88, 1, 32, 8, 36};
    unsigned char exp_arr[] = {112, 1, 8, 32, 12};
	size_t i = 0;
	size_t size = sizeof(arr) / (sizeof(arr[i]));
	int err = 0;
			
	while (i < size)
	{
		if (exp_arr[i] != Swap3And5(arr[i]))	
		{
			printf("ERROR at index %lu\n", i);
			err = 1;
		}
		++i;
	}
	
	if(0 == err)
	{
		printf("All good\n");
	}

	return ;	
}

static void TestByteMirrorLoop()
{
    unsigned char arr[] = {88, 1, 32, 8, 36, 0, 255, 68467311635};
    unsigned char exp_arr[] = {26, 128, 4, 16, 36, 0, 255, 4};
	size_t i = 0;
	size_t size = sizeof(arr) / (sizeof(arr[i]));
	int err = 0;
		
	while (i < size)
	{
		if (exp_arr[i] != ByteMirrorLoop(arr[i]))	
		{
			printf("ERROR at index %lu\t %lu\n", i, ByteMirrorLoop(arr[i]));
			err = 1;
		}
		++i;
	}
	
	if(0 == err)
	{
		printf("All good\n");
	}
	
	return ;		
}
static void TestByteMirrorNoLoop()
{
    unsigned char arr[] = {88, 1, 32, 8, 36, 255};
    unsigned char exp_arr[] = {26, 128, 4, 16, 36, 255};
	size_t i = 0;
	size_t size = sizeof(arr) / (sizeof(arr[i]));
	int err = 0;
	
	while (i < size)
	{
		if (exp_arr[i] != ByteMirrorNoLoop(arr[i]))	
		{
			printf("ERROR at index %lu\n", i);
			err = 1;
		}
		++i;
	}
	
	if(0 == err)
	{
		printf("All good\n");
	}
	return ;		
}

static void TestDivideBy16()
{
    unsigned char arr[] = {88, 1, 32, 18, 36, 255};
    unsigned char exp_arr[] = {80, 0, 32, 16, 32, 240};
	size_t i = 0;
	size_t size = sizeof(arr) / (sizeof(arr[i]));
	int err = 0;
	
	while (i < size)
	{
		if (exp_arr[i] != DivideBy16(arr[i]))	
		{
			printf("ERROR at index %lu\n", i);
			err = 1;
		}
		++i;
	}
	
	if(0 == err)
	{
		printf("All good\n");
	}
	
	return ;		
}

static void TestCountBitsNoLoop()
{
    int arr[] = {88, 1, 32, 18, -1, 255};
    unsigned int exp_arr[] = {3, 1, 1, 2, 32, 8};
	size_t i = 0;
	int err = 0;
	size_t size = sizeof(arr) / (sizeof(arr[i]));

	while (i < size)
	{
		if (exp_arr[i] != CountBitsNoLoop(arr[i]))	
		{
			printf("ERROR at index %lu\n", i);
			err = 1;
		}
		++i;
	}
	
	if(0 == err)
	{
		printf("All good\n");
	}
	return ;		
}

static void TestPrintFloatBits()
{
	float user_float = 0;
	
	scanf("%f", &user_float);
	printf("for -4.66 the bits are\n\t\t\t\t11000000100101010001111010111000\n");
	PrintFloatBits(user_float);
	return ;
}


	
