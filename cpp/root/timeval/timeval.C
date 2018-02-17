#include <iostream>
#include <fstream>

#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TH2.h>
#include <TAxis.h>    // need to be included in spite of included TGraph.h

#include "TimeValTree.h"

using std::cout;     using std::endl;

ClassImp(TimeValTree)

/*
.q
root -l
gStyle->SetTimeOffset(0)
.L timeval.C+
t = timeval()
t->Draw("val:time","")
// tax("#splitline{%y\/%d}{%H:%M}")
timax(t->GetHistogram()->GetXaxis(), "#splitline{%y\/%d}{%H:%M}")
new TCanvas
t->Draw("val:time","time>1225693573 && time<1225721413")
timax(t->GetHistogram()->GetXaxis(), "#splitline{%y\/%d}{%H:%M}")
*/

void timax(TAxis *axis, const char *format="")
{
   if (format == 0) {
      axis->SetTimeDisplay(0);
      return;
   }
   axis->SetTimeDisplay(1);
   axis->SetTimeFormat(format);
   gPad->Modified();
   gPad->Update();
}

TTree *timeval(const char *ifname="timeval.dat", const char *ofname="timeval.root", const char *dfname="timeval.txt")
{
   ifstream ifile(ifname);
   if (!ifile) {
      cout<< "File not found: " << ifname <<endl;
      return 0;
   }

   // text dump of the tree content
   ofstream dfile(dfname);

   TFile::Open(ofname, "recreate");
   TTree *tree = new TTree("t", "time tree");

   TimeValTree *timeval = new TimeValTree;
   tree->Branch("tv", "TimeValTree", &timeval);

   tree->SetMarkerStyle(7);
   tree->SetMarkerColor(2);

   Int_t year;
   Int_t mon;
   Int_t day;
   Int_t hour;
   Int_t min;
   Int_t sec;
   Float_t val;

   while (ifile >> year >> mon >> day >> hour >> min >> sec >> val) {
      timeval->Set(year, mon, day, hour, min, sec, val);
      dfile << year <<" "<< mon <<" "<< day <<" "<< hour <<" "<< min <<" "<< sec <<" "<< timeval->time <<" "<< val <<endl;
      tree->Fill();
   }
   ifile.close();
   dfile.close();

   cout<< "writing output file " << tree->GetCurrentFile()->GetName() << " with " << tree->GetEntries() << " events" <<endl;
   tree->GetCurrentFile()->Write();
   return tree;
}
