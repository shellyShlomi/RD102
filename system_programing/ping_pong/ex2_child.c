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

static void PingPongChild();
void Handler(int);
/*------------------------------ implementetion --------------------------------*/
volatile int flag = 0;

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
    status = sigaction(SIGUSR2, &handler, NULL);
    if (status)
    {
        return;
    }
    
    while (0 == status)
    {
        printf("PONG\n");
        status = kill(getppid(), SIGUSR2);
        pause();
        sleep(1);
    }

    return;
}

void Handler(int num)
{
    (void)num;
    return;
}
