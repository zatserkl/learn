#include <iostream>

using std::cout;      using std::endl;

main()
{
  int k = l = 0;
  cout<< "k = " << k << " l = " << l <<endl;

  for (int i=j=0; i<10; ++i) {
    cout<< "i = " << i << " j = " << j <<endl;
  }
}

/*
zatserkl/learn> g++ for_ij.cpp
for_ij.cpp: In function ‘int main()’:
for_ij.cpp:7: error: ‘l’ was not declared in this scope
for_ij.cpp:10: error: ‘j’ was not declared in this scope
*/
