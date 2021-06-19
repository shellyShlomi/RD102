#include <stdio.h>
/*
double Pow(double x, int y)
{

    double res = 1.0;

    if (0 > y)
    {
        x = 1 / x;
        y *= -1;
    }

    while (0 < y)
    {
        res = res * x;
        --y;
    }
}
*/

double AritmeticsPow(double x, int y);
double Pow(double x, int y);

int main()
{
    printf("%f\n", Pow(3, 3));
    printf("%f\n", Pow(3, 2));
    printf("AritmeticsPow %f\n", AritmeticsPow(3, 3));
    printf("AritmeticsPow %f\n", AritmeticsPow(3, 2));

    printf("\n");

    return (0);
}

double AritmeticsPow(double x, int y)
{

    double res = 1.0;
    int odd_even_y = (y & (y - 1));
    y = y / 2;

    if (0 > y)
    {
        x = 1 / x;
        y *= -1;
    }

    while (0 < y)
    {
        y = y / 2;
        res = res * x * x;
    }

    return odd_even_y ? (res * x) : res;
}

double Pow(double x, int y)
{

    double res = 1.0;
    int original_y = y; 
    y >>= 1;

    if (0 > y)
    {
        x = 1 / x;
        y *= -1;
    }

    while (0 < y)
    {
        y >>= 1;
        res = res * x * x;
    }

    return (original_y & (original_y - 1)) ? (res * res) / x : res;
}

