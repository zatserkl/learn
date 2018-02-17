#include <iostream>

using std::cout;      using std::endl;

class A {
public:
  A() {
    cout<< "constructor A" <<endl;
  }
 ~A() {
    cout<< "destructor ~A" <<endl;  
  }
  int a_;
};

main()
{
  for (int i=0; i<5; ++i) {
    A a;
    a.a_ = i;
  }
}
