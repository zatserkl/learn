#include <iostream>
#include <string>

using std::cout;      using std::endl;

int main()
{
  std::string str = "0abc0";
  cout<< "initial str = ---" << str << "---" <<endl;
  str.erase(0,1);
  str.erase(str.size()-1,1);
  cout<< "after stripping zeros: ---" << str << "---" <<endl;

  return 0;
}
