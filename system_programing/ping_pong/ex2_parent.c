/*  Developer: Shelly Shlomi;									*
 *  Status:in development;                                      *
 *  Date Of Creation:06.07.21;									*
 *  Date Of Approval:--.07.21;									*
 *  Approved By:  ;                                             *	 
 *  Description: signals Ping Pong                              */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <assert.h>


static void ForkPhas1(char *const argv[])
{
    pid_t child_pid = {0};
    int status = 1;

    assert(argv);

    while (status)
    {
        child_pid = fork();
        if (child_pid == -1)
        {
            exit(EXIT_SUCCESS);
        }
        else if (child_pid > 0)
        {
            wait(&status);
        }
        else
        {
            execv("/home/shelly/git/system_programing/simple_watchdog/dummy", argv);
            exit(EXIT_SUCCESS);
        }
        printf("PHAS 1 : returnd status :%d\n", WEXITSTATUS(status));
    }
    printf("\nend of PHAS 1\n");

    return;
}