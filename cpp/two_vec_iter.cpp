#include <iostream>
#include <vector>
#include <string>

using std::cout;      using std::endl;

main()
{
  std::vector<std::string> vstring;
  std::vector<int> vint;

  vstring.push_back("one");
  vint.push_back(1);

  vstring.push_back("two");
  vint.push_back(2);

  vstring.push_back("three");
  vint.push_back(3);

  //-- distance is SIGNED:
  //-- the number on increaments or decreaments
  //--
  //-- int i = std::distance(first, last)
  //--

  for (std::vector<std::string>::iterator i_string=vstring.begin(); i_string!=vstring.end(); ++i_string) {
    int i = std::distance(vstring.begin(), i_string);
    cout<< i <<" "<< *i_string <<endl;
  }

  for (std::vector<std::string>::iterator i_string=vstring.begin(); i_string!=vstring.end(); ++i_string) {
    int i = std::distance(vstring.begin(), i_string);
    cout<< i <<"   "<< *i_string <<endl;
  }

  for (std::vector<int>::iterator i_int=vint.begin(); i_int!=vint.end(); ++i_int) {
    int i = std::distance(vint.begin(), i_int);
    cout<< i <<"   "<< *i_int <<endl;
  }

  for (std::vector<std::string>::iterator i_string=vstring.begin(); i_string!=vstring.end(); ++i_string) {
    int i = std::distance(vstring.begin(), i_string);
    int n = vint.at(i);
    cout<< i <<"   "<< n <<"   "<< *i_string <<endl;
  }
}
