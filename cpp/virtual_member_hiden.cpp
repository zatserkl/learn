/*
g++ -Wall -Woverloaded-virtual virtual_member_hiden.cpp
virtual_member_hiden.cpp:22:18: warning: ‘virtual void intermediate::exception(const char*)’ was hidden [-Woverloaded-virtual]
virtual_member_hiden.cpp:32:18: warning:   by ‘virtual void derived::exception()’ [-Woverloaded-virtual]
*/

#include <iostream>

using std::cout;    using std::endl;

class Base {
public:
  virtual void exception() = 0;
  virtual void exception(const char*) = 0;
};

class Intermediate : public Base {
public:
  virtual void exception() {
    cout << "Intermediate::exception: unknown exception" << endl;
  }

  virtual void exception(const char* msg) {
    cout << "Intermediate::exception(const char*): exception: " << msg << endl;
  }
};

class Derived : public Intermediate {
public:
  using Intermediate::exception;    //-- solution to GEANT4 problem with warning on geant4/work/B2/B2b/include/B2bChamberParameterisation.hh

  virtual void exception() { 
    //Intermediate::exception("Derived::exception: unknown exception");   // the same effect
    cout<< "Derived::exception: unknown exception" <<endl;
  }
};

int main()
{
  Derived derived;

  derived.exception();              // w/o parameters, defined in the Derived: works anyway

  derived.exception("some text");   // this function (with const char*) is not available
  /*
     If I 
     1) uncomment derived.exception("some text")
     2) comment using Intermediate::exception; in the Derived, I will get compiler messages:

     The reason from my point of view is:
     class Derived overloaded method with the name exception. In spite of it overloaded just method 
     w/o parameters, the method with parameters got lost too.

     learn$ g++ -Wall -Woverloaded-virtual virtual_member_hiden.cpp
     virtual_member_hiden.cpp:23:16: warning: ‘virtual void Intermediate::exception(const char*)’ was hidden [-Woverloaded-virtual]
     virtual_member_hiden.cpp:30:16: warning:   by ‘virtual void Derived::exception()’ [-Woverloaded-virtual]
     virtual_member_hiden.cpp: In function ‘int main()’:
     virtual_member_hiden.cpp:40:32: error: no matching function for call to ‘Derived::exception(const char [10])’
     virtual_member_hiden.cpp:40:32: note: candidate is:
     virtual_member_hiden.cpp:30:16: note: virtual void Derived::exception()
     virtual_member_hiden.cpp:30:16: note:   candidate expects 0 arguments, 1 provided
   */

  return 0;
}
