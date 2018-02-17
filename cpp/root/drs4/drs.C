#include <TFile.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <TCanvas.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>

using std::cout;     using std::endl;

class OscChannel: public TObject
{
   public:
      Int_t ch;
      Float_t x[1024];
      Float_t y[1024];

   public:
      void clear() {
         ch = 0;
         for (int i=0; i<1024; ++i) {
            x[i] = 0;
            y[i] = 0;
         }
      }
      OscChannel(): TObject() {
         clear();
      }
      ~OscChannel() {}
      ClassDef(OscChannel, 1)
};

class OscEvent: public TObject
{
   public:
      Int_t evt;
      TClonesArray* oscCh;                   //-> array of OscChannel

   public:
      void clear() {
         evt = 0;
         oscCh->Clear();
      }
      OscEvent(): TObject() {
         oscCh = new TClonesArray("OscChannel");
         clear();
      }
      ~OscEvent() {
         delete oscCh;   oscCh = 0;
      }
      const OscChannel* oscChannel(int ich) const {return (const OscChannel*) oscCh->At(ich);}
      ClassDef(OscEvent, 1)
};

#ifdef __MAKECINT__
#pragma link C++ class OscChannel;
#pragma link C++ class OscEvent;
#endif

ClassImp(OscChannel);
ClassImp(OscEvent);

/*
.q
root -l drs.C+
t->Draw("y:x","ch==2")
*/
TTree* drs(const char* ifname="3_sig_sig-3events.xml")
{
   std::ifstream ifile(ifname);
   if (!ifile) {
      cout<< "File not found: " << ifname <<endl;
      return 0;
   }

   OscEvent* oscEvent = new OscEvent;

   TFile* ofile = TFile::Open(Form("%s.root",ifname), "recreate");
   TTree* tree = new TTree("t", "DRS4 tree");
   tree->Branch("oscEvent","OscEvent", &oscEvent);

   std::string line;
   std::stringstream ss;

   while (std::getline(ifile,line))
   {
      if (line.find("</DRSOSC>") != std::string::npos) {
         cout<< "Found </DRSOSC> ==> break" <<endl;
         break;
      }

      if (line.find("<DRSOSC>") != std::string::npos)
      {
         // start loop over events

         while (std::getline(ifile,line) && line.find("<Event>") != std::string::npos)
         {
            // start processing of the event

            oscEvent->clear();

            // read event number
            std::getline(ifile, line);

            // remove <Serial> and </Serial> from the line
            const std::string serial_begin = "<Serial>";
            const std::string serial_end = "</Serial>";
            line.replace(line.find(serial_begin), serial_begin.size(), " ");
            line.replace(line.find(serial_end), serial_end.size(), " ");

            ss.str("");
            ss << line;
            ss >> oscEvent->evt;
            //cout<< "oscEvent->evt = " << oscEvent->evt <<endl;

            // skip two lines with HUnit and VUnit
            std::getline(ifile, line);
            std::getline(ifile, line);

            while (getline(ifile,line) && line.find("<CHN") != std::string::npos)
            {
               // add oscilloscope channel

               //Int_t n = oscEvent->oscCh->GetEntries();
               //new ((*oscEvent->oscCh)[n]) OscChannel;
               //OscChannel* oscChannel = (OscChannel*) &oscEvent->oscCh[n];
               OscChannel* oscChannel = new ((*oscEvent->oscCh)[oscEvent->oscCh->GetEntries()]) OscChannel;

               const std::string chn_begin = "<CHN";
               line.replace(line.find(chn_begin), chn_begin.size(), " ");

               ss.str("");
               ss << line;
               ss >> oscChannel->ch;
               //cout<< "oscChannel->ch = " << oscChannel->ch <<endl;

               // read data for this oscilloscope channel in the current event
               for (int ichan=0; ichan<1024; ++ichan)
               {
                  std::getline(ifile,line);           // read current channel
                  // substitute the comma by space
                  line.replace(line.find(","), 1, " ");

                  // get rid of tag <Data>
                  const std::string data_begin = "<Data>";
                  const std::string data_end = "</Data>";
                  line.replace(line.find(data_begin), data_begin.size(), " ");
                  line.replace(line.find(data_end), data_end.size(), " ");

                  ss.str("");
                  ss << line;
                  ss >> oscChannel->x[ichan] >> oscChannel->y[ichan];
                  //cout<< "ichan " << ichan << " x " << oscChannel->x[ichan] << " y " << oscChannel->y[ichan] <<endl;
               }

               // skip line with </CHN
               std::getline(ifile,line);
            } // loop over oscilloscope channels

            //cout<< "--- End of event: line = " << line <<endl;
            //cout<< "end of event " << oscEvent->evt <<endl;

            //--
            //-- Fill the tree
            //--
            tree->Fill();
            Int_t nevent = tree->GetEntries();
            if (nevent == 100) cout<< "Filled event " << nevent <<endl;
            if (nevent % 1000 == 0) cout<< "Filled event " << nevent <<endl;
         } // loop over events
      }
   }

   cout<< "Total events filled: " << tree->GetEntries() << ". Output file is " << ofile->GetName() <<endl;
   ofile->Write();

   tree->ResetBranchAddresses();       // drop branches current objects and allocate new ones
   delete oscEvent;

   return tree;
}
