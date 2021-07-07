/*  Developer: Shelly Shlomi;									*
 *  Status:Approved;                                            *
 *  Date Of Creation:06.07.21;									*
 *  Date Of Approval:06.07.21;									*
 *  Approved By: NIR  ;                                         *	 
 *  Description: signals Ping Pong - ex 3                       */
#define _POSIX_C_SOURCE 199309L
#define _POSIX_SOURCE
#include <stdlib.h>    /* EXIT_FAILURE */
#include <sys/types.h> /* pid_t */
#include <unistd.h>    /* pause */
#include <signal.h>    /* struct sigaction  */
#include <stdio.h>     /* printf */
/*------------------------------ exercise func --------------------------------*/

static void Ping();
void Handler(int num, siginfo_t *pinfo, void *data);
/*------------------------------ implementetion --------------------------------*/

volatile int flag = 0;
volatile pid_t glob = {0};

int main()
{
    Ping();

    return (EXIT_SUCCESS);
}

static void Ping()
{
    struct sigaction handler = {0};
    int status = 1;
    handler.sa_flags = SA_SIGINFO;
    handler.sa_sigaction = Handler;

    status = sigaction(SIGUSR1, &handler, NULL);
    if (status)
    {
        return;
    }
    else
    {
        printf("%d\n", getpid());
        while (!flag)
        {
            ;
        }
    }

    while (!status)
    {
        if (flag)
        {
            printf("\033[0;33m");
            printf("PING\n");
            printf("\033[0m");
            flag = 0;
            status = kill(glob, SIGUSR2);
        }
    }

    return;
}

void Handler(int num, siginfo_t *pinfo, void *data)
{
    (void)data;
    flag = 0;

    if (num == SIGUSR1)
    {
        glob = pinfo->si_pid;
        flag = 1;
    }

    return;
}
