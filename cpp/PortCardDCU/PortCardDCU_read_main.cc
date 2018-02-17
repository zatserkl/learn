/*
main for test of PortCardDCU
to compile:
g++ PortCardDCU.cc PortCardDCU_read_main.cc
*/

#include "PixelUtilities/PixelTKFECDataTools/include/PortCardDCU.h"

#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

bool debug_ = true;

main()
{
  //--- sends test Data-Point values to PixelDCStoTrkFECDpInterface
  
  cout << "<PixelDCSTestApplication::TestDCStoTrkFECDpInterface>" << endl;

  std::ostringstream fname;
  //--xdaq fname << BUILD_HOME << "/" << "pixel/PixelDCSInterface/xml/" << "xdaqjcPID15965.log.dat";
  //fname << "xdaqjcPID15965.log.dat";
  fname << "xdaqjcPID15965.log";
  // fname << "Log_15Dec2009_08-14-45_GMT__PixelDCSFSMInterface.log";

  std::ifstream file(fname.str().c_str());
  if (!file) {
    cout<< "***ERROR PixelDCSTestApplication::TestDCStoTrkFECDpInterface: data file not found: " << fname.str() <<endl;
    //--xdaq return MakeSOAPMessageReference("TestDCStoTrkFECDpInterfaceFailed");
    return 0;
  }
  else {
    cout<< "PixelDCSTestApplication::TestDCStoTrkFECDpInterface: read DCU data from file " << fname.str() <<endl;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////

  // variables for actual values
  std::string portcardName;
  unsigned fecBoardId, mfecId, ccuId, ccuChannelId, mode, Vaa, Vdd, rtd2, rtd3, aoh, Vpc, Vbg, ts;
  // variables for text names
  std::string portcardName_;
  std::string fecBoardId_, mfecId_, ccuId_, ccuChannelId_, mode_, Vaa_, Vdd_, rtd2_, rtd3_, aoh_, Vpc_, Vbg_, ts_;
  std::string eq;

  // output for each portcard in the log file consists of two lines. Example:
  // portcardName_ = FPix_BmI_D1_PRT1 fecBoardId_ = 18 mfecId_ = 5 ccuId_ = 126 ccuChannelId_ = 16
  // mode_ = 1 Vaa_ = 2390 Vdd_ = 3062 rtd2_ = 2598 rtd3_ = 2592 aoh_ = 2488 Vpc_ = 2690 Vbg_ = 2493 ts_ = 2747

  int nevents = 0;
  std::string line;
  for (std::streampos pos; pos=file.tellg(), std::getline(file, line); )    // save position in stream before current line
  {
    if (line.find("portcardName_ = ") == 0)     // line starts from "portcardName_ = "
    {
      // put stream pointer before this line and read data for all portcards
      file.seekg(pos);

      // dataset for the whole FPix
      std::vector<PortCard::AddressDCU> portCards;

      // if (debug_) cout<< "// PixelDCSTestApplication::TestDCStoTrkFECDpInterface: emulated data:" <<endl;

      for (int ipc=0; ipc<32; ++ipc)
      {
        file
          // first (address) line
          >> portcardName_ >> eq >> portcardName
          >> fecBoardId_ >> eq >> fecBoardId
          >> mfecId_ >> eq >> mfecId
          >> ccuId_ >> eq >> ccuId
          >> ccuChannelId_ >> eq >> ccuChannelId
          // second (data) line
          >> mode_ >> eq >> mode
          >> Vaa_ >> eq >> Vaa
          >> Vdd_ >> eq >> Vdd
          >> rtd2_ >> eq >> rtd2
          >> rtd3_ >> eq >> rtd3
          >> aoh_ >> eq >> aoh
          >> Vpc_ >> eq >> Vpc
          >> Vbg_ >> eq >> Vbg
          >> ts_ >> eq >> ts
        ;

        double Trtd2 = (2./3850.e-6) * (1. - double(rtd2)/double(Vpc));
        double Trtd3 = (2./3850.e-6) * (1. - double(rtd3)/double(Vpc));
        double Taoh  = (2./3850.e-6) * (1. - double(aoh)/double(Vpc));

        //
        //  test printout
        //
        if (debug_) {
          cout
            << ipc << "\t "
            <<" "<< portcardName_ <<" "<< portcardName
            // <<" "<< fecBoardId_ <<" "<< fecBoardId
            // <<" "<< mfecId_ <<" "<< mfecId
            // <<" "<< ccuId_ <<" "<< ccuId
            // <<" "<< ccuChannelId_ <<" "<< ccuChannelId
            <<" "<< mode_ <<" "<< mode
            // <<" "<< Vaa_ <<" "<< Vaa
            // <<" "<< Vdd_ <<" "<< Vdd
            <<" "<< rtd2_ <<" "<< rtd2
            <<" "<< rtd3_ <<" "<< rtd3
            <<" "<< aoh_ <<" "<< aoh
            <<" "<< Vpc_ <<" "<< Vpc
            // <<" "<< Vbg_ <<" "<< Vbg
            // <<" "<< ts_ <<" "<< ts

            << " Trtd2 = " << Trtd2 << " Trtd3 = " << Trtd3 << " Taoh = " << Taoh
            <<endl
          ;
        }

        PortCard::AddressDCU addressDCU;

        addressDCU.address_.portcardName_  = portcardName;
        addressDCU.address_.fecBoardId_    = fecBoardId;
        addressDCU.address_.mfecId_        = mfecId;
        addressDCU.address_.ccuId_         = ccuId;
        addressDCU.address_.ccuChannelId_  = ccuChannelId;
        addressDCU.dcu_.mode_ = 1;
        addressDCU.dcu_.Vaa_  = Vaa;
        addressDCU.dcu_.Vdd_  = Vdd;
        addressDCU.dcu_.rtd2_ = rtd2;
        addressDCU.dcu_.rtd3_ = rtd3;
        addressDCU.dcu_.aoh_  = aoh;
        addressDCU.dcu_.Vpc_  = Vpc;
        addressDCU.dcu_.Vbg_  = Vbg;
        addressDCU.dcu_.ts_   = ts;

        portCards.push_back(addressDCU);
      }
      // end of event
      ++nevents;
      if (debug_) cout<< "End of event " << nevents <<endl;
      cout<< "file.eof() = " << file.eof() <<endl;

      // prepare message with this data

      //--xdaq xoap::MessageReference soapMessage = PortCard::SOAP_ReadAll::Make(PortCard::SOAP_ReadAll::name_command_, portCards);
      cout<< "--> prepare and send message to PixelDCStoTrkFECDpInterface" <<endl;
    }
  }
  // return MakeSOAPMessageReference("TestDCStoTrkFECDpInterfaceDone");
  return 0;
}
