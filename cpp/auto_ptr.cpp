/*
see my c++ google doc, extraction from http://www.codepedia.com/1/CppAutoPtr
*/
#include <iostream>
#include <memory>
using namespace std;

int main(int argc, char **arv)
{
  int *i = new int;
  auto_ptr<int> x(i);
  auto_ptr<int> y;

  *x = 5;
  cout<< "*i = " << *i <<endl;
  cout<< "*x = " << *x <<endl;

  int* ptr = x.get();
  cout<< "*ptr = " << *ptr <<endl;

  // do not assign like this: object x pointed to will be destroyed and x=0
  y = x;

  cout << x.get() << endl;
  cout << y.get() << endl;
}
