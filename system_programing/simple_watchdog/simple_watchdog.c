
/*  Developer: Shelly Shlomi;									*
 *  Status:Approved;                                            *
 *  Date Of Creation:05.07.21;									*
 *  Date Of Approval:05.07.21;									*
 *  Approved By: sagi ;                                         *	 
 *  Description: a simply watchdog                              */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <assert.h>

#define UNUESD(x) ((void)(x))
/*------------------------------ exercise func --------------------------------*/

static void ForkPhas1(char *const argv[]);
static void SystemPhas2(char *const argv[]);

/*------------------------------ implementetion --------------------------------*/

int main(int argc, char *const argv[])
{
    UNUESD(argc);

    ForkPhas1(argv);
    SystemPhas2(argv);

    return (0);
}

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

static void SystemPhas2(char *const argv[])
{
    int status = 0;

    assert(argv);

    while (((status = system(argv[1])),
            (!WIFSIGNALED(status) &&
             (WTERMSIG(status) != SIGINT && WTERMSIG(status) != SIGQUIT)) &&
                WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_FAILURE)))
    {
        printf("returnd status :%d\n", WEXITSTATUS(status));
    }

    if (SIGINT == WTERMSIG(status))
    {
        printf("process was SIGINT\n");
    }
    if (SIGQUIT == WTERMSIG(status))
    {
        printf("process was SIGQUIT\n");
    }
    printf("PHAS 2 : returnd status :%d\n", WEXITSTATUS(status));

    printf("\nend of PHAS 2\n");

    return;
}