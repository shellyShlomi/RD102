#include <stdio.h>
#include <stdlib.h>

int main()
{
	
	printf("Insert a single character: ");
	system("stty -icanon -echo");

	if (0 == getchar() % 2)
	{
		printf("\neven!\n");
		system("stty icanon echo");

		return (0);
	}
	printf("\nodd!\n");
	system("stty icanon echo");

	return (1);	
}