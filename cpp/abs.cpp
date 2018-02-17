#include <iostream>
#include <cmath>

using std::cout;      using std::endl;

main()
{
  double pi = std::acos(-1.);
  cout<< "std::abs(pi) = " << std::abs(pi) <<endl;

  double e = std::exp(1.);
  cout<< "std::pow(e,3) = " << std::pow(e,3) <<endl;
}
