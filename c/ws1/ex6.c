#include <stdio.h>
int FlipNum(int n);

int main()
{
    int a = 56340;
    int exp_a = 4365;
    
    if (exp_a != FlipNum(a))
    {
        printf("the num is %d\n the expected num is %d\n", a, exp_a);
        printf("ERROR\n");
    }
    else
    {
        printf("the num is %d\n the expected num is %d\n", a, exp_a);
        printf("YESSSSSS\n");
    }

    a = 0;
    exp_a = 0;
    if (exp_a != FlipNum(a))
    {
        printf("the num is %d\n the expected num is %d\n", a, exp_a);
        printf("ERROR\n");
    }
    else
    {
        printf("the num is %d\n the expected num is %d\n", a, exp_a);
        printf("YESSSSSS\n");
    }

    a = -1;
    exp_a = -1;
    if (exp_a != FlipNum(a))
    {
        printf("the num is %d\n the expected num is %d\n", a, exp_a);
        printf("ERROR\n");
    }
    else
    {
        printf("the num is %d\n the expected num is %d\n", a, exp_a);
        printf("YESSSSSS\n");
    }

    a = 2345;
    exp_a = 5432;
    if (exp_a != FlipNum(a))
    {
        printf("the num is %d\n the expected num is %d\n", a, exp_a);
        printf("ERROR\n");
    }
    else
    {
        printf("the num is %d\n the expected num is %d\n", a, exp_a);
        printf("YESSSSSS\n");
    }

    a = -2345;
    exp_a = -5432;
    if (exp_a != FlipNum(a))
    {
         printf("the num is %d\n the expected num is %d\n", a, exp_a);
        printf("ERROR\n");
    }
    else
    {
       printf("the num is %d\n the expected num is %d\n", a, exp_a);
        printf("YESSSSSS\n");
    }

    a = -23456;
    exp_a = -65432;
    if (exp_a != FlipNum(a))
    {
         printf("the num is %d\n the expected num is %d\n", a, exp_a);
        printf("ERROR\n");
    }
    else
    {
       printf("the num is %d\n the expected num is %d\n", a, exp_a);
        printf("YESSSSSS\n");
    }
    
    return 0;
}

int FlipNum(int n)
{
    int ans = 0;
    int res = 0;
    int sing = 1;
    
    
    if (n < 0)
    {
    	n = -(n);
   	sing = -1;
    }
    
    while (n != 0)
    {
    	int base = 10;
        res = n % base;
        n = n / base;

        if (n == 0)
        {
            return (ans + res)*sing;
        }
        
        ans = (res + ans) * base;
    }

    return (ans*sing);
}
