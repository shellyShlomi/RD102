#include <stdio.h>  /*for print*/
#include <string.h>	/*for strlen*/
#include <assert.h>	/*for assert*/
#include <stdlib.h>	/*for malloc*/
#include <ctype.h> /*tolower function*/

/* Developer: Shelly Shlomi 
   Status: aproved by ANNA;   
   Description:Print Envirement Variables In Lower Case*/
   
size_t NumberOfElement(char **pointrs);
void *MemoryAllocation(char **pointrs, size_t i);
void MemoryRealles(char **str, size_t j);
char *StrDup(const char *str);
char *StrCpy(char *dest, const char *src);
void PrintEnv(char **pointrs, char **str);

int main(int argc, char **argv, char **envp)
{

	NumberOfElement(envp);
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
		while (NULL != pointrs[j])
		{
			str[j] = StrDup(pointrs[j]);

			if (NULL == str[j])
			{	
				MemoryRealles(str, j);
				
				printf("malloc failed\n");
				return NULL;
			}
			
			++j;
		}
		
		str[j] = NULL;
		
		PrintEnv(pointrs, str);
		
		MemoryRealles(str, j);
	
	}

	return NULL;
}

void MemoryRealles(char **str, size_t j)
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

char *StrDup(const char *str)
{
	char *new_string = NULL;
	size_t size = 0;

	assert(str);
		
	size = strlen(str) + 1;
	
	new_string = (char *)malloc(size);
		
	if (!new_string) 
	{
		printf("malloc failed\n");
		return NULL;
	}

	return StrCpy(new_string, str);

}
void PrintEnv(char **pointrs, char **str)
{
	size_t j = 0;
	assert(pointrs);
	assert(str);

	while (NULL != *(pointrs))
	{
		printf("%lu: %s\n", j, *pointrs);
		++j;
		++pointrs;
	}

	printf("-------------------------------------------\n");
	
	j = 0;
	
	while (NULL != *(str))
	{
		printf("%lu: %s\n", j, *str);
		++j;
		++str;
	}

}

