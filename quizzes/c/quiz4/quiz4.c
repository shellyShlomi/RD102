#include <stdio.h>  /*for print*/
#include <assert.h>	/*for assert*/
/* Developer: Shelly Shlomi 
   Status: Done ;   
   Description: Bursa */

int FindBastProfit(int arr[], size_t size, size_t *first_i, size_t *secound_i);

int main()
{	
	size_t low = 0;
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
	printf("the secound index is: %lu\n\n",  high);
	return (0);
}

int FindBastProfit(int arr[], size_t size, size_t *first_i, size_t *secound_i)
{	
	size_t low = 0;
	size_t high = 1;
	size_t i = 0;
	size_t j = 0;
	int bast_profit = 0;
	int curent_profit = 0;
	
	assert(first_i);
	assert(secound_i);
	
	while (0 == bast_profit && high < (size - 1))
	{	
		curent_profit = arr[high] - arr[low];
		
		if (curent_profit > bast_profit)
		{	
			*first_i = low;
			*secound_i = high;
			
			bast_profit = curent_profit; 
			
			i = i + high;
			j = low;
			
			break;
		}
		
		++high;
		++low;
	}
	
	while ( i < (size - 1) &&  j < (size - 1) )
	{	
		curent_profit = arr[i] - arr[j];
		
		if ( 0 > curent_profit )
		{
			j = i;
		}
		else if (bast_profit < curent_profit)
		{
			bast_profit = curent_profit;
			high = i;
			low = j;
		
		}
		
		++i;
		
	}
	
	*first_i = low;
	*secound_i = high;
	
	return bast_profit;
}
