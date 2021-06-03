
#include <stdio.h>  /* print */
#include <assert.h>

void SwapTemp(int *x, int *y);
void SwapAritmetics(int *x, int *y);
void Swap(int *x, int *y);

static void Test();

int main()
{  
	
	Test();

	return 0;
}


static void Test()
{

    int a = 3;
    int b = 2;
    int *a_ptr = &a;
    int *b_ptr = &b;

    Swap(a_ptr, b_ptr);
   
    if(a != 2 || b != 3)
    {
		printf("Swap with XOR failed\n");
    }


    a = 3;
    b = 2;
    a_ptr = &a;
    b_ptr = &b;

    SwapAritmetics(a_ptr, b_ptr);
   
    if(a != 2 || b != 3)
    {
		printf("Swap Aritmetics failed\n");
    }


 	a = 3;
    b = 2;
    a_ptr = &a;
    b_ptr = &b;

    SwapTemp(a_ptr, b_ptr);
   
    if(a != 2 || b != 3)
    {
		printf("SwapTemp failed\n");
    }
  
   return ;
}

void Swap(int *x, int *y)
{
	assert(NULL != x);
	assert(NULL != y);
	assert(x != y);

    *x = *y ^ *x;
    *y = *y ^ *x;
    *x = *y ^ *x;

    return ;		
}

void SwapAritmetics(int *x, int *y)
{
   	assert(NULL != x);
	assert(NULL != y);
	assert(x != y);
	
    *x = *x + *y;
    *y = *x - *y;
    *x = *x - *y;
    
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




