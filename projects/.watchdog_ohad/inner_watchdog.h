#ifndef __OL102_INNER_WATCHDOG_H__
#define __OL102_INNER_WATCHDOG_H__

#define _POSIX_C_SOURCE 199309L
#define _POSIX_SOURCE

#include <semaphore.h> 
#include <stddef.h>

#include "scheduler.h"

#define TIME_TO_SIG "TIME_TO_SIG"
#define TIME_TO_CHECK_SIGS "TIME_TO_CHECK_SIGS"
#define USER_APP_NAME "USER_APP_NAME"
#define USER_ARGV "USER_ARGV"
#define WATCH_DOG_PID "WATCH_DOG_PID"

#define MALLOC_FAILD (2)

typedef struct watchdog
{
    scheduler_t *schedular;
    pid_t send_pid;
    sem_t *sig;
    sem_t *flag;
    char *user_app_name;
    char **argv;
    int is_watchdog;

} watchdog_t;

void *WDRun(void *arg);
void CleanUpWD(void *param);
int InitElements(watchdog_t **item, size_t time_to_sig, size_t time_to_check_sigs);

#endif /* __OL102_INNER_WATCHDOG_H__ */ 