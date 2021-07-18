/*  Developer: Shelly Shlomi;									*
 *  Status:;                                                    *
 *  Date Of Creation:14.07.21;									*
 *  Date Of Approval:00.07.21;									*
 *  Approved By:  ;                                             *	 
 *  Description: Producers Consumers problem multiple Consumers *
 *               and Producers 1 mutex 2 semaphores -FSQ        *
 *                                                              */

#include <stdio.h>     /*           printf             */
#include <pthread.h>   /*           thread             */
#include <semaphore.h> /*          semaphore           */
#include <fcntl.h>     /*      For O_* constants       */
#include <stdatomic.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define THREADS_SIZE (10)
#define Q_SIZE (100)

typedef enum return_val
{
    THREAD_CREATE_FAILDE = 1,
    CIRCULAR_QUEUE_CREATE_FAILDE,
    SEM_CREATE_FAILDE
} return_val_t;

static void *Producers(void *mutex_fsq);
static void *Consumers(void *mutex_fsq);

static int CreatThreads(pthread_t arr_threads[], pc_fsq_t *struct_fsq);
static return_val_t Manager();
static void MutexDestroy(pc_fsq_t *mutex_fsq);

static void Test();
static int Compare(const void *data1, const void *data2);
static int IsBufferCoreect();

pthread_mutex_t *lock = NULL;
pthread_cond_t *cond = NULL;
sem_t *sem = NULL;

atomic_int queue[Q_SIZE];
atomic_size_t write = 0; /* index to write to */
atomic_size_t read = 0;  /* index to read from */

int buf[Q_SIZE];

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

    Test();
    return (0);
}

static return_val_t Manager()
{
    size_t i = 0;
    pthread_t arr_threads[THREADS_SIZE] = {0};
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    lock = &mutex;

    for (i = 0; i < Q_SIZE; ++i)
    {
        printf("%d ", buf[i]);
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

    for (i = 0; i < Q_SIZE; ++i)
    {
        printf("%d ", buf[i]);
    }
    printf("\n");

    return (0);
}

static void MutexDestroy(pc_fsq_t *pc_fsq)
{
    assert(pc_fsq);

    pthread_mutex_destroy((lock));

    return;
}

static int CreatThreads(pthread_t arr_threads[], pc_fsq_t *pc_fsq)
{
    size_t k = 0;

    assert(arr_threads);
    assert(pc_fsq);

    for (k = 0; k < THREADS_SIZE / 2; ++k)
    {
        if (pthread_create(arr_threads + k, NULL, Producers, (void *)(pc_fsq)))
        {
            return (1);
        }
    }

    for (k = THREADS_SIZE / 2; k < THREADS_SIZE; ++k)
    {
        if (pthread_create(arr_threads + k, NULL, Consumers, (void *)(pc_fsq)))
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

static void *Producers(void *pc_fsq)
{
    int insert = 0;
    pc_fsq_t *fsq = (pc_fsq_t *)pc_fsq;

    while (insert < Q_SIZE)
    {
        /*-------------------critical section---------------------*/
        pthread_mutex_lock(fsq->lock);
        if (Q_SIZE == fsq->que->write - fsq->que->read)
        {
            pthread_mutex_unlock(fsq->lock);
            sched_yield();
        }
        else
        {
            __sync_fetch_and_and(fsq->que->queue + (fsq->que->write % (Q_SIZE)), 0);
            atomic_fetch_add(fsq->que->queue + (fsq->que->write % (Q_SIZE)), insert);
            atomic_fetch_add(&fsq->que->write, 1);

            __sync_fetch_and_add(&insert, 1);
            pthread_mutex_unlock(fsq->lock);
        }
        /*-------------------critical section---------------------*/
    }

    return (NULL);
}

static void *Consumers(void *pc_fsq)
{
    size_t j = 0;
    pc_fsq_t *fsq = (pc_fsq_t *)pc_fsq;

    while (j < Q_SIZE)
    {

        /*-------------------critical section---------------------*/

        pthread_mutex_lock(fsq->lock);

        if (0 == fsq->que->write - fsq->que->read)
        {
            pthread_mutex_unlock(fsq->lock);
            sched_yield();
        }
        else
        {

            buf[j] = fsq->que->queue[fsq->que->read % (Q_SIZE)];
            __sync_fetch_and_add(fsq->que->queue + (fsq->que->read % (Q_SIZE)), 0);

            __sync_fetch_and_add(&(fsq->que->read), 1);

            ++j;
            pthread_mutex_unlock(fsq->lock);
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
        if (5 < count_arr[j])
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
