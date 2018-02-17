#include <iostream>

using namespace std;

struct StructA {
  // void StructA::Fun()    // error in Ubuntu 9.04 but works at SL4
  void Fun()
  {
    cout<< "This is a function " << __FUNCTION__ << " from the file " << __FILE__ <<endl;
  }
};

main()
{
  StructA structA;
  structA.Fun();
}
