
#define _POSIX_SOURCE

#include <stdio.h>    /*           printf           */
#include <stddef.h>   /*           size_t           */
#include <unistd.h>   /*            pid_t           */
#include <pthread.h>  /*           thread           */
#include <semaphore.h>/*          semaphore         */
#include <fcntl.h>    /*      For O_* constants     */
#include <assert.h>   /*            assert          */
#include <signal.h>   /*       struct sigaction     */
#include <string.h>   /*          memset            */
#include <sys/wait.h> /*          waitpid           */
#include <stdlib.h>   /*          setenv            */

#include "watch_dog.h"
#include "watchdog_iner.h"
#include "scheduler.h"
#include "uid.h"

/*------------- general defines ------------*/

#define SIZE (5)
#define BUF_SIZE (1000)
#define SIGNAL ("signal")
#define BLOCK ("block")

/*------------- defines for setting environment variable ------------*/

#define USER_PID ("WD_USER_PID")
#define WD_PID ("WD_PID")
#define USER_APP ("WD_USER_APP")
#define WD_APP ("WD_APP")
#define SEM_SIGNAL_NAME ("WD_SEM_SIGNAL_NAME")
#define SEM_BLOCK_NAME ("WD_SEM_BLOCK_NAME")

/*------------- the watchdog struct ------------*/

typedef struct watchdog
{
    scheduler_t *scheduler;
    sem_t *sem_signal;
    sem_t *sem_block;
    char **argv;
    pid_t signal_pid;
    int is_WD;
    /*     int check_ratio;
    int beats_interval; */

} watchdog_t;

atomic_size_t counter = 0;
static atomic_int to_stop = 0;
watchdog_t *watchdog_g = NULL;

#ifdef NDEBUG

#else

#endif

int setenv(const char *name, const char *value, int overwrite); /* librery func nedded to be declerd */
/*------------- start halper funcs ------------*/
static int CreatWD(watchdog_t **watchdog_elem);
static int SetEnvVar(watchdog_t *watchdog, char *argv[], int check_ratio, int beats_interval, char *sem_signa_name, char *sem_block_name);
static int CreatSemaphors(sem_t **sem_signal, sem_t **sem_block);

/*------------- general funcs ------------*/
static void CleanUp(watchdog_t *watchdog,
                    int to_close_sem_signal,
                    int to_close_sem_block,
                    int to_unlink_sem_signal,
                    int to_unlink_sem_block,
                    int to_stop_scheduler,
                    int to_destroy_scheduler,
                    int to_free_watchdog);
/*------------- Tasks funcs ------------*/
static int SetTasks(watchdog_t **watchdog, int beats_interval, int check_ratio);

static int StopTask(void *param);
static int Task1(void *param);
static int Task2(void *param);
static int Task(void *param);

/*------------- signaling funcs ------------*/
static int InitHandler1(void (*handler_func)(int num));
static int InitHandler2(void (*handler_func)(int num));

static void Handler1(int num);
static void Handler2(int num);

/*------------- user thread funcs ------------*/
static void *UserThread(void *param);

/*------------------------------ implementetion --------------------------------*/

/*--------------- WDStart ---------------*/

int WDStart(char *argv[], int check_ratio, int beats_interval)
{
    pthread_t thread = {0};
    watchdog_t *watchdog_elem = NULL;
    pid_t pid_child = 0;
    static sem_t *sem_signal = NULL;
    static sem_t *sem_block = NULL;
    int sem_val = 0;

    InitHandler1(Handler1);

    InitHandler2(Handler2);

    if (CreatWD(&watchdog_elem))
    {
        return (1);
    }
    watchdog_g = watchdog_elem;

    watchdog_elem->is_WD = !strncmp(argv[0], "WD_file_for_user", strlen("WD_file_for_user"));

    watchdog_elem->scheduler = SchedulerCreate();
    if (!watchdog_elem->scheduler)
    {
        CleanUp(watchdog_elem, 0, 0, 0, 0, 0, 0, 1);
        return (1);
    }

    /*init Scheduler Tasks*/

    if (SetTasks(&watchdog_elem, beats_interval, check_ratio))
    {
        CleanUp(watchdog_elem, 0, 0, 0, 0, 0, 1, 1);
        printf("SetTasks fail\n");
        return (1);
    }

    if (SetEnvVar(watchdog_elem, argv, check_ratio, beats_interval, SIGNAL, BLOCK))
    {
        CleanUp(watchdog_elem, 0, 0, 0, 0, 0, 1, 1);
        printf("SetEnvVar fail\n");
        return (1);
    }

    if (CreatSemaphors(&sem_signal, &sem_block))
    {
        CleanUp(watchdog_elem, 0, 0, 0, 0, 0, 1, 1);
        return (1);
    }
    watchdog_elem->sem_block = sem_block;
    watchdog_elem->sem_signal = sem_signal;
    watchdog_elem->argv = argv;

    printf("%d %s\n", watchdog_elem->is_WD, argv[0]);
    /*TODO: the func of setWD*/
    if (!watchdog_elem->is_WD) /*so im the user*/
    {
        pid_child = fork();

        if (0 == pid_child)
        {
            if (-1 == execv(getenv(WD_APP), argv))
            {
                CleanUp(watchdog_elem, 1, 1, 1, 1, 0, 1, 1);
                return (1);
            }
        }

        else if (-1 == pid_child)
        {

            return (1);
        }
        else
        {
            watchdog_elem->signal_pid = pid_child;

            if (!sem_wait(watchdog_elem->sem_block))
            {
                sem_getvalue(sem_signal, &sem_val);
                if (0 == sem_val)
                {
                    if (pthread_create(&thread, NULL, UserThread, watchdog_elem))
                    {
                        CleanUp(watchdog_elem, 1, 1, 1, 1, 0, 1, 1);
                        return (1);
                    }
                    pthread_detach(thread);
                }
            }
            else
            {
                CleanUp(watchdog_elem, 1, 1, 1, 1, 0, 1, 1);
                /*printf("sem_wait fail \n");*/
                return (1);
            }
        }
        return (0);
    }
    else
    {
        watchdog_elem->signal_pid = atoi(getenv(USER_PID));
        SchedulerRun(watchdog_elem->scheduler);
    }
    return (0);
}

/*--------------- WDStop ---------------*/

void WDStop(void)
{
    if (kill(watchdog_g->signal_pid, SIGUSR2))
    {
        /*printf("usignal sending fail\n");*/
    }
    if (watchdog_g->is_WD)
    {
        CleanUp(watchdog_g, 0, 0, 0, 0, 0, 1, 1);
    }
    return;
}

/*------------- start halper funcs ------------*/

static int SetEnvVar(watchdog_t *watchdog, char *argv[], int check_ratio, int beats_interval, char *sem_signa_name, char *sem_block_name)
{
    char arg[BUF_SIZE] = {"\0"};

    assert(watchdog);
    assert(argv);
    assert(sem_signa_name);
    assert(sem_block_name);

    if (0 > sprintf(arg, "%d", check_ratio) || -1 == setenv(CHECK_RATIO, arg, 0))
    {
        return (1);
    }
    memset(arg, 0, BUF_SIZE);

    if (0 > sprintf(arg, "%d", beats_interval) || -1 == setenv(BEATS_INTERVAL, arg, 0))
    {
        return (1);
    }
    memset(arg, 0, BUF_SIZE);

    if (0 > sprintf(arg, "%d", getpid()) || -1 == setenv(USER_PID, arg, 0))
    {
        return (1);
    }
    memset(arg, 0, BUF_SIZE);

    if (-1 == setenv(SEM_BLOCK_NAME, sem_block_name, 0) || 
        -1 == setenv(SEM_SIGNAL_NAME, sem_signa_name, 0) ||
        -1 == setenv(WD_APP, "/home/shelly/git/ds/bin/WD_file_for_user", 0) || 
        -1 == setenv(USER_APP, (argv[0]), 0))
    {
        return (1);
    }

    return (0);
}

static int CreatWD(watchdog_t **watchdog_elem)
{
    assert(watchdog_elem);

    (*watchdog_elem) = (watchdog_t *)malloc(sizeof(watchdog_t));
    if (!*watchdog_elem)
    {
        return (1);
    }

    return (0);
}

static int CreatSemaphors(sem_t **sem_signal, sem_t **sem_block)
{
    assert(sem_signal);
    assert(sem_block);

    *sem_block = sem_open(getenv(SEM_BLOCK_NAME), O_CREAT, 0660, 0);
    if (SEM_FAILED == *sem_block)
    {
        return (1);
    }

    *sem_signal = sem_open(getenv(SEM_SIGNAL_NAME), O_CREAT, 0660, 0);
    if (SEM_FAILED == *sem_signal)
    {
        sem_close(*sem_block);
        sem_unlink(getenv(SEM_BLOCK_NAME));
        return (1);
    }

    return (0);
}

/*------------- Tasks funcs ------------*/

static int SetTasks(watchdog_t **watchdog, int beats_interval, int check_ratio)
{

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

static int Task1(void *param)
{
    if (kill(((watchdog_t *)param)->signal_pid, SIGUSR1))
    {
        /*printf("signal sending fail to %d %s\n", ((watchdog_t *)param)->signal_pid, getenv(USER_APP));*/
        return (0);
    }

    return (2);
}

static int Task2(void *param)
{
    static pid_t pid_child_T2 = 0;
    assert(param);

    /*printf("Task2 %d %d %d \n", to_stop, ((watchdog_t *)param)->is_WD, counter);*/
    if (atomic_load(&to_stop))
    {
        /* NOTE : meybe here try to debug the reopen of 
        the user app if the WD is realive affter the stop sigmal */
        return (0);
    }
    if (0 < atomic_load(&counter))
    {
        atomic_exchange(&counter, 0);
        /*printf("Task2: counter = 0 \n");*/
        /*printf("pid is :%d, and ((watchdog_t *)param)->is_WD is :%d cunter is: %d\n", getpid(), ((watchdog_t *)param)->is_WD, counter); */
        return (2);
    }
    if ((0 == atomic_load(&counter)))
    {
        if (((watchdog_t *)param)->is_WD) /*im WD*/
        {
            atomic_exchange(&counter, 1);
            /*             kill(((watchdog_t *)param)->signal_pid, SIGTERM);
            waitpid(((watchdog_t *)param)->signal_pid, NULL, 0); */

            CleanUp(((watchdog_t *)param), 1, 1, 0, 0, 1, 1, 0);
            ((watchdog_t *)param)->argv[0] = getenv(USER_APP);
            execv(getenv(USER_APP), ((watchdog_t *)param)->argv);
        }
        else
        {
            kill(((watchdog_t *)param)->signal_pid, SIGTERM);
            waitpid(((watchdog_t *)param)->signal_pid, NULL, 0);
            atomic_exchange(&counter, 1);
            pid_child_T2 = fork();

            if (0 == pid_child_T2)
            {
                execv(getenv(WD_APP), ((watchdog_t *)param)->argv);
            }

            ((watchdog_t *)param)->is_WD = 0;
            ((watchdog_t *)param)->signal_pid = pid_child_T2;
            sem_wait(((watchdog_t *)param)->sem_block);
            return (0);
        }
    }
    return (2);
}

static int StopTask(void *param)
{
    assert(param);

    if (atomic_load(&to_stop))
    {
        CleanUp(((watchdog_t *)param), 1, 1, 1, 1, 1, 0, 0);

        return (0);
    }

    return (2);
}

static int Task(void *param)
{
    assert(param);

    sem_post(((watchdog_t *)param)->sem_block);

    return (0);
}

/*------------- signaling funcs ------------*/
/* TODO:merge the inithendlers */
static int InitHandler1(void (*handler_func)(int num))
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

static int InitHandler2(void (*handler_func)(int num))
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

static void Handler1(int num)
{
    (void)num;

    /* printf("counter %lu is WD %d\n", counter, watchdog_g->is_WD); */
    atomic_fetch_add(&counter, 1);

    return;
}

static void Handler2(int num)
{

    (void)num;
    /*printf("Handler2 %d %d \n", to_stop, watchdog_g->is_WD);*/
    atomic_exchange(&to_stop, 1);

    return;
}

/*------------- user thread funcs ------------*/

static void *UserThread(void *param)
{
    assert(param);

    SchedulerRun(((watchdog_t *)param)->scheduler);
    CleanUp(((watchdog_t *)param), 0, 0, 0, 0, 0, 1, 1);

    return (NULL);
}

/*------------------------------ general --------------------------------*/

static void CleanUp(watchdog_t *watchdog,
                    int to_close_sem_signal,
                    int to_close_sem_block,
                    int to_unlink_sem_signal,
                    int to_unlink_sem_block,
                    int to_stop_scheduler,
                    int to_destroy_scheduler,
                    int to_free_watchdog)
{
    assert(watchdog);

    if (to_stop_scheduler)
    {
        SchedulerStop(watchdog->scheduler);
    }
    if (to_close_sem_signal)
    {
        sem_close(watchdog->sem_signal);
    }
    if (to_close_sem_block)
    {
        sem_close(watchdog->sem_block);
    }
    if (to_unlink_sem_signal)
    {
        sem_unlink("sem_signal");
    }
    if (to_unlink_sem_block)
    {
        sem_unlink("sem_block");
    }
    if (to_destroy_scheduler)
    {
        SchedulerDestroy(watchdog->scheduler);
    }
    if (to_free_watchdog)
    {
        free(watchdog);
    }

    return;
}