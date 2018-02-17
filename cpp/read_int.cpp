// this is a data line 1000

/*
    Linux and Mac OS X read the first line (int as a string) of this file in different way:

    Linux:
// this is a data  -1

    Mac OS X:
// this is a data  0
*/

#include <iostream>
#include <fstream>
#include <string>

using std::cout;      using std::endl;

int main()
{
  std::ifstream file(__FILE__);

  std::string comment_str;
  std::string this_str;
  std::string is_str;
  std::string a_str;
  std::string data_str;
  std::string line_str;

  int number = -1;

  //--correct-- file >> comment_str >> this_str >> is_str >> a_str >> data_str >> line_str >> number;
  file >> comment_str >> this_str >> is_str >> a_str >> data_str /*>> line_str*/ >> number;

  cout<< comment_str <<" "<< this_str <<" "<< is_str <<" "<< a_str <<" "<< data_str <<" "<< line_str <<" "<< number <<endl;

  return 0;
}
