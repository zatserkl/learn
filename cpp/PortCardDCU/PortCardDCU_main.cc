/*
main for test of PortCardDCU
to compile:
g++ PortCardDCU.cc PortCardDCU_main.cc
*/

#include "PixelUtilities/PixelTKFECDataTools/include/PortCardDCU.h"

#include <map>
#include <iostream>

using namespace std;

main()
{
  //PortCard::AddressDCU addressDCU1;
  //PortCard::AddressDCU addressDCU2;
  
  PortCard::Address address1("FPix_BmO_D1_PRT3", 12, 8, 127, 27);
  PortCard::Address address2("FPix_BmO_D2_PRT3", 12, 8, 127, 26);
  
  PortCard::DCU dcu1(1, 2335, 3251, 2634, 2633, 2583, 2736, 2510, 2726);
  PortCard::DCU dcu2(1, 2344, 2970, 2617, 2619, 2580, 2727, 2512, 2660);
  
  std::vector<PortCard::DCU> vdcu1;
  std::vector<PortCard::DCU> vdcu2;
  
  vdcu1.push_back(dcu1);
  vdcu2.push_back(dcu2);
  
  std::map<PortCard::Address, std::vector<PortCard::DCU> > address_vpoints_map_;
  
  address_vpoints_map_[address1] = vdcu1;
  address_vpoints_map_[address2] = vdcu2;
  
  for (std::map<PortCard::Address, std::vector<PortCard::DCU> >::const_iterator
    i_address_vpoints = address_vpoints_map_.begin();
    i_address_vpoints != address_vpoints_map_.end(); ++i_address_vpoints)
  {
    const PortCard::Address& address = i_address_vpoints->first;
    const std::vector<PortCard::DCU>& vdcu = i_address_vpoints->second;
    
    cout << "Port Card " << address.prints() << " has vdcu.size() = " << vdcu.size() << " data points" <<endl;
    for (std::vector<PortCard::DCU>::const_iterator i_vdcu=vdcu.begin(); i_vdcu!=vdcu.end(); ++i_vdcu)
    {
      cout<< i_vdcu->prints() <<endl;
    }
  }
}
