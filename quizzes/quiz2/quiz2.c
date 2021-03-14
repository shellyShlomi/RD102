#include "quiz2.h" /*the function declaration*/

void PrintNumbres(int number)
{
	int i = 1;
	int sing = 1;

	if (number <= 0)
	{
		sing = -sing;
	}

	while (i != number)
	{
		if (((i * sing) % 3) == 0)
		{
			printf("T");
		}
		if (((i * sing) % 5) == 0)
		{
			printf("F");
		}
		else if (((i * sing) % 3) != 0)
		{
			printf("%d", (i));
		}

		i = i + sing;
	}
}

void ReversString(char str[])
{
	char temp = 0;
	size_t i = 0;
	size_t size = strlen(str);
	size_t length = size - 1;

	while (i < (size / 2))
	{
		if (str[length - i] <= 90 && str[length - i] >= 65)
		{
			str[length - i] += 32;
		}

		if (str[i] <= 90 && str[i] >= 65)
		{
			str[i] += 32;
		}

		temp = str[length - i];
		str[length - i] = str[i];
		str[i] = temp;
		
		++i;
	}
	
	if ( 0 != (size % 2))
	{
		str[size / 2] = tolower(str[size / 2]);
	}
	
	printf("%s", str);
}
