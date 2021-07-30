#include <stdio.h>
#include <sys/wait.h>
#include "watchdog.h"
#include <unistd.h>

void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod);

int main(int argc, char *argv[])
{
    size_t i = 0;

    printf("in user:\n");
    StartWD(argv, 2, 5);
    /* towerOfHanoi(40, 'a', 'b', 'c'); */
    for (i = 0; i < 30; ++i)
    {
        printf("%d 1\n", i);
        sleep(1);

        if (20 == i)
        {
            StopWD();
        }
    }

    StartWD(argv, 2, 5);

    for (i = 0; i < 20; ++i)
    {
        printf("%d 2 \n", i);
        sleep(1);
        if (i == 15)
        {
            StopWD();
        }
    }

    return 0;
}

void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod)
{
    if (n == 1)
    {
        /* printf("Move disk 1 from rod %c to rod %c\n" ,from_rod ,to_rod); */
        return;
    }
    towerOfHanoi(n - 1, from_rod, aux_rod, to_rod);
    /* printf("Move disk 1 from rod %c to rod %c\n" ,from_rod ,to_rod); */
    towerOfHanoi(n - 1, aux_rod, to_rod, from_rod);
}

