#include <iostream>
#include <string>
#include <sstream>

using std::cout;      using std::endl;

main()
{
  std::string str;
  std::stringstream ss("message1 message2");
  ss >> str;
  cout<< "string after the first input: " << str <<endl;
  ss >> str;
  cout<< "string after the second input: " << str <<endl;
}
