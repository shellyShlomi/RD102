#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#include <typeinfo>
#include <typeinfo>
#include <cstddef>


class Base {
public:

  virtual ~Base() {std::cout << "Base Dtor " << this << std::endl;};
   Base(int d_ = 0) : r(0),i(d_) {std::cout << "Base Ctor " << this << std::endl;};
  protected:
   virtual void foo(){};
  int i;
  private:
    int r;    void g(Base& b, class Derived& d);


};
 
class Derived : public Base {
public:
   Derived(int d_ = 0) {std::cout << "Derived Ctor " << this << std::endl;}
   ~Derived() {std::cout << "Derived Dtor " << this << std::endl;}
    // void foo(){++i;}
  void f(Base& b, Derived& d) { 
    ++d.i;                      // OK: the type of d is Derived
    ++i; 
//  ++b.i;                     // error: can't access a protected member through
    }                   // OK: the type of the implied '*this' is Derived
    private:      
                                // other derived classes, like a hypothetical
                                // Derived2, base implementation)
 
};
 
void Base::g(Base& b, Derived& d) { // member function of Base
  ++i; 
  ++r;                             // OK
  ++b.i;    
  foo();
  b.foo();                        // OK
//   ++d.i;                            // OK
}
 
void x(Base& b, Derived& d) { // non-member non-friend
//++b.i;                      // error: no access from non-member
//++d.i;      
}



int main()
{
   
    // Base *b = new Derived;// = *y1;
    Derived d;// = *y1;
    Base b1;
    // b1.foo();
    // d.foo();
// d.i = 0;
// delete b;

    return 0;
}