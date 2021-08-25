#include <assert.h>
#include "quiz3.h" 


int IsSumFunde( int *p_num1, int *p_num2, int arr[], int sum, size_t size)
{	
	int *big_index = NULL;
	int *small_index = NULL;

	assert(p_num1);
	assert(p_num2);
	assert(arr);
	
	big_index = arr + (size - 1);
	small_index = arr;

	
	while (big_index > small_index)
	{

		if ((*big_index + *small_index) == sum)
		{
			*p_num1 = small_index - arr;
			*p_num2 = big_index - arr;
			return 1;
		}		
		else if ((*big_index + *small_index) > sum)
		{	
			--big_index;
		}
		else  
		{
			++small_index;		
		}
		
	}
		
	*p_num1 = -1;
	*p_num2 = -1;
			
	return 0;
}


