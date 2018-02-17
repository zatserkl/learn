#include <string>
#include <iostream>

using std::cout;    std::endl;

main()
{
  // this is a comment
  //-- this is an important comment
  //this is a commented out line

  typedef int integer;

  std::string s1 = "This is a string";
  std::string s2 = " ";

  s2 = s1;
  cout<< "s2 = " << s2 <<endl;
}
