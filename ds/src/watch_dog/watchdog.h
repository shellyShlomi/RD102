#ifndef __OL102_WATCHDOG_H__
#define __OL102_WATCHDOG_H__

#include <stddef.h>    /* size_t */
#include <unistd.h>    /* pid_t */
#include <stdatomic.h> /* atomic_size_t */

#include "scheduler.h"
#include "uid.h"

typedef enum arr_elemnets
{
    PATH,
    FORK_PID_TO_CHECK,
    SIGNAL_PID,
    CHECK_RATIO,
    BEATS_INTERVAL,
    NULL_ELEM,
    SIZE_OF_ARGV
} arr_elemnets_t;

typedef struct watchdog
{
    scheduler_t *scheduler;
    /* char **cmlarg; */
    size_t counter;
    pid_t check_pid_fork;
    pid_t signal_pid;
    int flag;
} watchdog_t;

int InitAll(watchdog_t **watchdog_elem, pid_t check_pid_fork, pid_t signal_pid, 
            int check_ratio, int beats_interval, sem_t **sem_signal, sem_t **sem_block);


#endif /* __OL102_WATCHDOG_H__ */ 