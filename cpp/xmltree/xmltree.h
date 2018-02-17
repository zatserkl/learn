#ifndef xmltree_h
#define xmltree_h

#include <Rtypes.h>
#include <TObject.h>

#include <iostream>

using std::cout;        using std::endl;

//
// For PVSS tree
//

class LV: public TObject {
public:
  Float_t  v;
  Float_t  i;
  LV(): TObject() {
    clear();
  }
 ~LV() {}
  void clear() {
    v = i = 0;
  }
  ClassDef(LV, 2)
};

class Disk: public TObject {
public:
  // CAEN
  LV        pcard;
  LV        dig[4];
  LV        ana[4];
  // SIEMENS
  Float_t   RTD[8];     // hardware readout RTDs
  Disk(): TObject() {
    clear();
  }
  ~Disk() {}
  void clear() {
    pcard.clear();
    for (int i=0; i<4; ++i) {
      dig[i].clear();
      ana[i].clear();
    }
    for (int i=0; i<8; ++i) RTD[i] = 0;
  }
  ClassDef(Disk, 3)
};

class HCyl: public TObject {
public:
  Float_t  t;           // astronomocal time - Jan 1, 2007 (in seconds)
  Float_t  air;
  // electronics
  LV ccu;
  Disk     disk[2];
  HCyl(): TObject() {
    clear();
  }
  void clear() {
    t = 0;
    air = 0;
    ccu.clear();
    for (int i=0; i<2; ++i) disk[i].clear();
  }
  ClassDef(HCyl, 3)
};

//
// For DCU tree
//

class DCU: public TObject {
public:
  Int_t   LIR;
  Int_t   HIR;
  Float_t  Vaa;
  Float_t  Vdd;
  Float_t  rtd2;
  Float_t  rtd3;
  Float_t  aoh;        // AOH RTD
  Float_t  Vpc;        // Port Card Vpower
  Float_t  Vbg;        // DCU reference BandGap voltage
  Float_t  ts;         // DCU diode-based Temperature Sensor
  // pedestal
  Float_t ped;
  Float_t Trtd2;       // T in degrees of Celsius, Trtd2 = (2/3850e-6)*(1 - rtd2/Vpc)
  Float_t Trtd3;       // Trtd3 = (2/3850e-6)*(1 - rtd3/Vpc)
  Float_t Taoh;        // Taoh = (2/3850e-6)*(1 - aoh/Vpc)
  //-- cross-reference
  Int_t d;
  Int_t pc;
  DCU(): TObject() {
   clear();
  }
  void clear() {
    LIR = HIR = 0;
    Vaa = Vdd = rtd2 = rtd3 = aoh = Vpc = Vbg = ts = 0;
    ped = 0;
    Trtd2 = Trtd3 = Taoh = 0;
    d = pc = 0;
  }
  ClassDef(DCU, 3)
};

class DiskDCU: public TObject {
public:
  DCU       dcu[4];
  DiskDCU(): TObject() {
    clear();
  }
  void clear() {
    for (int i=0; i<4; ++i) dcu[i].clear();
  }
  ClassDef(DiskDCU, 2)
};

class HCylDCU: public TObject {
public:
  Float_t  t;                   // astronomocal time - Jan 1, 2007 (in seconds)
  // electronics
  DiskDCU  disk[2];
  HCylDCU(): TObject() {
    clear();
  }
  void clear() {
    t = 0;
    for (int i=0; i<2; ++i) disk[i].clear();
  }
  ClassDef(HCylDCU, 2)
};

#endif
