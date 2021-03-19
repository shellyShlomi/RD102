#include <stdio.h>  /*for print*/

#define FILE_NAME 1 

/* Developer: Shelly Shlomi 
   Status: in development;   
   Description: log program */

void WriteToMyFile(char *file_name);

int main (int argc, char **argv) { 
	
	char *file_name = argv[FILE_NAME];
 
	printf("%s \n", file_name);
	return(0);
}


 /* FILE * fp;

   fp = fopen ("file.txt", "w+");
   fprintf(fp, "%s %s %s %d", "We", "are", "in", 2012);
   
   fclose(fp);*/
