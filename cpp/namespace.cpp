#include <iostream>

using std::cout;      using std::endl;

namespace some_namespace {
  void print() {
    cout<< "I am some_namespace::print" <<endl;
  }
}

main()
{
  using some_namespace::print;

  print();
}
