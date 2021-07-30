
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


watchdog_t *g_wd;
watchdog_t *g_user;
char *arg_m[SIZE_OF_ARGV] = {NULL};

/* int is_WD;
 */
/*------------- start halper funcs ------------*/
/* static int WDStartIner(int check_ratio, int beats_interval, char **cmlarg);
 */
/*------------- helper funcs ------------*/
static int SetLocalArgs(char *argv[], int is_WD, int check_ratio, int beats_interval);
static void ClenUp();
int CreatSemaphors(sem_t **sem_signal, sem_t **sem_block);

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
    sem_t *sem_block = NULL;
    sem_t *sem_signal = NULL;
    size_t i = 0;

    pid_t pid = getpid();

    int sem_val = 0;
    printf("%s\n", argv[0]);

    if (CreatWD(&watchdog_elem))
    {
        return (1);
    }
    /*TODO: the func of setWD*/
    if (!strstr(argv[0], "WD_file_for_user")) /*so im the user*/
    {
        g_user = watchdog_elem;
        watchdog_elem->check_ratio = check_ratio;
        watchdog_elem->beats_interval = beats_interval;
        watchdog_elem->is_WD = 0;
    }
    else
    {
        g_wd = watchdog_elem;
        watchdog_elem->check_ratio = atoi(argv[CHECK_RATIO]);
        watchdog_elem->beats_interval = atoi(argv[BEATS_INTERVAL]);
        watchdog_elem->is_WD = 1;
    }

    SetLocalArgs(argv, watchdog_elem->is_WD, check_ratio, beats_interval);
    watchdog_elem->sem_block = sem_block;
    watchdog_elem->sem_signal = sem_signal;
    CreatSemaphors(&watchdog_elem->sem_signal, &watchdog_elem->sem_block );



    /*     for (i = 0; i < NULL_ELEM; ++i)
    {
        printf("%s\n", watchdog_elem->args[i]);
    } */

    return (0);
}

static int SetLocalArgs(char *argv[], int is_WD, int check_ratio, int beats_interval)
{
    static char arg[10] = {"\0"};
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
    {
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