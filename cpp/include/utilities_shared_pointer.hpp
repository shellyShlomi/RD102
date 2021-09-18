#ifndef __UTILITIES_SHARED_PTR_SHELLY__
#define __UTILITIES_SHARED_PTR_SHELLY__

namespace utilities
{
    namespace utilities_shared_ptr_shelly
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

        const static int BASE2(3);
        const static int DERIVED2(4);

        class Base2
        {
        public:
            Base2();
            virtual ~Base2();
            virtual int Display();

        private:
            int z;
        };

        Base2::Base2() : z(BASE2)
        {
            //empty
        }

        Base2::~Base2()
        {
            z = 0;
        }

        int Base2::Display()
        {
            return (z);
        }

        class Derived2 : public Base, public Base2
        {
        public:
            Derived2();
            ~Derived2();
            int Display();

        private:
            int y;
        };

        Derived2::Derived2() : y(DERIVED2)
        {
            //empty
        }

        Derived2::~Derived2()
        {
            y = 0;
        }

        int Derived2::Display()
        {
            return (y);
        }

        const static int FIRST(1);
        const static int SECOND(2);
    } //utilities_shared_ptr_shelly



} //utilities

#endif /* __UTILITIES_SHARED_PTR_SHELLY__ */
