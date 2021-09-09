#ifndef __UTILITIES_HPP__
#define __UTILITIES_HPP__

namespace utilities
{
    const static int BASE(1);
    const static int DERIVED(2);

    class Base
    {
    public:
        Base();
        virtual ~Base();
        virtual int Display();

    private:
        int x;
    };

    class Derived : public Base
    {
    public:
        Derived();
        ~Derived();
        int Display();

    private:
        int y;
    };

    Base::Base() : x(BASE)
    {
        //empty
    }

    Base::~Base()
    {
        x = 0;
    }
    int Base::Display()
    {
        return (x);
    }

    Derived::Derived() : y(DERIVED)
    {
        //empty
    }

    Derived::~Derived()
    {
        y = 0;
    }

    int Derived::Display()
    {
        return (y);
    }
    const static int FIRST(1);
    const static int SECOND(2);
} //utilities

#endif /* __UTILITIES_HPP__ */
