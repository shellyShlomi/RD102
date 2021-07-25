

#include <stdio.h>
#include <unistd.h>

#include "watch_dog.h"

int main(int argc, char **argv)
{
    size_t i = 0;
    (void)argc;
   printf("WDStart %d\n", WDStart(argv, 5, 1));
/* 
    for (i = 0; i < 20; i++)
    {
        sleep(1);
        printf(" %lu \n", i);
    }
    WDStop(); 
    printf("WDStart %d\n", WDStart(argv, 5, 1)); */

    for (i = 0; i < 10; i++)
    {
         printf(" %lu \n", i);

        if (i == 5)
        {
            WDStop();
        }
    }
    return (0);
}