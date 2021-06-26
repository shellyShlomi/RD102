#include <stdio.h>




void goo(void)
{
int i = 7;
static int j = 12;
    puts("Hello, shelly, from goo()\n");
    printf("%p, %p\n",&i, &j);
}
