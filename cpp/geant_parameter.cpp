#include <iostream>
#include <string>

using std::cout;      using std::endl;

void fun(std::string str, int ipar)
{
  cout<< "str = " << str <<endl;
  cout<< "ipar = " << ipar <<endl;
}

main()
{
  std::string str;
  int ipar;

  fun(str="some string", ipar=123);
}
