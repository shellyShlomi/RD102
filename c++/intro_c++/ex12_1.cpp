#include <iostream>

namespace useless
{
    unsigned int g_wasteful[400];
    extern int g_notthere;
    void Foo()
    {
        std::cout << "useless" << std::endl;
    }


    namespace wasteoftyme
    {
        void Foo()
        {
            std::cout << "wastteoftyme" << std::endl;
        }
    }
    int x;

}

namespace stupid
{
    void Foo()
    {
        std::cout << "stupid" << std::endl;
    }
    void Bar(){}
    void DoNothing(unsigned int)
    {
        std::cout << "do nothing stupid" << std::endl;
    }
    int x;
}
using namespace useless;

void DoStuff()
{
    int x;
    stupid::Bar();
    Foo(); 
     using stupid::x;
     Foo();
}
 namespace useless
{
    void DoNothing(int)
    {
        std::cout << "do nithing useless" << std::endl;
    }
}

void Foo()
{
    std::cout << "global" << std::endl;
}

using namespace stupid;


namespace comeon = useless::wasteoftyme;

void DoMoreStuff()
{
    comeon::Foo();
    ::Foo();
    Bar();
}

namespace useless
{
    void DoUselessStuff()
    {
        DoNothing(g_wasteful[3] + 1);
    }
}

int main()
{
    DoStuff();
    DoMoreStuff();

    /* code */
    return 0;
}
