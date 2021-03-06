/*  Developer: Shelly Shlomi;									*
 *  Status:Approved;                                            *
 *  Date Of Creation:14.07.21;									*
 *  Date Of Approval:18.07.21;									*
 *  Approved By:Sagi;                                           * 
 *  Description: Producers Consumers problem multiple Consumers *
 *               and Producers 1 mutex 2 semaphores -FSQ        *
 *                                                              */

#include <stdio.h>     /* printf */
#include <pthread.h>   /* thread */
#include <semaphore.h> /* semaphore */
#include <fcntl.h>     /* For O_* constants */
#include <stdatomic.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define THREADS_SIZE (10)
#define SIZE (100)
#define Q_SIZE (100)

typedef enum return_val
{
    PTHREAD_CREATE_FAILDE,
    CIRCULAR_QUEUE_CREATE_FAILDE
} return_val_t;

typedef struct que
{
    size_t size; /*the num of elem in the queue*/
    size_t read; /*index to read from*/
    int queue[Q_SIZE];

} cq_t;

typedef struct mutex_fsq
{
    cq_t *que;
    pthread_mutex_t *lock;
    sem_t *sem_w;
    sem_t *sem_r;

} mutex_fsq_t;

static void PushNum(cq_t *que, int num);
static int PopNum(cq_t *que);
static cq_t *CQueueCreate();
static void CQueueDestroy(cq_t *que);

static void *Producers(void *mutex_fsq);
static void *Consumers(void *mutex_fsq);

static return_val_t CreatThreads(pthread_t arr_threads[], mutex_fsq_t *struct_fsq);
static return_val_t Manager();

static void Test();
static int Compare(const void *data1, const void *data2);
static int IsBufferCoreect();

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

    Test();
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
        printf("%d ", buf[i]);
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

            return (NULL);
        }

        pthread_mutex_lock(((mutex_fsq_t *)mutex_fsq)->lock);
        PushNum(((mutex_fsq_t *)mutex_fsq)->que, insert);
        ++insert;
        pthread_mutex_unlock(((mutex_fsq_t *)mutex_fsq)->lock);

        if (sem_post(((mutex_fsq_t *)mutex_fsq)->sem_r))
        {
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
            return (NULL);
        }

        pthread_mutex_lock(((mutex_fsq_t *)mutex_fsq)->lock);
        buf[j] = PopNum(((mutex_fsq_t *)mutex_fsq)->que);
        ++j;
        pthread_mutex_unlock(((mutex_fsq_t *)mutex_fsq)->lock);

        if (sem_post(((mutex_fsq_t *)mutex_fsq)->sem_w))
        {
            return (NULL);
        }
    }

    return (NULL);
}

/*------------------------------implementetion--------------------------------*/

static void PushNum(cq_t *que, int num)
{

    assert(que);

    que->queue[(que->read + que->size) % (Q_SIZE)] = num;

    ++que->size;

    return;
}

static int PopNum(cq_t *que)
{
    int num = 0;

    assert(que);

    num = que->queue[que->read];

    que->read = (que->read + 1) % (Q_SIZE);
    --que->size;

    return num;
}

static cq_t *CQueueCreate()
{
    cq_t *que = (cq_t *)malloc(sizeof(cq_t));

    if (NULL == que)
    {
        return NULL;
    }

    que->read = 0;
    que->size = 0;

    return que;
}

static void CQueueDestroy(cq_t *que)
{
    assert(NULL != que);

    que->size = 0xFFFFFFFF;
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
