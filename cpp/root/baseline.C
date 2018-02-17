// Andriy.Zatserklyaniy@cern.ch     Aug 8, 2009

#include <TH1.h>
#include <TCanvas.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>

using std::cout;     using std::endl;

/*
Some remarks
------------
File contains huge number of lines, it's impossible to store all values in an array, so I fill histogram.
With CINT code works very slowly: compile with ACLiC

root -l 'baseline.C+(33,110315)'
*/

TH1F* baseline(Int_t fed=0, Int_t run=0)
{
   if (fed == 0 || run == 0) {
      cout<<endl<< "Usage:" <<endl;
      cout<<       "-----"  <<endl;
      cout<< "root> .L baseline.C+" <<endl;
      cout<< "root> baseline(33,110315)" <<endl;
      cout<<endl<< "or directly from UNIX command line:" <<endl;
      cout<< "root -l 'baseline.C+(33,110315)'" <<endl<<endl;
      return 0;
   }

   cout<< "fed = " << fed << " run = " << run <<endl;

   Int_t run000 = run/1000*1000;
   std::stringstream ifname;
   ifname.str("");
   ifname << "/pixel/data0/Run_" << run000 << "/Run_" << run << "/BaselineCorrectionFED_" << fed << "_" << run << ".txt";
   cout<< "ifname = " << ifname.str() <<endl;
   
   std::ifstream ifile(ifname.str().c_str());
   if (!ifile) {
      cout<< "***ERROR: file not found: " << ifname.str() <<endl;
   }

/*
File /pixel/data0/Run_110000/Run_110315/BaselineCorrectionFED_33_110315.txt

Time: Fri Aug  7 21:31:44 2009 : Baseline Correction for FED 0x13000000, Channel 1 has Mean=10.8 and StdDev=1.32665
Time: Fri Aug  7 21:31:45 2009 : Baseline Correction for FED 0x13000000, Channel 2 has Mean=11.3 and StdDev=1.18743
Time: Fri Aug  7 21:31:45 2009 : Baseline Correction for FED 0x13000000, Channel 3 has Mean=8.7 and StdDev=1.26886
Time: Fri Aug  7 21:31:45 2009 : Baseline Correction for FED 0x13000000, Channel 4 has Mean=10 and StdDev=1.84391
Time: Fri Aug  7 21:31:46 2009 : Baseline Correction for FED 0x13000000, Channel 5 has Mean=9 and StdDev=0.894427
Time: Fri Aug  7 21:31:46 2009 : Baseline Correction for FED 0x13000000, Channel 6 has Mean=8.6 and StdDev=1.2
Time: Fri Aug  7 21:31:46 2009 : Baseline Correction for FED 0x13000000, Channel 7 has Mean=8.6 and StdDev=0.663325
Time: Fri Aug  7 21:31:47 2009 : Baseline Correction for FED 0x13000000, Channel 8 has Mean=5.8 and StdDev=1.16619
Time: Fri Aug  7 21:31:47 2009 : Baseline Correction for FED 0x13000000, Channel 9 has Mean=10.6 and StdDev=1.0198
Time: Fri Aug  7 21:31:47 2009 : Baseline Correction for FED 0x13000000, Channel 10 has Mean=9.2 and StdDev=0.4
Time: Fri Aug  7 21:31:48 2009 : Baseline Correction for FED 0x13000000, Channel 11 has Mean=6 and StdDev=1.18322
Time: Fri Aug  7 21:31:48 2009 : Baseline Correction for FED 0x13000000, Channel 12 has Mean=6.7 and StdDev=0.9
Time: Fri Aug  7 21:31:48 2009 : Baseline Correction for FED 0x13000000, Channel 13 has Mean=5 and StdDev=1.09545
Time: Fri Aug  7 21:31:48 2009 : Baseline Correction for FED 0x13000000, Channel 14 has Mean=6 and StdDev=2.14476
Time: Fri Aug  7 21:31:48 2009 : Baseline Correction for FED 0x13000000, Channel 15 has Mean=9.4 and StdDev=1.68523
Time: Fri Aug  7 21:31:49 2009 : Baseline Correction for FED 0x13000000, Channel 16 has Mean=8.5 and StdDev=1.20416
Time: Fri Aug  7 21:31:49 2009 : Baseline Correction for FED 0x13000000, Channel 17 has Mean=12.2 and StdDev=1.16619
Time: Fri Aug  7 21:31:49 2009 : Baseline Correction for FED 0x13000000, Channel 18 has Mean=13 and StdDev=0.894427
Time: Fri Aug  7 21:31:49 2009 : Baseline Correction for FED 0x13000000, Channel 19 has Mean=7.1 and StdDev=0.830662
Time: Fri Aug  7 21:31:50 2009 : Baseline Correction for FED 0x13000000, Channel 20 has Mean=7.8 and StdDev=0.87178
Time: Fri Aug  7 21:31:50 2009 : Baseline Correction for FED 0x13000000, Channel 21 has Mean=4.4 and StdDev=1.35647
Time: Fri Aug  7 21:31:50 2009 : Baseline Correction for FED 0x13000000, Channel 22 has Mean=4.4 and StdDev=2.72764
Time: Fri Aug  7 21:31:50 2009 : Baseline Correction for FED 0x13000000, Channel 23 has Mean=10 and StdDev=1.94936
Time: Fri Aug  7 21:31:50 2009 : Baseline Correction for FED 0x13000000, Channel 24 has Mean=3.4 and StdDev=1.35647
...
*/

   // define two histogram: one big and one small
   TH1F* h200 = new TH1F(Form("hbaseline_fed%d_run%d_200", fed, run), Form("Baseline correction for FED %d, run %d;mean", fed, run), 400, -200, 200);
   h200->SetFillColor(2);
   h200->SetLineColor(2);
   TH1F* h = new TH1F(Form("hbaseline_fed%d_run%d", fed, run), Form("Baseline correction for FED %d, run %d;mean", fed, run), 200, -100, 100);
   h->SetFillColor(2);
   h->SetLineColor(2);

   std::string line;

   Float_t mean;
   // Float_t sigma;

   Int_t nlines = 0;
   while (getline(ifile,line))
   {
      ++nlines;
      if (nlines == 1000) cout<< "processing line " << nlines <<endl;
      if (nlines == 10000) cout<< "processing line " << nlines <<endl;
      if (nlines == 50000) cout<< "processing line " << nlines <<endl;
      if (nlines % 100000 == 0) cout<< "processing line " << nlines <<endl;
      // if (nlines % 1000 == 0) cout<< "read " << nlines << " lines" <<endl;
      // if (nlines == 10000+1) break;

      const std::string pattern = "Mean=";
      const size_t len = pattern.size();

      size_t pos = line.rfind(pattern) + len;
      sscanf(line.substr(pos).c_str(), "%f", &mean);

      h200->Fill(mean);
   }
   cout<< "Read " << nlines << " lines" <<endl;
   ifile.close();

   // for debug
   // h200->Fill(101);
   
   // do we have baseline over 100 in abs value?
   bool exceeds100 = false;
   for (int i=0; i<100; ++i) {
      Int_t bin_neg = i+1;
      Int_t bin_pos = 2*200 - 100 + i+1;
      if (h200->GetBinContent(bin_neg) > 0 || h200->GetBinContent(bin_pos) > 0) {
         exceeds100 = true;
         break;
      }
   }

   if (!exceeds100)
   {
      // copy (-100,100) to histogram h
      int shift = (h200->GetNbinsX() - h->GetNbinsX())/2;
      for (int i=1; i<=h->GetNbinsX(); ++i) {
         int i200 = shift + i;
         h->SetBinContent(i, h200->GetBinContent(i200));
      }
   }
   else {
      // remove empty histogram h
      h->SetDirectory(0);
      h->Delete();
      // change pointer h to h200
      h = h200;
   }

   new TCanvas;
   gPad->SetLogy();
   h->Draw();

   return h;
}
