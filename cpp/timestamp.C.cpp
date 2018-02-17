/*
g++ `$ROOTSYS/bin/root-config --cflags --glibs` timestamp.C.cpp
*/

#include <TRint.h>          // the only include you need
#include <TROOT.h>          // to use gPad, etc.
#include <TTimeStamp.h>

#include <iostream>
#include <cstdarg>
#include <ctime>

#include <TH1.h>
#include <TCanvas.h>

using std::cout;      using std::endl;

main(int argc, char *argv[])
{
  TRint* theApp = new TRint("Rint", &argc, argv, 0, 0, 1);  // do not show splash screen

  // code starts here

   // TTimeStamp tstamp(2008,10,22,16,56,47);
   TTimeStamp tstamp;

   tstamp.Set(2008,10,22, 19,01,0,0,kTRUE,0);
   time_t sec = tstamp.GetSec();
   cout<< "sec = " << sec <<endl;

   const tm* gmt = gmtime(&sec);
   cout
      << "year = " << gmt->tm_year + 1900
      << " month = " << gmt->tm_mon + 1
      << " day = " << gmt->tm_mday
      << " hour = " << gmt->tm_hour
      << " minute = " << gmt->tm_min
      << " second = " << gmt->tm_sec
   <<endl;

  // work in command line mode
  theApp->Run();
  delete theApp;
}

