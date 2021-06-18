#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "calculator.h"

static void TestCalculator();
static void TestCalculator2();
static void TestCalculatorMathErr();

int main()
{
    TestCalculatorMathErr();
    TestCalculator();
    TestCalculator2();

    return (0);
}

static void TestCalculatorMathErr()
{
    const char *str[] = {
        "2^2(2 + 1)/0 +8",
        "1 + 2/0 + 1 * 3(1+2)) + 1",
        "(1 + 2) * 0 ^ 0 * 4 ^ 2 + 2^3(2+3+4) + 2(2)",
        "0 ^-1",
        "0 ^ -10"};

    int exp_status[] = {2, 2, 2, 2, 2};
    double result_arr[sizeof(exp_status) / sizeof(exp_status[0])] = {0};

    size_t size = sizeof(exp_status) / sizeof(exp_status[0]);
    size_t i = 0;
    int status = 6;

    for (i = 0; i < size; ++i)
    {
        status = Calculate(str[i], result_arr + i);

        if ((exp_status[i] != status))
        {
            printf("\nTestCalculatorMathErr failed at index: %lu\n", i);
            printf("user equation: %s\n", str[i]);
            printf("calaulator status expected result: %d\n", exp_status[i]);
            printf("calaulator status actual result: %d\n\n", status);
        }
    }

    return;
}

static void TestCalculator()
{

    const char *str[] = {
        "2^2(2 + 1)",
        "2-1 + 5 *2 * 2",
        "(3 * 5) + 2 + 2 * (2*2^2) + 2",
        "---4*1",
        "(1 + 2) * 3 ^ 2 * 4 ^ 2 + 2^3(2+3+4) + 2(2)",
        "6/2",
        "3 + 2^3",
        "6/2*3 +2",
        "2^2",
        "2+3 +5*6+5",
        "2 +3 +5 + 1(6 +5)",
        "2 + 3 + 5*(6+5)",
        "2^-2"};

    double exp_result[] = {12.0, 21.0, 35.0, -4, 508.0, 3.0, 11.0, 11.0, 4.0, 40.0, 21.0, 60.0, 0.25};
    int exp_status[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    double result_arr[sizeof(exp_result) / sizeof(exp_result[0])] = {0};

    size_t size = sizeof(exp_result) / sizeof(exp_result[0]);
    size_t i = 0;
    int status = 6;

    for (i = 0; i < size; ++i)
    {
        status = Calculate(str[i], result_arr + i);
        if (exp_result[i] != result_arr[i])
        {
            printf("\nTestCalculator failed at index: %lu\n", i);
            printf("user equation: %s\n", str[i]);
            printf("expected result: %.2f\n", exp_result[i]);
            printf("actual result: %.2f\n", result_arr[i]);
        }

        if ((exp_status[i] != status))
        {
            printf("\nTestCalculator failed at index: %lu\n", i);
            printf("user equation: %s\n", str[i]);
            printf("calaulator status expected result: %d\n", exp_status[i]);
            printf("calaulator status actual result: %d\n\n", status);
        }
    }

    return;
}

static void TestCalculator2()
{
    const char *str[] = {
        "2*3 )+(((2^2))) +5*2",
        "2*4)",
        ")",
        "()",
        "q",
        "(",
        "4+ 5 . 3",
        "4a4",
    };

    int status = 6;

    int exp_status[] = { 1, 1, 1, 1, 1, 1, 1, 1};
    double result_arr[sizeof(exp_status) / sizeof(exp_status[0])] = {0};

    size_t size = sizeof(exp_status) / sizeof(exp_status[0]);
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        status = Calculate(str[i], result_arr + i);

        if ((exp_status[i] != status))
        {
            printf("\nTestCalculator2 failed at index: %lu\n", i);
            printf("user equation: %s\n", str[i]);
            printf("calaulator status expected result: %d\n", exp_status[i]);
            printf("calaulator status actual result: %d\n\n", status);
        }
    }

    return;
}
