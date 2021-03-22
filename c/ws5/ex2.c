/* Developer: Shelly Shlomi 
   Status: impl tested;   
   Description: log program */
   
#include <stdlib.h> /*stty*/
#include <assert.h> /*assert*/
#include <string.h> /*strlen*/
#include "ex2.h"	/*the function declaration*/

#define SIZE 5
#define BUFF 101
#define TEMP ".tmp"

enum return_val 
{
	SUCCESS,
	ERROR,
	COMP_SUCCESS = ERROR,
	COMP_FALS = SUCCESS
	
}return_val;

/*flow control functions*/
static int Analyzer(const char *buf , const char *f_name);
static int Comp(const char *str1, const char *str2); 

/*functions that procces the input and operat on it*/
static enum return_val Logger(const char *file_name, const char *buf);
static enum return_val Remove(const char *file_name, const char *buf);
static enum return_val AddBeginig(const char *file_name, const char *buf);
static enum return_val Count(const char *file_name, const char *buf);
static enum return_val ExitPorg(const char *file_name, const char *buf);


struct file_sturct
{
	const char *str;
	int (*Compar)(const char *str1, const char *str2); 
	enum return_val (*Operation)(const char *file_name, const char *buf);
};

int Meneger(const char *file_name)
{
	int ret = 0;
	char buf[BUFF] = {'\0'};

	assert(file_name);

	printf("***The folowing commend can halpe you control your file : ***\n");
	printf("*** <\t-exit\t-count\t-remove ***\n\n");
	printf("Enter your text here (top 100):\n");

	while (ERROR != ret) 
	{	
		fgets(buf, BUFF, stdin);
		ret = Analyzer(buf, file_name);
	}

	return SUCCESS;
}

static int Analyzer(const char(*buf), const char(*f_name))
{	
	static struct file_sturct arr[SIZE] =
	{
		{"-exit ", Comp, ExitPorg},
		{"< ", Comp, AddBeginig},
		{"-count ", Comp, Count},
		{"-remove ", Comp, Remove},
		{"", Comp, Logger} 
	};
								
	int done_looping = COMP_FALS;
	size_t i = 0;
	size_t elements = SIZE - 1;

	assert(f_name);
	
	if (NULL == buf)
	{
		return ERROR;
	}

	done_looping = arr[i].Compar(arr[i].str, buf);
	
	while (i < elements && (!done_looping))
	{
		++i;
		done_looping = arr[i].Compar(arr[i].str, buf);
	}
	
	return arr[i].Operation(f_name, buf);
}

static int Comp(const char *str1, const char *str2)
{
	assert(str1);
	assert(str2);
	/*test all operator - except <,beas on the length and the content*/
	if (0 == strncmp(str1, str2, (strlen(str1) - 1))
			&& strlen(str1) == strlen(str2))
	{
		return COMP_SUCCESS;
	}
	
	if (0 == strncmp(str1, str2, (strlen(str1) - 1)) /*test for the < operator*/
	 		 && 1 == (strlen(str1) - 1))/*based on the length of the stract str*/
	{
		return COMP_SUCCESS;
	}
	return COMP_FALS;
}
/*Addtion of text to the end of the file*/
static enum return_val Logger(const char *file_name, const char *buf)
{
	FILE *file_ptr = NULL;
	
	assert(file_name);
	assert(buf);

	file_ptr = fopen(file_name, "a");
	if (NULL == file_ptr)
	{
		return ERROR;
	}

	if (EOF == fputs(buf, file_ptr))
	{
		return ERROR;
	}

	fclose(file_ptr);

	return SUCCESS;
}
/*Remove the file*/
static enum return_val Remove(const char *file_name, const char *buf)
{
	assert(file_name);
	UNUSED(buf);
	
	if (!remove(file_name))
	{	
		return SUCCESS;
		printf("The file is Deleted successfully\n");
	}

	printf("the file is not Deleted / There is no such file\n");
	return SUCCESS;

}
/*Addtion of text to the begining of the file*/
static enum return_val AddBeginig(const char *file_name, const char *buf)
{	
	FILE *file_ptr = NULL;
	FILE *temp_ptr = NULL;
	int ret = 1;
	char buffer[BUFF] = {'\0'}; /* To store the character read from file */

	assert(file_name);
	assert(buf);
	
	(char *)++buf; /* To exlude the < char from the file*/
	
	file_ptr = fopen(file_name, "r+");
	if (NULL == file_ptr)
	{
		printf("No such file\n");
		
		if(SUCCESS == Logger(file_name, buf))
		{
			printf("Created a new file for you with the name assked for\n");
			return SUCCESS;			
		}
		return ERROR;
	}
	
	if(SUCCESS != Logger(TEMP, buf)) /*adding the user string to a new file*/
	{
		return ERROR;
	}
	
	temp_ptr = fopen(TEMP, "a"); /*opening the new file created by Logger*/
	if (NULL == temp_ptr)
	{
		return ERROR;
	}

	while (NULL != fgets(buffer, BUFF, file_ptr))
	{
		if (EOF == fputs(buffer, temp_ptr))
		{
			return ERROR;
		}
	}
	
	ret = rename(TEMP, file_name);
	if(0 != ret) 
	{
      return ERROR;
    } 
    
	fclose(temp_ptr);
	fclose(file_ptr);
	
	return SUCCESS;
}


/* count the lines in the file*/
static enum return_val Count(const char *file_name, const char *buf)
{
	FILE *file_ptr = NULL;
	int line_count = 0;
	char ch = '\0'; /* To store a character read from file */

	assert(file_name);
	assert(buf);

	file_ptr = fopen(file_name, "r+");
	
	if (NULL == file_ptr)
	{	
		printf("No such file\n");
		return SUCCESS;
	}

	ch = getc(file_ptr);

	while (EOF != ch)
	{
		if (ch == '\n') /* Increment counter if this character is newline*/
		{
			++line_count;
		}
		ch = getc(file_ptr);
	}
	printf("num of lines in your file is: %d\n", line_count);

	fclose(file_ptr);
	
	return SUCCESS;
}

static enum return_val ExitPorg(const char *file_name, const char *buf)
{
	UNUSED(buf);
	UNUSED(file_name);
	return ERROR;
}


