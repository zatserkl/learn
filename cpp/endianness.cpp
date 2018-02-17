#include <iostream>

using std::cout;      using std::endl;

/* Returns true if the machine is little-endian, false if the
 * machine is big-endian
 */
bool isLittleEndian(){
  int
    testNum;
  char *ptr;
  testNum = 1;
  ptr = (char *) &testNum;
  return (*ptr); /* Returns the byte at the lowest address */
}

/* Returns true if the machine is little-endian, false if the
 * machine is big-endian
 */
bool isLittleEndianUnion(){
  union {
    int theInteger;
    char singleByte;
  } endianTest;
  endianTest.theInteger = 1;
  return endianTest.singleByte;
}

int main()
{
  if (isLittleEndian()) cout<< "this is machine is a little-endian" <<endl;
  else cout<< "this machine is a big-endian machine" <<endl;

  if (isLittleEndianUnion()) cout<< "this is machine is a little-endian" <<endl;
  else cout<< "this machine is a big-endian machine" <<endl;

  return 0;
}
