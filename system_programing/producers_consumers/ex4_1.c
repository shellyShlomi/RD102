/*  Developer: Shelly Shlomi;									*
 *  Status:;                                                    *
 *  Date Of Creation:14.07.21;									*
 *  Date Of Approval:00.07.21;									*
 *  Approved By:  ;                                             *	 
 *  Description: Producers Consumers problem multiple Consumers *
 *               and Producers 1 mutex 2 semaphores -FSQ        *
 *                                                              */

#include <stdio.h>      /*           printf             */
#include <pthread.h>    /*           thread             */
#include <semaphore.h>  /*          semaphore           */
#include <fcntl.h>      /*      For O_* constants       */
#include <stdatomic.h>
#include <stdlib.h>
#include <assert.h>

#define THREADS_SIZE (4)
#define SIZE (100)
#define Q_SIZE (100)

typedef enum return_val
{
    PTHREAD_CREATE_FAILDE,
    CIRCULAR_QUEUE_CREATE_FAILDE
} return_val_t;

typedef struct que
{
    atomic_int write; /*the num of elem in the queue*/
    atomic_int read; /*index to read from*/
    atomic_int queue[Q_SIZE];

} cq_t;

typedef struct mutex_fsq
{
    cq_t *que;
    pthread_mutex_t *lock;
    sem_t *sem_w;
    sem_t *sem_r;

} mutex_fsq_t;

static int CQueueIsEmpty(const cq_t *que);
static size_t CQueueSize(const cq_t *que);
static void PushNum(cq_t *que, int num);
static int PopNum(cq_t *que);
static int PeekNum(cq_t *que);
static cq_t *CQueueCreate();
static void CQueueDestroy(cq_t *que);

static void *Producers(void *mutex_fsq);
static void *Consumers(void *mutex_fsq);

static return_val_t CreatThreads(pthread_t arr_threads[], mutex_fsq_t *struct_fsq);
static return_val_t Manager();

int buf[SIZE];

int main()
{
    int status = Manager();

    if (status)
    {
        switch (status)
        {

        case PTHREAD_CREATE_FAILDE:
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

    return (0);
}

static return_val_t Manager()
{
    size_t i = 0;
    pthread_t arr_threads[THREADS_SIZE] = {0};
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    mutex_fsq_t mutex_fsq = {0};

    mutex_fsq.lock = &mutex;

    mutex_fsq.sem_r = sem_open("sem_r", O_CREAT, 0660, 0);
    if (SEM_FAILED == mutex_fsq.sem_r)
    {
        return (1);
    }

    mutex_fsq.sem_w = sem_open("sem_w", O_CREAT, 0660, Q_SIZE);
    if (SEM_FAILED == mutex_fsq.sem_w)
    {
        return (1);
    }

    mutex_fsq.que = CQueueCreate();
    if (!mutex_fsq.que)
    {
        return (CIRCULAR_QUEUE_CREATE_FAILDE);
    }

    if (CreatThreads(arr_threads, &mutex_fsq))
    {
        return (PTHREAD_CREATE_FAILDE);
    }

    pthread_mutex_destroy((mutex_fsq.lock));
    CQueueDestroy(mutex_fsq.que);
    sem_close(mutex_fsq.sem_w);
    sem_close(mutex_fsq.sem_r);
    sem_unlink("sem_r");
    sem_unlink("sem_w");

    for (i = 0; i < SIZE; ++i)
    {
        printf("%u ", buf[i]);
    }
    printf("\n");

    return (0);
}

static return_val_t CreatThreads(pthread_t arr_threads[], mutex_fsq_t *struct_fsq)
{
    size_t k = 0;

    for (k = 0; k < THREADS_SIZE / 2; ++k)
    {
        if (pthread_create(arr_threads + k, NULL, Producers, (void *)(struct_fsq)))
        {
            return (1);
        }
    }

    for (k = THREADS_SIZE / 2; k < THREADS_SIZE; ++k)
    {
        if (pthread_create(arr_threads + k, NULL, Consumers, (void *)(struct_fsq)))
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

static void *Producers(void *mutex_fsq)
{
    int insert = 0;

    while (insert < Q_SIZE)
    {

        if (sem_wait(((mutex_fsq_t *)mutex_fsq)->sem_w))
        {
            pthread_mutex_unlock(((mutex_fsq_t *)mutex_fsq)->lock);

            return (NULL);
        }

        pthread_mutex_lock(((mutex_fsq_t *)mutex_fsq)->lock);
        PushNum(((mutex_fsq_t *)mutex_fsq)->que, insert);
        ++insert;
        pthread_mutex_unlock(((mutex_fsq_t *)mutex_fsq)->lock);

        if (sem_post(((mutex_fsq_t *)mutex_fsq)->sem_r))
        {
            pthread_mutex_unlock(((mutex_fsq_t *)mutex_fsq)->lock);

            return (NULL);
        }
    }

    return (NULL);
}

static void *Consumers(void *mutex_fsq)
{
    size_t j = 0;

    while (j < SIZE)
    {
        if (sem_wait(((mutex_fsq_t *)mutex_fsq)->sem_r))
        {
            pthread_mutex_unlock(((mutex_fsq_t *)mutex_fsq)->lock);

            return (NULL);
        }

        pthread_mutex_lock(((mutex_fsq_t *)mutex_fsq)->lock);
        buf[j] = PopNum(((mutex_fsq_t *)mutex_fsq)->que);
        ++j;
        pthread_mutex_unlock(((mutex_fsq_t *)mutex_fsq)->lock);

        if (sem_post(((mutex_fsq_t *)mutex_fsq)->sem_w))
        {
            pthread_mutex_unlock(((mutex_fsq_t *)mutex_fsq)->lock);

            return (NULL);
        }
    }

    return (NULL);
}

/*------------------------------implementetion--------------------------------*/

static void PushNum(cq_t *que, int num)
{

    assert(que);

    que->queue[que->write] = num;
    que->write = (que->write + 1) % (Q_SIZE);

    return;
}

static int PopNum(cq_t *que)
{
    int num = 0;

    assert(que);
    assert(que->read + que->write > 0);

    num = que->queue[que->read];

    que->read = (que->read + 1) % (Q_SIZE);

    return num;
}

static int PeekNum(cq_t *que)
{
    assert(que);

    return que->queue[que->read];
}
/* 
static size_t CQueueSize(const cq_t *que)
{
    assert(NULL != que);

    return (que->size);
}

static int CQueueIsEmpty(const cq_t *que)
{
    assert(NULL != que);

    return (0 == que->size);
}
 */
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
