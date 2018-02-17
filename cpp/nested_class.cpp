#include <iostream>

using std::cout;      using std::endl;

class Outer {
public:
  int a;
  Outer(): a(5) {
    cout<< "Outer: a = " << a <<endl;
  }
  class Inner {
    Inner() {
      cout<< "Inner: a = " << a <<endl;
    }
  };
};

int main()
{
  Outer out;
  return 0;
}

/*
learn$ g++ -Wall nested_class.cpp
nested_class.cpp: In constructor ‘Outer::Inner::Inner()’:
nested_class.cpp:7:7: error: invalid use of non-static data member ‘Outer::a’
nested_class.cpp:13:31: error: from this location
*/

