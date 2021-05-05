#include <stdlib.h> /* exit status */
#include <stdio.h>	/* printf */
#include <assert.h> /* assert */

static int FindNumInArr(int arr[], size_t size, int num);
static void Test();


int main()
{
	Test();
	
	return EXIT_SUCCESS;
}


static int FindNumInArr(int arr[], size_t size, int num)
{
	size_t i = 0;
	long int flag = 1;		/* long to avoid overflow as mach as we can */
	
	assert(NULL != arr);

	for (i = 0; i < size; ++i)
	{
		flag *= (num ^ arr[i]);
	}
	
	return (!flag);
}




static void Test()
{
	int arr[] = {13, -21, 1, 15, 3, 6, 7};
	size_t size = sizeof(arr)/ sizeof(arr[0]);

    size_t arr_of_nums[] = {1, 2, 3, -4, -21, 6};
	size_t size_of_nums = sizeof(arr_of_nums)/ sizeof(arr_of_nums[0]);

    int exp_result[] = {1, 0, 1, 0, 1, 1};
	size_t i = 0;
	
	for (i = 0; i < size_of_nums; ++i)
	{

		if	(exp_result[i] != FindNumInArr(arr, size, arr_of_nums[i]))
		{
			printf("FindNumInArr error at line : %d, index : %lu \n",__LINE__, i);
		}

	}

	return ;
}

