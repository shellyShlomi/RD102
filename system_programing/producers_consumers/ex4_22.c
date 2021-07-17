/***************************************************************
* Developer: Ohad Ezra
* Status: Approved
* Reviewer: 
* Group: OL102
* date: 14.07.2021 - 15.07.2021
* description: Implementation ex4_2 producer-consumer with 
               FSQ + read_index + write_index + 2 mutex only
* *****************************************************************/

#include <stdio.h>     /* printf */
#include <stdlib.h>    /* EXIT_FAILURE */
#include <semaphore.h> /* sem_open */
#include <pthread.h>   /* pthread_create */
#include <stdatomic.h> /* __sync_fetch_and_add */
#include <sched.h>     /* sched_yield */
#include <assert.h>    /* assert */
#include <fcntl.h>     /* O_CREAT */

#define SIZE (10)
#define ARR_SIZE (100)
#define BUFF_SIZE (10)
#define THREAD_SIZE (10)

int arr[BUFF_SIZE] = {0};
int test_arr[ARR_SIZE] = {0};
size_t producerCount = 0;
size_t consumerCount = 0;

typedef struct manager
{
    pthread_mutex_t *mutex_p;
    pthread_mutex_t *mutex_c;
    size_t index;

} manage_t;

void *Producer(void *arg);
void *Consumer(void *arg);
int Manager(void);
void TestArr();

int main()
{
    return (Manager());
}

int Manager(void)
{
    pthread_t producer_thr[THREAD_SIZE] = {0};
    pthread_t consumer_thr[THREAD_SIZE] = {0};

    size_t index[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
    size_t i = 0;

    manage_t list[THREAD_SIZE] = {0};

    pthread_mutex_t m_var1 = {0};
    pthread_mutex_t m_var2 = {0};

    if (pthread_mutex_init(&m_var1, NULL) != 0)
    {
        printf("mutex init has failed\n");

        return (EXIT_FAILURE);
    }

    if (pthread_mutex_init(&m_var2, NULL) != 0)
    {
        printf("mutex init has failed\n");

        return (EXIT_FAILURE);
    }

    for (i = 0; i < THREAD_SIZE; ++i)
    {
        list[i].mutex_p = &m_var1;
        list[i].mutex_c = &m_var2;
        list[i].index = index[i];
    }

    for (i = 0; i < THREAD_SIZE; ++i)
    {
        if (0 != pthread_create(producer_thr + i, NULL, Producer, (void *)(list + i)))
        {
            printf("error at line: %d\n", __LINE__);
            return (EXIT_FAILURE);
        }
    }

    for (i = 0; i < THREAD_SIZE; ++i)
    {
        if (0 != pthread_create(consumer_thr + i, NULL, Consumer, (void *)(list + i)))
        {
            printf("error at line: %d\n", __LINE__);
            return (EXIT_FAILURE);
        }
    }

    for (i = 0; i < THREAD_SIZE; ++i)
    {
        pthread_join(producer_thr[i], NULL);
        pthread_join(consumer_thr[i], NULL);
    }

    TestArr();

    if (0 != pthread_mutex_destroy(&m_var1))
    {
        printf("error at line: %d\n", __LINE__);
    }

    if (0 != pthread_mutex_destroy(&m_var2))
    {
        printf("error at line: %d\n", __LINE__);
    }

    return (EXIT_SUCCESS);
}

void *Producer(void *arg)
{
    size_t i = 0;
    manage_t *list = (manage_t *)arg;

    while (i < SIZE)
    {
        pthread_mutex_lock(list->mutex_p);

        if (producerCount - consumerCount == BUFF_SIZE)
        {
            pthread_mutex_unlock(list->mutex_p);
            sched_yield(); /* sharedBuffer is full */
        }

        else
        {

            __sync_fetch_and_add((arr + (producerCount % BUFF_SIZE)), i);
            __sync_fetch_and_add((&producerCount), 1);
            ++i;
            pthread_mutex_unlock(list->mutex_p);
        }

    }

    return (NULL);
}

void *Consumer(void *arg)
{
    size_t i = 0;
    manage_t *list = (manage_t *)arg;
    int temp = 0;

    while (i < SIZE)
    {
        pthread_mutex_lock(list->mutex_c);

        if (producerCount - consumerCount == 0)
        {
            pthread_mutex_unlock(list->mutex_c);
            sched_yield(); /* sharedBuffer is empty */
        }

        else
        {
            temp = __sync_fetch_and_and((arr + (consumerCount % BUFF_SIZE)), 0);
            test_arr[list->index] = temp; 
            ++list->index;
            ++i;
            __sync_fetch_and_add((&consumerCount), 1);
            pthread_mutex_unlock(list->mutex_c);
        }
    }

    return (NULL);
}

void TestArr()
{
    size_t i = 0;

    for (i = 0; i < ARR_SIZE; ++i)
    {
        printf("%d ", test_arr[i]);

        if (0 == (i + 1) % 10)
        {
            printf("\n\n");
        }
    }

    printf("\n");

    return;
}