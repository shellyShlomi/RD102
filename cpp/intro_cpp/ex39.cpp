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
    X(double d_) : m_a(d_) {std::cout << "X Ctor " << this << std::endl;};
    virtual ~X(){std::cout << "X Dtor " << this << std::endl;};
    virtual void  D(){std::cout << "D at X " << this << std::endl;};

private:
    double m_a;
};

class Y : public X
{
public:

    Y(double d_ = 0, int i_ = 0) : X(d_), m_b(i_) {std::cout << "Y Ctor " << this << std::endl;};
    ~Y() { std::cout << "Y Dtor " << this << std::endl; } //delete m_b;}
     void  D(){std::cout << "D at Y " << this << std::endl;};


private:
    int m_b;
};

int main()
{
    Y *y1 = new Y;
    X *y2 = new Y;
    X y3 = *y2;

    y1->D();
    y2->D();
    y3.D();
    y1->X::D();
    y2->X::D();
    y3.X::D();



delete y1;
delete y2;

    return 0;
}