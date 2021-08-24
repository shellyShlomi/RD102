#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#include <typeinfo>
#include <typeinfo>
#include <cstddef>
class X
{
public:
    X() : m_a(4) { std::cout << "X Ctor" << this << std::endl; }
    virtual ~X() { std::cout << "X Dtor" << this << std::endl; }

    double m_a;
private:
};

class Y : public X
{
public:
    Y(int b = 0) : m_b(b) { std::cout << "Y Ctor" << this << std::endl
                             << std::endl; }
    ~Y() { std::cout << "Y Dtor" << this << std::endl; } //delete m_b;}

    int m_b;
private:
};

// void Foo(X *x)
// {
//     std::cout << "Foo x " << sizeof(x) << std::endl;

//     std::cout << "Foo" << &x << std::endl;
// }
// int main()
// {
//     // X *xp[5] = {new X, new Y, new Y, new Y, new Y};
//     // X *xp= new Y[5];

//     Y *y1 = new Y;
//     std::cout << "y1 " << &y1 << std::endl;
//     std::cout << "y1 " << y1 << std::endl;
//     std::cout << "y1 " << sizeof(y1) << std::endl;
//     std::cout << "X " << sizeof(X) << std::endl;

//     Foo(y1);
//     // for (size_t i = 0; i < 5; ++i)
//     // {
//     //     delete xp[5 - 1 - i];
//     // }
//     delete y1 ;

//     return 0;
// }

 void Foo(X x)
{
    
    std::cout << " x is : " << sizeof(x) << std::endl;
    std::cout << " x is : "<< std::endl;
}

int main()
{
    Y y1(15);
        std::cout << "y1 " << sizeof(y1) << std::endl;
    std::cout << "X " << sizeof(X) << std::endl;

    Foo(y1);

    return 0;
}