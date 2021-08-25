#include <iostream>
#include <typeinfo>
struct X
{
    X(int a_, int b_);

    void Inc();
    void Dec();

    int m_a;
    int m_b;
};

X::X(int a_, int b_) : m_a(a_), m_b(b_)
{
    //std::cout << "this:" << this << " X Ctor. m_a" << m_a << " m_b:" << m_b << std::endl;
}

void X::Inc()
{
    ++m_a;
    ++m_b;
    std::cout << "X::Inc():" << " "<< "this:" << this << std::endl;
}

void X::Dec()
{
    --m_a;
    --m_b;
    std::cout << typeid(this).name()<< " "<<"this:" << this <<  std::endl;
}

void Inc()
{
    //std::cout << "Inc:" << std::endl;
}

int main()
{
     X x1(7, -55);
    X x2(x1);
    Inc();
    x1.Inc();
    x1.Inc();
    x2.Dec();
    std::cout << &(x1) << std::endl;

    return 0;
}