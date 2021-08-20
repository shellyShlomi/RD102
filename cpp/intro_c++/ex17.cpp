#include <iostream>
#include <cstdio>

int i = 8;
int &ip = i;

struct boobs
{
    double x;
    double y;
};

int main()
{
    ip = 9;
    std::cout << i << std::endl;

    struct boobs x = {1.4, 2.7};
    struct boobs &xp = x;
    
    double f = 8.1f;
    double &ipf = f;
    ipf = 9.1f;
    std::cout << f << std::endl;

    printf("var address: %p, ref pointer: %p\n", &i, &ip);
    printf("var address: %p, ref pointer: %p\n", &f, &ipf);
    printf("var address: %p, ref pointer: %p\n", &x, &xp);

    printf("var size: %lu, ref size: %lu\n", sizeof(i), sizeof(ip));
    printf("var size: %lu, ref size: %lu\n", sizeof(f), sizeof(ipf));
    printf("var size: %lu, ref size: %lu\n", sizeof(x), sizeof(xp));

    return (0);
}
