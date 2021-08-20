
#include <iostream>
inline void foo();
void goo();

int main()
{

    foo();
    /* code */
    return 0;
}

inline void foo()
{
    std::cout << "kkk";
}

void goo()
{
    std::cout << "kkk";
}