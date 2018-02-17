#include <iostream>
#include <fstream>
#include <string>

using std::cout;      using std::endl;

int main()
{
  std::ifstream file_good;
  cout<< "before open: !file_good = " << !file_good <<endl;

  cout<< "this source file __FILE__ = " << __FILE__ <<endl;
  file_good.open(__FILE__);
  cout<< "after open of this file: !file_good = " << !file_good <<endl;
  
  // std::string line;
  // while (std::getline(file_good,line)) cout<< line <<endl;

  std::ifstream file_bad;
  file_bad.open("xxxxx");
  cout<< "after open of non-existing file: !file_bad = " << !file_bad <<endl;

  return 0;
}
