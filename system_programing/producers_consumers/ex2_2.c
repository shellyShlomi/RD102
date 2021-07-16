/*  Developer: Shelly Shlomi;									*
 *  Status:Approved;                                            *
 *  Date Of Creation:14.07.21;									*
 *  Date Of Approval:14.07.21;									*
 *  Approved By:  ;                                             *	 
 *  Description: Producers Consumers problem multiple Consumers *
 *               and multiple Producers 1 mutex 1 semaphores    */

#include <stdio.h>     /* printf */
#include <pthread.h>   /* thread */
#include <semaphore.h> /* semaphore */
#include <fcntl.h>     /* For O_* constants */
#include <stdatomic.h>

#include "sll.h"

#define THREADS_SIZE (4)
#define SIZE (100)

typedef enum return_val
{
    MUTEX_FAILDE = 1,
    PTHREAD_CREATE_FAILDE,
    LIST_CREATE_FAILDE
} return_val_t;

typedef struct mutex_list
{
    s_list_t *list;
    pthread_mutex_t *lock;
    sem_t *sem;
} mutex_list_t;

static void *Producers(void *list_mutex);
static void *Consumers(void *list_mutex);

static return_val_t CreatThreads(pthread_t arr_threads[], mutex_list_t *struct_ml);
static return_val_t Manager();

size_t buf[SIZE];

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
        case LIST_CREATE_FAILDE:
        {
            printf("list create failde\n");
            break;
        }
        default:
            break;
        }
    }

    return (0);
}

static return_val_t Manager()
{
    size_t i = 0;
    pthread_t arr_threads[THREADS_SIZE] = {0};
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    mutex_list_t mutex_list = {0};

    mutex_list.lock = &mutex;

    mutex_list.sem = sem_open("sem", O_CREAT, 0660, 0);
    if (SEM_FAILED == mutex_list.sem)
    {
        return (1);
    }

    mutex_list.list = SLLCreate();
    if (!mutex_list.list)
    {
        return (LIST_CREATE_FAILDE);
    }

    if (CreatThreads(arr_threads, &mutex_list))
    {
        return (PTHREAD_CREATE_FAILDE);
    }

    pthread_mutex_destroy((mutex_list.lock));
    SLLDestroy(mutex_list.list);
    sem_close(mutex_list.sem);
    sem_unlink("sem");

    for (i = 0; i < SIZE; ++i)
    {
        printf("%d ", buf[i]);
    }
    printf("\n");

    return (0);
}

static return_val_t CreatThreads(pthread_t arr_threads[], mutex_list_t *struct_ml)
{
    size_t k = 0;

    for (k = 0; k < THREADS_SIZE / 2; ++k)
    {
        if (pthread_create(arr_threads + k, NULL, Producers, (void *)(struct_ml)))
        {
            return (1);
        }
    }

    for (k = THREADS_SIZE / 2; k < THREADS_SIZE; ++k)
    {
        if (pthread_create(arr_threads + k, NULL, Consumers, (void *)(struct_ml)))
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

static void *Producers(void *list_mutex)
{
    size_t i = 0;
    s_list_iter_t insert = NULL;

    while (i < SIZE)
    {
        pthread_mutex_lock(((mutex_list_t *)list_mutex)->lock);

        insert = SLLInsert(SLLBegin(((mutex_list_t *)list_mutex)->list), (void *)i);

        if (SLLIsSameIter(insert, SLLEnd(((mutex_list_t *)list_mutex)->list)))
        {
            pthread_mutex_unlock(((mutex_list_t *)list_mutex)->lock);
            return (NULL);
        }

        ++i;
        pthread_mutex_unlock(((mutex_list_t *)list_mutex)->lock);
        
        if (sem_post(((mutex_list_t *)list_mutex)->sem))
        {
            return (NULL);
        }
    }

    return (NULL);
}

static void *Consumers(void *list_mutex)
{
    size_t j = 0;

    while (j < SIZE)
    {

        if (sem_wait(((mutex_list_t *)list_mutex)->sem))
        {
            return (NULL);
        }

        pthread_mutex_lock(((mutex_list_t *)list_mutex)->lock);

        buf[j] = (size_t)SLLGetData(SLLBegin(((mutex_list_t *)list_mutex)->list));
        SLLRemove(SLLBegin(((mutex_list_t *)list_mutex)->list));
        ++j;

        pthread_mutex_unlock(((mutex_list_t *)list_mutex)->lock);
    }

    return (NULL);
}
