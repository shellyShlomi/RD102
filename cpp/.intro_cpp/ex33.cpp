

#include <iostream>
#include <exception>
#include <stdexcept>

struct Foo
{
    int count = std::uncaught_exception();
    ~Foo()
    {
        std::cout << (count == std::uncaught_exception()
                          ? "~Foo() called normally\n"
                          : "~Foo() called during stack unwinding\n");
    }
};
int main()
try
{
    Foo f;
    // try {
    //     Foo f;
    //     std::cout << "Exception thrown\n";
    //     throw std::runtime_error("test exception");
    //}
}
catch (const std::exception &e)
{
    std::cout << "Exception caught: " << e.what() << '\n';
}