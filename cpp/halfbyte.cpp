#include <iostream>
#include <iomanip>

using std::cout;      using std::endl;

int main()
{
  unsigned char buf[4];
  buf[0] = 0x12;
  buf[1] = 0x34;
  buf[2] = 0x56;
  buf[3] = 0xFF;

  for (int i=0; i<4; ++i) {
    cout<< std::setw(2) << std::setfill('0') << std::hex << (unsigned) buf[i] << " ";
  }
  cout<<endl;

  cout<< "  shift for half of byte" <<endl;

  // buf[0] = (buf[0] << 4) | (buf[1] >> 4);
  for (int i=0; i<3; ++i) {
    buf[i] = (buf[i] << 4) | (buf[i+1] >> 4);
  }

  for (int i=0; i<4; ++i) {
    cout<< std::setw(2) << std::setfill('0') << std::hex << (unsigned) buf[i] << " ";
  }
  cout<<endl;

  return 0;
}
