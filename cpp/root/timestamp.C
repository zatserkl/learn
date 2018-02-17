#include <TTimeStamp.h>
#include <TGraph.h>
#include <TAxis.h>      // need to include TAxis.h in spite of including of TGraph.h
#include <TCanvas.h>

#include <iostream>
#include <ctime>

using std::cout;     using std::endl;

void timestamp()
{
   // TTimeStamp tstamp(2008,10,22,16,56,47);
   TTimeStamp tstamp;         //-- NB: TTimeStamp tstamp() produces a comp. error!

   tstamp.Set(2008,10,22,16,56,47, 0,kTRUE,0);
   time_t sec = tstamp.GetSec();
   cout<< "sec = " << sec <<endl;
   
   struct tm* gmt = gmtime(&sec);
   cout
      << "year = " << gmt->tm_year + 1900
      << " month = " << gmt->tm_mon + 1
      << " day = " << gmt->tm_mday
      << " hour = " << gmt->tm_hour
      << " minute = " << gmt->tm_min
      << " second = " << gmt->tm_sec
   <<endl;

   Float_t xtime[100];
   Float_t value[100];
   Int_t np = 0;

   tstamp.Set(2008,10,22, 19,01,0,0,kTRUE,0);
   cout<< "tstamp.AsString() = " << tstamp.AsString() <<endl;
   xtime[np] = tstamp.GetSec();
   value[np] = 39;
   ++np;

   tstamp.Set(2008,10,23, 7,01,0,0,kTRUE,0);
   cout<< "tstamp.AsString() = " << tstamp.AsString() <<endl;
   xtime[np] = tstamp.GetSec();
   value[np] = 40;
   ++np;

   tstamp.Set(2008,10,23, 19,01,0,0,kTRUE,0);
   cout<< "tstamp.AsString() = " << tstamp.AsString() <<endl;
   xtime[np] = tstamp.GetSec();
   value[np] = 41;
   ++np;

   tstamp.Set(2008,10,24, 7,01,0,0,kTRUE,0);
   cout<< "tstamp.AsString() = " << tstamp.AsString() <<endl;
   xtime[np] = tstamp.GetSec();
   value[np] = 42;
   ++np;

   for (int i=0; i<np; ++i) {
      cout<< i << "\t xtime = " << xtime[i] << "\t value = " << value[i] <<endl;
   }

   TGraph* gr = new TGraph(np, xtime, value);
   gr->SetNameTitle("time","time plot;some time;some T^{o}C");
   gr->SetMarkerStyle(20);
   gr->GetXaxis()->SetTimeDisplay(1);
   gr->GetXaxis()->SetTimeFormat("%d-%H:%M");
   gr->GetXaxis()->SetNdivisions(506);

   new TCanvas;
   gr->Draw("awp");
}
