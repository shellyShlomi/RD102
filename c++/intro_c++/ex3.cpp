
#include <cstdio>
/* bool j;
int main()
{

    bool j1 = true;
    bool j3;
    int x = 90;
    bool i;

    x = j1;
j1 = x;
    printf("j = %d, i = %d, j1 = %d\n", j, i, j1);
    return (0);
}
 */

int main()
{

    bool b1 = true;
    bool b2;
    int i = b1;
    i = 700;

    b2 = i;
    printf("%d %lu\n",b2, sizeof(bool));
    return (0);
}
