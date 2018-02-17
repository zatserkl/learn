#include <iostream>
#include <sstream>
//#include <iomanip>  // do not need at least for g++ 4.3.3

using std::cout;      using std::endl;

main()
{
  double a = 0.1;
  double b = -0.2;
  double c = 0.3;

  std::stringstream ss;

  // the same effect
  // ---------------
  // ss.setf(std::ios::showpos);
  // ss.unsetf(std::ios::showpos);

  ss 
    << std::showpos     // NB: in ROOT works only ss.setf(std::ios::showpos)
    << a
    << "*("
    << b
    << c
    << ")"
    << std::noshowpos   // NB: in ROOT works only ss.setf(std::ios::noshowpos)
  ;

  cout<< "ss.str() = " << ss.str() <<endl;
}
