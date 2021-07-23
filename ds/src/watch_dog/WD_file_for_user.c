
#include <stdio.h>  /*           printf           */
#include <string.h> /*            atoi            */
#include <stdlib.h> /*          getenv            */

#include "watch_dog.h"
#include "watchdog_iner.h"

/*------------- task funcs ------------*/

int main()
{
    static char *app[1] = {'\0'};
    int status = 0;
    app[0] = __FILE__;
    status = WDStart(app, atoi(getenv(CHECK_RATIO)), atoi(getenv(BEATS_INTERVAL)));

    printf("%d WD start \n", status);

    WDStop();

    return (0);
}
