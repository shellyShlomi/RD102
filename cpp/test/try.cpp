// #include <iostream>
// using namespace std;
// class Base
// {
// public:
//    Base(int i) : m_i(i), m_iptr(&m_i) { cout << "Ctor Base" << endl; }
//    virtual void foo() { cout << *(m_iptr) << endl; }
//    virtual void bar() { cout << m_i << endl; }

// protected:
//    virtual ~Base() = 0;

// private:
//    int m_i;
//    int *m_iptr;
// };

// inline Base::~Base() { cout << "Dtor Base" << endl; }

// class Derived : public Base
// {
// public:
//    Derived(int i, char c) : Base(i), m_c(c), m_c2(c) { cout << "Ctor Derived" << endl; }
//    void bar()
//    {
//       foo();
//       Base::foo();
//    }
//    ~Derived() { cout << "Dtor Derived" << endl; };

// private:
//    void foo() { cout << m_c << endl; }
//    char m_c, m_c2;
// };

// class OtherDerived : public Base
// {
// };

// int main(int argc, char **argv)
// {
//    Derived d1(5, 'x');
//    Derived d2(3, 'w');

//    Base *b1 = &d1;
//    b1->foo();
//    b1->bar();

//    Base *b2 = &d2;
//    *b2 = *b1;
//    b2->foo();
//    d2.bar();

//    return 0;
// }

// 11010011 << 4
//       |
//       V
// 00110000

// 11010011 >> 4
//       |
//       V
// 00110000

#include <bitset>
#include <iostream>

int main()
{
   std::bitset<15> b{0b011101111010011};
   std::cout << b << " (initial value) ";
   std::cout  << " b <<= 5\n";
   b <<= 5;

   std::cout << b << "\n";
   std::bitset<15> b1;
   std::cout << b1.set(3) << " (initial value) ";
   std::cout <<  " b <<= 5\n";
   b1 <<= 5;
   // for (; b.any(); b <<= 1)
   // {

   //    std::cout << b << '\n';
   // }
   std::cout << b1 << '\n';

   return 0;//sdasd
}//sdasd