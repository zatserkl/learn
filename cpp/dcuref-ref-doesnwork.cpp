#include <iostream>
#include <map>
//#include <multimap>     // multimap: No such file or directory

using namespace std;

class PortCardDCU {
public:
  unsigned channel[8];
  unsigned& Vaa;         // analog voltage
  unsigned& Vdd;         // digital voltage
  unsigned& rtd2;        // RTD connected with DCU channel 2
  unsigned& rtd3;        // RTD connected with DCU channel 3
  unsigned& aoh;         // AOH RTD: RTD situated on Port Card under the AOH mezzanine board
  unsigned& Vpc;         // Port card Vpower. NB: this value should be used for normalizing of the rest of all channels.
  unsigned& ch6;         // unknown (for me)
  unsigned& ts;          // DCU internal diode-based temperature sensor
  PortCardDCU():
    Vaa(channel[0]),
    Vdd(channel[1]),
    rtd2(channel[2]),
    rtd3(channel[3]),
    aoh(channel[4]),
    Vpc(channel[5]),
    ch6(channel[6]),
    ts(channel[7])
  {
    for (unsigned i=0; i<8; ++i) channel[i] = 0;
  }
  PortCardDCU& operator = (const PortCardDCU& portcardDCU) {
    for (unsigned i=0; i<8; ++i) channel[i] = portcardDCU.channel[i];
    return *this;
  }
  void Print() const {
    cout<< "PortCardDCU::Print" <<endl;
    for (unsigned i=0; i<8; ++i) cout<< i << "\t " << channel[i] <<endl;
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

typedef std::map<unsigned, PortCardDCU> ccuChannelId_map_type;
typedef std::map<unsigned, ccuChannelId_map_type> ccuId_map_type;
typedef std::map<unsigned, ccuId_map_type> mfecId_map_type;
typedef std::map<unsigned, mfecId_map_type> fecBoardId_map_type;


main()
{
  PortCardDCU portcardDCU;
  
  for (unsigned i=0; i<8; ++i) {
    portcardDCU.channel[i] = i;
  }
  
  cout<< "portcardDCU.Vaa = " << portcardDCU.Vaa <<endl;
  cout<< "portcardDCU.Vdd = " << portcardDCU.Vdd <<endl;
  cout<< "portcardDCU.rtd2 = " << portcardDCU.rtd2 <<endl;
  cout<< "portcardDCU.rtd3 = " << portcardDCU.rtd3 <<endl;
  cout<< "portcardDCU.aoh = " << portcardDCU.aoh <<endl;
  cout<< "portcardDCU.Vpc = " << portcardDCU.Vpc <<endl;
  cout<< "portcardDCU.ch6 = " << portcardDCU.ch6 <<endl;
  cout<< "portcardDCU.ts = " << portcardDCU.ts <<endl;
  
  // modify content
  portcardDCU.Vaa   += 1000;
  portcardDCU.Vdd   += 1000;
  portcardDCU.rtd2  += 1000;
  portcardDCU.rtd3  += 1000;
  portcardDCU.aoh   += 1000;
  portcardDCU.Vpc   += 1000;
  portcardDCU.ch6   += 1000;
  portcardDCU.ts    += 1000;
  
  for (unsigned i=0; i<8; ++i) {
    cout<< i << "\t " << portcardDCU.channel[i] <<endl;
  }
  
  PortCardDCU portcardDCU_copy = portcardDCU;
  cout<< "portcardDCU_copy.ts = " << portcardDCU_copy.ts <<endl;
  cout<< "portcardDCU_copy.Print()" <<endl;
  portcardDCU_copy.Print();
  
  // modify content
  portcardDCU.Vaa   += 1000;
  portcardDCU.Vdd   += 1000;
  portcardDCU.rtd2  += 1000;
  portcardDCU.rtd3  += 1000;
  portcardDCU.aoh   += 1000;
  portcardDCU.Vpc   += 1000;
  portcardDCU.ch6   += 1000;
  portcardDCU.ts    += 1000;
  
  portcardDCU_copy = portcardDCU;
  cout<< "after adding another 1000: portcardDCU_copy.Print()" <<endl;
  portcardDCU_copy.Print();
  
  std::pair<unsigned, PortCardDCU> pair_dcu;
  pair_dcu.first = 123;
  pair_dcu.second = portcardDCU;
  cout<< "pair_dcu.second.Print();" <<endl;
  pair_dcu.second.Print();
  
  fecBoardId_map_type fec_map;
  
  unsigned ccuChannelId = 11;
  unsigned ccuId = 2;
  unsigned mfecId = 3;
  unsigned fecBoardId = 4;
  
//   fec_map[fecBoardId][mfecId][ccuId][ccuChannelId] = portcardDCU;
//   
//   cout<< "fec_map.size() = " << fec_map.size() <<endl;
//   
//   for(fecBoardId_map::iterator it=fec_map.begin(); it!=fec_map.end(); ++it)
//   {
//     cout<< it->second.second.second.secon.ts <<endl;
//   }

  ccuChannelId_map_type ccuChannelId_map;
  ccuChannelId_map[ccuChannelId] = portcardDCU;
  
  cout<< "ccuChannelId_map[ccuChannelId].ts = " << ccuChannelId_map[ccuChannelId].ts <<endl;
  
  cout<< "ccuChannelId_map.size() = " << ccuChannelId_map.size() <<endl;
  
  //cout<< ccuChannelId_map[ccuChannelId].ts <<endl;
  
  for (ccuChannelId_map_type::iterator it=ccuChannelId_map.begin(); it!=ccuChannelId_map.end(); ++it)
  {
    cout<< it->first <<endl;
    PortCardDCU dcu = it->second;
    //cout<< it->second.ts <<endl;
    //cout<< dcu.ts <<endl;
    dcu.Print();
  }
}





















