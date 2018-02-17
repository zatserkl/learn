#include <iostream>

// see http://yosefk.com/c++fqa/ctors.html
// [10.2] Is there any difference between List x; and List x();?

using std::cout;      using std::endl;

class A {
public:
  A() {cout<< "A()" <<endl;}
};

class B {
public:
  B(int i=0) {cout<< "B(int i=0): i = " << i <<endl;}
};

main()
{
  // A a();   // NO printout! -- Basically this is declaration of function,
              // which returns A and takes no argument
  A a;        //-- Omit parentheses when call default constructor!
              //-- like: new TCanvas;

  A somefunction();   // declaration of some function which returns A and takes no arguments

  // B b();   //-- NOT a call of constructor either!
  B b;
}
