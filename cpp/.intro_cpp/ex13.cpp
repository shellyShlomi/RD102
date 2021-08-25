#include <stdio.h>
     const int zzzz = 3;
      int xxxxx = 3;
      int eeeeee;
      static int aaaeee = 9;

int main()
{
      int SSSSSSi = 3;
     int *ip = (int *)&SSSSSSi;
    printf("%p %p\n", &SSSSSSi, ip);
    int arr[SSSSSSi];

    *ip = 5;
    printf("%p %p\n", &SSSSSSi, ip);

    printf("%d %d\n", SSSSSSi, *ip);
    return 0;
}