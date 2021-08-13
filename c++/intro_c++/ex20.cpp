#include <iostream>

struct X
{

    int m_b;
    int m_a;
};


int main()
{
    X xxxxxx1;
    X x3;
    xxxxxx1 = x3;
    X *px = new X;
    delete px;
    px = 0;
    X x4(xxxxxx1);

    std::cout << xxxxxx1.m_a<< xxxxxx1.m_b<< std::endl;
  
    return 0;
}