/*
[cmsfpix2] learn> g++ switch_string.cpp
switch_string.cpp: In function `int main()':
switch_string.cpp:14: switch quantity not an integer
*/

#include <string>
#include <iostream>

using std::cout;      using std::endl;

main()
{
  std::string s = "some example";

  const std::string s1 = "this example";
  const std::string s2 = "that example";
  const std::string s3 = "some example";

  switch (s) {
    case s1: cout<< "s1" <<endl; break;
    case s2: cout<< "s2" <<endl; break;
    case s3: cout<< "s3" <<endl; break;
    default: cout<< "unknown" <<endl;
  }
}
