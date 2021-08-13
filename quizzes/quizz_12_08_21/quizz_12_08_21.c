#include <stdio.h>
void func2(void *arg)
{
    long f2;
    printf("Enter func2\n");

    /* Area2 */

    printf("Exit func2\n");
    
}
void func1()
{
    long f1;
    printf("Enter func1\n");
    func2(&f1);
    printf("Exit func1\n");
}

int main()
{
    const long x = 1;
    long y = 5;

    /* Area1 */
    long *ptr_x = (long *)(&x);
    *((((long *)&x) )) = 2;
    printf("&x=%p\n", &x);
    printf("&y=%p\n", &y);
    printf("&ptr_x=%p\n", &ptr_x);
    printf("ptr_x=%p\n", ptr_x);
    printf("&(*ptr_x) - 16 = %p, %d\n", ((((long *)&x)+3)),  *((((long *)&x)+3)));

    printf("y=%ld\n", y);
    printf("x=%ld\n", x);
    printf("*ptr_x=%ld\n", *ptr_x);
    func1();

    printf("Exit main\n");
    return 0;
}