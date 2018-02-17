/*
http://www.devx.com/tips/Tip/5602

Expertise: All
Language: C++
March 29, 1999
Initializing const static Data Members
The C++ Standard now allows initialization of const static data members of an integral type inside their class.

 
#include <string>
class Buff
{
private:
  static const int MAX = 512; //definition
  static const char flag = 'a'; //also a defintion
  static const std::string msg; //non-integral type; must be defined outside the class body
public:
//..
};
const std::string Buff::msg = "hello";

The initialization inside the class body also defines the data member, so it shouldn't be defined outside the class, as opposed const static data members of non-integral types, which have to be defined outside the class body.
Danny Kalev
*/

#include <string>
#include <iostream>

using namespace std;

class Stat {
public:
  static const int a = 1;
  static const int b = 1 + 1;
  static const int c = b + 1;
  //static const std::string str = "this is a string";
  //const char chstr[] = "character string";
};

main()
{
  Stat stat;
  //std::cout<< stat.str <<std::endl;
  std::cout<< stat.a <<std::endl;
  std::cout<< stat.b <<std::endl;
  std::cout<< stat.c <<std::endl;
}
