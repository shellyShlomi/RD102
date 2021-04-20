


#include <stdio.h> /* printf */



unsigned int Add1(unsigned int n);
static void TestAdd1();



int main()
{  
	TestAdd1();
	
	return (0);
}




unsigned int Add1(unsigned int n)
{
	unsigned int orig_val = n;
	unsigned int flipetr = 1;
	
	while (orig_val >= n)
	{
		n ^= flipetr;
		flipetr <<= 1;
	}
	return (n);
}

static void TestAdd1()
{	

	unsigned int num_arr[] = {8, 12, 3, 20, 9, 127, 0};
	unsigned int exp_arr[] = {9, 13, 4, 21, 10, 128, 1};
	size_t i = 0;
	size_t size = sizeof(exp_arr) / (sizeof(exp_arr[i]));
		
	while (i < size)
	{	
		if (exp_arr[i] != Add1(num_arr[i]))	
		{
			printf("ERROR at index %lu\n", i);
		}
		++i;
	}

	return;
}
