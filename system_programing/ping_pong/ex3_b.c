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

volatile int flag = 0;

int main()
{
    PingPong();

    return (EXIT_SUCCESS);
}

static void PingPong()
{
    pid_t child_pid = {0};
    struct sigaction handler = {0};

    handler.sa_handler = Handler;

    sigaction(SIGUSR1, &handler, NULL);
    sigaction(SIGUSR2, &handler, NULL);

    child_pid = fork();
    flag = 1;
    while (flag)
    {


        if (child_pid == -1)
        {
            exit(EXIT_FAILURE);
        }
        else if (child_pid > 0)
        {

            printf("PING\n");

            kill(child_pid, SIGUSR1);
        }
        else
        {

            printf("PONG\n");

            kill(getppid(), SIGUSR2);
        }
    }
    return;
}

void Handler(int num)
{
    /*     if (SIGUSR2 == num)
 */
    {
        flag = 1;
    }
    /*     else if (SIGUSR1 == num)
    {
        flag = 0;
    } */

    return;
}
