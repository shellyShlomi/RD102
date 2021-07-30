
#include <time.h>   /*  clock_t   */
#include <stdio.h>  /* printf */
#include <string.h> /* memset */

#include "knights_tour.h"

#define BOARD_AXIS (8)
#define COMPLEX_TEST (19)
#define EASY_TEST (0)

static void KnightsTourTest();
/* static void KnightsTourTest1();*/
static void WarnsdorffsTourTest();

int main()
{
    KnightsTourTest();
    /* KnightsTourTest1(); */
    WarnsdorffsTourTest();

    return (0);
}

static void KnightsTourTest()
{
    size_t i = 0;

    char path[BOARD_SIZE] = {'\0'};
    clock_t end_time = 0;
    clock_t start_time = 0;

    /****************************** easy_test ******************************/
    printf("KnightsTour\n");

    printf("start point is %d\n", EASY_TEST);
    start_time = clock();
    printf("status :%d\n", CreateTour(EASY_TEST, path));
    end_time = clock();
    printf("phat is \n");
    for (i = 0; i < BOARD_SIZE - 1; ++i)
    {
        printf("%d->", (int)(path[i]));
    }
    printf("%d\n", (int)(path[i]));
    printf("duration: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);
    printf("\n");

    /****************************** complex_test ******************************/

    printf("start point is %d\n", COMPLEX_TEST);
    start_time = clock();
    printf("status :%d\n", CreateTour(COMPLEX_TEST, path));
    end_time = clock();
    printf("phat is \n");
    for (i = 0; i < BOARD_SIZE - 1; ++i)
    {
        printf("%d->", (int)(path[i]));
    }
    printf("%d\n", (int)(path[i]));
    printf("duration: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);
    printf("\n");

    return;
}

/****************************** all numbers ******************************/
/* static void KnightsTourTest1()
{
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    int error = 0;
    int status = 1;

    char path[BOARD_SIZE] = {'\0'};
    clock_t end_time = 0;
    clock_t start_time = 0;

    printf("KnightsTour\n");

    for (j = 1; j < BOARD_SIZE; ++j)
    {
        memset(path, 0, BOARD_SIZE);
        start_time = clock();
        status = CreateTour(j, path);
        end_time = clock();

        for (i = 0; i < BOARD_SIZE; ++i)
        {
            for (k = 0; k < BOARD_SIZE; ++k)
            {
                if ((i != k) && (path[i] == path[k]))
                {
                    printf("path finding faild at num: %lu\n", j);
                    printf("path[i] : %d\n", path[i]);
                    printf("i : %lu\n", i);
                    printf("path[k] : %d\n", path[k]);
                    printf("k : %lu\n", k);
                    ++error;
                }
            }
        }
        if (0 != error)
        {
            printf("\n");

            printf("start point is %d\n", (int)j);
            printf("status :%d\n", status);

            printf("phat is \n");
            for (i = 0; i < BOARD_SIZE - 1; ++i)
            {
                printf("%d->", (int)(path[i]));
            }
            printf("%d\n", (int)(path[i]));
            printf("duration: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);
        }
    }

    return;
} */

static void WarnsdorffsTourTest()
{
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    int error = 0;
    int status = 1;
    double sum = 0;

    char path[BOARD_SIZE] = {'\0'};
    clock_t end_time = 0;
    clock_t start_time = 0;

    printf("\nWarnsdorffsTour\n");
    /****************************** all numbers ******************************/

    for (j = 0; j < BOARD_SIZE; ++j)
    {
        memset(path, 0, BOARD_SIZE);
        start_time = clock();
        status = WarnsdorffsTour(j, path);
        end_time = clock();

        for (i = 0; i < BOARD_SIZE; ++i)
        {
            for (k = 0; k < BOARD_SIZE; ++k)
            {
                if ((i != k) && (path[i] == path[k]))
                {
                    printf("path finding faild at num: %lu\n", j);
                    printf("path[i] : %d\n", path[i]);
                    printf("i : %lu\n", i);
                    printf("path[k] : %d\n", path[k]);
                    printf("k : %lu\n", k);
                    ++error;
                }
            }
        }
        if (0 == error)
        {
            printf("\n");

            printf("start point is %d\n", (int)j);
            printf("status :%d\n", status);

            printf("phat is \n");
            for (i = 0; i < BOARD_SIZE - 1; ++i)
            {
                printf("%d->", (int)(path[i]));
            }
            printf("%d\n", (int)(path[i]));
            printf("duration: %f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);
        }
            sum+=(double)(end_time - start_time) / CLOCKS_PER_SEC;
    }
            printf("sum: %f\n", sum);

    return;
}
