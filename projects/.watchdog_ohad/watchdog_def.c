/***************************************************************
* Developer: Ohad Ezra
* Status: 
* Reviewer: Shelly
* Group: OL102
* date: 21.7.21 - 26.7.21
* description: Implementation of watchdog project that protect user's application
*              if it falls between StartWD to StopWD function 
******************************************************************/

#define _POSIX_C_SOURCE 199309L
#define _POSIX_SOURCE

#ifndef NDEBUG
#define DEBUG_PRINT(x) \
    do                 \
    {                  \
        printf x;      \
    } while (0)
#else
#define DEBUG_PRINT(x) \
    do                 \
    {                  \
    } while (0)        
#endif

#include <stdio.h>     /* printf */
#include <unistd.h>    /* fork */
#include <semaphore.h> /* sem_open */
#include <sys/types.h> /* fork */
#include <signal.h>    /* SIGUSR1 */
#include <sys/wait.h>  /* waitpid */
#include <stdlib.h>    /* malloc */
#include <pthread.h>   /* sem_wait */
#include <assert.h>    /* assert */
#include <fcntl.h>     /* O_CREAT */
#include <stdatomic.h> /* atomic_exchange */

#include "watchdog.h"
#include "inner_watchdog.h"
#include "scheduler.h"
#include "uid.h"

#define UNUSED(X) ((void)X)

sem_t *sig = NULL;
sem_t *flag = NULL;
pthread_t user_thread = 0;
static atomic_int to_stop = 0;
static atomic_size_t counter = 0;

static void InitUserWDElements(watchdog_t *item, char **argv, pid_t c_pid);
static int SetTask(watchdog_t *item, size_t time_to_sig, size_t time_to_check_sigs);
static int SetEnvVars(char **argv, size_t time_to_sig, size_t time_to_check_sigs);
static int SetSigHandlers(void);
static int InitSemaphors(void);

/* handlers functions */
static void UpdateToStop(int signum, siginfo_t *pinfo, void *data);
static void IncrementCounter(int signum, siginfo_t *pinfo, void *data);

/* Counter increment */
static int Task1(void *param);

/* check counter if greater from zero it will reset the counter
 * if zero (user app or watchdog dead) it will revive the terminate process  
 */
static int Task2(void *param);

/* stop the schedular if to_stop is set to one */
static int Task3(void *param);

/* block signals functiom */
static void SigMaskBlock(void);
static void SigMaskWD(int how);

/**********************************api function********************************/

int StartWD(char **argv, size_t time_to_sig, size_t time_to_check_sigs)
{
    watchdog_t *item = NULL;
    char arg[BUFSIZ] = {'\0'};
    pid_t c_pid = 0;
    int status = 0;

    assert(argv);
    assert(0 < time_to_sig);
    assert(0 < time_to_check_sigs);

    if (SetEnvVars(argv, time_to_sig, time_to_check_sigs))
    {
        return (EXIT_FAILURE);
    }

    if (EXIT_FAILURE == InitElements(&item, time_to_sig, time_to_check_sigs))
    {
        DEBUG_PRINT(("InitElements function failed:\n"));
        free(item);
        return (EXIT_FAILURE);
    }

    c_pid = fork();

    if (c_pid < 0)
    {
        DEBUG_PRINT(("fork function failed:\n"));
        free(item);
        return (EXIT_FAILURE);
    }

    if (0 == c_pid)
    {
        if (-1 == execv("watchdog", argv))
        {
            DEBUG_PRINT(("exec failed:\n"));
            return (EXIT_FAILURE);
        }
    }

    sem_wait(sig);
    sem_getvalue(flag, &status);

    if (status)
    {
        DEBUG_PRINT(("failed to init watch dog:\n"));
        free(item);

        return (EXIT_FAILURE);
    }

    else
    {
        sprintf(arg, "%lu", c_pid);
        setenv(WATCH_DOG_PID, arg, 1);
        InitUserWDElements(item, argv, c_pid);
        if (0 != pthread_create(&user_thread, NULL, WDRun, item))
        {
            CleanUpWD(item);
            return (EXIT_FAILURE);
        }
    }

    SigMaskWD(SIG_BLOCK);  /*move to affect only the thread!*/

    return (EXIT_SUCCESS);
}

void StopWD()
{
    int watchdog_pid = atoi(getenv(WATCH_DOG_PID));
    atomic_exchange(&to_stop, 1);
    kill(watchdog_pid, SIGUSR2);
    waitpid(watchdog_pid, NULL, 0);
    pthread_join(user_thread, NULL);

    return;
}

static void InitUserWDElements(watchdog_t *item, char **argv, pid_t c_pid)
{
    assert(item);

    item->is_watchdog = 0;
    item->argv = argv;
    item->send_pid = c_pid;

    return;
}

static int SetEnvVars(char **argv, size_t time_to_sig, size_t time_to_check_sigs)
{
    char arg1[BUFSIZ] = {'\0'};
    char arg2[BUFSIZ] = {'\0'};

    assert(argv);

    if (0 > sprintf(arg1, "%lu", time_to_sig) ||
        0 > sprintf(arg2, "%lu", time_to_check_sigs))
    {
        DEBUG_PRINT(("sprintf failed:\n"));
        return (EXIT_FAILURE);
    }

    if (-1 == setenv(TIME_TO_SIG, arg1, 1) ||
        -1 == setenv(TIME_TO_CHECK_SIGS, arg2, 1) ||
        -1 == setenv(USER_APP_NAME, argv[0], 1))
    {
        DEBUG_PRINT(("set environment variable:\n"));
        return (EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}

/********************************inner function*********************************/

int InitElements(watchdog_t **item, size_t time_to_sig, size_t time_to_check_sigs)
{
    watchdog_t *helper = NULL;

    assert(item);

    helper = (watchdog_t *)malloc(sizeof(watchdog_t));

    if (NULL == helper)
    {
        DEBUG_PRINT(("malloc failed:\n"));
        return (MALLOC_FAILD);
    }

    helper->schedular = SchedulerCreate();

    if (NULL == helper->schedular)
    {
        DEBUG_PRINT(("failed to create scheduler:\n"));
        return (EXIT_FAILURE);
    }

    if (InitSemaphors() || SetSigHandlers() ||
        SetTask(helper, time_to_sig, time_to_check_sigs))
    {
        return (EXIT_FAILURE);
    }

    *item = helper;
    (*item)->flag = flag;
    (*item)->sig = sig;

    return (EXIT_SUCCESS);
}

static int InitSemaphors(void)
{
    sig = sem_open("sig", O_CREAT, 0666, 0);
    flag = sem_open("flag", O_CREAT, 0666, 0);

    if (SEM_FAILED == sig ||
        SEM_FAILED == flag)
    {
        DEBUG_PRINT(("failed to open semaphore:\n"));
        return (EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}

static int SetSigHandlers(void)
{
    struct sigaction sig_usr_1 = {0};
    struct sigaction sig_usr_2 = {0};

    sig_usr_1.sa_flags = SA_SIGINFO;
    sig_usr_1.sa_sigaction = IncrementCounter;
    sig_usr_2.sa_flags = SA_SIGINFO;
    sig_usr_2.sa_sigaction = UpdateToStop;

    if (-1 == sigaction(SIGUSR1, &sig_usr_1, NULL) ||
        -1 == sigaction(SIGUSR2, &sig_usr_2, NULL))
    {
        DEBUG_PRINT(("failed to set handlers:\n"));
        return (EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}

static int SetTask(watchdog_t *item, size_t time_to_sig, size_t time_to_check_sigs)
{
    ilrd_uid_t bad_uid = GetBadUid();
    ilrd_uid_t task1_uid = {0};
    ilrd_uid_t task2_uid = {0};
    ilrd_uid_t task3_uid = {0};

    assert(item);

    task1_uid = SchedulerAdd(item->schedular, Task1, time_to_sig, (void *)item);
    task2_uid = SchedulerAdd(item->schedular, Task2, time_to_check_sigs, (void *)item);
    task3_uid = SchedulerAdd(item->schedular, Task3, time_to_sig / 2, (void *)item);

    if (UidIsSame(task1_uid, bad_uid) ||
        UidIsSame(task2_uid, bad_uid) ||
        UidIsSame(task3_uid, bad_uid))
    {
        DEBUG_PRINT(("failed to add task:\n"));
        return (EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}
/*s: good*/
void CleanUpWD(void *param)
{
    watchdog_t *item = (watchdog_t *)param;

    sem_close(item->flag);
    sem_close(item->sig);
    sem_unlink("sig");
    sem_unlink("flag");
    SchedulerDestroy(item->schedular);
    free(item);

    return;
}

/*****************************user thread function******************************/

void *WDRun(void *arg)
{
    SigMaskBlock();

    SigMaskWD(SIG_UNBLOCK);
    SchedulerRun(((watchdog_t *)arg)->schedular);
    CleanUpWD(arg);

    return (NULL);
}

/*****************************handler function*********************************/
/*s: good*/
static void IncrementCounter(int signum, siginfo_t *pinfo, void *data)
{
    UNUSED(signum);
    UNUSED(pinfo);
    UNUSED(data);

    atomic_fetch_add(&counter, 1);

    return;
}

/*s: good*/
static void UpdateToStop(int signum, siginfo_t *pinfo, void *data)
{
    UNUSED(signum);
    UNUSED(pinfo);
    UNUSED(data);

    /* to_stop = 1; */
    atomic_exchange(&to_stop, 1);

    return;
}

/*************************task function for scheduler**************************/

static int Task1(void *param)
{
    watchdog_t *item = (watchdog_t *)param;
    kill(item->send_pid, SIGUSR1);

    return (2);
}

static int Task2(void *param)
{
    watchdog_t *item = (watchdog_t *)param;
    pid_t c_pid = 0;
    char arg[BUFSIZ] = {'\0'};

    assert(param);

    /* if to_stop is 1 it's remove this task from schedular */
    if (to_stop)
    {
        return (0);
    }

    if (0 < counter)
    {
        DEBUG_PRINT(("reset counter:\n"));
        /* DEBUG_PRINT(("counter size before reset: %lu\n", counter)); */
        atomic_exchange(&counter, 0);
        return (2);
    }

    /* user process terminated */
    if (item->is_watchdog)
    {
        DEBUG_PRINT(("\nreviving user\n"));
        execv(item->argv[0], item->argv);
    }

    /* watchdog process terminated */
    else
    {
        kill(item->send_pid, SIGTERM);
        waitpid(item->send_pid, NULL, 0);

        c_pid = fork();

        if (0 == c_pid)
        {
            DEBUG_PRINT(("\nreviving watch_dog\n"));
            execv("watchdog", item->argv);
        }

        atomic_exchange(&counter, 1);
        sem_wait(sig);
        sprintf(arg, "%lu", c_pid);
        setenv(WATCH_DOG_PID, arg, 1);
        item->send_pid = c_pid;
    }

    return (2);
}

/* end watchdog protection, user app send StopWD */
static int Task3(void *param)
{
    watchdog_t *item = (watchdog_t *)param;

    if (to_stop)
    {
        DEBUG_PRINT(("\nstop task activate\n"));
        SchedulerStop(item->schedular);
        atomic_exchange(&to_stop, 0);
        return (0);
    }

    return (2);
}

/* Block all other signals that are not SIGUSR1/2 */
static void SigMaskBlock(void)
{
    sigset_t sig_set;

    sigfillset(&sig_set);
    sigdelset(&sig_set, SIGUSR1);
    sigdelset(&sig_set, SIGUSR2);
    pthread_sigmask(SIG_BLOCK, &sig_set, NULL);

    return;
}

static void SigMaskWD(int how)
{
    sigset_t sig_set;

    sigemptyset(&sig_set);
    sigaddset(&sig_set, SIGUSR1);
    sigaddset(&sig_set, SIGUSR2);
    pthread_sigmask(how, &sig_set, NULL);

    return;
}