#include "quiz3.h" /*the function declaration*/

int IsSumFunde( int *p_num1, int *p_num2, int arr[], int sum, size_t size);
void TestIsFunde();

int main()
{

	TestIsFunde();
	return 0;
}


void TestIsFunde()
{
	int arr[] = { -8, -5, -4, -1, 0, 1, 2, 4, 5, 6, 7};
	int sums[] = { 3, 4, 0, 20, 7};
	
	size_t size_sum = sizeof(sums) / (sizeof(int));
	size_t size_num = sizeof(arr) / (sizeof(int));
	int i = 0;
	int j = 0;

	int return_val = 5;
	int *small_index = &i;
	int *big_index = &j;
	
	while ( 0 < size_sum )
	{	
		return_val = IsSumFunde(small_index, big_index, arr, 
												sums[size_sum - 1], size_num);
												
		switch (return_val)
		{	
			case 1:
			{
				printf("\nthe indexes of the array are %d\tand %d\n", i, j);
				printf("and the return value is:\t%d\n", return_val);
				printf("the sum is %d\n\n", sums[size_sum - 1]);
				break;
			}
			case 0:
			{
				printf("\nthis sum is not exsistiong in the geiven array\n");
				printf("the sum is %d\n\n", sums[size_sum - 1]);
				break;
			}
			default:
			{
				printf("\nERROR\n");
				break;
			}
		}
		
		--size_sum;
	
	}
	
	return;
}

