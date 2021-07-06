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

static void PingPongChild();
void Handler(int);
/*------------------------------ implementetion --------------------------------*/
volatile int flag = 1;

int main()
{
    PingPongChild();

    return (EXIT_SUCCESS);
}

static void PingPongChild()
{
    struct sigaction handler = {0};
    int status = 1;

    handler.sa_handler = Handler;

    status = sigaction(SIGUSR1, &handler, NULL);
    if (status)
    {
        return;
    }
    while (0 == status)
    {
        if (flag)
        {
            printf("\033[0;35m");
            printf("PONG\n");
            printf("\033[0m");

            flag = 0;
            status = kill(getppid(), SIGUSR2);
        }
    }

    return;
}

void Handler(int num)
{
    if (num == SIGUSR1)
    {
        flag = 1;
    }

    return;
}
