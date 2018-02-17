#include <string>
#include <sstream>
#include <iostream>

using std::cout;      using std::endl;

main()
{
  std::string line = "<dist_1:CAEN/pixelTIF_SY1527/branchController15/easyCrate0/easyBoard00/channel000.actual.iMon:_online.._value alias=\"Portcards_D1_LV_iMon\">1.830000</dist_1:CAEN/pixelTIF_SY1527/branchController15/easyCrate0/easyBoard00/channel000.actual.iMon:_online.._value>";

  //   std::stringstream ss;
  //   ss << line;

  cout<< line <<endl;
  
}
