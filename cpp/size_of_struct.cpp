/*
$ g++ size_of_struct.cpp
$ ./a.out
8
12
*/

#include <iostream>

using std::cout;    using std::endl;

struct A
{
  char c;
  char d;
  int i;
};
struct B
{
  char c;
  int i;
  char d;
};
int main() {
  cout << sizeof(A) << endl;
  cout << sizeof(B) << endl;
  return 0;
}
