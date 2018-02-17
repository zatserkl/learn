/*
NB: inverse quotes ``!
g++ `$ROOTSYS/bin/root-config --cflags --glibs` xydy.C

the data file xydy_strict.dat is
        # this is a comment
// this is a commented out line too
 1   1   .5     t
2   20  2
3   30  3
4   25  3
5   35  4
100
# NB: last three lines: line with spaces " " and two empty lines
   

*/

#include <TRint.h>         // to build stand-along ROOT program
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <iostream>
#include <fstream>
#include <sstream>

using std::cout;     using std::endl;

TGraphErrors* xydy(const char* ifname="xydy_strict.dat")
{
   cout<< "Using data from " << ifname <<endl;

   std::ifstream ifile(ifname);

   if (!ifile) {
      cout<< "File not found: " << ifname <<endl;
      return 0;
   }

   const Int_t dim = 1000;
   Float_t x[dim], y[dim],dy[dim], dx[dim];
   Int_t np = 0;

   for (std::string line; std::getline(ifile,line);)
   {
      std::istringstream ss(line);

      //-- "strict" version of readout

      // analyze the first word in the line
      std::string word;
      ss >> word;
      if (ss.rdstate() & ss.failbit) continue;  // line contains whitespaces only
      if (word.find("#") == 0) continue;        // shell "#" comment
      if (word.find("//") == 0) continue;       // C++ "//" comment
      ss.seekg(0);   // set position to the beginning of the stream

      ss >> x[np] >> y[np] >> dy[np];
      cout<< np << "\t " << x[np] <<" "<< y[np] <<" "<< dy[np] <<endl;
      dx[np] = 0.;
      np++;
   }
   ifile.close();
   cout<< "Read " << np << " lines" <<endl;

   new TCanvas;

   gPad->SetFillColor(0);
   gPad->SetGrid(1,1);

   TGraphErrors *gr = new TGraphErrors(np,x,y,dx,dy);
   gr->SetMarkerStyle(20);
   gr->SetMarkerColor(2);
   gr->SetLineColor(2);
   gr->SetName("gr");
   gr->SetTitle("y vs x;abscissa;ordinate");
   gr->Draw("ap");

   // gPad->SaveAs("xydy.png");

   return gr;
}

#if !defined(__CINT__)
int main(int argc, char *argv[])                      // w/o int ACLiC warning ~ "no type"
{
   TRint* theApp = new TRint("Rint", 0, 0, 0, 0, 1);   // do not show splash screen

   const char* ifname = "xydy.dat";
   if (argc > 1) ifname = argv[1];

   xydy(ifname);

   // // work in command line mode
   // cout<< argv[0] << ": load macro xydy.C" <<endl;
   // gROOT->LoadMacro("xydyC");                       // add "+" to compile with ACLiC
   // if (ifname != "") gROOT->ProcessLine(Form("xydy(\"%s\")", ifname));
   // else              gROOT->ProcessLine("xydy()");

   theApp->Run();
   delete theApp;
}
#endif
