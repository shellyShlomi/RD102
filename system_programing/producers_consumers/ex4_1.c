/*  Developer: Shelly Shlomi;									*
 *  Status:Approved;                                            *
 *  Date Of Creation:14.07.21;									*
 *  Date Of Approval:18.07.21;									*
 *  Approved By:Sagi;                                           * 
 *  Description: Producers Consumers problem multiple Consumers *
 *               and Producers 1 mutex, and 2 atomic counters   *
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

typedef enum return_val
{
    THREAD_CREATE_FAILDE = 1,
    CIRCULAR_QUEUE_CREATE_FAILDE
} return_val_t;

static void *Producers();
static void *Consumers();

static int CreatThreads(pthread_t arr_threads[]);
static return_val_t Manager();
static void MutexDestroy();

static void Test();
static int Compare(const void *data1, const void *data2);
static int IsBufferCoreect();

pthread_mutex_t *lock = NULL;
int test_buf[Q_SIZE];
sig_atomic_t write = 0; /* index to write to */
sig_atomic_t read = 0;  /* index to read from */
int queue[Q_SIZE];

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
    size_t i = 0;
    pthread_t arr_threads[THREADS_SIZE] = {0};
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    lock = &mutex;

    if (CreatThreads(arr_threads))
    {
        return (THREAD_CREATE_FAILDE);
    }

    MutexDestroy();

    for (i = 0; i < Q_SIZE; ++i)
    {
        printf("%d ", test_buf[i]);
    }
    printf("\n");

    return (0);
}

static void MutexDestroy()
{
    pthread_mutex_destroy((lock));

    return;
}

static int CreatThreads(pthread_t arr_threads[])
{
    size_t k = 0;

    assert(arr_threads);

    for (k = 0; k < THREADS_SIZE / 2; ++k)
    {
        if (pthread_create(arr_threads + k, NULL, Producers, NULL))
        {
            return (1);
        }
    }

    for (k = THREADS_SIZE / 2; k < THREADS_SIZE; ++k)
    {
        if (pthread_create(arr_threads + k, NULL, Consumers, NULL))
        {
            return (1);
        }
    }

    for (k = 0; k < THREADS_SIZE; ++k)
    {
        pthread_join(arr_threads[k], NULL);
    }

    return (0);
}

static void *Producers()
{
    int insert = 0;

    while (insert < Q_SIZE)
    {
        /*-------------------critical section---------------------*/
        pthread_mutex_lock(lock);
        if (Q_SIZE == write - read)
        {
            pthread_mutex_unlock(lock);
            sched_yield();
        }
        else
        {
            queue[write % (Q_SIZE)] = insert;

            ++write;
            ++insert;
            
            pthread_mutex_unlock(lock);
        }
        /*-------------------critical section---------------------*/
    }

    return (NULL);
}

static void *Consumers()
{
    size_t j = 0;

    while (j < Q_SIZE)
    {

        /*-------------------critical section---------------------*/
        pthread_mutex_lock(lock);

        if (0 == read - write)
        {
            pthread_mutex_unlock(lock);
            sched_yield();
        }
        else
        {
            test_buf[j] = queue[read % Q_SIZE];

            queue[read % Q_SIZE] = 0;
            ++read;

            ++j;
            pthread_mutex_unlock(lock);
        }

        /*-------------------critical section---------------------*/
    }

    return (NULL);
}


/*---------------------------------Test funcs---------------------------------*/

static void Test()
{
    size_t i = 0;
    int copy[Q_SIZE] = {0};

    memcpy(copy, test_buf, Q_SIZE);

    qsort(copy, Q_SIZE, sizeof(int), Compare);

    if (IsBufferCoreect(copy))
    {
        for (i = 0; i < Q_SIZE; ++i)
        {
            printf("sorted test_buf[i] is: %d \n", copy[i]);
        }
    }
}

static int IsBufferCoreect()
{
    size_t i = 0;
    size_t j = 0;
    size_t count_arr[Q_SIZE] = {0};

    for (i = 0; i < Q_SIZE; ++i)
    {
        ++(count_arr[test_buf[i]]);
    }

    for (j = 0; j < Q_SIZE; ++j)
    {
        if (50 < count_arr[j])
        {
            for (i = 0; i < Q_SIZE; ++i)
            {
                printf("count_arr[i] is: %lu and i is: %lu\n", count_arr[i], i);
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
