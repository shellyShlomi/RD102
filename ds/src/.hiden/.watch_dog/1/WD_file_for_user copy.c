
#define _POSIX_C_SOURCE 199309L
#define _POSIX_SOURCE
#include <stdlib.h> /* malloc */
#include <stdio.h>
#include <stddef.h>    /* size_t */
#include <unistd.h>    /* pid_t */
#include <stdatomic.h> /* atomic_size_t */
#include <pthread.h>   /*           thread             */
#include <semaphore.h> /*          semaphore           */
#include <fcntl.h>     /*      For O_* constants       */
#include <assert.h>
#include <string.h>
#include <signal.h> /* struct sigaction  */

#include "watch_dog.h"
#include "watchdog.h"

/*------------- task funcs ------------*/

static int Task(void *param);

sem_t *sem_block = 0;

int main(int argc, char **argv)
{
    pthread_t thread = {0};
    watchdog_t *watchdog_elem = NULL;
    static char *app[1] = {'\0'};
    sem_t *sem_signal = 0;

    app[0] = argv[PATH];

    if (CreatWD(&watchdog_elem))
    {
        sem_post(sem_signal);
    }

/*     watchdog_elem->check_pid_fork = atoi(argv[FORK_PID_TO_CHECK]);
    watchdog_elem->signal_pid = getppid();

    if (UidIsSame(
            SchedulerAdd(watchdog_elem->scheduler,
                         Task,
                         0,
                         watchdog_elem),
            GetBadUid()))
    {
        sem_post(sem_signal);
        return (1);
    }

    printf("%s \n",  argv[2]);
    SchedulerRun(watchdog_elem->scheduler);
 */
    return (0);
}

static int Task(void *param)
{
    sem_post(sem_block);
    return (0);
}
