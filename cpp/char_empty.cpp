#include <iostream>
#include <cstring>

using std::cout;      using std::endl;

void fun(const char* str="")
{
  if (str && strlen(str)>0)               // OK
  // if (std::strcmp(str,"") != 0)        // Segmentation fault
  // if (std::strlen(str) > 0)            // Segmentation fault
  // if (str != "")                       // passes condition
  {
    cout<< "---" << str << "---" <<endl;
  }
  else cout<< "the string is empty" <<endl;
}

main()
{
  fun(0);
}
