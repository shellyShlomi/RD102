#include <stdio.h>  /*for print*/


/* Developer: Shelly Shlomi 
   Status: in development;   
   Description: josephus problem */
   
int Josephus(int n, size_t k);
int FilingArray();
size_t JosephusProblem(int arr[], size_t size);

int main()
{	
	printf("%lu\n",	FilingArray());
	return 0;
}

/*int josephus(size_t n, int k) {
    int res = 0;
    for (int i = 1; i <= n; ++i)
      res = (res + k) % i;
    return res + 1;
}*/
size_t JosephusProblem(int arr[], size_t size)
{	
	size_t kiler = 0;
	size_t counter = 0;  /*indicate the number of kills prepormde*/
    size_t to_die = 1;  /*indicate the element which are going to be killed */
    size_t start = 0;
    size_t round = 0;
    
    while (counter <= (size -1))
    {
		if (0 != (round % 2) && 0 != (size % 2))
		{	
			arr[start] = 0;
			++counter;
			start = start +(2*round);
			kiler =  start; 
			to_die = kiler + start;
		
			if (counter == (size - 2))
			{	
			    return kiler;
			}	
		}
		
			
		if (arr[kiler] == arr[to_die] && counter < (size -1))
		{
			arr[to_die] = 0;
			++counter;
			kiler = (kiler + 2) % i;
			to_die = kiler + round + 1;
			
			if (counter == (size - 2))
			{	
			    return kiler;
			}	
			
			if ((kiler) == (size - 1))
			{	
				
				++round;
				start = start +(2*round);
				kiler = start + 2 + round;
				to_die = start + 3 + round;
				continue;
			}
			else if ((kiler) > (size - 1))
			{	
				++round;
				start = start +(2*round);
				 kiler = start + 2 + round;
				 
				continue;
			}
		}
		else 
		{
			++to_die;
			if ((to_die) > (size - 1))
			{
				to_die = 0;
			}	
		}
		
	}
    
    return 90;

}

int FilingArray()
{
	size_t index = 0;
	int arr[18] = {0};
	size_t size = 0;
	int res = 0;
	int i = 0;
	size = sizeof(arr) / sizeof(int);
	
	while (index < size)
	{
		*(arr + index) = 1;
		++index;
	}
	i=1;
	while (i  <= size)
	{
		 res = (res + 2) % i;
		++i;
	}

  return res + 1;
    
	
	
	
}

