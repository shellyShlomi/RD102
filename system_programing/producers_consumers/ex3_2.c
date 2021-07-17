/*  Developer: Shelly Shlomi;                                   *
 *  Status:;                                                    *
 *  Date Of Creation:14.07.21;                                  *
 *  Date Of Approval:14.07.21;                                  *
 *  Approved By:;                                               *	 
 *  Description:                                                *    
 *          Producers Consumers problem multiple                *
 *          Consumers and Producers 1 mutex 2 semaphores -FSQ   *
 *                                                              */

#include <stdio.h>     /*           printf             */
#include <pthread.h>   /*           thread             */
#include <semaphore.h> /*          semaphore           */
#include <fcntl.h>     /*      For O_* constants       */
#include <string.h>    /*          memcpy              */
#include <stdatomic.h>
#include <stdlib.h>
#include <assert.h>

#define THREADS_SIZE (4)
#define Q_SIZE (100)

typedef enum return_val
{
    SEM_CREATE_FAILDE = 1,
    THREAD_CREATE_FAILDE,
    CIRCULAR_QUEUE_CREATE_FAILDE
} return_val_t;

typedef struct que
{
    atomic_int write; /* index to write to */
    atomic_int read;  /*index to read from*/
    atomic_int queue[Q_SIZE];

} cq_t;

typedef struct mutex_fsq
{
    size_t i;
    cq_t *que;
    pthread_mutex_t *lock_r;
    pthread_mutex_t *lock_w;
    sem_t *sem_w;
    sem_t *sem_r;

} mutex_fsq_t;


static cq_t *CQueueCreate();
static void CQueueDestroy(cq_t *que);

static void *Producers(void *mutex_fsq);
static void *Consumers(void *mutex_fsq);

static int CreatThreads(pthread_t arr_threads[], mutex_fsq_t *struct_fsq);
static return_val_t Manager();
static void MutexDestroy(mutex_fsq_t *mutex_fsq);
static return_val_t SemCreated(mutex_fsq_t *mutex_fsq);
static void SemDestroy(mutex_fsq_t *mutex_fsq);

static void Test();
static int Compare(const void *data1, const void *data2);
static int IsBufferCoreect();

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
            printf("pthread create failde\n");
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
    mutex_fsq_t mutex_fsq = {0};
    mutex_fsq.i = 0;

    mutex_fsq.lock_r = &mutex1;
    mutex_fsq.lock_w = &mutex2;

    if (SEM_CREATE_FAILDE == SemCreated(&mutex_fsq))
    {
        return (SEM_CREATE_FAILDE);
    }

    mutex_fsq.que = CQueueCreate();
    if (!mutex_fsq.que)
    {
        return (CIRCULAR_QUEUE_CREATE_FAILDE);
    }

    if (CreatThreads(arr_threads, &mutex_fsq))
    {
        return (THREAD_CREATE_FAILDE);
    }

    MutexDestroy(&mutex_fsq);
    CQueueDestroy(mutex_fsq.que);
    SemDestroy(&mutex_fsq);

    for (i = 0; i < Q_SIZE; ++i)
    {
        printf("%d ", buf[i]);
    }
    printf("\n");

    return (0);
}

static void MutexDestroy(mutex_fsq_t *mutex_fsq)
{
    assert(mutex_fsq);
    pthread_mutex_destroy((mutex_fsq->lock_r));
    pthread_mutex_destroy((mutex_fsq->lock_w));

    return;
}
static return_val_t SemCreated(mutex_fsq_t *mutex_fsq)
{
    assert(mutex_fsq);

    mutex_fsq->sem_r = sem_open("sem_r", O_CREAT, 0660, 0);
    if (SEM_FAILED == mutex_fsq->sem_r)
    {
        return (SEM_CREATE_FAILDE);
    }

    mutex_fsq->sem_w = sem_open("sem_w", O_CREAT, 0660, Q_SIZE);
    if (SEM_FAILED == mutex_fsq->sem_w)
    {
        return (SEM_CREATE_FAILDE);
    }

    return (0);
}
static void SemDestroy(mutex_fsq_t *mutex_fsq)
{
    assert(mutex_fsq);

    sem_close(mutex_fsq->sem_w);
    sem_close(mutex_fsq->sem_r);
    sem_unlink("sem_r");
    sem_unlink("sem_w");

    return;
}

static int CreatThreads(pthread_t arr_threads[], mutex_fsq_t *struct_fsq)
{
    size_t k = 0;

    assert(arr_threads);
    assert(struct_fsq);

    for (k = 0; k < THREADS_SIZE / 2; ++k)
    {
        if (pthread_create(arr_threads + k, NULL, Producers, (void *)(struct_fsq)))
        {
            return (1);
        }
    }

    if (pthread_create(arr_threads + k, NULL, Consumers, (void *)(struct_fsq)))
    {
        return (1);
    }

    ++k;
    struct_fsq->i = Q_SIZE / 2;
    if (pthread_create(arr_threads + k, NULL, Consumers, (void *)(struct_fsq)))
    {
        return (1);
    }

    for (k = 0; k < THREADS_SIZE; ++k)
    {
        pthread_join(arr_threads[k], NULL);
    }

    return (0);
}

static void *Producers(void *mutex_fsq)
{
    int insert = 0;
    mutex_fsq_t *fsq = (mutex_fsq_t *)mutex_fsq;

    while (insert < Q_SIZE)
    {
        if (sem_wait(fsq->sem_w))
        {
            return (NULL);
        }

        /*-------------------critical section---------------------*/
        pthread_mutex_lock(fsq->lock_r);

        __atomic_store_n(fsq->que->queue + (fsq->que->write), insert, __ATOMIC_SEQ_CST);

        fsq->que->write = (fsq->que->write + 1) % (Q_SIZE);
        ++insert;
        pthread_mutex_unlock(fsq->lock_r);
        /*-------------------critical section---------------------*/

        if (sem_post(fsq->sem_r))
        {
            return (NULL);
        }
    }

    return (NULL);
}

static void *Consumers(void *mutex_fsq)
{
    size_t j = 0;
    mutex_fsq_t *fsq = (mutex_fsq_t *)mutex_fsq;

    while (j < Q_SIZE)
    {

        if (0 != sem_wait(fsq->sem_r))
        {
            return (NULL);
        }

        /*-------------------critical section---------------------*/
        pthread_mutex_lock(fsq->lock_w);

        __atomic_store_n((buf + j), fsq->que->queue[fsq->que->read], __ATOMIC_SEQ_CST);
        __atomic_store_n(fsq->que->queue + fsq->que->read, 0, __ATOMIC_SEQ_CST);

        fsq->que->read = (fsq->que->read + 1) % (Q_SIZE);
        ++j;
        pthread_mutex_unlock(fsq->lock_w);
        /*-------------------critical section---------------------*/

        if (sem_post(fsq->sem_w))
        {
            return (NULL);
        }
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

    que->write = 0xFFFFFFFF;
    que->read = 0xFFFFFFFF;

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
        if (2 < count_arr[j])
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
