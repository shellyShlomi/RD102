#include <stdio.h> 	/* ptintf */
#include <assert.h> /* assert */

size_t BitsCouple(unsigned char num);
void Swap(int *x, int *y);
void SwapAritmetics(int *x, int *y);
void SwapTemp(int *x, int *y);
size_t BitOnInLong(long int num);
static void TestBitCouple();
static void TestSwap();
static void TestBitOnInLong();

int main()
{
	TestBitCouple();
	TestSwap();
	TestBitOnInLong();
    
    return 0;
}


size_t BitsCouple(unsigned char num)
{
	size_t couples = 0;
	
	while(0 < num)
	{
		couples += (3 == (num & 3));
		num >>= 1;
	}
		
	return couples;
}


void Swap(int *x, int *y)
{
	assert(NULL != x);
	assert(NULL != y);

    if (x != y)
    {
        *x = *y ^ *x;
        *y = *y ^ *x;
        *x = *y ^ *x;
    }
    return ;		
}

void SwapAritmetics(int *x, int *y)
{
   	assert(NULL != x);
	assert(NULL != y);
	
    if (x != y)
    {
        *x = *x + *y;
        *y = *x - *y;
        *x = *x - *y;
    }
    return ;		
}

void SwapTemp(int *x, int *y)
{	
	int temp = 0;

	assert(NULL != x);
	assert(NULL != y);
	
	temp = *x;
	*x = *y;
	*y = temp; 
    
    return ;		
}

size_t BitOnInLong(long int num)
{
	size_t count = 0;
	
	while (0 != num)
	{
		num &= (num - 1);
		++count;
	}
	
	return count;
}

static void TestBitCouple()
{	
	int err = 0;
	size_t i = 0;
	unsigned char num_arr[] = {0x08, 0, 0x03, 0x0F, 0xFF};
	size_t exp_arr[] = {0, 0, 1, 3, 7};
	size_t size = sizeof(exp_arr) / (sizeof(exp_arr[i]));
	
	printf("Bit Couples \n\n");   	

	while (i < size )
	{	
		if (exp_arr[i] != BitsCouple(num_arr[i]))	
		{
			printf("ERROR at index %lu\n\n", i);
			err = 1;
		}
		++i;
	}
	
	if(0 == err)
	{
		printf("All good\n\n");
	}
	return ;		
}

static void TestSwap()
{

    int a = 3;
    int b = 2;
    int *a_ptr = &a;
    int *b_ptr = &b;

    Swap(a_ptr, b_ptr);
 
    printf("Swap ^\n\n");   
   
    if(a == 2 && b == 3)
    {
        printf("All good\n\n");
    }
    else
    {
        printf("There is an Error!\n\n");
    }

    a = 3;
    b = 2;
    a_ptr = &a;
    b_ptr = &b;

    SwapAritmetics(a_ptr, b_ptr);
   
    printf("Swap Aritmetics\n\n");   
    
    if(a == 2 && b == 3)
    {
        printf("All good\n\n");
    }
    else
    {
        printf("There is an Error!\n\n");
    }


 	a = 3;
    b = 2;
    a_ptr = &a;
    b_ptr = &b;

    SwapTemp(a_ptr, b_ptr);
   
    printf("Swap Temp\n\n");   
   
    if(a == 2 && b == 3)
    {
        printf("All good\n\n");
    }
    else
    {
        printf("There is an Error!\n\n");
    }
  
   return ;
}

static void TestBitOnInLong()
{	
	int err = 0;
	size_t i = 0;
	long int num_arr[] = {0x08, 0, 0x03, 0x0FFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF};
	size_t exp_arr[] = {1, 0, 2, 60, 64};
	size_t size = sizeof(exp_arr) / (sizeof(exp_arr[i]));
	
	printf("Bit On In Long\n\n");   	

	while (i < size)
	{	
		if (exp_arr[i] != BitOnInLong(num_arr[i]))	
		{
			printf("ERROR at index %lu\n\n", i);
			err = 1;
		}
		++i;
	}
	
	if(0 == err)
	{
		printf("All good\n\n");
	}
	return ;		
}
