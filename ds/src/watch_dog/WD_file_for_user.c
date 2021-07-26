
#include <stdio.h>  /*           printf           */
#include <string.h> /*            atoi            */
#include <stdlib.h> /*          getenv            */

#include "watch_dog.h"
#include "watchdog_iner.h"

#define UNUSED(x) (void)(x)

/*------------- watch_dog funcs ------------*/

int main(int argc, char **argv)
{
    int status = 0;

    UNUSED(argc);

    argv[0] = __FILE__;
    status = WDStart(argv, atoi(getenv(CHECK_RATIO)), atoi(getenv(BEATS_INTERVAL)));

    printf("%d WD start \n", status);

    return (0);
}
