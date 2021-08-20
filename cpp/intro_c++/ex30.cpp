

#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>

using namespace std;

class X
{
public:
    X() { cout << "hello world!!" << endl; }
    ~X() { cout << "goodbye world!!" << endl; }
};

class BadDog : public runtime_error
{
public:
    BadDog(const string &s_ = "This is a bad dog\n") : runtime_error(s_) {}
};

void Fifi() //throw(bad_exception)
{
    cerr << "Fifi() befor throw" << endl;
    throw BadDog /* runtime_error */ ("bad pup\n");
    // throw std::exception();
    cerr << "Fifi() after throw" << endl;
    cerr << "Fifi() after throw" << endl;
}
void Foo() throw(bad_exception) // unhandled exception: calls terminate handler
{
    X x1;
    Fifi();
    cerr << "Foo() after Fifi()\n"
         << endl;
}

void Bar()
{
    Foo();
    cerr << "Bar() after Foo()\n"
         << endl;
}

void ggg()
{
    cerr << "ggg() \n"
         << endl;
    // abort() ;
    throw;
}

int main()
{
    // std::set_unexpected(ggg);
    int *x = new int;
    // std::set_terminate(ggg);
    try
    {
        Bar();
    }
    catch (BadDog &b)
    {
        cerr << "Bad dog exception: \n"
             << b.what();
        return (3);
    }
    catch (exception &r)
    {
        cerr << "unknown exception: \n"
             << r.what();
        return (4);
    }

    catch (...)
    {
        cerr << "Out of memory!.\n";
        return (2);
    }

    
    
    delete x;
    return 0;
}
