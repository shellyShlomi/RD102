#include <iostream>
#include <memory>
 
struct Foo
{
   Foo(int in) : a(in) {
      std::cout << "ctor" << '\n';
      

   }
      ~Foo() {
      std::cout << "dtor" << '\n';
      

   }
   void print() const
   {
      std::cout << "a = " << a << '\n';
   }
   int a;
};
 
int main()
{
   // Foo x(1);
   // Foo *p = &x;
   // p->print();
   auto ptr = std::make_shared<Foo>(10);
   // ptr->print();
   (*ptr).print();
   return 0;
}