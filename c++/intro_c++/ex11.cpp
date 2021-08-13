#include <iostream>

int Foo(float x);
char Foo(char x);
float Foo(int x);
int Foo(float y, int x);

int main()
{
    int x = 9;
    std::cout << Foo(1.5,(unsigned char)'1') << std::endl;
    return (0);

}
int Foo(float x)
{
    return 2;
}

char Foo(char x)
{
    return '1';
}

int Foo(float y, int x)
{
    return 4;
}