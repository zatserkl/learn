#include <iostream>
#include <map>

using namespace std;

class PortCardDCU {
public:
  std::map<const std::string, unsigned> dcuChan;
  PortCardDCU() {
    dcuChan["Vaa"]  = 0;
    dcuChan["Vdd"]  = 0;
    dcuChan["rtd2"] = 0;
    dcuChan["rtd3"] = 0;
    dcuChan["aoh"]  = 0;      // AOH RTD
    dcuChan["Vpc"]  = 0;      // Port card Vpower
    dcuChan["ch6"]  = 0;      // unknown (for me)
    dcuChan["ts"]   = 0;      // DCU internal diode-based temperature sensor
  }
};

main()
{
  PortCardDCU portcardDCU;
  
  
  
  cout<< "portcardDCU.dcuChan.size() = " << portcardDCU.dcuChan.size() <<endl;
}
