#include <iostream>

using std::cout;      using std::endl;

#define murmur 123

// #define gav

int main()
{
  int a = 1;
  int b = a + murmur;
  cout<< "b = " << b <<endl;

#ifdef gav
  cout<< "the gav is defined" <<endl;
#endif

  return 0;
}
