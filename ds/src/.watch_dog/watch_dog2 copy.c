
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
#include "watchdog.h"
#include "scheduler.h"
#include "uid.h"

#define SIZE (5)

static size_t counter_wd = 0;
static size_t counter_user = 0;
static int flag = 0;
static pid_t check_pid_fork = 0;
char *arg_glob[SIZE_OF_ARGV] = {NULL};
char **arr_g = {NULL};
sem_t *sem_block = 0;
sem_t *sem_signal = 0;
int check_ratio;
int beats_interval;

/*------------- start halper funcs ------------*/
/* static int WDStartIner(int check_ratio, int beats_interval, char **cmlarg);
 */
/*------------- helper funcs ------------*/
static char *GetCmlArgs();
static void GetDataFoWD(char *(*dest_arr[]), pid_t fork_pid, pid_t signal_pid, int check_ratio, int beats_interval);
static void ClenUp();
static int SetLocalArgs(char *argv[], int is_WD, int check_ratio, int beats_interval);

/*------------- Tasks funcs ------------*/
int SetTasks(watchdog_t **watchdog, int beats_interval, int check_ratio);

int StopTask(void *param);
int Task1(void *param);
int Task2(void *param);

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

    static char arg[BUFSIZ] = {"\0"};
    size_t i = 0;

    pid_t pid = getpid();

    int sem_val = 0;
    arr_g = argv;
    beats_interval = beats_interval;
    check_ratio = check_ratio;
    if (InitAll(&watchdog_elem, pid, pid, check_ratio, beats_interval, &sem_signal, &sem_block))
    {
        return (1);
    }

    watchdog_elem->check_pid_fork = fork();
    check_pid_fork = watchdog_elem->check_pid_fork;

    if (0 == watchdog_elem->check_pid_fork)
    {

        strcpy(arg, __FILE__);
        arg_glob[PATH] = (char *)malloc(strlen(arg) + 1);
        strcpy(arg_glob[PATH], arg);
        memset(arg, BUFSIZ, 0);

        sprintf(arg, "%d", watchdog_elem->check_pid_fork);
        arg_glob[FORK_PID_TO_CHECK] = (char *)malloc(strlen(arg) + 1);
        strcpy(arg_glob[FORK_PID_TO_CHECK], arg);
        memset(arg, BUFSIZ, 0);

        sprintf(arg, "%d", pid);
        arg_glob[SIGNAL_PID] = (char *)malloc(strlen(arg) + 1);
        strcpy(arg_glob[SIGNAL_PID], arg);
        memset(arg, BUFSIZ, 0);

        sprintf(arg, "%d", check_ratio);
        arg_glob[CHECK_RATIO] = (char *)malloc(strlen(arg) + 1);
        strcpy(arg_glob[CHECK_RATIO], arg);
        memset(arg, BUFSIZ, 0);

        sprintf(arg, "%d", beats_interval);
        arg_glob[BEATS_INTERVAL] = (char *)malloc(strlen(arg) + 1);
        strcpy(arg_glob[BEATS_INTERVAL], arg);

        arg_glob[NULL_ELEM] = NULL;

        if (-1 == execv("/home/shelly/git/ds/bin/WD_file_for_user", arg_glob))
        {
            ClenUp();
            /*sem_distroy*/
            return (1);
        }
    }

    else if (-1 == watchdog_elem->check_pid_fork)
    {
        ClenUp();
        /*sem_distroy*/
        return (1);
    }
    else
    {
        watchdog_elem->signal_pid = watchdog_elem->check_pid_fork;
        check_pid_fork = watchdog_elem->check_pid_fork;

        sem_wait(sem_block);
        sem_getvalue(sem_signal, &sem_val);
        if (0 == sem_val)
        {
            if (pthread_create(&thread, NULL, UserThread, watchdog_elem->scheduler))
            {
                ClenUp();
                /*sem_distroy*/
                return (1);
            }
        }
        else
        {
            ClenUp();
            /*sem_distroy*/
            return (1);
        }
    }

    return (0);
}

static char *GetCmlArgs()
{

    return (NULL);
}

int InitAll(watchdog_t **watchdog_elem, pid_t check_pid_fork, pid_t signal_pid, int check_ratio, int beats_interval, sem_t **sem_signal, sem_t **sem_block)
{

    (*watchdog_elem) = (watchdog_t *)malloc(sizeof(watchdog_t));
    if (!*watchdog_elem)
    {
        return (1);
    }

    InitHandler1(Handler1);

    InitHandler2(Handler2WD);

    (*watchdog_elem)->flag = flag;

    /*phas 2*/
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

    (*watchdog_elem)->scheduler = SchedulerCreate();
    if (!(*watchdog_elem)->scheduler)
    {
        ClenUp();
        /*sem_distroy*/
        sem_close(*sem_block);
        sem_close(*sem_signal);
        sem_unlink("sem_block");
        sem_unlink("sem_signal");
        return (1);
    }

    if (SetTasks(watchdog_elem, beats_interval, check_ratio))
    {
        ClenUp();
        /*sem_distroy*/
        sem_close(*sem_block);
        sem_close(*sem_signal);
        sem_unlink("sem_block");
        sem_unlink("sem_signal");
        return (1);
    }

    return (0);
}

int SetTasks(watchdog_t **watchdog, int beats_interval, int check_ratio)
{
    if (UidIsSame(
            SchedulerAdd((*watchdog)->scheduler,
                         Task1,
                         beats_interval,
                         *watchdog),
            GetBadUid()))
    {
        return (1);
    }

    if (UidIsSame(
            SchedulerAdd((*watchdog)->scheduler,
                         Task2,
                         (check_ratio * beats_interval),
                         *watchdog),
            GetBadUid()))
    {
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
        return (1);
    }
    return (0);
}

void WDStop(void)
{
    if (kill(getpid(), SIGUSR2))
    {
        printf("usignal sending fail\n");
    }
    return;
}

/*------------------------------ general --------------------------------*/

int Task1(void *param)
{
    if (kill(((watchdog_t *)param)->signal_pid, SIGUSR1))
    {
        printf("signal sending fail to %d\n", ((watchdog_t *)param)->signal_pid);
    }

    return (2);
}

int Task2(void *param)
{
    /*the wd get a signal ((watchdog_t *)param)->check_pid_fork != ((watchdog_t *)param)->signal_pid - wd procees */
    pthread_t thread = {0};
    int sem_val = 0;
    static char arg[BUFSIZ] = {"\0"};
    static local_count_of_wd = 0;
    static local_count_of_user = 0;
    int status = 1;

    if ((1 > counter_user))
    {
        ++local_count_of_user;
    }
    else if ((1 > counter_wd))
    {
        ++local_count_of_wd;
    }

    if ((5 <= counter_wd) && ((watchdog_t *)param)->check_pid_fork == 0 )
    {
        counter_wd = 0;
    }
    else if ((5 <= counter_user) && ((watchdog_t *)param)->check_pid_fork != 0 )
    {
        counter_user = 0;
    }

    /*if im the user*/
    if ((1 < local_count_of_user) && ((watchdog_t *)param)->check_pid_fork != 0)
    {
        local_count_of_user = 0;
        printf("WD is dead\n");
        printf("counter_user is %lu\n", counter_user);
        if ((status = kill(((watchdog_t *)param)->signal_pid, SIGUSR1)))
        {
            printf("signal sending fail to %d\n", ((watchdog_t *)param)->signal_pid);
        }
        wait(status);
        /*   SchedulerDestroy(((watchdog_t *)param)->scheduler);
        if ((1 > counter_user) && local_count_of_user < 0)
        {

            WDStart(check_ratio, beats_interval);
        } */
        flag = 0;

        status = fork();

        if (status == 0)
        {
            if (-1 == execv("/home/shelly/git/ds/bin/WD_file_for_user", arg_glob))
            {

                ClenUp();
                return (1);
            }
        }

        else if (-1 == status)
        {
            ClenUp();
            return (1);
        }
        else
        {

            ((watchdog_t *)param)->signal_pid = ((watchdog_t *)param)->check_pid_fork;
            check_pid_fork = ((watchdog_t *)param)->check_pid_fork;

            sem_wait(sem_block);
            sem_getvalue(sem_signal, &sem_val);
            if (0 == sem_val)
            {
                flag = 0;
            }
            else
            {
                ClenUp();
                printf("samting fail\n");
                return (1);
            }
        }
    }
    else if ((1 > counter_wd) && (1 < local_count_of_wd) && ((watchdog_t *)param)->check_pid_fork == 0)
    {
        local_count_of_wd = 0;
        SchedulerDestroy(((watchdog_t *)param)->scheduler);
        
        if (-1 == execv("/home/shelly/git/ds/bin/WD_file_for_user", arg_glob))
        {
            printf("execv fail\n");
        }
        printf("user is dead\n");
        printf("counter_wd is %lu\n", counter_wd);
    }
    return (2);
}

int StopTask(void *param)
{
    if (flag)
    {
        SchedulerStop(((watchdog_t *)param)->scheduler);
    }

    return (0);
}

static void *UserThread(void *scheduler)
{

    SchedulerRun(scheduler);

    return (NULL);
}

static void ClenUp()
{
}

void Handler1(int num)
{
    (void)num;

    if (check_pid_fork == 0)
    {
        /*the wd get a signal check_pid_fork == 0 - wd procees */

        printf("counter_wd %lu\n", counter_wd);
        ++counter_wd;
    }
    else
    {
        /*the user get a signal*/
        ++counter_user;
        printf("counter_user %lu\n", counter_user);
    }

    return;
}

/* void Handler2User(int num, siginfo_t *pinfo, void *data)
{

    (void)pinfo;
    (void)num;
    ((watchdog_t *)data)->flag = 1;

    return;
    void Handler2User(int num);
void Handler2WD(int num);
} */

void Handler2WD(int num)
{

    (void)num;
    flag = 1;

    return;
}

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

    /*set SIGUSER1 Handler*/
    handler.sa_handler = handler_func;
    if (sigaction(SIGUSR2, &handler, NULL))
    {
        return (1);
    }

    return (0);
}


static int SetLocalArgs(char *argv[], int is_WD, int check_ratio, int beats_interval)
{
   /*  static char arg[10] = {"\0"};
    char **start = NULL;
    size_t i = 0;

    arg_m[0] = (char *)malloc(strlen(argv[0]) + 1);
    strcpy(arg_m[0], argv[0]);

    sprintf(arg, "%d", check_ratio);
    arg_m[CHECK_RATIO] = (char *)malloc(strlen(arg) + 1);
    strcpy(arg_m[CHECK_RATIO], arg);
    memset(arg, BUFSIZ, 0);

    sprintf(arg, "%d", beats_interval);
    arg_m[BEATS_INTERVAL] = (char *)malloc(strlen(arg) + 1);
    strcpy(arg_m[BEATS_INTERVAL], arg);

    arg_m[NULL_ELEM] = NULL;

    if (is_WD) /*so im the WD*/
    /*{
        start = g_wd->args;
        for (i = 0; i < NULL_ELEM; ++i)
        {
            g_wd->args = (arg_m + i);
            g_wd->args = g_wd->args + strlen((arg_m[i]));
        }
        g_wd->args = start;
        g_wd->args = arg_m;
    }
    else
    {

        start = g_user->args;
        for (i = 0; i < NULL_ELEM; ++i)
        {
            g_user->args = (arg_m + i);
            g_user->args = g_user->args + strlen((arg_m[i]));
        }
        g_user->args = start;
        g_user->args = arg_m;
    }
 */
    return (0);
}

/* 
static void GetDataFoWD(char *(*dest_arr[]), pid_t fork_pid, pid_t signal_pid, int check_ratio, int beats_interval)
{
    char *arr[SIZE_OF_ARGV] = {NULL};
    assert(dest_arr);
    
    arr = *dest_arr;

    arr[PATH] = __FILE__;
    sprintf(arr[FORK_PID_TO_CHECK], "%d", fork_pid);
    sprintf(arr[SIGNAL_PID], "%d", signal_pid);
    sprintf(arr[CHECK_RATIO], "%d", check_ratio);
    sprintf(arr[BEATS_INTERVAL], "%d", beats_interval);

    strcpy();

    return;
}
 */
/* static char *GetData()
{
    char *next_file = NULL;
    char *file_name = NULL;
    char *path = NULL;

    if (!(path = getenv("PATH")))
    {
        return (NULL);
    }

    next_file = strtok(path, "/");

    while (next_file)
    {
        file_name = next_file;
        next_file = strtok(NULL, "/");
    }
    file_name = strtok(file_name, ".");

    return (file_name);
} */
