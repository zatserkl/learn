/*
  NB: inverse quotes ``!
  g++ `$ROOTSYS/bin/root-config --cflags --glibs` stringstream.C
*/

#include <TRint.h>          // the only include you need to call ROOT
//#include <Rtypes.h>

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

using std::cout;     using std::endl;

void stringstream_loop()
{
   for (int i=0; i<3; ++i) {
      std::string str = Form("%d", i);
      std::stringstream ss(str);
      cout<< "ss.str() = " << ss.str() <<endl;
   }
}

#if !defined(__CINT__)
int main()
{
   stringstream_loop();

   return 0;
}
#endif
