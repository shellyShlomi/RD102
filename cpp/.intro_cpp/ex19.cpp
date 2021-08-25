#include <iostream>

/* struct X
{
   explicit X();
    explicit X(int a_, int b_ = 8);
    X(const X &other_);
    X &operator=(const X &other_);
    ~X();
    int m_b;
    int m_a;
}; */
class Y
{
  //  X m_x;
    int m_i;
};
/* 
X::X() : m_a(3), m_b(4)
{
    std::cout << "this:" << this << " X default Ctor. m_a" << m_a << " m_b:" << m_b << std::endl;
}

X::X(int a_, int b_) : m_a(a_), m_b(b_)
{
    std::cout << "this:" << this << " X int int Ctor. m_a:" << m_a << "m_b:" << m_b << std::endl;
}

X::X(const X &other_) : m_a(other_.m_a), m_b(other_.m_b)
{
    std::cout << "this:" << this << " X copy Ctor. m_a:" << m_a << " m_b:" << m_b << std::endl;
}

X &X::operator=(const X &other_)
{
    m_a = other_.m_a;
    //m_b= other_.m_b;
    std::cout << "this" << this << " X assignment operator. m_a:" << m_a << " does not change m_b:" << m_b << std::endl;
    return *this;
}

X::~X()
{
    std::cout << "this:" << this << " X Dtor. m_a:" << m_a << " m_b:" << m_b << std::endl;
}
 */
int main()
{
/*     X xxxxxx1;
    X x3;
    xxxxxx1 = x3;
    X *px = new X;
    delete px;
    px = 0;
    X x2(7);
    X x4(xxxxxx1); */

    Y y1;
  //  y1.m_x.m_a = 250;
    // y1.m_x.m_b = 750;
    Y y2(y1);
    Y y3;

    y3 = y1;
    

        return 0;
}