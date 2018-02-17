#include <iostream>

using std::cout;      using std::endl;

union ByteBit {
  struct
  {
    unsigned char bit0 : 1;
    unsigned char bit1 : 1;
    unsigned char bit2 : 1;
    unsigned char bit3 : 1;
    unsigned char bit4 : 1;
    unsigned char bit5 : 1;
    unsigned char bit6 : 1;
    unsigned char bit7 : 1;
  };
  unsigned char byte;
};

int main()
{
  ByteBit bytebit;

  bytebit.bit0 = 1;
  bytebit.bit1 = 0;
  bytebit.bit2 = 1;
  bytebit.bit3 = 0;
  bytebit.bit4 = 0;
  bytebit.bit5 = 0;
  bytebit.bit6 = 1;
  bytebit.bit7 = 0;

  // unsigned int a = bytebit.byte;
  // cout<< "a = " << a <<endl;

  cout<< "bytebit.byte = " << (unsigned int) bytebit.byte <<endl;

  return 0;
}
