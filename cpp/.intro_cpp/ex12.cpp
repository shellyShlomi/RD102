namespace useless
{
    unsigned int g_wasteful[400];
    extern int g_notthere;
    void Foo(){}


    namespace wasteoftyme
    {
        void Foo(){}
    }
}

namespace stupid
{
    void Foo(){}
    void Bar(){}
    void DoNothing(unsigned int){}
}

namespace useless
{
    void DoNothing(int){}
}

using namespace useless;

void DoStuff()
{
    stupid::Bar();
    //Foo();
    using stupid::Foo;
    Foo();
    DoNothing(g_wasteful[3] + 1);
}

void Foo(){}

using namespace stupid;

namespace comeon = useless::wasteoftyme;

void DoMoreStuff()
{
    comeon::Foo();
    comeon::Foo();
    Bar();
    DoNothing(g_wasteful[3] + 1);
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
    /* code */
    return 0;
}

Message @Maor Seri