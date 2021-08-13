#include <iostream>
#include <cstdio>
#include <typeinfo>
void Foo(const double &x);
void Bar(double &x);

int main()
{
    /*     double num1 = 9;
 */
    int num = 9;

    Foo(num);
    std::cout << "num value:" << num << ", num pointer: " << &num << std::endl;
    std::cout << std::endl;

    Bar(reinterpret_cast<double &>(num));
    std::cout << "num value:" << num << ", num pointer: " << &num << std::endl;
    std::cout << std::endl;

    /*   Foo(num1);
    std::cout << "num value:" << num1 << ", num pointer: " << &num1 << std::endl;
    std::cout << std::endl;

    Bar((num1));
    std::cout << "num value:" << num1 << ", num pointer: " << &num1 << std::endl;
    std::cout << std::endl;
 */
    return (0);
}

void Foo(const double &x)
{
    int y;
    double *ptrx = (double *)&x;
    

    std::cout << "Foo :var value:" << x << sizeof(x) << ", var pointer: " << &x << std::endl;
    std::cout << std::endl;

    std::cout << "Foo :&y local :" << &y << " " << (double *)((char *)ptrx - 4) << std::endl;
    std::cout << std::endl;

    std::cout << "Foo : local :" << (ptrx) << " " << *(ptrx) << std::endl;
    std::cout << std::endl;

    std::cout << "Foo : local :" << (int *)((char *)ptrx - 4) << " " << *(int *)((char *)ptrx - 4) << std::endl;
    std::cout << std::endl;

    std::cout << typeid(x).name() << std::endl;
    std::cout << std::endl;
}

void Bar(double &x)
{
    std::cout << "Bar :var value:" << x << ", var pointer: " << &x << std::endl;
}