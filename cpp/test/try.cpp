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
#include "bitarray.hpp"
#include "bitarray_detail.hpp"

#include "tools.h"
using namespace ilrd;
namespace ilrd
{
   namespace detail
   {
static void TestCount()
{
   BitArray<8> b1;

   bool arr_test[] = {true, false, true, true, false, false, false, true, false, true, true, false};
   size_t n_true = 0;
   size_t n_false = 0;

   for (size_t i = 0; i < 8; ++i)
   {
      b1[i] = arr_test[i];

      if (arr_test[i])
      {
         ++n_true;
      }
      else
      {
         ++n_false;
      }
      Valid(b1[i] == arr_test[i], "b1\n", __LINE__);
   }

   Valid((n_true == b1.Count()), "", __LINE__);
}

static void TestToString()
{
   BitArray<8> b1;

   char message[detail::BYTE_MAX] = {'\0'};

   strcpy(message, "fail ToString");
   b1.SetAll();
   ValidStrEqual(b1.ToString().c_str(), "11111111", message, __LINE__);

   strcpy(message, "fail ToString b1.SetBit(3)");
   b1.SetBit(3, false);
   ValidStrEqual(b1.ToString().c_str(), "11110111", message, __LINE__);

   return;
}

      int TEST()
      {
         TestToString();
         TestCount();
         return 0;
      }
   } // detail

} // ilrd
  // 11010011 << 4
  //       |
  //       V
  // 00110000

// 11010011 >> 4
//       |
//       V
// 00110000

// #include <bitset>
// #include <iostream>

// int main()
// {
//    std::bitset<15> b{0b011101111010011};
//    std::cout << b << " (initial value) ";
//    std::cout  << " b <<= 5\n";
//    b <<= 5;

//    std::cout << b << "\n";
//    std::bitset<15> b1;
//    std::cout << b1.set(3) << " (initial value) ";
//    std::cout <<  " b <<= 5\n";
//    b1 <<= 5;
//    // for (; b.any(); b <<= 1)
//    // {

//    //    std::cout << b << '\n';
//    // }
//    std::cout << b1 << '\n';

//    return 0;//sdasd
// }//sdasd