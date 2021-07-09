
/*  Developer: Shelly Shlomi;									*
 *  Status:in development;                                      *
 *  Date Of Creation:08.07.21;									*
 *  Date Of Approval:00.07.21;									*
 *  Approved By:  ;                                             *	 
 *  Description: threads_100k_1                                 */

#include <stdio.h> /* printf */
#include <pthread.h> /* thread */
#include <unistd.h> /* sleep */

#define SIZE (100000)

int arr[SIZE] = {0};

pthread_t arr_threads[SIZE] = {0};

/*------------------------------ exercise func --------------------------------*/
static int CreatThreads();
static void *ThredsRoutine(void *index);

/*------------------------------ implementetion --------------------------------*/

int main()
{
    CreatThreads();

    return (0);
}

static int CreatThreads()
{
    size_t i = 0;

    for (i = 0; i < SIZE; i++)
    {
        pthread_create(arr_threads + i, NULL, ThredsRoutine, (void *)(i));
        
    }

    sleep(10);

    for (i = 0; i < SIZE && i == (size_t)arr[i]; i++)
    {
        ;
    }
    if (i != (size_t)arr[i] && arr[i] < SIZE)
    {
        printf("not the same at index : %lu\n", i);
    }

    return (0);
}

static void *ThredsRoutine(void *index)
{
    arr[((size_t)index)] = (size_t)index;

    return (NULL);
}

