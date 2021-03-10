/* test groups :                    *
 * 1.null pointers                  *
 * 2.negativ valuess for signed int */


#include <stdio.h>


void Swap(int *x, int *y);

int main()
{
    int a = 0;
    int b;
    int exp_a = a;
    int exp_b = 0;
    
    Swap(&a, NULL);
    if (exp_a == a)
    {
        printf("YESSSSSS\n");
    }
    else
    {
        printf("ERROR\n");
    }

    a = -4;
    b = 20;
    exp_a = 20;
    exp_b = -4;
    Swap(&a, &b);
    if ((exp_a == a) && (exp_b == b))
    {
        printf("YESSSSSS\n");
    }
    else
    {
        printf("ERROR\n");
    }

    a = 0;
    b = 20;
    exp_a = 20;
    exp_b = 0;
    Swap(&a, &b);
    if ((exp_a == a) && (exp_b == b))
    {
        printf("YESSSSSS\n");
    }
    else
    {        
        printf("ERROR\n");
    }
    return 0;
}

void Swap(int *x, int *y)
{
    if (NULL != x && NULL != y)
    {
        *x = *y ^ *x;
        *y = *y ^ *x;
        *x = *y ^ *x;
    }
    else 
    {
        printf("One or more of the pionters is a NULL pointer\n");
    }
}
