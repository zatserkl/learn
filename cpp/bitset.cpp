// bitset::to_ulong
#include <iostream>       // std::cout
#include <bitset>         // std::bitset

using std::cout;    using std::endl;

//-- forbidden: union works for Old Plain Data (OPD) only
union BitsetByte {
  std::bitset<8> bit;
  unsigned char byte;
};

int main ()
{
  std::bitset<4> foo;     // foo: 0000
  foo.set();              // foo: 1111

  std::cout << foo << " as an integer is: " << foo.to_ulong() << '\n';

  cout<< "test union with byte" <<endl;

  BitsetByte bitsetByte;
  bitsetByte.bit.set(0,1);
  bitsetByte.bit.set(1,0);
  bitsetByte.bit.set(2,1);
  bitsetByte.bit.set(3,0);
  bitsetByte.bit.set(4,0);
  bitsetByte.bit.set(5,0);
  bitsetByte.bit.set(6,1);
  bitsetByte.bit.set(7,0);

  cout<< "bitsetByte.byte = " << (unsigned int) bitsetByte.byte <<endl;

  return 0;
}
