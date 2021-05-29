#include <stddef.h> /*size_t*/
#include <stdio.h> /*printf*/
#include <assert.h>

#define SIZE 1024
/*---------------impl func-----------------*/
int FindMissingNum(int arr[], size_t size);

/*---------------test func-----------------*/
static void Test();


int main()
{
	
	Test();
	
	return 0;
}



static void Test()
{
	int exp_num = 666;
	int exp_num1 = 777;
	
	int arr[SIZE] = {0};

	size_t i = 0;
	
	for(i = 0; i < SIZE; ++i)
	{
		arr[i] = i;		
	}

	arr[exp_num] = SIZE;		
	
	if (exp_num != FindMissingNum(arr, SIZE))
	{
		printf("FindMissingNum error at line: %d\n", FindMissingNum(arr, SIZE));
	}
	
	for(i = 0; i < SIZE; ++i)
	{
		arr[i] = i;		
	}

	arr[exp_num1] = SIZE;		
	
	if (exp_num1 != FindMissingNum(arr, SIZE))
	{
		printf("FindMissingNum error at line: %d\n", FindMissingNum(arr, SIZE));
	}

	return; 
}


int FindMissingNum(int arr[], size_t size)
{
	size_t i = 0;
	size_t xor = 0;
	
	assert(arr);
	
	for(i = 0;i < size + 1; ++i)
	{
		xor ^= i;		
	}
	
	for(i = 0;i < size; ++i)
	{
		xor ^= arr[i];		
	}
	return ((int)xor);
}
