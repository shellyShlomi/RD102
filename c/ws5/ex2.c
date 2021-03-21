/* Developer: Shelly Shlomi 
   Status: impl tested;   
   Description: log program */
   
#include <stdlib.h> /*stty*/
#include <assert.h> /*assert*/
#include <string.h> /*strlen*/
#include "ex2.h"	/*the function declaration*/

#define SIZE 5
#define BUFF 6000

enum return_val 
{
	SUCCESS,
	ERROR,
	COMP_SUCCESS = ERROR,
	COMP_END = SUCCESS
	
}return_val;

/*flow control functions*/
static int Analyzer(const char *buf , const char *f_name);
static int Comp(const char *str1, const char *str2); 

/*functions that procces the input and operat on it*/
static int Logger(const char *file_name, const char *buf);
static int Remove(const char *file_name, const char *buf);
static int AddBeginig(const char *file_name, const char *buf);
static int Count(const char *file_name, const char *buf);
static int ExitPorg(const char *file_name, const char *buf);

struct file_sturct
{
	const char *str;
	int (*Compar)(const char *str1, const char *str2); 
	int (*Operation)(const char *file_name, const char *buf);
};


int Meneger(const char *file_name)
{
	int ret = 0;
	char buf[BUFF] = {'\0'};

	assert(file_name);

	printf("***The folowing commend can halpe you control your file : ***\n");
	printf("*** <\t-exit\t-count\t-remove ***\n\n");
	printf("Enter your text here :\n");

	while (ERROR != ret) 
	{	
		fgets(buf, BUFF, stdin);
		ret = Analyzer(buf, file_name);
	}

	return SUCCESS;
}

static int Analyzer(const char(*buf), const char(*f_name))
{	
	struct file_sturct arr[SIZE] = {{"< ", Comp, AddBeginig},
								{"-count ", Comp, Count},
								{"-exit ", Comp, ExitPorg},
								{"-remove ", Comp, Remove},
								{"", Comp, Logger}};
								
	int done_looping = 0;
	size_t i = 0;
	size_t elements = SIZE - 1;

	assert(f_name);
	assert(buf);

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
	 		 && 1 == (strlen(str1) - 1))/*beas on the length of the  stract str*/
	{
		return COMP_SUCCESS;
	}
	return COMP_END;
}
/*Addtion of text to the end of the file*/
static int Logger(const char *file_name, const char *buf)
{
	FILE *file_ptr = NULL;

	assert(file_name);
	assert(buf);

	file_ptr = fopen(file_name, "a");
	if (NULL == file_ptr)
	{
		return ERROR;
	}

	fputs(buf, file_ptr);

	fclose(file_ptr);

	return SUCCESS;
}
/*Remove the file*/
static int Remove(const char *file_name, const char *buf)
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
static int AddBeginig(const char *file_name, const char *buf)
{	
	FILE *file_ptr = NULL;
	size_t i = 0;
	char ch = '\0'; /* To store the character read from file */
	char buffer[BUFF] = {'\n'}; /* To store the read from file */

	assert(file_name);
	assert(buf);

	file_ptr = fopen(file_name, "r+");
	if (NULL == file_ptr)
	{
		printf("No such file\n");
		
		(char *)++buf;
		
		if(SUCCESS == Logger(file_name, buf))
		{
			printf("Created a new file for you with the name assked for\n");
			return SUCCESS;			
		}
		return ERROR;
	}
	
	ch = getc(file_ptr);

	while (EOF != ch)
	{
		buffer[i] = ch;
		++i;
		ch = getc(file_ptr);
	}
	fseek(file_ptr, 0, SEEK_SET);

	(char *)++buf;
	
	fputs(buf, file_ptr);

	fputs(buffer, file_ptr);
	fclose(file_ptr);
	
	return SUCCESS;
}

/* count the lines in the file*/
static int Count(const char *file_name, const char *buf)
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

static int ExitPorg(const char *file_name, const char *buf)
{
	UNUSED(buf);
	UNUSED(file_name);
	exit(SUCCESS);
}


