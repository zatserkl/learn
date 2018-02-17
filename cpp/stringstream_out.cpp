#include <iostream>
#include <sstream>

using std::cout;      using std::endl;

main()
{
  std::string str1("start");
  std::string str2("---");
  std::string str3("finish");

  // init output stringstream with string using constractor
  std::ostringstream ss(str1);

  // add other string
  ss << str2 << str3;

  cout<< "ostringstream: init failed: should be \"start---finish\" while we have: " << ss.str() <<endl;
}
