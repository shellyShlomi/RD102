
#include <stdio.h>	/* printf */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

static int FindkthElem(int arr[], size_t size, size_t k);
static size_t MinIndex(int arr[], size_t size);
void SwapTemp(int *x, int *y);
static void Test();

int main()
{
	Test();
	
	return EXIT_SUCCESS;
}


static int FindkthElem(int arr[], size_t size, size_t k)
{
	size_t i = 0;
	size_t j = 0;
	size_t index = 0;
	size_t orig_k = k;
	int *arr_temp = NULL;
	int k_min = 0;
	
	assert(NULL != arr);
	assert(k != 0);
	assert(k < size);

	
/*	the malloc is not nessery its only for the validety of the tsets - not to test sorted arr after repited func calls and for larg data we wont do an allocation and preporm the sorting in place	*/
	{
		arr_temp = (int *)malloc(size * sizeof(int));
		
		if	(NULL == arr_temp)
		{
			return (-1);
		}
		
		
		for (i = 0; i < size; ++i)
		{
			arr_temp[i] = arr[i];
		}

	}
	
	while(0 < k)
	{
		index = MinIndex(arr_temp + j, size);
		SwapTemp((arr_temp + j) , (arr_temp + j + index));
		
		--size;
		++j;
		--k;
	}
	
	k_min = *(arr_temp + orig_k - 1);
	
	free(arr_temp);
	arr_temp = NULL;
	
	return (k_min);
}



static void Test()
{
	int arr[] = {13, 21, 1, 15, 3, 6, 7};
    size_t arr_k[] = {1, 2, 3, 4, 5, 6};
    int exp_result[] = {1, 3, 6, 7, 13, 15, 21};
    int min_test[] = {-4, 5, 3, 0, -9};
	size_t size = sizeof(arr)/ sizeof(arr[0]);
	size_t size_k = sizeof(arr_k)/ sizeof(arr_k[0]);
	size_t size_min = sizeof(min_test)/ sizeof(min_test[0]);
	int k_elem = 0;
	size_t i = 0;
	
	/*	test for min && swap	*/
	if	(MinIndex(arr, size) != 2)
	{
		printf("Min error at line :%d\n",__LINE__);
	}
	
	if	(MinIndex(min_test, size_min) != 4)
	{
		printf("Min error at line :%d\n",__LINE__);
	}
	
	SwapTemp((min_test + 1), (min_test));
	
	if	((min_test[0] != 5) && (min_test[1] != -4))
	{
		printf("SwapTemp error at line :%d\n",__LINE__);
	}
	
	for (i = 0; i < size_k; ++i)
	{

		k_elem = FindkthElem(arr, size, arr_k[i]);
		
		if	(k_elem != exp_result[i])
		{
			printf("FindkthElem error at line :%d\n",__LINE__);
		}

	}
	
	for (i = 0; i < size - 1; ++i)
	{

		k_elem = FindkthElem(arr, size, arr_k[i]);
		
		if	(k_elem != exp_result[i])
		{
			printf("FindkthElem error at line :%d\n",__LINE__);
		}
	}

	return ;

}
	

static size_t MinIndex(int arr[], size_t size)
{
	int min = 0;
	size_t i = 0;
	int index = 0;
	
	assert(NULL != arr);	
	
	min = arr[i];
	++i;
	
	while(i < size)
	{
		if (min > arr[i])
		{
			min = arr[i];
			index = i;
		}
		
		++i;
	}
	
	return (index);

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

