#include <stdio.h>	/*printf function*/
#include <assert.h> /*assret function*/

void CopyArray(int array_to_copy_from[], int copy_array[], size_t size);
void TestFunction();

int main()
{
	TestFunction();
	return 0;
}

/*copy function*/
void CopyArray(int array_to_copy_from[], int copy_array[], size_t size)
{
	size_t i = 0;

	assert(array_to_copy_from);
	assert(copy_array);

	while (i < size)
	{
		/*if the original array is also auinitialized no need to copy*/
		copy_array[i] = array_to_copy_from[i];
		++i;
	}
}

/*tests function*/
void TestFunction()
{
	const int size = 7;
	int array_original[] = {4, 5, 2, 8, 4, 3, 2}; /*original array*/
	int array_to_fill[7] = {0};					  /*copy array*/
	int i = 0;

	CopyArray(array_original, array_to_fill, size);
	/*test swap with null pointer*/
	while (i < size)
	{
		if (array_original[i] != array_to_fill[i])
		{
			printf("ERROR\n");
			break;
		}

		++i;
	}

	if (i == size)
	{
		printf("YESSSSSS\n");
	}
}
