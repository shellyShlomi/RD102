
#include <stdio.h>		/*		printf		*/
#include <limits.h>		/*		UCHAR_MAX	*/

static int IsNumInFound(char *arr, size_t size, char num);
static void Test();


int main()
{
	Test();
	
	return 0;
}



static int IsNumInFound(char *arr, size_t size, char num)
{
	int lut_arr[UCHAR_MAX + 1] = {'\0'};
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		*(lut_arr + *(arr + i)) = 0x01;
	}
	
	return *(lut_arr + num);
}



static void Test()
{
	
	char arr_char[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', '\0'};
	char char_num[] = {'a', '\0', 'g', 'A', 'd', 'B'};
	int arr_exp[] = {0, 1, 0, 1, 0, 1};
	
	size_t size = sizeof(arr_char)/ sizeof(arr_char[0]);
	size_t size_exp = sizeof(arr_exp)/ sizeof(arr_exp[0]);
	size_t i = 0;
	  
	while (i < size_exp)
	{
		if (arr_exp[i] != IsNumInFound(arr_char, size, char_num[i]))
		{
			printf("IsNumInFound error at index: %lu\n", i);
		} 
		
		++i;
	}

	return;
}
