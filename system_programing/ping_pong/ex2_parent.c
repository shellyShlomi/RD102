/*  Developer: Shelly Shlomi;									*
 *  Status:Approved;                                            *
 *  Date Of Creation:06.07.21;									*
 *  Date Of Approval:06.07.21;									*
 *  Approved By: eden ;                                         *	 
 *  Description: signals Ping Pong - ex 2                       */
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
    else if (child_pid == 0)
    {
        execl("/home/shelly/git/system_programing/ping_pong/ex2_child", "shelly");
    }

    while (0 == status)
    {

        if (flag)
        {
            printf("\033[0;33m");
            printf("PING\n");
            printf("\033[0m");
            flag = 0;
            status = kill(child_pid, SIGUSR1);
        }
    }

    return;
}

void Handler(int num)
{
    if (num == SIGUSR2)
    {
        flag = 1;
    }

    return;
}
