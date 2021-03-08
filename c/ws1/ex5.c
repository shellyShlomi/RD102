#include <stdio.h>

double PowOfTeen(int n);

int main()
{
    int a = 0;
    double exp_a = 1;
    
    if (exp_a != PowOfTeen(a))
    {
        printf("the num is %d and the return value is %f\n the expected num is %f\n"
        	, a, PowOfTeen(a), exp_a);
        printf("ERROR\n");
    }
    else
    {
        printf("the num is %d and the return value is %f\n the expected num is %f\n"
        	, a, PowOfTeen(a), exp_a);
        printf("YESSSSSS\n");
    }

    a = -6;
    exp_a = (0.000001);
    if ((float)exp_a != (float)PowOfTeen(a))
    {
        printf("the num is %d and the return value is %f\n the expected num is %f\n"
        	, a, PowOfTeen(a), exp_a);
        printf("%f ERROR\n", PowOfTeen(a));
    }
    else
    {
        printf("the num is %d and the return value is %f\n the expected num is %f\n"
        	, a, PowOfTeen(a), exp_a);
        printf("YESSSSSS\n");
    }

    a = 4;
    exp_a = (10000);
    if (exp_a != PowOfTeen(a))
    {
        printf("the num is %d and the return value is %f\n the expected num is %f\n"
        	, a, PowOfTeen(a), exp_a);
        printf("ERROR\n");
    }
    else
    {
        printf("the num is %d and the return value is %f\n the expected num is %f\n"
        	, a, PowOfTeen(a), exp_a);
        printf("YESSSSSS\n");
    }

    return 0;
}

double PowOfTeen(int n)
{
    double base = 10;
    double ans = 1;
    int i;
    
    if (n < 0)
    {
        base = (1 / base);
        n = -(n);
    }
    
    for (i = 0; i < n; i++)
    {
        ans = base * ans;
    }
    
    return ans;
}
