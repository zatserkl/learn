// zatserkl@fnal.gov

/*
  NB: inverse quotes ``!
  g++ `$ROOTSYS/bin/root-config --cflags --glibs` -o sp3 sp3.C
*/
#include <TRint.h>          // the only include you need to call ROOT

#include <TTree.h>
#include <TFile.h>
#include <TH1.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TCut.h>
#include <TROOT.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

using std::cout;     using std::endl;

TH1* htemp(const char* name=0, const char* title=0);
TH1* htemp(const char* name, const char* title)
{
  if (gROOT->GetListOfCanvases()->GetEntries() == 0) {
    cout<< "No canvas found" <<endl;
    return 0;
  }
  TIter next(gPad->GetListOfPrimitives());
  TObject* obj = 0;
  while ((obj = next())) if (obj->IsA()->InheritsFrom("TH1")) break; else obj=0;
  if (!obj) return 0;
  TH1* h = (TH1*) obj;
  if (name && strlen(name) > 0) h->SetName(name);
  if (title && strlen(title) > 0) h->SetTitle(title);
  return h;
}

const char* nextcan(const char* base) {
   const char* cname = base;
   // if canvas 'cname' already exists increaments it like can_1, can_2, etc.
   // returns pointer to circular buffer owned by ROOT function Form
   int icycle = 0;
   while (gROOT->GetListOfCanvases()->FindObject(cname)) {
      cname = Form("%s_%d", base, ++icycle);
   }
   //cout<< "cname = " << cname <<endl;
   return cname;
}

//-- global pointer to the tree
TTree* t;
// limits
TCut sp_t1("sp_t1","t1>0&&t1<6000");
TCut sp_t2("sp_t2","t2>0&&t2<6000");
TCut sp_t3("sp_t3","t3>0&&t3<6000");
TCut sp_a1("sp_a1","a1>0&&a1<1024");
TCut sp_a2("sp_a2","a2>0&&a2<1024");
TCut sp_a3("sp_a3","a3>0&&a3<1024");
// pedestal
Double_t sp_ped[3] = {50, 37, 3};

//
// namespace Tree
//
namespace Tree
{
   Int_t evt;
   Int_t t1;
   Int_t t2;
   Int_t t3;
   Int_t a1;
   Int_t a2;
   Int_t a3;
   
   void clear()
   {
      evt      = 0;
      t1       = 0;
      t2       = 0;
      t3       = 0;
      a1       = 0;
      a2       = 0;
      a3       = 0;
   }
   
   void book(TTree* tree) {
      tree->Branch("evt",         &evt,        "evt/I");
      tree->Branch("t1",          &t1,         "t1/I");
      tree->Branch("t2",          &t2,         "t2/I");
      tree->Branch("t3",          &t3,         "t3/I");
      tree->Branch("a1",          &a1,         "a1/I");
      tree->Branch("a2",          &a2,         "a2/I");
      tree->Branch("a3",          &a3,         "a3/I");
   }
   void connect(TTree* tree)                                // need for event-by-event analysis
   {   
      // connects tree buffers with variables to use for event-by-event analysis
      // tree->SetBranchAddress("evt",           &evt);
      tree->SetBranchAddress("t1",            &t1);
      tree->SetBranchAddress("t2",            &t2);
      tree->SetBranchAddress("t3",            &t3);
      tree->SetBranchAddress("a1",            &a1);
      tree->SetBranchAddress("a2",            &a2);
      tree->SetBranchAddress("a3",            &a3);
   }
}  // namespace Tree

TTree* sp3(const char* ifname="data.out", const char* tree_name="t", Bool_t plot=kTRUE);
TTree* sp3(const char* ifname, const char* tree_name, Bool_t plot)
{
   TTree* tree_old = (TTree*) gDirectory->Get(tree_name);
   if (tree_old && strcmp(tree_old->GetTitle(), ifname)==0) delete tree_old;

   TTree* tree = new TTree(tree_name, ifname); // use ifname as a title
   Tree::book(tree);

   //-- assign to global pointer
   t = tree;

   std::ifstream ifile(ifname);
   if (!ifile) {
      cout<< "***ERROR : file not found: " << ifname <<endl;
      return 0;
   }

   Tree::clear();
   --Tree::evt;
   while (ifile
         >> Tree::t1
         >> Tree::t2
         >> Tree::t3
         >> Tree::a1
         >> Tree::a2
         >> Tree::a3
         )
   {
      ++Tree::evt;
      tree->Fill();
   }
   ifile.close();

   if (plot)
   {
      // TCanvas* can = new TCanvas;
      //gPad->SetWindowSize(1024,600);    // ROOT
      // can->SetWindowSize(1024,600);
      TCanvas* can = new TCanvas(nextcan(ifname), nextcan(ifname), 1024, 600);

      // can->Divide(2,1);
      // // can->cd(1); tree->Draw("t1", "t1>0&&t1<6000"); htemp()->Fit("gaus");
      // can->cd(1); tree->Draw("t1", "t1>0&&t1<6000");

      // // can->cd(2); tree->Draw("a1", "a1>1"); htemp()->Fit("gaus");
      // can->cd(2); tree->Draw("a1", "a1>1");
      // // Double_t gmean1 = htemp()->GetFunction("gaus")->GetParameter(1);
      // // Double_t gsigma1 = htemp()->GetFunction("gaus")->GetParameter(2);
      // // Double_t Npe1 = ((gmean1 - ped1)/gsigma1)*((gmean1 - ped1)/gsigma1);
      // // //cout<< "--> Fit parameters: gmean0 = " << gmean0 << " gsigma0 = " << gsigma0 <<endl;

      can->Divide(3,2);
      can->cd(1); tree->Draw("t1", sp_t1);
      can->cd(2); tree->Draw("t2", sp_t2);
      can->cd(3); tree->Draw("t3", sp_t3);
      can->cd(4); tree->Draw("a1", sp_a1);
      can->cd(5); tree->Draw("a2", sp_a2);
      can->cd(6); tree->Draw("a3", sp_a3);
      can->cd();
   }

   return tree;
}

void ampl()
{
   // TCanvas* can = new TCanvas(cname.c_str(), cname.c_str(), 1000,500);
   // TCanvas* can = new TCanvas(cname.c_str(), cname.c_str(), 1000,300);
   // TCanvas* can = new TCanvas;
   // can->Divide(3,1);
   // TCut cut;
   // if (plotmin > 0) cut += Form("a1>%d", plotmin);
   // if (plotmax > 0) cut += Form("a1<%d", plotmax);
   // t->Draw("a1", cut);
   // t->Draw("a1", cut); htemp()->Fit("gaus");
   // Double_t gmean1 = htemp()->GetFunction("gaus")->GetParameter(1);
   // Double_t gsigma1 = htemp()->GetFunction("gaus")->GetParameter(2);
   // Double_t Npe1 = ((gmean1 - ped1)/gsigma1)*((gmean1 - ped1)/gsigma1);
   // cout<< "Npe1 = " << Npe1 <<endl;
   // //cout<< "--> Fit parameters: gmean0 = " << gmean0 << " gsigma0 = " << gsigma0 <<endl;

   std::string cname = nextcan(Form("%s_ampl", t->GetTitle()));
   TCanvas* can = new TCanvas(cname.c_str(), cname.c_str(), 1000,300);
   can->Divide(3,1);
   TCut ampl_cut[3];
   ampl_cut[0] = sp_a1;
   ampl_cut[1] = sp_a1;
   ampl_cut[2] = sp_a3;

   for (int i=0; i<3; ++i) {
      can->cd(i+1);
      t->Draw(Form("a%d",i+1), ampl_cut[i]);
      htemp()->Fit("gaus");
      Double_t gmean = htemp()->GetFunction("gaus")->GetParameter(1);
      Double_t gsigma = htemp()->GetFunction("gaus")->GetParameter(2);
      Double_t Npe = ((gmean - sp_ped[i])/gsigma)*((gmean - sp_ped[i])/gsigma);
      cout<< "Npe = " << Npe <<endl;
      //cout<< "--> Fit parameters: gmean = " << gmean << " gsigma = " << gsigma <<endl;
   }
   can->cd(0);
}

// void time(Int_t plotmin=0, Int_t plotmax=6000, Int_t fitmin=0, Int_t fitmax=0)
// {
//    // TCanvas* can = new TCanvas(cname.c_str(), cname.c_str(), 1000,500);
//    // TCanvas* can = new TCanvas(cname.c_str(), cname.c_str(), 1000,300);
//    TCanvas* can = new TCanvas;
//    // can->Divide(3,1);
//    TCut cut;
//    if (plotmin > -1) cut += Form("t1>%d", plotmin);
//    if (plotmax > -1) cut += Form("t1<%d", plotmax);
//    t->Draw("t1", cut);
//    // t->Draw("t1", cut); htemp()->Fit("gaus");
//    // Double_t gmean1 = htemp()->GetFunction("gaus")->GetParameter(1);
//    // Double_t gsigma1 = htemp()->GetFunction("gaus")->GetParameter(2);
//    // cout<< "--> Fit parameters: gmean0 = " << gmean0 << " gsigma0 = " << gsigma0 <<endl;
// }

#if !defined(__CINT__) && !defined(__MAKECINT__)
int main(int argc, char *argv[])                   // w/o int will be warning ~ "no type"
{
  //for (int i=0; i<argc; ++i) cout<< i << " " << argv[i] <<endl;

  TRint* theApp = new TRint("Rint", 0, 0, 0, 0, 1);  // do not show splash screen

  const char* ifname = "";
  if (argc > 1) ifname = argv[1];
  const char* tree_name = "t";
  if (argc > 2) tree_name = argv[2];
  Bool_t plot = kTRUE;
  if (argc > 3) plot = std::atoi(argv[3]);
  //cout<< "ifname = " << ifname << " tree_name = " << tree_name << " plot = " << plot <<endl;

  // sp3(ifname, tree_name, plot);  //-- NB: global pointer t will NOT be seen by CINT!

  // work in command line mode
  cout<< argv[0] << ": load macro sp3.C" <<endl;
  //gROOT->LoadMacro("sp3.C");
  gROOT->ProcessLine(".L sp3.C");
  gROOT->ProcessLine(Form("sp3(\"%s\",\"%s\",%d)", ifname,tree_name,plot));
  theApp->Run();
  delete theApp;
}
#endif
