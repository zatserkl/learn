/*
learn> g++ string_switch.cpp
string_switch.cpp: In function ‘int main()’:
string_switch.cpp:14: error: switch quantity not an integer
string_switch.cpp:15: error: ‘one’ cannot appear in a constant-expression
string_switch.cpp:16: error: ‘two’ cannot appear in a constant-expression
string_switch.cpp:17: error: ‘three’ cannot appear in a constant-expression
*/

#include <iostream>
#include <string>

using std::cout;      using std::endl;

main()
{
  const std::string one = "one";
  const std::string two = "two";
  const std::string three = "three";

  std::string number = two;

  switch (number) {
    case one: cout<< number <<endl; break;
    case two: cout<< number <<endl; break;
    case three: cout<< number <<endl; break;
    default: cout<< "number does not match" <<endl;
  }
}
