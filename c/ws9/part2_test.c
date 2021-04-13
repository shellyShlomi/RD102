
#include <stdio.h> /* printf */
#include <stdlib.h> /* exit status */
#include <string.h> /* strcmp */
#include "part2.h" 	/* function declaration */


static int TestItoaBase10();
static int TestAtoiBase10();
static int TestIsLittleEndian();
static int TestItoaBaseTil36();
static int TestAtoiBaseTil36();
static int TestPrintFirstAndSecond();

static int TestMacroIsLittleEndian();
extern int MacroIsLittleEndian();


int main()
{
	TestItoaBase10();
	TestAtoiBase10();
	TestItoaBaseTil36();
	TestAtoiBaseTil36();
	
	TestPrintFirstAndSecond();
	
	TestIsLittleEndian();
	TestMacroIsLittleEndian();
	
	return EXIT_SUCCESS;
}

static int TestItoaBase10()
{
	int num[] = {1024, 1, -100656 , 0};
	char *str_exp[] = {"1024", "1", "-100656", "0"}; 
	size_t i = 0;
	size_t size = sizeof(str_exp)/sizeof(str_exp[i]);
	char str_res[4][10] = {'\0'}; 
	
	for (i = 0; i < size; ++i)
	{
		ItoaBase10(num[i], str_res[i]);
		
		if (0 != strcmp(str_res[i],str_exp[i]))
		{
			printf("TestItoa error at index: %ld\n", i);
			
		}
	}

	
	return EXIT_SUCCESS; 
}

static int TestItoaBaseTil36()
{
	int num[] = {1, 300, 300 , -1, -7777, -7777, 0, 5};
	int base[] = {2, 2, 20 , 30, 36, 10, 17, 2};
	char *str_exp[] = {"1", "100101100","f0", "-1", "-601", "-7777", "0", "101"}; 
	size_t i = 0;
	size_t size = sizeof(base)/sizeof(base[i]);
	char str_res[6][10] = {'\0'}; 
	
	for (i = 0; i < size; ++i)
	{
		ItoaBaseTil36(num[i], str_res[i],base[i]);
		
		if (0 != strcmp(str_res[i],str_exp[i]))
		{
			printf("TestItoaBaseTil36 error at index: %ld\n", i);
			
		}
	}
	return EXIT_SUCCESS; 
}

static int TestAtoiBase10()
{
	char str_arr[][10] =  {
							"1024", 
							"    ++1", 
							"-100656", 
							"-10H0656", 
							"-0", 
							"0", 
							"\n\t-100656",
							"  -sh66",
							"-56j89",
							"g"
							}; 
	size_t i = 0;
	size_t size = sizeof(str_arr)/sizeof(str_arr[i]);

	for (i = 0; i < size; ++i)
	{
		if (atoi(str_arr[i]) != AtoiBase10(str_arr[i]))
		{
			printf("AtoiBase10 error at index: %ld \n", i);
		}
	}

	return EXIT_SUCCESS; 
}


static int TestAtoiBaseTil36()
{
	char str_arr[][10] = {
							"1024", 
							"    ++1", 
							"-100656", 
							"-10H0656", 
							"-0", 
							"0", 
							"\n\t-100656",
							"  -sh66",
							"-56j89",
							"g"
							}; 

	int base[] = {2, 2, 20, 30, 30, 36, 10, 17, 2};
	size_t i = 0;
	size_t size = sizeof(base)/sizeof(base[i]);

	for (i = 0; i < size; ++i)
	{
		if (strtol(str_arr[i], NULL, base[i]) != AtoiBaseTil36(str_arr[i], base[i]))
		{
			printf("AtoiBaseTil36 error at index: %ld \n", i);
		}
	}

	return EXIT_SUCCESS; 
}

static int TestPrintFirstAndSecond()
{
	const char char_arr1[] = {'a', 'v', 'g', '\0', '4', 'c', 'H'};
	size_t size1 = sizeof(char_arr1);
	const char char_arr2[] = {'a', 'g', '\0', 'c', 'H'};
	size_t size2 = sizeof(char_arr2);
	const char char_arr3[] = {'u', 'd', 'g', '0', 'e', 'c', 'f'};
	size_t size3 = sizeof(char_arr3);
	
	PrintFirstAndSecond(char_arr1, size1, char_arr2, size2, char_arr3, size3);
	
	return EXIT_SUCCESS; 
} 

static int TestIsLittleEndian()
{
	if (1 != IsLittleEndian())
	{
		printf("IsLittleEndian error\n");
		
	}
	return EXIT_SUCCESS; 
}

static int TestMacroIsLittleEndian()
{
	if (1 != IS_LITTLE_ENDIAN)
	{
		printf("MacroIsLittleEndian error\n");
	}
	return EXIT_SUCCESS; 
}



