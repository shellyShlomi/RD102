#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#include <typeinfo>

class X
{
public:
    X() : m_a(4) { std::cerr << "X Ctor" << this << std::endl; }
    /* virtual */ ~X() { std::cerr << "X Dtor" << this << std::endl; }

private:
    double m_a;
};

class Y : public X
{
public:
    Y() : m_b(9) { std::cerr << "Y Ctor" << this << std::endl
                             << std::endl; }
    ~Y() { std::cerr << "Y Dtor" << this << std::endl; } //delete m_b;}

private:
    int m_b;
};

int main()
{
    X *xp[5] = {new Y};//{new X, new Y, new Y, new Y, new Y};

    for (size_t i = 0; i < 5; ++i)
    {
        delete xp[5 -1 - i];
    }

    return 0;
}

// struct X
// {
//     X()
//     {
//         std::cerr << "X Ctor" << std::endl;
//         throw std::bad_cast();
//     }
//     X(int) { std::cerr << "X Ctor (int)" << std::endl; }
//     ~X() { std::cerr << "X Dtor" << std::endl; }
// };

// struct Y
// {
//     Y():m_a(new int(5)) { std::cerr << "Y Ctor" << std::endl; }
//     ~Y() { delete m_a; std::cerr << "Y Dtor" << std::endl; }
//     int *m_a;
// };

// class L
// {
// public:
//     L() : m_x(2) { std::cerr << "L Ctor" << std::endl; }
//     ~L() { std::cerr << "L Dtor" << std::endl; }

// private:
//     Y m_y;
//     X m_x;
// };

// class M
// {
// public:
//     M() { std::cerr << "M Ctor" << std::endl; }
//     ~M() { std::cerr << "M Dtor" << std::endl; }

// private:
//     X m_x;
//     Y m_y;
// };

// class N
// {
// public:
//     N() { std::cerr << "N Ctor" << std::endl; }
//     ~N() { std::cerr << "N Dtor" << std::endl; }

// private:
//     Y m_y;
//     X m_x;
// };

// class J
// {
// public:
//     J() : m_y(new Y), m_x(new X) { std::cerr << "J Ctor" << std::endl; }
//     ~J()
//     {
//         std::cerr << "J Dtor" << std::endl;
//         delete m_x;
//         delete m_y;
//     }

// private:
//     Y *m_y;
//     X *m_x;
// };

// class K
// {
// public:
//     K() :  m_x(new X), m_y(new Y)
//     {
//         std::cerr << "K Ctor" << std::endl;
//     }
//     ~K()
//     {
//         std::cerr << "K Dtor" << std::endl;
//         delete m_x;
//         delete m_y;
//     }

// private:
//     Y *m_y;
//     X *m_x;
// };

// int main()
// {
//     try
//     {
//         K var1;
//     }
//     catch (std::exception &e)
//     {

//         std::cerr << "exception cout. what:" << e.what() << std::endl;
//     }

//     return 0;
// }