
/*  Developer: Shelly Shlomi;									*
 *  Status:in development, functonalety - done;                 *
 *  Date Of Creation:19.07.21;									*
 *  Date Of Approval:00.07.21                                   *
 *  Approved By:                                                *
 *  Description: watchdog app :                                 *
 *          +   Have helgring problems, data race, whene        *
 *              WD/user killed;                                 *
 *          +   The WD hes a critical section if the WD is      *
 *              killed and the is realived but didnot run the   *
 *              schedualer yet to activet the stop task         *
 *              - sigmask for that section.                     */

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

#define USER_PID ("WD_USER_PID") /*TODO: not to have 2 pid doubel informetion!!! problrmatics!!! fix the problem*/
#define WD_PID ("WD_PID")        /*TODO: not to have 2 pid doubel informetion!!! problrmatics!!! fix the problem*/
#define USER_APP ("WD_USER_APP")
#define WD_APP ("WD_APP")
#define SEM_SIGNAL_NAME ("WD_SEM_SIGNAL_NAME")
#define SEM_BLOCK_NAME ("WD_SEM_BLOCK_NAME")

#ifndef NDEBUG
#define DEBUG_PRINT(x)  \
    do                  \
    {                   \
        /* printf x; */ \
    } while (0)
#else
#define DEBUG_PRINT(x) \
    do                 \
    {                  \
    } while (0)
#endif
/*------------- the watchdog struct ------------*/

typedef struct watchdog
{
    scheduler_t *scheduler;
    sem_t *sem_signal;
    sem_t *sem_block;
    char **argv;
    pid_t signal_pid;
    int is_WD;
} watchdog_t;

atomic_size_t counter = 0;
static atomic_int to_stop = 0;
watchdog_t *watchdog_g = NULL;
pthread_t *thread = NULL;

/* static void SigMaskWD(int how)
{
    sigset_t sig_set;

    sigaddset(&sig_set, SIGUSR1);
    sigaddset(&sig_set, SIGUSR2);
    pthread_sigmask(how, &sig_set, NULL);

    return;
}
 */

/* librery func nedded to be declerd */
int unsetenv(const char *name);

int setenv(const char *name, const char *value, int overwrite);

/*------------- start halper funcs ------------*/
static int InitWD(watchdog_t *watchdog_elem,
                  char *argv[],
                  int check_ratio,
                  int beats_interval);

static watchdog_t *CreatWD();

static int SetEnvVar(watchdog_t *watchdog, char *argv[],
                     int check_ratio,
                     int beats_interval,
                     char *sem_signa_name,
                     char *sem_block_name);
static int CreatSemaphors(watchdog_t *watchdog);

/*------------- general funcs ------------*/
static void CleanUp(watchdog_t *watchdog, int clean_up_descriptor);

/*------------- Tasks funcs ------------*/
static int SetTasks(watchdog_t *watchdog, int beats_interval, int check_ratio);

static int StopTask(void *param);

static int SignalTask(void *param);

static int ViabilityTask(void *param);

static int UnblockSemaphorTask(void *param);

/*------------- signaling funcs ------------*/
static int InitHandler(void (*handler_func)(int num), int signal_to_send);

static void IncramentCounterHandler(int num);

static void TernOnToStopHandler(int num);

/*------------- user thread funcs ------------*/
static void *UserThread(void *param);

/******************************* implementetion *******************************/

/*********************************** WDStart ***********************************/

int WDStart(char **argv, int check_ratio, int beats_interval)
{
    static pthread_t thread_l = {0};
    watchdog_t *watchdog_elem = NULL;
    pid_t pid_child = 0;
    int sem_val = 0;

    atomic_exchange(&to_stop, 0);

    if (InitHandler(TernOnToStopHandler, SIGNAL2))
    {
        return (1);
    }
    if (InitHandler(IncramentCounterHandler, SIGNAL1))
    {
        return (1);
    }
    watchdog_elem = CreatWD();
    if (!watchdog_elem)
    {
        return (1);
    }
    watchdog_elem->is_WD = !strncmp(argv[0], "WD_file_for_user", strlen("WD_file_for_user"));

    if (InitWD(watchdog_elem, argv, check_ratio, beats_interval))
    {
        return (1);
    }
    /* DEBUG_PRINT */ printf("WDsatrt, at the begining, is_WD: %d argv[0]: ", watchdog_elem->is_WD);
    /* DEBUG_PRINT */ printf("%s argv[1]: %s argv[2]: %s \n", argv[0], argv[1], argv[2]);

    if (!watchdog_elem->is_WD) /*so im the user*/
    {
        watchdog_g = watchdog_elem;
        if (getenv(WD_PID))
        {
            watchdog_elem->signal_pid = atoi(getenv(WD_PID));
        }

        pid_child = fork();

        if (0 == pid_child)
        {
            argv[0] = getenv(WD_APP);
            if (-1 == execv(getenv(WD_APP), argv))
            {
                CleanUp(watchdog_elem, CF_CLOSE_SEM_SIGNAL |
                                           CF_CLOSE_SEM_BLOCK |
                                           CF_UNLINK_SEM_SIGNAL |
                                           CF_UNLINK_SEM_BLOCK |
                                           CF_DESTROY_SCHEDULER |
                                           CF_FREE_WATCHDOG);
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
            thread = &thread_l;

            if (!sem_wait(watchdog_elem->sem_block))
            {
                sem_getvalue(watchdog_elem->sem_signal, &sem_val);
                if (0 == sem_val) /*TODO:finetuning the semaphor of signaling*/
                {
                    if (pthread_create(&thread_l, NULL, UserThread, watchdog_elem))
                    {
                        CleanUp(watchdog_elem, CF_CLOSE_SEM_SIGNAL |
                                                   CF_CLOSE_SEM_BLOCK |
                                                   CF_UNLINK_SEM_SIGNAL |
                                                   CF_UNLINK_SEM_BLOCK |
                                                   CF_DESTROY_SCHEDULER |
                                                   CF_FREE_WATCHDOG |
                                                   CF_STOP_SCHEDULER);
                        return (1);
                    }
                    return (0);
                }
                return (1);
            }
            else
            {
                CleanUp(watchdog_elem, CF_CLOSE_SEM_SIGNAL |
                                           CF_CLOSE_SEM_BLOCK |
                                           CF_UNLINK_SEM_SIGNAL |
                                           CF_UNLINK_SEM_BLOCK |
                                           CF_DESTROY_SCHEDULER |
                                           CF_FREE_WATCHDOG);
                DEBUG_PRINT(("sem_wait fail \n"));

                return (1);
            }
        }
        return (1);
    }
    else
    {
        watchdog_elem->signal_pid = atoi(getenv(USER_PID));
        SchedulerRun(watchdog_elem->scheduler);
        kill(watchdog_elem->signal_pid, SIGUSR2);
        CleanUp(watchdog_elem, CF_CLOSE_SEM_SIGNAL |
                                   CF_CLOSE_SEM_BLOCK |
                                   CF_UNLINK_SEM_SIGNAL |
                                   CF_UNLINK_SEM_BLOCK |
                                   CF_DESTROY_SCHEDULER |
                                   CF_FREE_WATCHDOG);
        return (0);
    }

    return (0);
}

/*********************************** WDStop ***********************************/

void WDStop(void)
{

    kill(watchdog_g->signal_pid, SIGUSR2);

    DEBUG_PRINT(("usignal sending fail\n"));

    /*------------- hepends only on the user -------------*/

    waitpid(watchdog_g->signal_pid, NULL, 0);

    if (watchdog_g && !watchdog_g->is_WD)
    {
        kill(watchdog_g->signal_pid, SIGTERM); /*new 17:20????*/
        pthread_join(*thread, NULL);
    }

    return;
}

/***************************** start halper funcs *****************************/

static int InitWD(watchdog_t *watchdog_elem, char *argv[], int check_ratio, int beats_interval)
{

    if (SetEnvVar((watchdog_elem), argv, check_ratio, beats_interval, SIGNAL, BLOCK))
    {
        CleanUp(watchdog_elem, CF_DESTROY_SCHEDULER |
                                   CF_FREE_WATCHDOG);
        DEBUG_PRINT(("SetEnvVar fail\n"));

        return (1);
    }

    if (CreatSemaphors((watchdog_elem)))
    {
        CleanUp(watchdog_elem, CF_DESTROY_SCHEDULER |
                                   CF_FREE_WATCHDOG);
        return (1);
    }

    (watchdog_elem)->scheduler = SchedulerCreate();
    if (!(watchdog_elem)->scheduler)
    {
        CleanUp(watchdog_elem, CF_CLOSE_SEM_SIGNAL |
                                   CF_CLOSE_SEM_BLOCK |
                                   CF_UNLINK_SEM_SIGNAL |
                                   CF_UNLINK_SEM_BLOCK |
                                   CF_FREE_WATCHDOG);
        return (1);
    }

    if (SetTasks((watchdog_elem), beats_interval, check_ratio))
    {
        CleanUp(watchdog_elem, CF_CLOSE_SEM_SIGNAL |
                                   CF_CLOSE_SEM_BLOCK |
                                   CF_UNLINK_SEM_SIGNAL |
                                   CF_UNLINK_SEM_BLOCK |
                                   CF_DESTROY_SCHEDULER |
                                   CF_FREE_WATCHDOG);

        DEBUG_PRINT(("SetTasks fail\n"));

        return (1);
    }

    (watchdog_elem)->argv = argv;

    return (0);
}
/*TODO: the sem postfor signal if it relevent*/
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
        -1 == setenv(WD_APP, "/home/shelly/git/ds/bin/WD_file_for_user", 0))
    {
        return (1);
    }
    if (!watchdog->is_WD)
    {
        if (-1 == setenv(USER_APP, (argv[0]), 0))
        {
            return (1);
        }
    }
    else
    {
        if (0 > sprintf(arg, "%d", getpid()) || -1 == setenv(WD_PID, arg, 0))
        {
            return (1);
        }
    }

    return (0);
}

static watchdog_t *CreatWD()
{
    watchdog_t *watchdog_elem = NULL;

    watchdog_elem = (watchdog_t *)malloc(sizeof(watchdog_t));

    return (watchdog_elem);
}

static int CreatSemaphors(watchdog_t *watchdog)
{
    static sem_t *sem_signal = NULL;
    static sem_t *sem_block = NULL;

    assert(watchdog);

    sem_block = sem_open(getenv(SEM_BLOCK_NAME), O_CREAT, 0666, 0);
    if (SEM_FAILED == sem_block)
    {
        return (1);
    }

    sem_signal = sem_open(getenv(SEM_SIGNAL_NAME), O_CREAT, 0666, 0);
    if (SEM_FAILED == sem_signal)
    {
        sem_close(sem_block);
        sem_unlink(getenv(SEM_BLOCK_NAME));
        return (1);
    }
    watchdog->sem_block = sem_block;
    watchdog->sem_signal = sem_signal;

    return (0);
}

/*------------- Tasks funcs ------------*/

static int SetTasks(watchdog_t *watchdog, int beats_interval, int check_ratio)
{

    if (watchdog->is_WD)
    {
        if (UidIsSame(
                SchedulerAdd(watchdog->scheduler,
                             UnblockSemaphorTask,
                             0,
                             watchdog),
                GetBadUid()))
        {
            sem_post(watchdog->sem_signal);
            return (1);
        }
    }
    if (UidIsSame(
            SchedulerAdd(watchdog->scheduler,
                         SignalTask,
                         beats_interval,
                         watchdog),
            GetBadUid()))
    {
        sem_post(watchdog->sem_signal);
        return (1);
    }

    if (UidIsSame(
            SchedulerAdd(watchdog->scheduler,
                         ViabilityTask,
                         (check_ratio * beats_interval),
                         watchdog),
            GetBadUid()))
    {
        sem_post(watchdog->sem_signal);
        return (1);
    }

    if (UidIsSame(
            SchedulerAdd(
                watchdog->scheduler,
                StopTask,
                beats_interval / 2,
                watchdog),
            GetBadUid()))
    {
        sem_post(watchdog->sem_signal);
        return (1);
    }

    return (0);
}

static int SignalTask(void *param)
{
    DEBUG_PRINT(("SignalTask is_WD: %d counter: %lu\n", ((watchdog_t *)param)->is_WD, counter));

    if (kill(((watchdog_t *)param)->signal_pid, SIGUSR1))
    {
        DEBUG_PRINT(("signal sending fail to %d user_app: %s\n", ((watchdog_t *)param)->signal_pid, getenv(USER_APP)));

        return (0);
    }

    return (2);
}

static int ViabilityTask(void *param)
{
    static pid_t pid_child_T2 = 0;
    assert(param);

    DEBUG_PRINT(("ViabilityTask to_stop: %d is_WD: %d counter: %lu \n", to_stop, ((watchdog_t *)param)->is_WD, counter));

    if (atomic_load(&to_stop))
    {
        atomic_exchange(&to_stop, 0);
        /* NOTE : meybe here try to debug the reopen of 
        the user app if the WD is realive affter the stop sigmal */
        return (0);
    }
    if (0 < atomic_load(&counter))
    {
        atomic_exchange(&counter, 0);

        DEBUG_PRINT(("ViabilityTask: counter = 0 \n"));
        DEBUG_PRINT(("pid is :%d, and ((watchdog_t *)param)->is_WD is :%d counter is: %lu\n", getpid(), ((watchdog_t *)param)->is_WD, counter));

        return (2);
    }
    if ((0 == atomic_load(&counter)))
    {
        if (((watchdog_t *)param)->is_WD) /*im WD*/
        {

            DEBUG_PRINT(("ViabilityTask user is dead %d argv[0] %s counter %lu\n", ((watchdog_t *)param)->is_WD, ((watchdog_t *)param)->argv[0], counter));

            atomic_exchange(&counter, 1);
            CleanUp(((watchdog_t *)param), CF_CLOSE_SEM_SIGNAL |
                                               CF_CLOSE_SEM_BLOCK |
                                               CF_UNLINK_SEM_SIGNAL |
                                               CF_UNLINK_SEM_BLOCK);

            ((watchdog_t *)param)->argv[0] = getenv(USER_APP);
            ((watchdog_t *)param)->is_WD = 0;
            unsetenv(WD_PID);

            execve(getenv(USER_APP), ((watchdog_t *)param)->argv, NULL);
        }
        else
        {
            DEBUG_PRINT(("ViabilityTask wd is dead  %d %s %lu\n", ((watchdog_t *)param)->is_WD, ((watchdog_t *)param)->argv[0], counter));

            kill(((watchdog_t *)param)->signal_pid, SIGTERM);
            waitpid(((watchdog_t *)param)->signal_pid, NULL, 0);
            atomic_exchange(&counter, 1);

            pid_child_T2 = fork();

            if (0 == pid_child_T2)
            {
                ((watchdog_t *)param)->argv[0] = getenv(WD_APP);
                unsetenv(WD_PID);
                execv(getenv(WD_APP), ((watchdog_t *)param)->argv);
            }

            ((watchdog_t *)param)->is_WD = 0;
            ((watchdog_t *)param)->signal_pid = pid_child_T2;
            sem_wait(((watchdog_t *)param)->sem_block); /*move to be the first?*/
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
        CleanUp(((watchdog_t *)param), CF_STOP_SCHEDULER);
        return (0);
    }
    return (2);
}

static int UnblockSemaphorTask(void *param)
{
    assert(param);

    sem_post(((watchdog_t *)param)->sem_block);

    return (0);
}

/*------------- signaling funcs ------------*/
static int InitHandler(void (*handler_func)(int num), int signal_to_send)
{
    struct sigaction handler = {0};

    /*set SIGUSER1 Handler */
    handler.sa_handler = handler_func;
    if (sigaction(signal_to_send, &handler, NULL))
    {
        return (1);
    }

    return (0);
}

static void IncramentCounterHandler(int num)
{
    (void)num;
    DEBUG_PRINT(("counter %lu is WD %d\n", counter, watchdog_g->is_WD));

    atomic_fetch_add(&counter, 1);

    return;
}

static void TernOnToStopHandler(int num)
{

    (void)num;

    DEBUG_PRINT(("TernOnToStopHandler %d %d \n", to_stop, watchdog_g->is_WD));

    atomic_exchange(&to_stop, 1);

    return;
}

/*------------- user thread funcs ------------*/

static void *UserThread(void *param)
{
    assert(param);

    DEBUG_PRINT(("%d %lu\n", ((watchdog_t *)param)->is_WD, counter));

    SchedulerRun(((watchdog_t *)param)->scheduler);
    CleanUp(((watchdog_t *)param),  CF_CLOSE_SEM_SIGNAL |
                                    CF_CLOSE_SEM_BLOCK |
                                    CF_UNLINK_SEM_SIGNAL |
                                    CF_UNLINK_SEM_BLOCK |
                                    CF_DESTROY_SCHEDULER |
                                    CF_FREE_WATCHDOG);

    return (NULL);
}

/********************************* general *********************************/
static void CleanUp(watchdog_t *watchdog, int clean_up_descriptor)
{
    assert(watchdog);

    if (clean_up_descriptor & CF_STOP_SCHEDULER)
    {
        SchedulerStop(watchdog->scheduler);
    }
    if (clean_up_descriptor & CF_CLOSE_SEM_SIGNAL)
    {
        sem_close(watchdog->sem_signal);
    }
    if (clean_up_descriptor & CF_CLOSE_SEM_BLOCK)
    {
        sem_close(watchdog->sem_block);
    }
    if (clean_up_descriptor & CF_UNLINK_SEM_SIGNAL)
    {
        sem_unlink("sem_signal");
    }
    if (clean_up_descriptor & CF_UNLINK_SEM_BLOCK)
    {
        sem_unlink("sem_block");
    }
    if (clean_up_descriptor & CF_DESTROY_SCHEDULER)
    {
        SchedulerDestroy(watchdog->scheduler);
    }
    if (clean_up_descriptor & CF_FREE_WATCHDOG)
    {
        free(watchdog);
    }

    return;
}