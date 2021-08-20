#include<stdio.h>
#include<stdlib.h>
int main()
{
	int *ptr1 = (int *)malloc(sizeof(int));
	delete ptr1;
	int *ptr2 = new int[1000];
	int *ptr =0;

	free (12);
	delete ptr;

	return 0;
}
