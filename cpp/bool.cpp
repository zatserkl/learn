#include <iostream>
#include <iomanip>

using std::cout;      using std::endl;

union BoolChar {
  bool a_bool;
  char a_char;
  unsigned char a_uchar;
};

int main()
{
  BoolChar bc;
  bc.a_uchar = 131;
  cout<< "(unsigned) bc.a_uchar " << (unsigned) bc.a_uchar << " bc.a_uchar " << bc.a_uchar <<endl;
  cout<< "(int) bc.a_char " << (int) bc.a_char << " bc.a_char " << bc.a_char <<endl;
  cout<< "bc.a_bool " << bc.a_bool <<endl;
 
  // for (int i=0; i<256; ++i) {
  //   char ichar = i;
  //   cout<< i << "\t " << ichar <<endl;
  // }

  return 0;
}
