/*  Developer: Shelly Shlomi;									*
 *  Status:Approved;                                            *
 *  Date Of Creation:14.07.21;									*
 *  Date Of Approval:14.07.21;									*
 *  Approved By: anna ;                                         *	 
 *  Description: Producers Consumers problem single Consumers   *
 *               and single Producers no mutex                  */


#include <stdio.h>   /* printf */
#include <pthread.h> /* thread */
#include <stdatomic.h> /* __sync_fetch_and_add */

#define THREADS_SIZE (2)
#define BUFF (10)

static void *Producers();
static void *Consumers();

static void CreatThreads(pthread_t arr_threads[]);
static void Manager();

atomic_int lock = 0;
static int data = 0;
int buf[BUFF];

int main()
{
    Manager();

    return (0);
}

static void Manager()
{
    size_t i = 0;
    pthread_t arr_threads[THREADS_SIZE] = {0};

    CreatThreads(arr_threads);

    pthread_join((arr_threads[0]), NULL);
    pthread_join((arr_threads[1]), NULL);

    for (i = 0; i < BUFF; ++i)
    {
        printf("%d ", buf[i]);
    }
    printf("\n");

    return;
}

static void CreatThreads(pthread_t arr_threads[])
{

    size_t j = 0;

    if (pthread_create(arr_threads, NULL, Producers, (void *)(j)))
    {
        return;
    }
    
    if (pthread_create(arr_threads + 1, NULL, Consumers, (void *)(j)))
    {
        return;
    }

    return;
}

static void *Producers()
{

    while (data < BUFF)
    {
        if (lock == 0)
        {
            __sync_fetch_and_add(&data, 1);
            __sync_fetch_and_add(&lock, 1);
        }
    }

    return (NULL);
}

static void *Consumers()
{
    size_t i = 0;

    while (i < BUFF)
    {
        if (lock == 1)
        {
            __sync_fetch_and_add(buf + i, data);
            __sync_fetch_and_add(&i, 1);
            __sync_fetch_and_sub(&lock, 1);
        }
    }

    return (NULL);
}
