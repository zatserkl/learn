#include <iostream>
#include <sstream>

using std::cout;      using std::endl;

main()
{
  std::stringstream ss("some looooooooong string");   // the same for ostringstream
  ss << "SHORT";

  cout<< ss.str() <<endl;
}
