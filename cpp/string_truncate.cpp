#include <iostream>
#include <string>

using std::cout;      using std::endl;

main()
{
  std::string str = "this is a string";

  cout<< "___" << str << "___" <<endl;

  str.erase(str.find("ing"));             // CINT don't know erase

  cout<< "___" << str << "___" <<endl;

  str.resize(str.find(" str"));           //-- truncate a string

  cout<< "___" << str << "___" <<endl;
}
