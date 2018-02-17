#include <string>
#include <sstream>
#include <iostream>

using std::cout;      using std::endl;

main()
{
  std::stringstream ss;
  ss << "123.000";

  int a;

  ss.operator>>(a);

  cout<< "a = " << a <<endl;
}
