

#include <stdlib.h> /* malloc */
#include <assert.h>
#include <stdio.h>

#include "watch_dog.h"

int main()
{
    size_t i = 0;
    printf("WDStart %d\n", WDStart(5, 1));

    for (i = 0; i < 300; i++)
    {
        sleep(1);
        printf("%lu\n", i);
    }

    return (0);
}