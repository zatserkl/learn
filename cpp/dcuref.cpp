#include <iostream>
#include <map>
//#include <multimap>     // multimap: No such file or directory

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
  PortCardDCU& operator = (const PortCardDCU& portcardDCU) {
    Vaa = portcardDCU.Vaa;
    Vdd = portcardDCU.Vdd;
    rtd2 = portcardDCU.rtd2;
    rtd3 = portcardDCU.rtd3;
    aoh = portcardDCU.aoh;
    Vpc = portcardDCU.Vpc;
    ch6 = portcardDCU.ch6;
    ts = portcardDCU.ts;
    return *this;
  }
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

typedef std::map<unsigned, PortCardDCU> ccuChannelId_map_type;
typedef std::map<unsigned, ccuChannelId_map_type> ccuId_map_type;
typedef std::map<unsigned, ccuId_map_type> mfecId_map_type;
typedef std::map<unsigned, mfecId_map_type> fecBoardId_map_type;


main()
{
  PortCardDCU portcardDCU;
  
  portcardDCU.Vaa   = 0;
  portcardDCU.Vdd   = 1;
  portcardDCU.rtd2  = 2;
  portcardDCU.rtd3  = 3;
  portcardDCU.aoh   = 4;
  portcardDCU.Vpc   = 5;
  portcardDCU.ch6   = 6;
  portcardDCU.ts    = 7;
  
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
  
  unsigned ccuChannelId = 1;
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
    cout<< "it->second.ts = " << it->second.ts <<endl;
  }
  
  ccuId_map_type ccuId_map;
  ccuId_map[ccuId][ccuChannelId] = portcardDCU;
  
  cout<< "ccuId_map[ccuId][ccuChannelId].ts = " << ccuId_map[ccuId][ccuChannelId].ts <<endl;
  
  for (ccuId_map_type::iterator it=ccuId_map.begin(); it!=ccuId_map.end(); ++it)
  {
    cout<< it->first <<endl;
    ccuChannelId_map_type ccuChannelId_map = it->second;
    for (ccuChannelId_map_type::iterator it_ccuChan=ccuChannelId_map.begin(); it_ccuChan!=ccuChannelId_map.end(); ++it_ccuChan)
    {
      cout<< it_ccuChan->first <<endl;
      cout<< "it_ccuChan->second.ts = " << it_ccuChan->second.ts <<endl;
    }
  }
  
  // next level
  cout<< "--> parse ccuId_map" <<endl;
  
  for (ccuId_map_type::iterator iccuId=ccuId_map.begin(); iccuId!=ccuId_map.end(); ++iccuId)
  {
    unsigned ccuId = iccuId->first;
    cout<< "ccuId = " << ccuId <<endl;
    for (ccuChannelId_map_type::iterator it_ccuChan=iccuId->second.begin(); it_ccuChan!=iccuId->second.end(); ++it_ccuChan)
    {
      unsigned ccuChannelId = it_ccuChan->first;
      cout<< "ccuChannelId = " << ccuChannelId <<endl;
      cout<< "it_ccuChan->second.ts = " << it_ccuChan->second.ts <<endl;
    }
  }
  
  cout<<endl<< "finally" <<endl<<endl;
  
  fec_map[fecBoardId][mfecId][ccuId][ccuChannelId] = portcardDCU;
  
  for (fecBoardId_map_type::iterator ifecBoardId=fec_map.begin(); ifecBoardId!=fec_map.end(); ++ifecBoardId)
  {
    unsigned fecBoardId = ifecBoardId->first;
    cout<< "fecBoardId = " << fecBoardId <<endl;
    for (mfecId_map_type::iterator imfecId=ifecBoardId->second.begin(); imfecId!=ifecBoardId->second.end(); ++imfecId)
    {
      unsigned mfecId = imfecId->first;
      cout<< "mfecIdId = " << mfecId <<endl;
      for (ccuId_map_type::iterator iccuId=imfecId->second.begin(); iccuId!=imfecId->second.end(); ++iccuId)
      {
        unsigned ccuId = iccuId->first;
        cout<< "ccuId = " << ccuId <<endl;
        for (ccuChannelId_map_type::iterator iccuChannelId=iccuId->second.begin(); iccuChannelId!=iccuId->second.end(); ++iccuChannelId)
        {
          unsigned ccuChannelId = iccuChannelId->first;
          cout<< "ccuChannelId = " << ccuChannelId <<endl;
          PortCardDCU dcu = iccuChannelId->second;
          cout<< "dcu.Vaa   = " << dcu.Vaa <<endl;
          cout<< "dcu.Vdd   = " << dcu.Vdd <<endl;
          cout<< "dcu.rtd2  = " << dcu.rtd2 <<endl;
          cout<< "dcu.rtd3  = " << dcu.rtd3 <<endl;
          cout<< "dcu.aoh   = " << dcu.aoh <<endl;
          cout<< "dcu.Vpc   = " << dcu.Vpc <<endl;
          cout<< "dcu.ch6   = " << dcu.ch6 <<endl;
          cout<< "dcu.ts    = " << dcu.ts <<endl;
        }
      }
    }
  }
}





















