#include <stdio.h>  /*for print*/
#include <string.h>	/*for strlen*/
#include <assert.h>	/*for assert*/
#include <stdlib.h>	/*for malloc*/
#include <ctype.h> /*tolower function*/

/* Developer: Shelly Shlomi 
   Status: aproved by ANNA;   
   Description:Print Envirement Variables In Lower Case*/

#define UNUSED(x) (void)(x)
   
static size_t Execute(char **pointrs);
static void *MemoryAllocation(char **pointrs, size_t i);
static void MemoryRealles(char **str, size_t j);
static char *StrDupToLower(const char *str);
static char *StrCpy(char *dest, const char *src);
static void PrintEnv(char **pointrs);

int main(int argc, char **argv, char **envp)
{	
	int err = 0;
	UNUSED(argc);
	UNUSED(argv);

	err = Execute(envp);
	return 0;
}


size_t Execute(char **pointrs)
{
	size_t i = 0;
	char *err = NULL;
	while (NULL != *pointrs)
	{
		++pointrs;
		++i;
	}
	pointrs -= i;
	err = MemoryAllocation(pointrs, i);
	assert(err);

	return i;
}

void *MemoryAllocation(char **pointrs, size_t i)
{
	char **str = NULL;
	size_t j = 0;
	
	assert(pointrs);

	str = (char **)malloc((i + 1) * sizeof(char *));/*adding 1 for null pointer*/

	if (NULL == str)
	{	
		printf("malloc failed.\n");
		return NULL;
	}

	while (NULL != pointrs[j])
	{
		str[j] = StrDupToLower(pointrs[j]);

		if (NULL == str[j])
		{	
			MemoryRealles(str, j);
			return NULL;
		}
		
		++j;
	}
	
	str[j] = NULL;
	
	PrintEnv(pointrs);
	PrintEnv(str);
	MemoryRealles(str, j);

	return pointrs;
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
		
	return ; 	
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

char *StrDupToLower(const char *str)
{
	char *new_string = NULL;
	size_t size = 0;

	assert(str);
		
	size = strlen(str);
	
	new_string = (char *)malloc(size + 1);
		
	if (!new_string) 
	{
		printf("malloc failed\n");
		return NULL;
	}

	return StrCpy(new_string, str);

}
void PrintEnv(char **pointrs)
{
	size_t j = 0;
	assert(pointrs);


	while (NULL != *(pointrs))
	{
		printf("%lu: %s\n", j, *pointrs);
		++j;
		++pointrs;
	}
	
	return;

}

