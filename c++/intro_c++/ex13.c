#include <stdio.h>


int main()
{
     const int SSSSSSi = 3;
     int *ip = (int *)&SSSSSSi;
    /* int arr[SSSSSSi]; */

    *ip = 5;

    printf("%d %d\n", SSSSSSi, *ip);
    return 0;
}