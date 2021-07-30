/*  Developer: Shelly Shlomi;									*
 *  Status:Approved;                                            *
 *  Date Of Creation:14.07.21;									*
 *  Date Of Approval:18.07.21;									*
 *  Approved By:ohad;                                           *	 
 *  Description: Producers Consumers problem multiple Consumers *
 *               and Producers 1 mutex, 1 semaphore ,           *
 *               1 conditional variable -FSQ                    */

#include <stdio.h>     /*           printf             */
#include <pthread.h>   /*           thread             */
#include <semaphore.h> /*          semaphore           */
#include <fcntl.h>     /*      For O_* constants       */
#include <stdatomic.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <signal.h>

#define THREADS_SIZE (11)
#define Q_SIZE (7)
#define SIZE (700)
#define STRING_SIZE (4)

typedef enum return_val
{
    THREAD_CREATE_FAILDE = 1,
    CIRCULAR_QUEUE_CREATE_FAILDE,
    SEM_CREATE_FAILDE
} return_val_t;

static void *Producers();
static void *Consumers(void *data);

static int CreatThreads(pthread_t arr_threads[]);
static return_val_t Manager();
static void MutexDestroy();

pthread_mutex_t *lock = NULL;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
sem_t *sem = NULL;
size_t count = 0;

char queue[Q_SIZE];
size_t write = 0; /* index to write to */
size_t read = 0;  /* index to read from */

char buf[SIZE];

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
        case SEM_CREATE_FAILDE:
        {
            printf("semophore create failde\n");
            break;
        }

        default:
        {
            break;
        }
        }
    }

    return (0);
}

static return_val_t Manager()
{
    pthread_t arr_threads[THREADS_SIZE] = {0};
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    size_t k = 0;
    lock = &mutex;

    for (k = 0; k < SIZE; ++k)
    {
        printf("%c", buf[k]);
    }    
    printf("\n");

    sem = sem_open("sem", O_CREAT, 0660, 0);
    if (SEM_FAILED == sem)
    {
        return (SEM_CREATE_FAILDE);
    }

    if (CreatThreads(arr_threads))
    {
        return (THREAD_CREATE_FAILDE);
    }

    MutexDestroy();
    sem_close(sem);
    sem_unlink("sem");
    pthread_cond_destroy(&cond);

    for (k = 0; k < SIZE; ++k)
    {
        printf("%c", buf[k]);
    }
    printf("\n");

    return (0);
}

static void MutexDestroy()
{
    pthread_mutex_destroy(lock);

    return;
}

static int CreatThreads(pthread_t arr_threads[])
{
    size_t k = 0;

    assert(arr_threads);

    if (pthread_create(arr_threads + k, NULL, Producers, NULL))
    {
        return (1);
    }

    for (k = 1; k < THREADS_SIZE; ++k)
    {
        if (pthread_create(arr_threads + k, NULL, Consumers, 
                                        (void *)(k * STRING_SIZE * Q_SIZE)))
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
    size_t i = 0;
    size_t j = 0;
    char *strs[] = {"shelly ", "shlomi ", "IvyIvy ", "RonRon "};

    while (j < STRING_SIZE)
    {
        /*-------------------critical section---------------------*/
        pthread_mutex_lock(lock);

        memcpy(queue, strs[j], Q_SIZE);

        for (i = 0; i < THREADS_SIZE - 1; i++)
        {
            sem_post(sem);
        }

        pthread_cond_wait(&cond, lock);
        pthread_mutex_unlock(lock);

        ++j;
        /*-------------------critical section---------------------*/
    }

    return (NULL);
}

static void *Consumers(void *data)
{
    size_t j = 0;

    while (j < STRING_SIZE)
    {

        sem_wait(sem);

        /*-------------------critical section---------------------*/
        pthread_mutex_lock(lock);

        memcpy(buf + (size_t)data + (j * Q_SIZE), queue, Q_SIZE);
        ++count;

        if (THREADS_SIZE - 1 == count)
        {
            count = 0;
            pthread_cond_broadcast(&cond);
        }
        else
        {
            pthread_cond_wait(&cond, lock);
        }
        pthread_mutex_unlock(lock);
        ++j;
        /*-------------------critical section---------------------*/
    }

    return (NULL);
}
/*---------------------------------Test funcs---------------------------------*/

/* 
static void Test()
{
    size_t i = 0;
    int copy[Q_SIZE] = {0};

    memcpy(copy, buf, Q_SIZE);

    qsort(copy, Q_SIZE, sizeof(int), Compare);

    if (IsBufferCoreect(copy))
    {
        for (i = 0; i < Q_SIZE; ++i)
        {
            printf("sorted buf[i] is: %d \n", copy[i]);
        }
    }

    return;
}

static int IsBufferCoreect()
{
    size_t i = 0;
    size_t j = 0;
    size_t count_arr[Q_SIZE] = {0};

    for (i = 0; i < Q_SIZE; ++i)
    {
        ++(count_arr[buf[i]]);
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
 */