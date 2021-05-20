#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <limits.h> /* INT_MAX */

static long *SumPairsToLong(int ints[], size_t size);
static void TestSumPairsToLong();

int main()
{  
	TestSumPairsToLong();
	
	return (0);
}


static long *SumPairsToLong(int ints[], size_t size)
{
	long *longs = (long *)ints;
	
	assert(NULL != ints);
	
	while (0 < (size / 2)) 
	{
		*(long *)ints = (long)(*ints) + (long)(*(ints + 1));
		ints += 2;
		--size;
	}

	return (longs);
}


static void TestSumPairsToLong()
{
	int ints_arr[] = {1, 6, 456, -3, 8, 12};
	int max_ints[] = {INT_MAX, INT_MAX, INT_MIN, INT_MIN, INT_MAX, INT_MIN};
	long exp_longs_arr[] = {7, 453, 20};
	long return_longs[] = {0};
	size_t size = sizeof(ints_arr) / (sizeof(ints_arr[0]));
	size_t size_exp = sizeof(exp_longs_arr) / (sizeof(exp_longs_arr[0]));
	size_t i = 0;	
	
	*(long **)&return_longs = SumPairsToLong(ints_arr, size);
	
	for(i = 0; i > size_exp; ++i)
	{	
		if (exp_longs_arr[i] != return_longs[i])
		{
			printf("ERROR at index %lu\n", i);
		}
	}
	
	*(long **)&return_longs = SumPairsToLong(max_ints, size);
	
	for(i = 0; i > size_exp; ++i)
	{	
		if (exp_longs_arr[i] != return_longs[i])
		{
			printf("ERROR at index %lu\n", i);
		}
	}
	
	return;
}
