

#include <stdlib.h> /* malloc */
#include <assert.h>
#include <stdio.h>

#include "watch_dog.h"

int main(int argc, char **argv)
{
    size_t i = 0;
    (void)argc;
    printf("WDStart %d\n", WDStart(argv, 5, 1));

    for (i = 0; i < 100; i++)
    {
        sleep(1);
        printf(" %lu \n", i);

        if (i == 30)
        {
            WDStop();
        }
    }
    return (0);
}