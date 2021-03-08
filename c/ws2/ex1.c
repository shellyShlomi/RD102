//test groups :
//1.null pointers
//2.negativ valuess for signed int


#include <stdio.h>
#include "ex1.h"

int main()
{
    int a = 0;
    int b;
    int exp_a = a;
    int exp_b = 0;
    Swap(&a, NULL);
    if (exp_a == a)
    {
        printf("a is stil %d \n", a);
        printf("YESSSSSS\n");
    }
    else
    {
        printf("a is now %d \n", a);
        printf("ERROR\n");
    }

    a = -4;
    b = 20;
    exp_a = 20;
    exp_b = -4;
    Swap(&a, &b);
    if ((exp_a == a) && (exp_b == b))
    {
        printf("a was %d b was %d\n", exp_b, exp_a);
        printf("a is %d b is %d\n", a, b);
        printf("YESSSSSS\n");
    }
    else
    {
        printf("a was %d  b was %d\n", exp_b, exp_a);
        printf("a is %d  b is %d\n", a, b);
        printf("ERROR\n");
    }

    a = 0;
    b = 20;
    exp_a = 20;
    exp_b = 0;
    Swap(&a, &b);
    if ((exp_a == a) && (exp_b == b))
    {
        printf("a was %d b was %d\n", exp_b, exp_a);
        printf("a is %d b is %d\n", a, b);
        printf("YESSSSSS\n");
    }
    else
    {
        printf("a was %d  b was %d\n", exp_b, exp_a);
        printf("a is %d  b is %d\n", a, b);
        printf("ERROR\n");
    }
    
    return 0;
}

void Swap(int *x, int *y)
{
    if (x != NULL && y != NULL)
    {
        *x = *y ^ *x;
        *y = *y ^ *x;
        *x = *y ^ *x;
    }
    else 
    {
        printf("One or more of the pionters is a NULL pointer");
    }
}
