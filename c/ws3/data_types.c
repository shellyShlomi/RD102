#include <stdio.h>  /*for print*/


/* Developer: Shelly Shlomi 
   Status: Noga;   
   Description: print SIZE OF data types in c*/
   

void PrintSizeOf();

int main()
{

	PrintSizeOf();
	return 9;
}
void PrintSizeOf()
{
    /* sizeof evaluates the size of a variable*/
    printf("Size of char : %lu byte\n", sizeof(char));
    printf("Size of unsigned char : %lu byte\n", sizeof(unsigned char));
    printf("Size of short : %lu byte\n", sizeof(short));
    printf("Size of unsigned short : %lu byte\n", sizeof(unsigned short));
    printf("Size of short int : %lu byte\n", sizeof(short int));
    printf("Size of unsigned short int : %lu byte\n", sizeof(unsigned short int));
    printf("Size of int: %lu bytes\n", sizeof(int));
    printf("Size of unsigned int : %lu bytes\n", sizeof(unsigned int));
    printf("Size of long : %lu byte\n", sizeof(long));
    printf("Size of unsigned long : %lu byte\n", sizeof(unsigned long));
    printf("Size of long int : %lu byte\n", sizeof(long int));
    printf("Size of unsigned long int : %lu byte\n", sizeof(unsigned long int));
    printf("Size of float: %lu bytes\n", sizeof(float));
    printf("Size of double: %lu bytes\n", sizeof(double));
    printf("Size of long double: %lu bytes\n", sizeof(long double));
    printf("Size of pointer: %lu bytes\n", sizeof(void *));
    return ;
}

