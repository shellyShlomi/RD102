#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#include <typeinfo>

using namespace std;

int Foo(int) throw(bad_alloc)
{
    throw bad_alloc();
    cerr << "Foo() after throw" << endl;
}

void Bar() throw(bad_cast)
{
    throw bad_cast();
    cerr << "Bar() after throw" << endl;
}

class X
{
public:
    X()
    {
        std::cout << "Ctor" << std::endl;
    }
    ~X();
    int m_a;
};

X::~X()
{
    std::cout << "Dtor" << std::endl;
    cerr << Foo(m_a) << endl;
    cerr << "X::~X() after a call to Foo" << endl;

}

void Fishi()
{
    X x1;

    Bar();
    cerr << "Fishi() after a call to Bar" << endl;

}

int main()
{
    try
    {
        Fishi();
    }

 
    catch (...)
    {
        cerr << "Out of memory! exiting.";
        exit(2);
    }

    return (0);
}