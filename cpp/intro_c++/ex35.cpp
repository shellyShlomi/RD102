#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#include <typeinfo>

struct X
{
    X() 
    {
        std::cerr << "X Ctor" << std::endl;
        throw std::bad_cast();
    }
    X(int) { std::cerr << "X Ctor (int)" << std::endl; }
    ~X() { std::cerr << "X Dtor" << std::endl; }
};

struct Y 
{
    Y():m_a(new int(5)) { std::cerr << "Y Ctor" << std::endl; }
    ~Y() { delete m_a; std::cerr << "Y Dtor" << std::endl; }
    int *m_a;
};

class L
{
public:
    L() : m_x(2) { std::cerr << "L Ctor" << std::endl; }
    ~L() { std::cerr << "L Dtor" << std::endl; }

private:
    Y m_y;
    X m_x;
};

class M
{
public:
    M() { std::cerr << "M Ctor" << std::endl; }
    ~M() { std::cerr << "M Dtor" << std::endl; }

private:
    X m_x;
    Y m_y;
};

class N
{
public:
    N() { std::cerr << "N Ctor" << std::endl; }
    ~N() { std::cerr << "N Dtor" << std::endl; }

private:
    Y m_y;
    X m_x;
};

class J
{
public:
    J() : m_y(new Y), m_x(new X) { std::cerr << "J Ctor" << std::endl; }
    ~J()
    {
        std::cerr << "J Dtor" << std::endl;
        delete m_x;
        delete m_y;
    }

private:
    Y *m_y;
    X *m_x;
};

class K
{
public:
    K() :  m_x(new X), m_y(new Y)
    {
        std::cerr << "K Ctor" << std::endl;
       
        
    }
    ~K()
    {
        std::cerr << "K Dtor" << std::endl;
        delete m_x;
        delete m_y;
    }

private:
    X *m_x;
    Y *m_y;
};

int main()
{
    try
    {
        M var1;
    }
    catch (std::exception &e)
    {

        std::cerr << "exception cout. what:" << e.what() << std::endl;
    }

    return 0;
}