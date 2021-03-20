#include "ex2.h" /*the function declaration*/
#include <stdlib.h> /*stty*/

/* Developer: Shelly Shlomi 
   Status: in development;   
   Description: log program */

int Logger(char **file_name);

 /* FILE * fp;

   fp = fopen ("file.txt", "w+");
   fprintf(fp, "%s %s %s %d", "We", "are", "in", 2012);
   
   fclose(fp);*/

int Logger(char **file_name)
{	
	FILE *file_ptr;
	char str[6000];
	char *file_ptr = NULL;	
	file_ptr = file_name[1];
	
	
	printf("%s\t**print**\n", *file_name);
	
	file_ptr = fopen("file.txt" , "r");
	
	if(file_ptr == NULL) {
	perror("Error opening file");
	
	return(-1);
	}
	system("stty -icanon -echo");
	
	if( fgets (str, 6000, file_ptr)!=NULL ) {

	puts(str);
	}
	
	fclose(file_ptr);
	system("stty icanon echo");
	
	return(0);
}

/*
void Logger()
{		
	char *file_name = argv[FILE_NAME];
	
	
	unsigned char c = '\0';
	size_t index = 0;
	void (*arrLut[SIZE])(void) = {0};

 	
	system("stty -icanon -echo");
	
	while (index < SIZE)
	{
		arrLut[index]= DontPrint;
		++index;
	}
	
	arrLut[ESC] = Esc;
	arrLut['A'] = PrintA;
	arrLut['T'] = PrintT;	
	arrLut['a'] = PrintA;
	arrLut['t'] = PrintT;
	

	while ( ESC != c )
	{			
 		c = getchar();
 	
        
		(*arrLut[c])();	
	
	}
	
	(*arrLut[ESC])();
	
	
	return;			
}

static void PrintA()
{
	printf( "A pressed\n");
}

static void PrintT()
{
	printf( "T pressed\n");
}

static void DontPrint()
{
	;
}

static void Esc()
{	
	system("stty icanon echo");
	return;
}

   void InputOutputIf()
{	
	char c = '\0';
	
	system("stty -icanon -echo");
	
	while ( ESC != c && EOF != c )
	{	
		c = getchar();
		
	
		if ( 'a' == c || 'A' == c ) 
		{
			printf( "A pressed\n");
		}
		else if ( 't' == c || 'T' == c )
		{
			printf( "T pressed\n");
		}
	}	
	
	system("stty icanon echo");
	
	return;
}
*/
