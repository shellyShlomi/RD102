/* Developer: Shelly Shlomi 
   Status: APPROVED BY OHAD;   
   Description: log program */

#include <stdlib.h> /* fopen */
#include <assert.h> /* assert */
#include <string.h> /* strlen */

#include "ex2.h"	/* the function declaration */

#define UNUSED(x) (void)(x)
#define SIZE 5
#define BUFF 101
#define TEMP ".tmp"

typedef enum return_val 
{
	SUCCESS,
	ERROR
	
}return_t;

/* flow control functions */
static return_t Analyzer	(const char *buf , const char *f_name);
static return_t Comp		(const char *str, const char *uesr_str); 

/* functions that procces the input and operat on it */
static return_t Logger		(const char *file_name, const char *buf);
static return_t Remove		(const char *file_name, const char *buf);
static return_t AddBeginig	(const char *file_name, const char *buf);
static return_t Count		(const char *file_name, const char *buf);
static return_t ExitPorg	(const char *file_name, const char *buf);


struct file_sturct
{
	const char *str;
	return_t (*Compar)(const char *str, const char *uesr_str); 
	return_t (*Operation)(const char *file_name, const char *buf);
};

void Meneger(const char *file_name)
{
	int ret = 0;
	char buf[BUFF] = {'\0'};

	assert(file_name);

	printf("***The folowing commend can halpe you control your file : ***\n");
	printf("*** <\t-exit\t-count\t-remove ***\n\n");
	printf("Enter your text here (top 100):\n");

	while (ERROR != ret) 
	{	
		fgets(buf, BUFF -1 , stdin);
		ret = Analyzer(buf, file_name);
	}
	
	return ;
}

static return_t Analyzer(const char(*buf), const char(*f_name))
{	
	static struct file_sturct arr[] =
	{
		{"-exit",	Comp, ExitPorg},
		{"<", 		Comp, AddBeginig},
		{"-count",	Comp, Count},
		{"-remove", Comp, Remove},
		{"", 		Comp, Logger} 
	};

	size_t i = 0;
	size_t elements = sizeof(arr)/sizeof(arr[0]) - 1;

	assert(f_name);

	if (NULL == buf)
	{
		return ERROR;
	}
	
	while (i < elements && (arr[i].Compar(arr[i].str, buf)))
	{
		++i;
	}
	
	return arr[i].Operation(f_name, buf);
}

static return_t Comp(const char *str, const char *uesr_str)
{
	size_t str_len = 0;
	size_t uesr_len = 0;
	
	assert(str);
	assert(uesr_str);
	
	str_len = strlen(str);
	uesr_len = strlen(uesr_str) - 1;
		
	/*test all operator beased on the length and the content*/
	if (str_len == uesr_len || 1 == str_len)
	{
		if (0 == strncmp(str, uesr_str, str_len))
		{
			return 0;			 
		}
	}	
	return 1;
}
/*Addtion of text to the end of the file*/
static return_t Logger(const char *file_name, const char *buf)
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
static return_t Remove(const char *file_name, const char *buf)
{
	assert(file_name);
	UNUSED(buf);
	
	if (!remove(file_name))
	{	
		printf("The file is Deleted successfully\n");
		return SUCCESS;
	}

	printf("the file is not Deleted / There is no such file\n");
	return SUCCESS;

}
/*Addtion of text to the begining of the file*/
static return_t AddBeginig(const char *file_name, const char *buf)
{	
	FILE *file_ptr = NULL;
	FILE *temp_ptr = NULL;
	char buffer[BUFF] = {'\0'}; /* To store the character read from file */

	assert(file_name);
	assert(buf);
	
	(char *)++buf; /* To exlude the < char from the file*/
	
	file_ptr = fopen(file_name, "r");
	
	if (NULL == file_ptr)
	{
		printf("ERROR Opening File\n");
		
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
	fclose(temp_ptr);
	
	if(SUCCESS != rename(TEMP, file_name)) 
	{
      return ERROR;
    } 
    
	fclose(file_ptr);
	
	return SUCCESS;
}


/* count the lines in the file*/
static return_t Count(const char *file_name, const char *buf)
{
	FILE *file_ptr = NULL;
	int line_count = 0;
	char ch = '\0'; /* To store a character read from file */

	assert(file_name);
	assert(buf);

	file_ptr = fopen(file_name, "r");
	
	if (NULL == file_ptr)
	{	
		printf("No such file\n");
		return SUCCESS;
	}

	while (EOF != (ch = getc(file_ptr)))
	{
		if ('\n' == ch) /* Increment counter if this character is newline*/
		{
			++line_count;
		}
	}
	printf("num of lines in your file is: %d\n", line_count);

	fclose(file_ptr);
	
	return SUCCESS;
}

static return_t ExitPorg(const char *file_name, const char *buf)
{
	UNUSED(buf);
	UNUSED(file_name);
	
	return ERROR;
}


