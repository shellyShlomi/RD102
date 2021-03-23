/* Developer: Shelly Shlomi 
   Status: approved by NIR;   
   Description: josephus problem */

#include <stdio.h>  /*for print*/

static void FilingArray(int arr[], size_t size);
void JosephusProblem(int arr[], size_t size);

int main()
{	
	int arr[17] = {0};
	int arr1[100] = {0};
	int arr2[2] = {0};
	int arr3[3] = {0};
	int arr4[1] = {0};	
	
	size_t arr_size = 17;
	size_t arr_size1 = 100;
	size_t arr_size2 = 2;
	size_t arr_size3 = 3;
	size_t arr_size4 = 1;
	
	JosephusProblem(arr, arr_size);
	printf("\n");
	
	JosephusProblem(arr1, arr_size1);	
	printf("\n");
	
	JosephusProblem(arr2, arr_size2);	
	printf("\n");

	JosephusProblem(arr3, arr_size3);
	printf("\n");
	
	JosephusProblem(arr4, arr_size4);	

	
	return 0;
}

void JosephusProblem(int arr[], size_t size)
{	
	size_t i = 0;
	
	FilingArray(arr, size);
	
	while(arr[i] != arr[arr[i]])
	{	
		arr[i] = arr[arr[i]]; /*pass the sword*/
		i = arr[i]; 
	}
	
	printf("when array size is %ld the lucky soldier is at: %d\n", size, arr[i]);
	
	return ;
}

static void FilingArray(int arr[], size_t size)
{
	size_t num = 1;

	while (num < (size))
	{		
		*arr = num;

		++arr;
		++num;
	}
	
	*arr = 0;
	arr = arr - (num - 1);
	
  return ;
	
}

