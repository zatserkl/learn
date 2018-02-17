// http://yosefk.com/c++fqa/exceptions.html#fqa-17.1

#include <iostream>

using std::cout;      using std::endl;

main()
{
  cout<< "*(int*)0 = 0;" <<endl;
  *(int*)0 = 0;
}
