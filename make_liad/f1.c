#include <stdio.h>

int iii;

void function_in_f1_file(void)
{
	++iii;
	printf("Hi from function_in_f1_file from f1.c;  ");
	printf("Value of iii is: %d;   Address of iii is: %p\n", iii, &iii);
}