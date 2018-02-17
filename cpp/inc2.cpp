#include <iostream>

using std::cout;      using std::endl;

main()
{
  for (int i=0; i<10; i+=2) {       // the same ++++i
    cout<< "i = " << i << " i+1 = " << i+1 <<endl;
  }
}
