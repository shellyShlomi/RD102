#include <stdlib.h> /*stty*/


/* Developer: Shelly Shlomi;
   Status: in development;   
   Description: InputOutput + LUT;*/
   
   
int getchar(void);


void InputOutput()
{	
	int c = 0;
	
	while ( 27 != c )
	{	
		c = getchar();
		
		if ( 65 == c ) 
		{
			printf( "A was pressd\n");
		}
		else if ( 84 == c )
		{
			printf( "T was pressd\n");
		}
	}	
	
	return;
}




/*
void InputOutput()
{	
	system("stty -icanon -echo");
	
	int c = 0;
	
	while ( 27 != c )
	{	
		c = getchar();
		
		if ( 65 == c ) 
		{
			printf( "A was pressd\n");
		}
		else if ( 84 == c )
		{
			printf( "T was pressd\n");
		}
	}	
	
	system("stty icanon echo");
	return;
}




/*size_t low = 0;
	size_t high = 0;
	size_t size = 0;
	
	int arr[] ={30, 5, 90, 1, 3, 20, 1, 100, 50};
	int arr0[]= {6, 12, 3, 5, 1, 4, 9, 2}; 
    int arr1[]= {6, 12, 3, 5, 1, 4, 1, 2};
    int arr2[]= {10, 9, 8, 6, 6, 5, 4, 1};
    
    size = sizeof(arr) / sizeof(int);
	printf("The bast profit is: %d\n", FindBastProfit(arr , size, &low, &high));
	printf("the first index is: %lu\n", low);
	printf("the secound index is: %lu\n\n",  high);
	
	size = sizeof(arr0) / sizeof(int);
	printf("The bast profit is: %d\n",FindBastProfit(arr0 , size, &low, &high));
	printf("the first index is: %lu\n", low);
	printf("the secound index is: %lu\n\n",  high);
	
	size = sizeof(arr1) / sizeof(int);
	printf("The bast profit is: %d\n", FindBastProfit(arr1 , size, &low, &high));
	printf("the first index is: %lu\n", low);
	printf("the secound index is: %lu\n\n",  high);
	
	size = sizeof(arr2) / sizeof(int);
	printf("The bast profit is: %d\n",FindBastProfit(arr2 , size, &low, &high));
	printf("the first index is: %lu\n", low);
	printf("the secound index is: %lu\n\n",  high);*/
