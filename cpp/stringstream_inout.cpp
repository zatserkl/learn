#include <iostream>
#include <sstream>
#include <string>

using std::cout;      using std::endl;

main()
{
  std::stringstream ss;

  ss << "abc";

  char a, b, c;
  ss >> a >> b >> c;

  cout<< "a = " << a << " b = " << b << " c = " << c << " ss.str() = " << ss.str() <<endl;
}
