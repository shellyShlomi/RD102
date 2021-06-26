#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
	int i = 88;
	int j = 16;
	int k = 8;
	int *p = 0x7fffffffdf7c;
	
	FILE *fp;
	
	if (0 == (fp = fopen("stoopid", "r")))
	{
		printf("well, that didn\'t work!\n");
		
		return -1; 
	} 

	fscanf(fp,"%p\n", &p);
	
	if (fclose(fp))
	{
		printf("oh well.");
		return -1;
	}
	
	printf("p points to: %d\n",*p);

	return 0;
}
