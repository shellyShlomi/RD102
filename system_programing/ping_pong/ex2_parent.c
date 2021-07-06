/*  Developer: Shelly Shlomi;									*
 *  Status:in development;                                      *
 *  Date Of Creation:06.07.21;									*
 *  Date Of Approval:--.07.21;									*
 *  Approved By:  ;                                             *	 
 *  Description: signals Ping Pong                              */
#define _XOPEN_SOURCE
#include <stdlib.h>    /* EXIT_FAILURE */
#include <sys/types.h> /* pid_t */
#include <unistd.h>    /* pause */
#include <signal.h>    /* struct sigaction  */
#include <stdio.h>     /* printf */
/*------------------------------ exercise func --------------------------------*/

static void PingPongParent();
void Handler(int);
/*------------------------------ implementetion --------------------------------*/

volatile int flag = 0;

int main()
{
    PingPongParent();

    return (EXIT_SUCCESS);
}

static void PingPongParent()
{
    pid_t child_pid = {0};
    struct sigaction handler = {0};
    int status = 1;
    handler.sa_handler = Handler;

    status = sigaction(SIGUSR1, &handler, NULL);
    if (status)
    {
        return;
    }
    status = sigaction(SIGUSR2, &handler, NULL);
    if (status)
    {
        return;
    }

    child_pid = fork();

    if (child_pid == -1)
    {
        exit(EXIT_FAILURE);
    }
    else if (child_pid > 0)
    {
        flag = 1;
        while (flag)
        {
            printf("PING\n");
/*             pause();
            sleep(1); */
            kill(child_pid, SIGUSR1);
        }
    }
    else
    {
        execl("/home/shelly/git/system_programing/ping_pong/ex2_child", "shelly");
    }

    return;
}

void Handler(int num)
{
    (void)num;
    return;
}
