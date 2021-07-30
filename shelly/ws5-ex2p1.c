#include <stdio.h>  /*for print*/
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define SIZE 5 


/*aproved by anna */

int Logger(const char *file_name);

int main(int argc, char **argv)
{	
	Logger(argv[1]);
	return (0);
}


int Logger(const char *file_name)
{	
	FILE *file_ptr = NULL;
	char buf[100] = {'\0'};	
	
	assert(file_name);
	
	printf("Ernter text - at top 100 charecters\n");
	
	if(NULL != fgets(buf, 100, stdin)) 
	{	
		file_ptr = fopen(file_name, "a");
		if(NULL == file_ptr) 
		{
			printf("Error opening file");
			return(-1);
		}
		
		fputs(buf, file_ptr);
		
		fclose(file_ptr);
	}
	

	return (0);
}

	
