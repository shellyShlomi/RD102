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

static void PingPong();
void Handler(int);
/*------------------------------ implementetion --------------------------------*/

volatile int flag = 1;

int main()
{
    PingPong();

    return (EXIT_SUCCESS);
}

static void PingPong()
{
    pid_t child_pid = {0};
    struct sigaction handler = {0};
    int status = 0;
    handler.sa_handler = Handler;

    sigaction(SIGUSR1, &handler, NULL);
    sigaction(SIGUSR2, &handler, NULL);

    child_pid = fork();

    while (!status)
    {
        if (child_pid == -1)
        {
            exit(EXIT_FAILURE);
        }
        else if (child_pid > 0)
        {
            if (flag == 1)
            {
                flag = 0;
                status = kill(child_pid, SIGUSR1);
                printf("\033[0;33m");
                printf("PING\n");
                printf("\033[0m");
            }
        }
        else
        {
            if (flag == 1)
            {
                flag = 0;
                status = kill(getppid(), SIGUSR2);
                printf("\033[0;35m");
                printf("PONG\n");
                printf("\033[0m");
            }
        }
    }
    return;
}

void Handler(int num)
{
    (void)num;

    flag = 1;

    return;
}
