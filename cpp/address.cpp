#include <iostream>
#include <map>

using namespace std;

class PortCardDCU {
public:
  unsigned Vaa;         // analog voltage
  unsigned Vdd;         // digital voltage
  unsigned rtd2;        // RTD connected with DCU channel 2
  unsigned rtd3;        // RTD connected with DCU channel 3
  unsigned aoh;         // AOH RTD: RTD situated on Port Card under the AOH mezzanine board
  unsigned Vpc;         // Port card Vpower. NB: this value should be used for normalizing of the rest of all channels.
  unsigned ch6;         // unknown (for me)
  unsigned ts;          // DCU internal diode-based temperature sensor
  PortCardDCU(): Vaa(0), Vdd(0), rtd2(0), rtd3(0), aoh(0), Vpc(0), ch6(0), ts(0) {}
//   PortCardDCU& operator = (const PortCardDCU& portcardDCU)
//   {
//     // do not really need this operator =
//     
//     Vaa = portcardDCU.Vaa;
//     Vdd = portcardDCU.Vdd;
//     rtd2 = portcardDCU.rtd2;
//     rtd3 = portcardDCU.rtd3;
//     aoh = portcardDCU.aoh;
//     Vpc = portcardDCU.Vpc;
//     ch6 = portcardDCU.ch6;
//     ts = portcardDCU.ts;
//     return *this;
//   }
  void Print() const {
    cout<< "PortCardDCU::Print" <<endl;
    cout<< "Vaa   = " << Vaa <<endl;
    cout<< "Vdd   = " << Vdd <<endl;
    cout<< "rtd2  = " << rtd2 <<endl;
    cout<< "rtd3  = " << rtd3 <<endl;
    cout<< "aoh   = " << aoh <<endl;
    cout<< "Vpc   = " << Vpc <<endl;
    cout<< "ch6   = " << ch6 <<endl;
    cout<< "ts    = " << ts <<endl;
  }
};

class AddressPortCard {
public:
  unsigned fecBoardId_;   // slot of FEC in crate
  unsigned mfecId_;       // == ring slot = position of FEC mezzanine board with optical cable in FEC board (counted from 0)
  unsigned ccuId_;        // CCU address. Actually, this is a position of CCU. For some reason it's counted from 0x70
  unsigned ccuChannelId_; // one of 12 CCU channels. Each channel connected with different Port Card
  AddressPortCard(): fecBoardId_(0), mfecId_(0), ccuId_(0), ccuChannelId_(0) {}
  AddressPortCard(unsigned fecBoardId, unsigned mfecId, unsigned ccuId, unsigned ccuChannelId):
    fecBoardId_(fecBoardId), mfecId_(mfecId), ccuId_(ccuId), ccuChannelId_(ccuChannelId)
  {}
  bool operator < (const AddressPortCard& address) const
  {
    // method to be used in std::map for comparison
    // Example of map definition:
    // std::map<AddressPortCard, PortCardDCU> dcu_map;
    //
    if (false
      || fecBoardId_ < address.fecBoardId_
      || mfecId_ < address.mfecId_
      || ccuId_ < address.ccuId_
      || ccuChannelId_ < address.ccuChannelId_
    ) return true;
    else return false;
  }
};

struct CompareAddressPortCard
{
  // This struct also can be used for std::map for AddressPortCard
  // Example of map definition:
  // std::map<AddressPortCard, PortCardDCU, CompareAddressPortCard> dcu_map;
  //
  bool operator()(const AddressPortCard& a1, const AddressPortCard& a2 ) const
  {
    if (false
      || a1.fecBoardId_ < a2.fecBoardId_
      || a1.mfecId_ < a2.mfecId_
      || a1.ccuId_ < a2.ccuId_
      || a1.ccuChannelId_ < a2.ccuChannelId_
    ) return true;
    else return false;
  }
};

main()
{
  PortCardDCU portcardDCU;
  
  portcardDCU.Vaa   = 1000;
  portcardDCU.Vdd   = 1001;
  portcardDCU.rtd2  = 1002;
  portcardDCU.rtd3  = 1003;
  portcardDCU.aoh   = 1004;
  portcardDCU.Vpc   = 1005;
  portcardDCU.ch6   = 1006;
  portcardDCU.ts    = 1007;
  
  cout<< "portcardDCU.Vaa = " << portcardDCU.Vaa <<endl;
  cout<< "portcardDCU.Vdd = " << portcardDCU.Vdd <<endl;
  cout<< "portcardDCU.rtd2 = " << portcardDCU.rtd2 <<endl;
  cout<< "portcardDCU.rtd3 = " << portcardDCU.rtd3 <<endl;
  cout<< "portcardDCU.aoh = " << portcardDCU.aoh <<endl;
  cout<< "portcardDCU.Vpc = " << portcardDCU.Vpc <<endl;
  cout<< "portcardDCU.ch6 = " << portcardDCU.ch6 <<endl;
  cout<< "portcardDCU.ts = " << portcardDCU.ts <<endl;
  
  // DCU (Port Card) address
  
  unsigned fecBoardId = 4;
  unsigned mfecId = 3;
  unsigned ccuId = 2;
  unsigned ccuChannelId = 1;
  
  AddressPortCard addressDCU(fecBoardId, mfecId, ccuId, ccuChannelId);
  
  // map
  
  // std::map<AddressPortCard, PortCardDCU, CompareAddressPortCard> dcu_map;  // works fine too
  std::map<AddressPortCard, PortCardDCU> dcu_map;
  
  dcu_map[addressDCU] = portcardDCU;
  
  // second entry
  
  // modify content
  portcardDCU.Vaa   += 1000;
  portcardDCU.Vdd   += 1000;
  portcardDCU.rtd2  += 1000;
  portcardDCU.rtd3  += 1000;
  portcardDCU.aoh   += 1000;
  portcardDCU.Vpc   += 1000;
  portcardDCU.ch6   += 1000;
  portcardDCU.ts    += 1000;
  addressDCU.fecBoardId_    = 4;
  addressDCU.mfecId_        = 3;
  addressDCU.ccuId_         = 22;
  addressDCU.ccuChannelId_  = 1;
  
  dcu_map[addressDCU] = portcardDCU;
  
  for (std::map<AddressPortCard, PortCardDCU>::const_iterator it=dcu_map.begin(); it!=dcu_map.end(); ++it)
  {
    unsigned fecBoard = it->first.fecBoardId_;
    unsigned mfec = it->first.mfecId_;
    unsigned ccu = it->first.ccuId_;
    unsigned ccuChannel = it->first.ccuChannelId_;
    cout<< "fecBoard = " << fecBoard << " mfec = " << mfec << " ccu = " << ccu << " ccuChannel = " << ccuChannel <<endl;
    it->second.Print();
  }
}
