#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "tools.h"

int IntArrayCompare(int arr1[], size_t len1, int arr2[], size_t len2)
{
		size_t i = 0;
		
		len1 = len1 / sizeof(int); 
		len2 = len2 / sizeof(int); 

		assert(arr1);
		assert(arr2);

		if (len1 > len2)
		{
				return 1;
		}
		else if (len1 < len2)
		{
				return -1;
		}
		for (i = 0; i < len1; ++i)
		{
				if (arr1[i] != arr2[i])
				{
						return arr1[i] - arr2[i];
				}
		}

		return 0;
}

void PrintIntArr(int arr[], size_t size)
{
	const int * const end = arr + size;
	for (arr = arr; arr < end; ++arr)
	{
		printf("%d, ",*arr);
	}
	puts("");
}

int V()
{
return printf("ddd\n");
}

