
#include <stdio.h>
#include <unistd.h>

#include "watch_dog.h"

static void Reset();
static void Cyan();
static void Purple(); 

int main(int argc, char **argv)
{
    size_t i = 0;
    (void)argc;

    printf("WDStart %d\n", WDStart(argv, 5, 2));
 
       for (i = 0; i < 30; i++)
    {
        sleep(1);
        Purple();
        printf("user app data1 %lu \n", i);
        Reset();
    }

    WDStop(); 

    printf("WDStart %d\n", WDStart(argv, 5, 2));

    for (i = 0; i < 50; i++)
    {

        Cyan();
        printf("user app data2 %lu \n", i);
        Reset();
        sleep(1);
        if (i == 20)
        {
            WDStop();
            printf("WDStop\n");
        }
    }
    return (0);
}

static void Cyan()
{
    printf("\033[0;36m");
}

 static void Purple()
{
    printf("\033[0;35m");
}
 
static void Reset()
{
    printf("\033[0m");
}
