#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#include <typeinfo>

using namespace std;

int Foo(int) throw(bad_alloc);
void Bar() throw(bad_cast);

class X
{
public:
    X() { cout << "in ctor" << endl; };
    ~X()
    {
        cout << "start of dtor" << endl;
        cerr << Foo(m_a) << endl;
        cout << "end of dtor" << endl;

    };

private:
    int m_a;
};

int Foo(int) throw(bad_alloc)
{
    throw(bad_alloc());
    return (0);
}

void Bar() throw(bad_cast)
{
    int x = 0;
    throw(bad_cast());
}

void Fishi()
{
    X x1;
    try
    {
        Bar();
    }
    catch (...)
    {
        cerr << "hello" << endl;
    }
}

int main()
{
    // try
    {
        Fishi();
    }
    // catch(...)
    // {
    //     cerr << "hello" << endl;
    // }

    return (0);
}
