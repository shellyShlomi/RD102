#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
/* Developer: Shelly Shlomi 
   Status: in development;   
   Description: strings libery*/
   
char *StrCpy(char *dest, const char *src);
size_t NumberOfElement(char **pointrs);
void *MemoryAllocation(char **pointrs, size_t i);
void PrintEnv(char **pointrs, char **str);
char *StrDup(const char *str);

int main(int argc, char **argv, char **envp)
{
	size_t size = 0;

	/*char *str = NULL;
	char(**arr) = envp;
	int i = 0;
	int j = 0;*/

	size = NumberOfElement(envp);


	return 0;
}


size_t NumberOfElement(char **pointrs)
{

	size_t i = 0;

	while (NULL != *(pointrs + i))
	{
		++i;
	}

	MemoryAllocation(pointrs, i);

	return i;
}

void *MemoryAllocation(char **pointrs, size_t i)
{
	char **str = NULL;
	size_t j = 0;
	assert(pointrs);

	str = (char **)malloc((i + 1) * sizeof(char *));

	if (NULL == str)
	{	
		printf("malloc failed.\n");
		return NULL;
	}
	else
	{
		while (j <= i && NULL != *(pointrs + j))
		{
			str[j] = StrDup(*(pointrs + j));

			if (NULL == str[j])
			{	
				while (j > 0)
				{
					free(str[j]);
					str[j] = NULL;
					--j;
				}
				
				free(str[j]);
				str[j] = NULL;
				free(str);
				str = NULL;
				printf("malloc failed\n");
				return NULL;
			}
			else
			{
				++j;
			}
		}

		str[j] = NULL;
		PrintEnv(pointrs, str);
		while (j > 0)
		{
			free(str[j]);
			str[j] = NULL;

			--j;
		}

		free(str[j]);
		str[j] = NULL;
		free(str);
		str = NULL;
	}

	return NULL;
}

char *StrCpy(char *dest, const char *src)
{
	char *dest_oregin = dest; /*saving the original location*/
							  /*of the destanetion pointer*/
	assert(src);
	assert(dest);

	while ('\0' != *src)
	{
		*dest = tolower(*src);
		++dest;
		++src;
	}
	*dest = '\0';

	return dest_oregin;
}

void PrintEnv(char **pointrs, char **str)
{
	size_t j = 0;
	assert(pointrs);
	assert(str);

	while (NULL != *(pointrs))
	{
		printf("%s\n", *pointrs);
		++j;
		*pointrs = *(pointrs + j);
	}
	pointrs = (pointrs - j);
	printf("-------------------------------------------\n");
	
	j = 0;
	
	while (NULL != *(str))
	{
		printf("%s\n", *str);
		++j;
		*str = *(str + j);
	}

	return;
}

