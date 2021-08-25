// set_unexpected example
#include <iostream>  // std::cerr
#include <exception> // std::set_unexpected
#include <cstdlib>        // std::abort
void myunexpected()
{
    std::cerr << "unexpected called\n";
    throw 0; // throws int (in exception-specification)
}

void myfunction() throw(int)
{
    throw 'x'; // throws char (not in exception-specification)
}


void myterminate () {
  std::cerr << "terminate handler called\n";
  abort();  // forces abnormal termination
}

int main(void)
{
    std::set_unexpected(myunexpected);
    std::set_terminate(myterminate);

    try
    {
        myfunction();
    }
    catch (int)
    {
        std::cerr << "caught int\n";
    }
    catch (...)
    {
        std::cerr << "caught some other exception type\n";
    }
    return 0;
}