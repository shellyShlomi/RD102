#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "tools.h"
#define NORMAL "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define BLUE "\x1B[34m"
static size_t err_count = 0;
static size_t count = 0;

int Validate(int expression, const char *message)
{
		++count;
		if (!expression)
		{
				printf("%s\n", message);
				++err_count;
				return 1;
		}

		return EXIT_SUCCESS;
}


int ValidStrEqual(const char *str1, const char *str2, const char *message)
{
	if (Validate(!strcmp(str1, str2), message))
	{
		printf("%s not equal ", str1);
		printf("%s \n", str2);

		return 1;
	}

	return EXIT_SUCCESS;
}
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

void TotalErrors(void)
{
		printf("Total tested: %s%ld", BLUE, count);
		printf("%s",NORMAL);

		printf(" | passed: %s%ld", GREEN, count - err_count);
		printf("%s",NORMAL);

		printf(" | failed: %s%ld\n", RED, err_count);

		return;
}

