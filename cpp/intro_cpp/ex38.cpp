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
    X(double d_) : m_a(d_) {}
    // X &operator=(const X &other_) {};
    virtual ~X() {};

private:
    double m_a;
};

class Y : public X
{
public:
    Y(double d_, int i_) : X(d_), m_b(i_) {}

private:
    int m_b;
};

int main()
{
    Y y1(0.0, 9), y2(15.2, 6);
    Y y3(0.0, 0), y4(14.2, 5);

    X &x1 = y1;
    X &x2 = y2;

    x1 = x2;
    y3 = y4;

    return 0;
}