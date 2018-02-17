////////////////////////
//
// same field in class
//
////////////////////////

#include <iostream>

using std::cout;      using std::endl;

class A {
public:
  int field_;
  A() {
    field_ = 1;
    cout<< "constructor A: set field_ to " << field_ <<endl;
  }
};

class B: public A {
public:
  int field_;
  B(): A() {
    field_ = 2;
    cout<< "constructor B: set field_ to " << field_ <<endl;
  }
};

main()
{
  B b;
  cout<< "b.field_ = " << b.field_ <<endl;

  cout<< "b.A::field_ = " << b.A::field_ <<endl;
}
