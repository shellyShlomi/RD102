/*  Developer: Shelly Shlomi;									*
 *  Status:Approved;                                            *
 *  Date Of Creation:06.07.21;									*
 *  Date Of Approval:06.07.21;									*
 *  Approved By: NIR  ;                                         *	 
 *  Description: signals Ping Pong - ex 3                       */
#define _XOPEN_SOURCE
#include <stdlib.h>    /* EXIT_FAILURE */
#include <sys/types.h> /* pid_t */
#include <unistd.h>    /* pause */
#include <signal.h>    /* struct sigaction  */
#include <stdio.h>     /* printf */
#include <assert.h>
/*------------------------------ exercise func --------------------------------*/

static void Pong(char *const argv[]);
void Handler(int);
/*------------------------------ implementetion --------------------------------*/

volatile int flag = 0;

int main(int argc, char *const argv[])
{
    (void)argc;

    Pong(argv);

    return (EXIT_SUCCESS);
}

static void Pong(char *const argv[])
{
    pid_t ping_pid = {0};
    struct sigaction handler = {0};
    int status = 1;
    handler.sa_handler = Handler;

    assert(argv);

    ping_pid = (pid_t)atoi(argv[1]);
    status = sigaction(SIGUSR2, &handler, NULL);
    if (status)
    {
        return;
    }

    status = kill(ping_pid, SIGUSR1);

    while (!status)
    {
        if (flag)
        {
            printf("\033[0;35m");
            printf("PONG\n");
            printf("\033[0m");
            flag = 0;
            status = kill(ping_pid, SIGUSR1);
        }
    }

    return;
}

void Handler(int num)
{
    flag = 0;

    if (num == SIGUSR2)
    {
        flag = 1;
    }

    return;
}
