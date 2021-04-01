
/* Developer: Shelly Shlomi;										*/
/* Status: Aproved by anna;											*/
/* Date Of Creation:31.03.21;										*/
/* Date Of Approval: 31.03.21;										*/
/* Description: 2 - macro of MAX; 3 - SIZEOF_VAR;4 - SIZEOF_TYPE;	*/

#include <stdio.h>/*print*/

/*Approved by NIR*/
#define MAX2(a, b) ((a) > (b) ? (a) : (b))

#define MAX3(a, b, c)((a) > (b) ? MAX2(a, c) : MAX2(b, c))


/*Approved by EDEN W*/
#define SIZEOF_VAR(var)((size_t)(&(var) + 1) - (size_t)(&(var)) )



/*Approved by EDEN W*/
#define SIZEOF_TYPE(type)((size_t)(1 + ((type*)0)))

static void TestMax2();
static void TestMax3();
static void TestSizeOf();

int main()
{
   
    TestMax2();
    TestMax3();
    TestSizeOf();
    return 0;
}


static void TestMax2()
{	
	int num_arr[] = {8, 0, 16, 20, 9, 127, 3};
	int exp_arr[] = {8, 16, 20, 20, 127, 127};
	size_t i = 0;
	size_t size = sizeof(exp_arr) / (sizeof(exp_arr[i]));
	int err = 0;
		
	while (i < size - 1)
	{	
		if (exp_arr[i] != MAX2(num_arr[i], num_arr[i + 1]))	
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

static void TestMax3()
{	
	int num_arr[] = {-8, 0, 16, 20, 9, ~0x80000000, -1, ~0x00000000,-2000};
	int exp_arr[] = {16, 20, 20, ~0x80000000, ~0x80000000, -1};
	size_t i = 0;
	size_t size = sizeof(exp_arr) / (sizeof(exp_arr[i]));
	int err = 0;
		
	while (i < size - 2)
	{	
		if (exp_arr[i] != MAX3(num_arr[i], num_arr[i + 1], num_arr[i + 2]))	
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

static void TestSizeOf()
{	
	struct test_struct
	{	
		long z;
		int x;
		int y;
	};
	

	int x = 10;

    printf("the size of var int is: %ld\n", SIZEOF_VAR(x));
    printf("struct of two ints & 1 long, the size is: %ld\n", 
    									SIZEOF_TYPE(struct test_struct));
    printf("double, the size is: %ld\n", SIZEOF_TYPE(double));


	return ;		
}
