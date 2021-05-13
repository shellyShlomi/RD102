#include <assert.h> /* assert */
#include <stdio.h> /* printf */


/*---------------------Quiz funcs---------------------*/
static void FindTwoMissingNumXOR(int arr[], size_t n);
static void FindTwoMissingNumAritmetics(int arr[], size_t n);

/*---------------------Test funcs---------------------*/
static void TestXOR();
static void TestAritmetics();

/*---------------------color funcs---------------------*/
static void Purple();
static void Cyan();
static void Reset();



int main()
{
	TestXOR();
	TestAritmetics();
	
	return 0;
}


static void FindTwoMissingNumAritmetics(int arr[], size_t n)
{
	int arr_sum = 0;
	int small_then_avg = 0;
	int sum_missing_num = 0;
	int avg_misiing_num = 0;
    int num1 = 0;
    int num2 = 0;
   
	size_t i = 0; 
   
	assert(NULL != arr);

	for (i = 0; i < n - 2; ++i)
	{
		arr_sum += arr[i];
	}
	
	/*	The Sum of 2 Missing Numbers - [the total sum - array sum]
	 */ 
	sum_missing_num = ((n * (n + 1)) / 2) - arr_sum;
	
	avg_misiing_num = (sum_missing_num) / 2;

	for (i = 0; i < n - 2; ++i)
	{
		if (arr[i] <= avg_misiing_num)
		{
		    small_then_avg += arr[i];
		}
	}

	num1 = ((avg_misiing_num  * (avg_misiing_num + 1)) / 2) - small_then_avg;

	num2 = sum_missing_num - num1;

    printf("The Missing Numbers Are: %d %d\n", num1, num2);
}


static void FindTwoMissingNumXOR(int arr[], size_t n)
{
   
    int xor = 0;
    int xor_right_bit = 0;
    int num1 = 0;
    int num2 = 0;
   	size_t i = 0;
   
    assert(NULL != arr);
  
    xor = arr[0];
    
    for (i = 1; i < n - 2; ++i)
    {
        xor ^= arr[i];
    }
    
    for (i = 1; i <= n; ++i)
    {
        xor ^= i;  	
	}

    xor_right_bit = xor & ~(xor - 1); 
   
    for (i = 0; i < n - 2; ++i)
	{
		if (arr[i] & xor_right_bit)
		{
			num1 ^= arr[i]; 
		}
		else
		{
			num2 ^= arr[i]; 
		}
	}

	for (i = 1; i <= n; ++i)
	{
		if (i & xor_right_bit)
		{
			num1 ^= i; 
		}
		else
		{
			num2 ^= i;
		}  
	}
  
    printf("The Missing Numbers Are: %d %d\n", num1, num2);
}


static void TestXOR()
{
	int arr[] = {1, 5, 2};
	int arr1[] = {1, 3, 5, 6};
   	int arr2[] = {1, 3, 5, 6, 4, 9, 8, 10};
   
  	size_t size = sizeof(arr)/ sizeof(arr[0]);
	size_t size1 = sizeof(arr1)/ sizeof(arr1[0]);
	size_t size2 = sizeof(arr2)/ sizeof(arr2[0]);
	
	size_t i = 0;
	
	printf("\n");
	Purple();
	printf("---------------------XOR---------------------\n\n");
	Reset();
	
	printf("arr is : ");
	for (i = 0; i < size; ++i)
	{	
		printf("%d ",arr[i]);
	}
	
	printf("\n\n");
	FindTwoMissingNumXOR(arr, size + 2);
	printf("FindTwoMissingNumXOR exp is: %d and %d\n", 4, 3);

	
	printf("\n\n");
	printf("arr is : ");
	for (i = 0; i < size1; ++i)
	{	
		printf("%d ",arr1[i]);
	}
	
	printf("\n\n");
	FindTwoMissingNumXOR(arr1, size1 + 2);
	printf("FindTwoMissingNumXOR exp is: %d and %d\n", 4, 2);

	printf("\n\n");
	printf("arr is : ");
	for (i = 0; i < size2; ++i)
	{	
		printf("%d ",arr2[i]);
	}
	
	printf("\n\n");
	FindTwoMissingNumXOR(arr2, size2 + 2);
	printf("FindTwoMissingNumXOR exp is: %d and %d\n", 7, 2);
	printf("\n");

	return ;

}

static void TestAritmetics()
{
	int arr[] = {3, 5, 2};
	int arr1[] = {1, 3, 5, 6};
   	int arr2[] = {1, 3, 5, 6, 4, 9, 8, 10};
   
  	size_t size = sizeof(arr)/ sizeof(arr[0]);
	size_t size1 = sizeof(arr1)/ sizeof(arr1[0]);
	size_t size2 = sizeof(arr2)/ sizeof(arr2[0]);
	
	size_t i = 0;
	
	printf("\n");
	Cyan();
	printf("---------------------Aritmetics---------------------\n");
	Reset();
	
	printf("arr is : ");
	for (i = 0; i < size; ++i)
	{	
		printf("%d ",arr[i]);
	}
	
	printf("\n\n");
	FindTwoMissingNumAritmetics(arr, size + 2);
	printf("FindTwoMissingNumXOR exp is: %d and %d\n", 4, 1);

	
	printf("\n\n");
	printf("arr is : ");
	for (i = 0; i < size1; ++i)
	{	
		printf("%d ",arr1[i]);
	}
	
	printf("\n\n");
	FindTwoMissingNumAritmetics(arr1, size1 + 2);
	printf("FindTwoMissingNumXOR exp is: %d and %d\n", 4, 2);

	printf("\n\n");
	printf("arr is : ");
	for (i = 0; i < size2; ++i)
	{	
		printf("%d ",arr2[i]);
	}
	
	printf("\n\n");
	FindTwoMissingNumAritmetics(arr2, size2 + 2);
	printf("FindTwoMissingNumXOR exp is: %d and %d\n", 7, 2);
	printf("\n");

	return ;

}



static void Reset() 
{
  printf("\033[0m");
}


static void Purple() 
{
  printf("\033[0;35m");
}


static void Cyan()
{
  printf("\033[0;36m");
}
