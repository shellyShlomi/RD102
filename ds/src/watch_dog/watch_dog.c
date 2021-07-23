
#define _POSIX_SOURCE
#define _POSIX_C_SOURCE 199309L
#include <stdlib.h> /* malloc */
#include <stdio.h>
#include <stddef.h>    /* size_t */
#include <unistd.h>    /* pid_t */
#include <pthread.h>   /*           thread             */
#include <semaphore.h> /*          semaphore           */
#include <fcntl.h>     /*      For O_* constants       */
#include <assert.h>
#include <string.h>
#include <signal.h> /* struct sigaction  */

#include "watch_dog.h"
#include "watchdog1.h"
#include "scheduler.h"
#include "uid.h"

#define SIZE (5)
#define BUF_SIZE (1000)

atomic_size_t counter = 0;
atomic_int to_stop = 0;
static sem_t *sem_signal;
static sem_t *sem_block;
watchdog_t *watchdog_g = NULL;

/*------------- start halper funcs ------------*/

/*------------- helper funcs ------------*/
static int SetEnvVar(char *argv[], int check_ratio, int beats_interval);
int CreatSemaphors(sem_t **sem_signal, sem_t **sem_block);
static char *SetUserApp(char user_app[]);
void ClenUp();

/*------------- Tasks funcs ------------*/
int SetTasks(watchdog_t **watchdog, int beats_interval, int check_ratio);

int StopTask(void *param);
int Task1(void *param);
int Task2(void *param);
int Task(void *param);

/*------------- signaling funcs ------------*/
int InitHandler1(void (*handler_func)(int num));
int InitHandler2(void (*handler_func)(int num));

void Handler1(int num);
void Handler1User(int num);
void Handler2User(int num);
void Handler2WD(int num);

/*------------- user thread funcs ------------*/

static void *UserThread(void *scheduler);

/*------------------------------ implementetion --------------------------------*/

/*------------------------------ start --------------------------------*/

int WDStart(char *argv[], int check_ratio, int beats_interval)
{
    pthread_t thread = {0};
    watchdog_t *watchdog_elem = NULL;

    pid_t pid = getpid();
    pid_t pid_child = 0;

    int sem_val = 0;
    int status = 0;

    InitHandler1(Handler1);

    InitHandler2(Handler2WD);

    if (CreatWD(&watchdog_elem))
    {
        return (1);
    }
    watchdog_g = watchdog_elem;

    watchdog_elem->is_WD = !strncmp(argv[0], "WD_file_for_user", strlen("WD_file_for_user"));
    watchdog_elem->counter = counter;

    /*TODO: the func of setWD*/
    if (!watchdog_elem->is_WD) /*so im the user*/
    {
        /*         printf("%d %s\n", watchdog_elem->is_WD, argv[0]);
 */
        /*init Scheduler*/
        watchdog_elem->scheduler = SchedulerCreate();
        if (!watchdog_elem->scheduler)
        {

            return (1);
        }

        /*init Scheduler Tasks*/

        if (SetTasks(&watchdog_elem, beats_interval, check_ratio))
        {
            printf("task fail\n");
            return (1);
        }

        SetEnvVar(argv, check_ratio, beats_interval);
        watchdog_elem->check_ratio = check_ratio;
        watchdog_elem->beats_interval = beats_interval;

        pid_child = fork();

        if (0 == pid_child)
        {
            if (-1 == execv("/home/shelly/git/ds/bin/WD_file_for_user", argv))
            {
                /*sem_distroy*/
                return (1);
            }
        }

        else if (-1 == pid_child)
        {

            return (1);
        }
        else
        {
            watchdog_elem->is_WD = 0;
            watchdog_elem->signal_pid = pid_child;
            watchdog_elem->argv = argv;

            if (CreatSemaphors(&sem_signal, &sem_block))
            {
                sem_post(sem_signal);
                return (1);
            }
            watchdog_elem->sem_block = sem_block;
            watchdog_elem->sem_signal = sem_signal;

            status = sem_wait(sem_block);
            if (!status)
            {
                sem_getvalue(sem_signal, &sem_val);
                if (0 == sem_val)
                {
                    if (pthread_create(&thread, NULL, UserThread, watchdog_elem->scheduler))
                    {
                        /*sem_distroy*/
                        return (1);
                    }
                }
            }
            else
            {
                printf("sem_wait fail %d\n", status);
                return (1);
            }
        }
        return (0);
    }
    else
    {
        /*         printf("%d %s\n", watchdog_elem->is_WD, argv[0]);
 */
        /*init Scheduler*/
        watchdog_elem->scheduler = SchedulerCreate();
        if (!watchdog_elem->scheduler)
        {

            return (1);
        }

        /*init Scheduler Tasks*/

        if (SetTasks(&watchdog_elem, beats_interval, check_ratio))
        {
            printf("task fail\n");
            return (1);
        }

        watchdog_elem->check_ratio = atoi(getenv(CHECK_RATIO));
        watchdog_elem->beats_interval = atoi(getenv(BEATS_INTERVAL));
        watchdog_elem->signal_pid = atoi(getenv(USER_PID));
        watchdog_elem->user_app = getenv(USER_APP);
        watchdog_elem->argv = argv;
        SetEnvVar(argv, check_ratio, beats_interval);

        if (CreatSemaphors(&sem_signal, &sem_block))
        {
            sem_post(sem_signal);
            return (1);
        }
        watchdog_elem->sem_block = sem_block;
        watchdog_elem->sem_signal = sem_signal;

        SchedulerRun(watchdog_elem->scheduler);
        SchedulerDestroy(watchdog_elem->scheduler);
    }
    return (0);
}

static int SetEnvVar(char *argv[], int check_ratio, int beats_interval)
{
    char arg[BUF_SIZE] = {"\0"};

    sprintf(arg, "%d", check_ratio);
    setenv(CHECK_RATIO, arg, 0);
    memset(arg, BUF_SIZE, 0);

    sprintf(arg, "%d", beats_interval);
    setenv(BEATS_INTERVAL, arg, 0);
    memset(arg, BUF_SIZE, 0);

    sprintf(arg, "%d", getpid());
    setenv(USER_PID, arg, 0);
    memset(arg, BUF_SIZE, 0);

    if (watchdog_g->is_WD)
    {
        sprintf(arg, "%d", getpid());
        setenv(WD_PID, arg, 0);
    }
    setenv(USER_APP, (argv[0]), 0);
    return (0);
}

int CreatWD(watchdog_t **watchdog_elem)
{
    assert(watchdog_elem);
    (*watchdog_elem) = (watchdog_t *)malloc(sizeof(watchdog_t));
    if (!*watchdog_elem)
    {
        return (1);
    }

    return (0);
}

int CreatSemaphors(sem_t **sem_signal, sem_t **sem_block)
{

    *sem_block = sem_open("sem_block", O_CREAT, 0666, 0);
    if (SEM_FAILED == *sem_block)
    {
        return (1);
    }

    *sem_signal = sem_open("sem_signal", O_CREAT, 0666, 0);
    if (SEM_FAILED == *sem_signal)
    {
        sem_close(*sem_block);
        sem_unlink("sem_block");
        return (1);
    }

    return (0);
}

int SetTasks(watchdog_t **watchdog, int beats_interval, int check_ratio)
{
    /*     printf("%d SetTasks (*watchdog)->is_WD\n", (*watchdog)->is_WD);
 */
    if ((*watchdog)->is_WD)
    {
        if (UidIsSame(
                SchedulerAdd((*watchdog)->scheduler,
                             Task,
                             0,
                             (*watchdog)),
                GetBadUid()))
        {
            sem_post((*watchdog)->sem_signal);
            return (1);
        }
    }
    if (UidIsSame(
            SchedulerAdd((*watchdog)->scheduler,
                         Task1,
                         beats_interval,
                         *watchdog),
            GetBadUid()))
    {
        sem_post((*watchdog)->sem_signal);
        return (1);
    }

    if (UidIsSame(
            SchedulerAdd((*watchdog)->scheduler,
                         Task2,
                         (check_ratio * beats_interval),
                         *watchdog),
            GetBadUid()))
    {
        sem_post((*watchdog)->sem_signal);
        return (1);
    }

    if (UidIsSame(
            SchedulerAdd(
                (*watchdog)->scheduler,
                StopTask,
                beats_interval / 2,
                *watchdog),
            GetBadUid()))
    {
        sem_post((*watchdog)->sem_signal);
        return (1);
    }

    return (0);
}

void WDStop(void)
{
    if (kill(watchdog_g->signal_pid, SIGUSR2))
    {
/*         printf("usignal sending fail\n");
 */    }
return;
}

/*------------------------------ general --------------------------------*/
int InitHandler1(void (*handler_func)(int num))
{
    struct sigaction handler = {0};

    /*set SIGUSER1 Handler */
    handler.sa_handler = handler_func;
    if (sigaction(SIGUSR1, &handler, NULL))
    {
        return (1);
    }

    return (0);
}

int InitHandler2(void (*handler_func)(int num))
{
    struct sigaction handler = {0};

    /*set SIGUSER2 Handler*/
    handler.sa_handler = handler_func;
    if (sigaction(SIGUSR2, &handler, NULL))
    {
        return (1);
    }

    return (0);
}

int Task1(void *param)
{
    if (kill(((watchdog_t *)param)->signal_pid, SIGUSR1))
    {
        /*         printf("signal sending fail to %d %s\n", ((watchdog_t *)param)->signal_pid, getenv(USER_APP));
 */
        return (0);
    }

    return (2);
}

int Task2(void *param)
{

    static pid_t pid_child_T2 = 0;
    assert(param);

    /*     printf("Task2 %d %d %d \n", to_stop, ((watchdog_t *)param)->is_WD, counter);
 */
    if (to_stop)
    {
        return (0);
    }
    if (0 < atomic_load(&counter))
    {
        atomic_exchange(&counter, 0);
        /* counter = 0;
         printf("Task2: counter = 0 \n");

        printf("pid is :%d, and ((watchdog_t *)param)->is_WD is :%d cunter is: %d\n", getpid(), ((watchdog_t *)param)->is_WD, counter); */
        return (2);
    }
    if ((0 == counter))
    {
        if (((watchdog_t *)param)->is_WD) /*im WD*/
        {
            atomic_exchange(&counter, 1);

            /*             counter = 1;
 */
            /*             printf("Task2: 1 == local_count WD %s \n", getenv(USER_APP));
 */
            sem_close(((watchdog_t *)param)->sem_block);
            sem_close(((watchdog_t *)param)->sem_signal);
            SchedulerDestroy(((watchdog_t *)param)->scheduler);

            if (-1 == execv(getenv(USER_APP), ((watchdog_t *)param)->argv))
            {
                printf("execv fail 2\n");
                return (0);
            }
        }
        else
        {
            /*             printf("Task2: 1 == local_count WD \n");
 */
            kill(((watchdog_t *)param)->signal_pid, SIGTERM);
            waitpid(((watchdog_t *)param)->signal_pid, NULL, 0);
            atomic_exchange(&counter, 1);
            pid_child_T2 = fork();

            if (0 == pid_child_T2)
            {
                execv("/home/shelly/git/ds/bin/WD_file_for_user", ((watchdog_t *)param)->argv);
            }

            sem_wait(((watchdog_t *)param)->sem_block);
            ((watchdog_t *)param)->is_WD = 0;
            ((watchdog_t *)param)->signal_pid = pid_child_T2;
            return (0);
        }
    }
    return (2);
}

int StopTask(void *param)
{
    assert(param);

    if (atomic_load(&to_stop))
    {
        sem_close(((watchdog_t *)param)->sem_block);
        sem_close(((watchdog_t *)param)->sem_signal);
        sem_unlink("sem_block");
        sem_unlink("sem_signal");
        SchedulerStop(((watchdog_t *)param)->scheduler);

        return (0);
    }

    return (2);
}

int Task(void *param)
{
    assert(param);

    sem_post(((watchdog_t *)param)->sem_block);

    return (0);
}

void Handler1(int num)
{
    (void)num;

    if (5 < atomic_load(&counter))
    {
        atomic_exchange(&counter, 1);
        return;
    }
    else
    {
        /*         printf("counter %lu is WD %d\n", counter, watchdog_g->is_WD);
 */
        atomic_fetch_add(&counter, 1);
/*        ++counter;
 */    }

return;
}

void Handler2WD(int num)
{

    (void)num;
    /*     printf("Handler2WD %d %d \n", to_stop, watchdog_g->is_WD);
 */
    atomic_exchange(&to_stop, 1);

    return;
}

static void *UserThread(void *scheduler)
{
    assert(scheduler);

    SchedulerRun(scheduler);
    SchedulerDestroy(scheduler);

    return (NULL);
}

static char *SetUserApp(char user_app[])
{
    char *next_file = NULL;
    char *file_name = NULL;
    char *path = user_app;

    assert(user_app);

    next_file = strtok(path, "/");

    while (next_file)
    {
        file_name = next_file;
        next_file = strtok(NULL, "/");
    }

    return (file_name);
}