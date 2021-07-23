
#define _POSIX_C_SOURCE 199309L
#define _POSIX_SOURCE
#include <stdlib.h> /* malloc */
#include <stdio.h>
#include <stddef.h>    /* size_t */
#include <unistd.h>    /* pid_t */
#include <stdatomic.h> /* atomic_size_t */
#include <pthread.h>   /*           thread             */
#include <semaphore.h> /*          semaphore           */
#include <fcntl.h>     /*      For O_* constants       */
#include <assert.h>
#include <string.h>
#include <signal.h> /* struct sigaction  */

#include "watch_dog.h"
#include "watchdog_iner.h"

/*------------- task funcs ------------*/

int main(int argc, char **argv)
{
    static char *app[1] = {'\0'};
    app[0] = __FILE__;
    
    (void)argc;
    
    printf("%d WD start \n", WDStart(app, atoi(getenv(CHECK_RATIO)), atoi(getenv(BEATS_INTERVAL))));
    
    WDStop();
    
    printf("end WD \n");

    return (0);
}
