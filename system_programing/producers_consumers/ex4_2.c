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
    CIRCULAR_QUEUE_CREATE_FAILDE
} return_val_t;

typedef struct que
{
    size_t write; /* index to write to */
    size_t read;  /* index to read from */
    int queue[Q_SIZE];

} cq_t;

typedef struct pc_fsq
{
    cq_t *que;
    pthread_mutex_t *lock_r;
    pthread_mutex_t *lock_w;
} pc_fsq_t;

static cq_t *CQueueCreate();
static void CQueueDestroy(cq_t *que);

static void *Producers(void *mutex_fsq);
static void *Consumers(void *mutex_fsq);

static int CreatThreads(pthread_t arr_threads[], pc_fsq_t *struct_fsq);
static return_val_t Manager();
static void MutexDestroy(pc_fsq_t *mutex_fsq);

static void Test();
static int Compare(const void *data1, const void *data2);
static int IsBufferCoreect();

int buf[Q_SIZE] = {0};

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
    pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
    pc_fsq_t pc_fsq = {0};

    pc_fsq.lock_r = &mutex1;
    pc_fsq.lock_w = &mutex2;

    pc_fsq.que = CQueueCreate();
    if (!pc_fsq.que)
    {
        return (CIRCULAR_QUEUE_CREATE_FAILDE);
    }

    if (CreatThreads(arr_threads, &pc_fsq))
    {
        return (THREAD_CREATE_FAILDE);
    }

    MutexDestroy(&pc_fsq);
    CQueueDestroy(pc_fsq.que);

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

    pthread_mutex_destroy((pc_fsq->lock_r));
    pthread_mutex_destroy((pc_fsq->lock_w));

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
        pthread_mutex_lock(fsq->lock_w);
        if (Q_SIZE == fsq->que->write - fsq->que->read)
        {
            pthread_mutex_unlock(fsq->lock_w);
            sched_yield();
        }
        else
        {
             __sync_fetch_and_and(fsq->que->queue + (fsq->que->write % (Q_SIZE)), 0);
             __sync_fetch_and_add(fsq->que->queue + (fsq->que->write % (Q_SIZE)), insert);
             __sync_fetch_and_add(&fsq->que->write, 1);

            __sync_fetch_and_add(&insert, 1);
            pthread_mutex_unlock(fsq->lock_w);
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

        pthread_mutex_lock(fsq->lock_r);

        if (0 == fsq->que->write - fsq->que->read)
        {
            pthread_mutex_unlock(fsq->lock_r);
            sched_yield();
        }
        else
        {

            buf[j] = fsq->que->queue[fsq->que->read % (Q_SIZE)];
            __sync_fetch_and_add(fsq->que->queue + (fsq->que->read % (Q_SIZE)), 0);

            __sync_fetch_and_add(&(fsq->que->read), 1);

            ++j;
            pthread_mutex_unlock(fsq->lock_r);
        }
        /*-------------------critical section---------------------*/
    }

    return (NULL);
}

/*--------------------------Circular Queue impl------------------------------*/

static cq_t *CQueueCreate()
{
    cq_t *que = (cq_t *)malloc(sizeof(cq_t));

    if (NULL == que)
    {
        return NULL;
    }

    que->read = 0;
    que->write = 0;

    return que;
}

static void CQueueDestroy(cq_t *que)
{
    assert(NULL != que);

    que->write = 0xFFFFFFFFFFFFFFFF;
    que->read = 0xFFFFFFFFFFFFFFFF;

    free(que);

    return;
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
