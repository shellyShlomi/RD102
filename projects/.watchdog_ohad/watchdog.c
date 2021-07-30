#define _POSIX_C_SOURCE 199309L
#define _POSIX_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <semaphore.h> /* sem_open */
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stddef.h>
#include <pthread.h>
#include <assert.h>
#include <fcntl.h> /* O_CREAT */

#include "watchdog.h"
#include "inner_watchdog.h"

int main(int argc, char *argv[])
{
    size_t time_to_sig = 0;
    size_t time_to_check_sigs = 0;
    watchdog_t *item = NULL;
    
    time_to_sig = atoi(getenv(TIME_TO_SIG));
    time_to_check_sigs = atoi(getenv(TIME_TO_CHECK_SIGS));

    if (EXIT_FAILURE == InitElements(&item, time_to_sig, time_to_check_sigs))
    {
        sem_post(item->flag);
        sem_post(item->sig);

        CleanUpWD(item);
    }

    item->argv = argv;
    item->is_watchdog = 1;
    item->send_pid = getppid();
    item->user_app_name = getenv(USER_APP_NAME);

    printf("watchdog pid: %d  parent pid: %d\n", getpid(), item->send_pid);
    sem_post(item->sig);
    WDRun((void *)item);
 
    return (EXIT_SUCCESS);
}