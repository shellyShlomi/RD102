
/*  Developer: Shelly Shlomi;									*
 *  Status:in development;                                      *
 *  Date Of Creation:08.07.21;									*
 *  Date Of Approval:00.07.21;									*
 *  Approved By:  ;                                             *	 
 *  Description: threads_100k_5                                 */

#include <stdio.h> /* printf */
#include <pthread.h> /* thread */

#define NUM (3000000000)
#define THREADS_SIZE (12)
#define RANG (250000000)

pthread_t arr_threads[THREADS_SIZE] = {0};

/*------------------------------ exercise func --------------------------------*/
static void CreatThreads();
static void SumOfDivisorsMulti();
static void *ThredsRoutine(void *index);
static void SumOfDivisorsSingle();

/*------------------------------ implementetion --------------------------------*/

int main()
{
    SumOfDivisorsMulti();
    /*SumOfDivisorsSingle();*/
    return (0);
}

static void SumOfDivisorsSingle()
{
    size_t i = 1;
    size_t sum = 0;

    for (; i <= NUM; i++)
    {
        if (0 == NUM % i)
        {
            sum += i;
        }
    }

    printf("sum: %lu\n", sum);

    return;

}

static void SumOfDivisorsMulti()
{
    size_t i = 0;
    void *output_param = NULL;
    size_t sum = 0;

    CreatThreads();

    for (i = 0; i < THREADS_SIZE; i++)
    {
        pthread_join((arr_threads[i]), &output_param);
        sum += (size_t)output_param;
    }

    printf("sum: %lu\n", sum);

    return;
}

static void CreatThreads()
{
    size_t i = 0;
    size_t j = 1;

    for (i = 0; i < THREADS_SIZE; i++)
    {
        pthread_create(arr_threads + i, NULL, ThredsRoutine, (void *)(j));
        j += RANG;
    }

    return;
}

static void *ThredsRoutine(void *index)
{
    size_t i = (size_t)index;
    size_t sum = 0;

    for (; i < (size_t)index + RANG; i++)
    {
        if (0 == NUM % i)
        {
            sum += i;
        }
    }
    return ((void *)sum);
}
