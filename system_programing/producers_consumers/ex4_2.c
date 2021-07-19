/*  Developer: Shelly Shlomi;									*
 *  Status:Approved;                                            *
 *  Date Of Creation:14.07.21;									*
 *  Date Of Approval:18.07.21;									*
 *  Approved By:Sagi;                                           *	 
 *  Description: Producers Consumers problem multiple Consumers *
 *               and Producers 2 mutex, and 2 indexses          *
 *                                   -FSQ                       */

#include <stdio.h>     /*           printf             */
#include <pthread.h>   /*           thread             */
#include <semaphore.h> /*          semaphore           */
#include <fcntl.h>     /*      For O_* constants       */
#include <stdatomic.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <signal.h>

#define THREADS_SIZE (10)
#define Q_SIZE (100)
#define CONSUMER_WRITE_SIZE (20)
#define TEST_SIZE (100)

typedef enum return_val
{
    THREAD_CREATE_FAILDE = 1,
    CIRCULAR_QUEUE_CREATE_FAILDE,
    BUFFER_IS_EMPTY
} return_val_t;

static void *Producers();
static void *Consumers(void *i);

static int CreatThreads(pthread_t arr_threads[]);
static return_val_t Manager();
static void MutexDestroy();

static void PrintArrays(const char *messeg);
static void ResetBuffre();

static void Test();
static int Compare(const void *data1, const void *data2);
static int IsBufferCoreect();
static int FindMax();

pthread_mutex_t *lock_w = NULL;
pthread_mutex_t *lock_r = NULL;
int buf[Q_SIZE];
size_t write = 1; /* index to write to */
size_t read = 0;  /* index to read from */
int queue[Q_SIZE];
size_t i = 0;

int main()
{
    int status = Manager();

    if (status)
    {
        switch (status)
        {

        case THREAD_CREATE_FAILDE:
        {
            printf("pthread create failde\n");
            break;
        }
        case CIRCULAR_QUEUE_CREATE_FAILDE:
        {
            printf("circular queue create failde\n");
            break;
        }
        case BUFFER_IS_EMPTY:
        {
            printf("buffer is empty\n");
            return (BUFFER_IS_EMPTY);
        }
        default:
        {
            break;
        }
        }
    }
    Test();
    return (0);
}
static return_val_t Manager()
{
    pthread_t arr_threads[THREADS_SIZE] = {0};
    pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
    return_val_t status = 0;

    lock_r = &mutex1;
    lock_w = &mutex2;

    ResetBuffre();

    PrintArrays("befor");

    status = CreatThreads(arr_threads);

    MutexDestroy();

    PrintArrays("after");

    return (status);
}

static void MutexDestroy()
{
    pthread_mutex_destroy(lock_r);
    pthread_mutex_destroy(lock_w);

    return;
}

static int CreatThreads(pthread_t arr_threads[])
{
    size_t i = 0;
    size_t k = 0;

    return_val_t status[THREADS_SIZE] = {0};
    void *output_param = NULL;

    assert(arr_threads);

    for (k = 0; k < THREADS_SIZE / 2; ++k)
    {
        if (pthread_create(arr_threads + k, NULL, Producers, NULL))
        {
            return (THREAD_CREATE_FAILDE);
        }
    }

    for (k = THREADS_SIZE / 2; k < THREADS_SIZE; ++k)
    {
        if (pthread_create(arr_threads + k, NULL, Consumers, (void *)(i * CONSUMER_WRITE_SIZE)))
        {
            return (THREAD_CREATE_FAILDE);
        }
        ++i;
    }

    for (k = 0; k < THREADS_SIZE; ++k)
    {
        pthread_join(arr_threads[k], &output_param);
        status[k] = (return_val_t)output_param;
    }

    for (k = 0; k < THREADS_SIZE; ++k)
    {
        if (status[k])
        {
            return (status[k]);
        }
    }

    return (0);
}

static void *Producers()
{
    int local_val = 0;

    while (local_val < Q_SIZE)
    {
        /*-------------------critical section---------------------*/
        pthread_mutex_lock(lock_r);
        pthread_mutex_lock(lock_w);
        if (Q_SIZE == write - read)
        {
            local_val = write + 1 - read;
            pthread_mutex_unlock(lock_w);
            pthread_mutex_unlock(lock_r);
            continue;
        }

        local_val = write + 1 - read;
        pthread_mutex_unlock(lock_r);
        queue[write % (Q_SIZE)] = write % (Q_SIZE);
        ++write;
        pthread_mutex_unlock(lock_w);

        /*-------------------critical section---------------------*/
    }

    return ((void *)EXIT_SUCCESS);
}

static void *Consumers(void *i)
{
    size_t j = (size_t)i;

    while (1)
    {
        /*-------------------critical section---------------------*/
        pthread_mutex_lock(lock_r);
        pthread_mutex_lock(lock_w);
        if (0 == write - read)
        {
            pthread_mutex_unlock(lock_w);
            pthread_mutex_unlock(lock_r);
            return ((void *)BUFFER_IS_EMPTY);
        }

        pthread_mutex_unlock(lock_w);

        buf[j] = queue[read % (Q_SIZE)];
        queue[read % (Q_SIZE)] = -1;
        ++read;
        ++j;
        pthread_mutex_unlock(lock_r);

        /*-------------------critical section---------------------*/
    }

    return ((void *)EXIT_SUCCESS);
}

/*---------------------------------Test funcs---------------------------------*/

static void PrintArrays(const char *messeg)
{
    size_t i = 0;

    printf("buf %s threds\n", messeg);

    for (i = 0; i < Q_SIZE; ++i)
    {
        printf("%d ", buf[i]);
    }
    printf("\n\n");

    printf("queue %s threds\n", messeg);
    for (i = 0; i < Q_SIZE; ++i)
    {
        printf("%d ", queue[i]);
    }
    printf("\n\n");

    return;
}

static void ResetBuffre()
{
    size_t i = 0;
    for (i = 0; i < Q_SIZE; ++i)
    {
        buf[i] = -9;
    }

    return;
}

/*---------------------------------Test funcs---------------------------------*/

static void Test()
{
    size_t i = 0;
    int copy[TEST_SIZE] = {0};
    size_t size = (size_t)FindMax();

    memcpy(copy, buf, size);

    qsort(copy, size, sizeof(int), Compare);

    if (IsBufferCoreect(copy))
    {
        for (i = 0; i < size; ++i)
        {
            printf("sorted test_buf[i] is: %d \n", copy[i]);
        }
    }
}

static int IsBufferCoreect()
{
    size_t i = 0;
    size_t j = 0;
    int count_arr[TEST_SIZE] = {0};
    size_t size = (size_t)FindMax();

    for (i = 0; i < size; ++i)
    {
        ++(count_arr[buf[i]]);
    }

    for (j = 0; j < size; ++j)
    {
        if ((5 < count_arr[j] && 0 < buf[j]) || (-1 == buf[j]))
        {
            for (i = 0; i < size; ++i)
            {
                printf("count_arr[i] is: %d and i is: %lu\n", count_arr[i], i);
            }

            return (1);
        }
    }

    return (0);
}

static int Compare(const void *data1, const void *data2)
{
    return (*(int *)data1 - *(int *)data2);
}

static int FindMax()
{
    size_t j = 0;
    int max = buf[0];

    for (j = 1; j < Q_SIZE; ++j)
    {
        max = buf[j] > max ? buf[j] : max;
    }

    return (max);
}