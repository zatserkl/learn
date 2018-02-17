// from http://www.cplusplus.com/reference/iostream/ios_base/setf/

//-- In g++ 4.3.3 setf(0, ios::showbase) does not work, but works unsetf(ios::showbase)

// modify flags
#include <iostream>
using namespace std;

int main () {
  cout.setf ( ios::hex, ios::basefield ); // set hex as the basefield
  cout.setf ( ios::showbase );            // activate showbase
  cout << 100 << endl;
  //-- cout.setf ( 0, ios::showbase );      // does not work in g++ 4.3.3 deactivate showbase
  cout.unsetf ( ios::showbase );          // deactivate showbase
  cout << 100 << endl;
  return 0;
}
