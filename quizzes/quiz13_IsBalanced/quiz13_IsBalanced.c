#include <stdio.h>  /* 	print 	*/
#include <ctype.h>	/* 	isspace	 */
#include <string.h>  /*  strlen	*/
#include <assert.h> /*	assert	*/

static void ReversString(char *str, char *end);
void ReversStrWords(char *str);
static void Test();

int main()
{
	Test();
	
	return 0;
}

void ReversStrWords(char *str)
{
	char *orig_str = str;
	char *temp_stat = orig_str;
	size_t size = 0;
	
	assert(NULL != str);
	
	size = strlen(str);

	ReversString(str, str + (size - 1));
	
	while ('\0' != *str)
	{
		if (isspace(*str))
		{	
			ReversString(temp_stat, str - 1);
			temp_stat = str + 1;		
		}
		
		++str;
	}
	
	ReversString(temp_stat, str - 1);

	str = orig_str;
	
	return;
}

static void ReversString(char *start, char *end)
{
	
	assert(NULL != end);
	assert(NULL != start);
	
	while (start < end)
	{
		*start = *end ^ *start;
		*end = *end ^ *start;
		*start = *end ^ *start;
		
		++start;
		--end;
	}

	return;
}

static void Test()
{
	char str_arr[][50] =  {
						"Shelly Shlomi loves Ivy", 
						"Ivy is the best dog",
						"anna is the best",
						"nir is always right"
													}; 
													
	char exp_arr[][50] =  {
						"Ivy loves Shlomi Shelly",
						"dog best the is Ivy",
						"best the is anna",
						"right always is nir"
													}; 
	size_t i = 0;
	size_t size = sizeof(str_arr)/sizeof(str_arr[0]);

	for (i = 0; i < size; ++i)
	{
		ReversStrWords(str_arr[i]);
		if (strcmp((str_arr[i]), (exp_arr[i])))
		{	
			printf("ReversStrWords error at index: %ld\n", i);
		}
	}

	return; 
}
