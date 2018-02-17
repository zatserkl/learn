// 26-JUL-07 Andriy Zatserklyaniy <zatserkl@fnal.gov>

const char* nextname(const char* base) {
  // if name 'base' already exists increaments it like h_1, h_2, etc.
  // returns pointer to circular buffer owned by ROOT function Form
  bool found = gDirectory->Get(base);
  if (!found) return base;
  Int_t icycle = 0;
  while (found) {
    stringstream ss;
    ss.str("");
    ss << base << "_" << ++icycle;
    //cout<< "   current hname: " << ss.str() <<endl;
    found = gDirectory->Get(ss.str().c_str());
  }
  //cout<< "new hname: " << Form("%s_%d",base,icycle) <<endl;
  return Form("%s_%d",base,icycle);
}

//
// namespace Tree
//
namespace Tree
{
   Int_t    n;
//    Bool_t   LIR;
//    Bool_t   HIR;
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
  
   void clear()
   {
      n  = 0;
      LIR = 0;
      HIR = 0;
      Vaa = 0;
      Vdd = 0;
      rtd2 = 0;
      rtd3 = 0;
      aoh = 0;
      Vpc = 0;
      Vbg = 0;
      ts = 0;
   }
  
   void book(TTree* tree) {
      tree->Branch("n",           &n,           "n/I");
//       tree->Branch("LIR",         &LIR,         "LIR/B");
//       tree->Branch("HIR",         &HIR,         "HIR/B");
      tree->Branch("LIR",         &LIR,         "LIR/I");
      tree->Branch("HIR",         &HIR,         "HIR/I");
      tree->Branch("Vaa",         &Vaa,         "Vaa");
      tree->Branch("Vdd",         &Vdd,         "Vdd");
      tree->Branch("rtd2",        &rtd2,        "rtd2");
      tree->Branch("rtd3",        &rtd3,        "rtd3");
      tree->Branch("aoh",         &aoh,         "aoh");
      tree->Branch("Vpc",         &Vpc,         "Vpc");          // By default equivalent to "a0/F"
      tree->Branch("Vbg",         &Vbg,         "Vbg");
      tree->Branch("ts",          &ts,          "ts");
   }
   void connect(TTree* tree)                                // need for event-by-event analysis
   {  
      // connects tree buffers with variables to use for event-by-event analysis
      tree->SetBranchAddress("n",             &n);
      tree->SetBranchAddress("LIR",           &LIR);
      tree->SetBranchAddress("HIR",           &HIR);
      tree->SetBranchAddress("Vaa",           &Vaa);
      tree->SetBranchAddress("Vdd",           &Vdd);
      tree->SetBranchAddress("rtd2",          &rtd2);
      tree->SetBranchAddress("rtd3",          &rtd3);
      tree->SetBranchAddress("aoh",           &aoh);
      tree->SetBranchAddress("Vpc",           &Vpc);
      tree->SetBranchAddress("Vbg",           &Vbg);
      tree->SetBranchAddress("ts",            &ts);
   }
}  // namespace Tree

//////////////////////////////////////////////////////////
//
//   dcutree
//
//////////////////////////////////////////////////////////

TTree* dcutree(const char* ifname_dat="dcu.dat", Int_t color=2);
TTree* dcutree(const char* ifname_dat, Int_t color)
{  
  gROOT->SetStyle("Plain");
  gStyle->SetCanvasBorderMode(1);
  gStyle->SetPadBorderMode(1);
  gStyle->SetOptStat(1111);
  gStyle->SetOptFit(111);
  gStyle->SetCanvasColor(0);
  gStyle->SetCanvasDefH(320);
  gStyle->SetCanvasDefW(420);
  gStyle->SetCanvasDefX(0);
  gStyle->SetCanvasDefY(0);
  gStyle->SetPadGridX(kTRUE);
  gStyle->SetPadGridY(kTRUE);
  gStyle->SetNdivisions(507,"XYZ");

  TFile* ofile = TFile::Open(Form("%s.root",ifname_dat), "recreate");

  TTree* tree = new TTree("dcu","tree example");
  tree->SetMarkerStyle(6);
  tree->SetMarkerColor(color);
  tree->SetLineColor(color);
  Tree::book(tree);
    
  Float_t Vaa_LIR, Vdd_LIR, rtd2_LIR, rtd3_LIR, aoh_LIR, Vpc_LIR, Vbg_LIR, ts_LIR;
  Float_t Vaa_HIR, Vdd_HIR, rtd2_HIR, rtd3_HIR, aoh_HIR, Vpc_HIR, Vbg_HIR, ts_HIR;

  ifstream ifile_dat(ifname_dat);
  if (!ifile_dat.is_open()) {
     cout<< "File not found: " << ifname_tem <<endl;
     return 0;
  }
 
  Int_t nline = 0;
  while (ifile_dat
          >> Vaa_LIR  >> Vaa_HIR
          >> Vdd_LIR  >> Vdd_HIR
          >> rtd2_LIR >> rtd2_HIR
          >> rtd3_LIR >> rtd3_HIR
          >> aoh_LIR  >> aoh_HIR
          >> Vpc_LIR  >> Vpc_HIR
          >> Vbg_LIR  >> Vbg_HIR
          >> ts_LIR   >> ts_HIR
        )
  {
    ++nline;
    // fill tree
    Tree::n  = nline;
    // LIR
    Tree::LIR = 1;
    Tree::HIR = 0;
    Tree::Vaa = Vaa_LIR;
    Tree::Vdd = Vdd_LIR;
    Tree::rtd2 = rtd2_LIR;
    Tree::rtd3 = rtd3_LIR;
    Tree::aoh = aoh_LIR;
    Tree::Vpc = Vpc_LIR;
    Tree::Vbg = Vbg_LIR;
    Tree::ts = ts_LIR;
    tree->Fill();
    // HIR
    Tree::LIR = 0;
    Tree::HIR = 1;
    Tree::Vaa = Vaa_HIR;
    Tree::Vdd = Vdd_HIR;
    Tree::rtd2 = rtd2_HIR;
    Tree::rtd3 = rtd3_HIR;
    Tree::aoh = aoh_HIR;
    Tree::Vpc = Vpc_HIR;
    Tree::Vbg = Vbg_HIR;
    Tree::ts = ts_HIR;
    tree->Fill();
  }
  cout<< "Read " << nline << " lines" <<endl;
  ifile_dat.close();
 
  ofile->Write();
  return tree;
}

Float_t correlation(Int_t n, Float_t x[], Float_t y[])
{
  //-- Float_t* w = new Float_t(n);   // ROOT
  Double_t w[10000];
  for (int i=0; i<n; ++i) w[i] = 1.;
 
  Float_t xmean = TMath::Mean(n, x, w);
  Float_t sx = TMath::RMS(n, x);
  Float_t ymean = TMath::Mean(n, y, w);
  Float_t sy = TMath::RMS(n, y);
 
  Float_t sxy = 0;
  for (int i=0; i<n; ++i) {
    sxy += (x[i] - xmean) * (y[i] - ymean);
  }
  sxy /= n;
 
  Float_t r = sxy/sx/sy;
 
  // cout<< "xmean = " << xmean << " ymean = " << ymean << " sx = " << sx << " sy = " << sy << " sxy = " << sxy <<endl;
 
  //delete[] w;
  return r;
}

void anatree(const char* ifname="dcu.dat", Int_t color=2);
void anatree(const char* ifname, Int_t color;)
{
  //TFile* ifile = TFile::Open(ifname);
  //if (!ifile) return;
  //
  //TTree* tree = (TTree*) ifile->Get("dcu");
  //if (!tree) {
  //  cout<< "Could not find tree dcu in file " << ifile->GetName() << endl;
  //  return 0;
  //}

  dcutree(ifname, color);

  TTree* tree = (TTree*) gDirectory->Get("dcu");
 
  Float_t Vaa_LIR[10000], Vdd_LIR[10000], rtd2_LIR[10000], rtd3_LIR[10000], aoh_LIR[10000], Vpc_LIR[10000], Vbg_LIR[10000], ts_LIR[10000];
  Float_t Vaa_HIR[10000], Vdd_HIR[10000], rtd2_HIR[10000], rtd3_HIR[10000], aoh_HIR[10000], Vpc_HIR[10000], Vbg_HIR[10000], ts_HIR[10000];

  Tree::connect(tree);
 
  Int_t n_LIR = 0;
  Int_t n_HIR = 0;
  for (Int_t ientry=0; ientry<tree->GetEntries(); ++ientry) {
    tree->GetEntry(ientry);
    if (Tree::LIR) {
      ++n_LIR;
      Vaa_LIR[ientry] = Tree::Vaa;
      Vdd_LIR[ientry] = Tree::Vdd;
      rtd2_LIR[ientry] = Tree::rtd2;
      rtd3_LIR[ientry] = Tree::rtd3;
      aoh_LIR[ientry] = Tree::aoh;
      Vpc_LIR[ientry] = Tree::Vpc;
      Vbg_LIR[ientry] = Tree::Vbg;
      ts_LIR[ientry] = Tree::ts;
    }
    else {
      ++n_HIR;
      Vaa_HIR[ientry] = Tree::Vaa;
      Vdd_HIR[ientry] = Tree::Vdd;
      rtd2_HIR[ientry] = Tree::rtd2;
      rtd3_HIR[ientry] = Tree::rtd3;
      aoh_HIR[ientry] = Tree::aoh;
      Vpc_HIR[ientry] = Tree::Vpc;
      Vbg_HIR[ientry] = Tree::Vbg;
      ts_HIR[ientry] = Tree::ts;
    }
  }
 
  Float_t r;
  r = correlation(n_LIR, rtd3_LIR, Vdd_LIR);
  cout<< "correlation rtd3_LIR and Vdd_LIR = " << r << endl;
 
  cout<< "correlation rtd2_LIR and rtd3_LIR = " << correlation(n_LIR, rtd2_LIR, rtd3_LIR) << endl;
 
//   new TCanvas();
//   dcu->Draw("Vdd_rtd3:n","");
//
//   new TCanvas();
//   dcu->Draw("rtd3*1.25/Vdd_rtd3:n","");
//
//   new TCanvas();
//   dcu->Draw("rtd3*1.25/Vdd_rtd3","");
//
//   new TCanvas();
//   dcu->Draw("rtd3*1.25/Vdd_rtd3","n>800");
//
//   new TCanvas();
//   dcu->Draw("ts*1.25/Vdd_ts:n","");
//
//   new TCanvas();
//   dcu->Draw("rtd2*1.25/Vdd_rtd2:n","");
//
//   new TCanvas();
//   dcu->Draw("rtd2*1.25/Vdd_rtd2","");
}

void calib_rtd3()
{
   const char ifname_tem[] ="dcu-glass-7.64-18.35-3010points-161min_temperature.dat";
   const char ifname_dat[] ="dcu-glass-7.64-18.35-3010points-161min.dat";
   
   Int_t ipoint_start = 100;     // start calibration from ipoint=nstart
   Int_t ipoint_end = 3010;      // end of calibration
  
   TGraph* grtem = new TGraph(ifname_tem);
   grtem->SetMarkerStyle(6);
   new TCanvas;
   grtem->Draw("AWP");
  
   TF1* ftem_rtd3 = new TF1("ftem_rtd3", "pol4", ipoint_start, ipoint_end);
   ftem_rtd3->SetLineWidth(1);
   ftem_rtd3->SetLineColor(4);
   
   grtem->Fit(ftem_rtd3, "R");
   
//    new TCanvas;
//    ftem_rtd3->Draw();
   
   Int_t npMax = 10000;
   Float_t* t  = new Float_t[npMax];
   Float_t* dt = new Float_t[npMax];
   Float_t* a  = new Float_t[npMax];
   Float_t* da = new Float_t[npMax];
  
   TTree* tree = dcutree(ifname_dat);
   if (!tree) return;
   
   Tree::connect(tree);
   Int_t np = 0;
   for (Int_t ientry=0; ientry<tree->GetEntries(); ++ientry) {
      tree->GetEntry(ientry);
      //if (Tree::n < ipoint_start) continue;
      //if (Tree::n > ipoint_end) break;
      if (Tree::n < ftem_rtd3->GetXmin()) continue;
      if (Tree::n > ftem_rtd3->GetXmax()) break;
      
      // HIR mode
      if (Tree::HIR == 0) continue;
      
      a[np]    = Tree::rtd3*2500./Tree::Vdd;
      da[np]   = 1;
      t[np]    = ftem_rtd3->Eval(Tree::n);
      dt[np]   = 0.01;
      //cout<< "np = " << np << "\t t[np] = " << t[np] <<endl;
      ++np;
   }
   cout<< "np = " << np << " t[0] = " << t[0] << " t[np] = " << t[np-1] <<endl;
   
//    Float_t* x  = t;
//    Float_t* y  = a;
//    Float_t* dx = dt;
//    Float_t* dy = da;
   Float_t* x  = a;
   Float_t* y  = t;
   Float_t* dx = da;
   Float_t* dy = dt;
   cout<< "np = " << np << " x[0] = " << x[0] << " x[np] = " << x[np-1] <<endl;
   
   TGraphErrors* grcal_rtd3 = new TGraphErrors(np, x, y, dx, dy);
   grcal_rtd3->SetName("grcal_rtd3");
   grcal_rtd3->SetTitle("Temperature calibration rtd3");
   grcal_rtd3->SetMarkerStyle(6);
   grcal_rtd3->SetMarkerColor(2);
   grcal_rtd3->SetLineColor(2);
  
   new TCanvas;
   grcal_rtd3->Draw("AWP");
   
   TF1* fcal_rtd3 = new TF1("fcal_rtd3", "pol1", x[0], x[np-1]);
   fcal_rtd3->SetLineWidth(1);
   fcal_rtd3->SetLineColor(8);
   
   grcal_rtd3->Fit(fcal_rtd3, "R");
   
   // fcal_rtd3->SetRange(0,25);
   fcal_rtd3->SetRange(1800, 2000);
   
   new TCanvas;
   fcal_rtd3->Draw();
   
   // // calib_rtd3()
   // Fitting results:
   // Parameters:
   // NO.             VALUE           ERROR
   // 0       7.321438e+00    5.591105e-01
   // 1       6.114978e-03    2.765406e-03
   // 2       -2.956067e-07   3.558403e-06
   // 3       -3.474200e-10   1.728343e-09
   // 4       5.828068e-14    2.804610e-13
   // Read 3013 lines
   // np = 2911 t[0] = 7.92964 t[np] = 18.3588
   // np = 2911 x[0] = 1910.55 x[np] = 1935.45
   // Fitting results:
   // Parameters:
   // NO.             VALUE           ERROR
   // 0       -7.683216e+02   4.953969e-02
   // 1       4.064047e-01    2.572120e-05
}


void calib_rtd2()
{
   const char ifname_tem[] ="dcu-glass-7.64-18.35-3010points-161min_temperature.dat";
   const char ifname_dat[] ="dcu-glass-7.64-18.35-3010points-161min.dat";
   
   Int_t ipoint_start = 100;     // start calibration from ipoint=nstart
   Int_t ipoint_end = 3010;      // end of calibration
  
   TGraph* grtem = new TGraph(ifname_tem);
   grtem->SetMarkerStyle(6);
   new TCanvas;
   grtem->Draw("AWP");
  
   TF1* ftem_rtd2 = new TF1("ftem_rtd2", "pol4", ipoint_start, ipoint_end);
   ftem_rtd2->SetLineWidth(1);
   ftem_rtd2->SetLineColor(4);
   
   grtem->Fit(ftem_rtd2, "R");
   
//    new TCanvas;
//    ftem_rtd2->Draw();
   
   Int_t npMax = 10000;
   Float_t* t  = new Float_t[npMax];
   Float_t* dt = new Float_t[npMax];
   Float_t* a  = new Float_t[npMax];
   Float_t* da = new Float_t[npMax];
  
   TTree* tree = dcutree(ifname_dat);
   if (!tree) return;
   
   Tree::connect(tree);
   Int_t np = 0;
   for (Int_t ientry=0; ientry<tree->GetEntries(); ++ientry) {
      tree->GetEntry(ientry);
      //if (Tree::n < ipoint_start) continue;
      //if (Tree::n > ipoint_end) break;
      if (Tree::n < ftem_rtd2->GetXmin()) continue;
      if (Tree::n > ftem_rtd2->GetXmax()) break;
      
      // HIR mode
      if (Tree::HIR == 0) continue;
      
      a[np]    = Tree::rtd2*2500./Tree::Vdd;
      da[np]   = 1;
      t[np]    = ftem_rtd2->Eval(Tree::n);
      dt[np]   = 0.01;
      //cout<< "np = " << np << "\t t[np] = " << t[np] <<endl;
      ++np;
   }
   cout<< "np = " << np << " t[0] = " << t[0] << " t[np] = " << t[np-1] <<endl;
   
//    Float_t* x  = t;
//    Float_t* y  = a;
//    Float_t* dx = dt;
//    Float_t* dy = da;
   Float_t* x  = a;
   Float_t* y  = t;
   Float_t* dx = da;
   Float_t* dy = dt;
   cout<< "np = " << np << " x[0] = " << x[0] << " x[np] = " << x[np-1] <<endl;
   
   TGraphErrors* grcal_rtd2 = new TGraphErrors(np, x, y, dx, dy);
   grcal_rtd2->SetName("grcal_rtd2");
   grcal_rtd2->SetTitle("Temperature calibration rtd2");
   grcal_rtd2->SetMarkerStyle(6);
   grcal_rtd2->SetMarkerColor(2);
   grcal_rtd2->SetLineColor(2);
  
   new TCanvas;
   grcal_rtd2->Draw("AWP");
   
   TF1* fcal_rtd2 = new TF1("fcal_rtd2", "pol1", x[0], x[np-1]);
   fcal_rtd2->SetLineWidth(1);
   fcal_rtd2->SetLineColor(8);
   
   grcal_rtd2->Fit(fcal_rtd2, "R");
   
   // fcal_rtd2->SetRange(0,25);
   fcal_rtd2->SetRange(480, 580);
   
   new TCanvas;
   fcal_rtd2->Draw();
   
   // // calib_rtd2()
   // Fitting results:
   // Parameters:
   // NO.             VALUE           ERROR
   // 0       7.321438e+00    5.591105e-01
   // 1       6.114978e-03    2.765406e-03
   // 2       -2.956067e-07   3.558403e-06
   // 3       -3.474200e-10   1.728343e-09
   // 4       5.828068e-14    2.804610e-13
   // Read 3013 lines
   // np = 2911 t[0] = 7.92964 t[np] = 18.3588
   // np = 2911 x[0] = 511.453 x[np] = 530.004
   // Fitting results:
   // Parameters:
   // NO.             VALUE           ERROR
   // 0       -2.846555e+02   1.838212e-02
   // 1       5.721595e-01    3.515777e-05
}

////////////////////////////////////////////////////////////////////////////////////

void calib_rtd3_tmp()
{
   const char ifname_tem[] ="dcu-tem.dat";
   const char ifname_dat[] ="dcu.dat";
  
   TGraph* grtem = new TGraph(ifname_tem);
   grtem->SetMarkerStyle(6);
   //grtem->SetMarkerStyle(1);
   new TCanvas;
   grtem->Draw("AWP");
   
//    Int_t ipoint_start = 100;     // start calibration from ipoint=nstart
//    Int_t ipoint_end = 3010;      // end of calibration
   Int_t ipoint_start = 0;     // start calibration from ipoint=nstart
   Int_t ipoint_end = 0;      // end of calibration
   
   if (ipoint_start == 0)  ipoint_start   = grtem->GetXaxis()->GetXmin();
   if (ipoint_end == 0)    ipoint_end     = grtem->GetXaxis()->GetXmax();
  
   TF1* ftem_rtd3 = new TF1("ftem_rtd3", "pol4", ipoint_start, ipoint_end);
   ftem_rtd3->SetLineWidth(1);
   ftem_rtd3->SetLineColor(4);
   
   grtem->Fit(ftem_rtd3, "R");
   
//    new TCanvas;
//    ftem_rtd3->Draw();
   
   Int_t npMax = 10000;
   Float_t* t  = new Float_t[npMax];
   Float_t* dt = new Float_t[npMax];
   Float_t* a  = new Float_t[npMax];
   Float_t* da = new Float_t[npMax];
  
   TTree* tree = dcutree(ifname_dat);
   if (!tree) return;
   
   Tree::connect(tree);
   Int_t np = 0;
   for (Int_t ientry=0; ientry<tree->GetEntries(); ++ientry) {
      tree->GetEntry(ientry);
      //if (Tree::n < ipoint_start) continue;
      //if (Tree::n > ipoint_end) break;
      if (Tree::n < ftem_rtd3->GetXmin()) continue;
      if (Tree::n > ftem_rtd3->GetXmax()) break;
      
      // HIR mode
      if (Tree::HIR == 0) continue;
      
      a[np]    = Tree::rtd3*2500./Tree::Vdd;
      da[np]   = 0.5;
      t[np]    = ftem_rtd3->Eval(Tree::n);
      dt[np]   = 0.01;
      //cout<< "np = " << np << "\t t[np] = " << t[np] <<endl;
      ++np;
   }
   cout<< "np = " << np << " t[0] = " << t[0] << " t[np] = " << t[np-1] <<endl;
   
//    Float_t* x  = t;
//    Float_t* y  = a;
//    Float_t* dx = dt;
//    Float_t* dy = da;
   Float_t* x  = a;
   Float_t* y  = t;
   Float_t* dx = da;
   Float_t* dy = dt;
   cout<< "np = " << np << " x[0] = " << x[0] << " x[np] = " << x[np-1] <<endl;
   
   TGraphErrors* grcal_rtd3 = new TGraphErrors(np, x, y, dx, dy);
   grcal_rtd3->SetName("grcal_rtd3");
   grcal_rtd3->SetTitle("Temperature calibration rtd3");
   // grcal_rtd3->SetMarkerStyle(6);
   grcal_rtd3->SetMarkerStyle(1);
   grcal_rtd3->SetMarkerColor(2);
   grcal_rtd3->SetLineColor(2);
  
   new TCanvas;
   grcal_rtd3->Draw("AWP");
   
   TF1* fcal_rtd3 = new TF1("fcal_rtd3", "pol1", x[0], x[np-1]);
   fcal_rtd3->SetLineWidth(1);
   fcal_rtd3->SetLineColor(8);
   
   grcal_rtd3->Fit(fcal_rtd3, "R");
   
   // fcal_rtd3->SetRange(0,25);
   //fcal_rtd3->SetRange(1800, 2000);
   
   new TCanvas;
   fcal_rtd3->Draw();
   
   // // calib_rtd3()
   // Fitting results:
   // Parameters:
   // NO.             VALUE           ERROR
   // 0       7.321438e+00    5.591105e-01
   // 1       6.114978e-03    2.765406e-03
   // 2       -2.956067e-07   3.558403e-06
   // 3       -3.474200e-10   1.728343e-09
   // 4       5.828068e-14    2.804610e-13
   // Read 3013 lines
   // np = 2911 t[0] = 7.92964 t[np] = 18.3588
   // np = 2911 x[0] = 1910.55 x[np] = 1935.45
   // Fitting results:
   // Parameters:
   // NO.             VALUE           ERROR
   // 0       -7.683216e+02   4.953969e-02
   // 1       4.064047e-01    2.572120e-05
}

void calib_rtd3_second()
{
   const char ifname_tem[] ="dcu-glass-5.59-17.70-2530points-135min_temperature.dat";
   const char ifname_dat[] ="dcu-glass-5.59-17.70-2530points-135min.dat";
  
   TGraph* grtem = new TGraph(ifname_tem);
   grtem->SetMarkerStyle(6);
   //grtem->SetMarkerStyle(1);
   new TCanvas;
   grtem->Draw("AWP");
   
//    Int_t ipoint_start = 100;     // start calibration from ipoint=nstart
//    Int_t ipoint_end = 3010;      // end of calibration
   Int_t ipoint_start = 0;     // start calibration from ipoint=nstart
   Int_t ipoint_end = 0;      // end of calibration
   
   if (ipoint_start == 0)  ipoint_start   = grtem->GetXaxis()->GetXmin();
   if (ipoint_end == 0)    ipoint_end     = grtem->GetXaxis()->GetXmax();
  
   TF1* ftem_rtd3 = new TF1("ftem_rtd3", "pol4", ipoint_start, ipoint_end);
   ftem_rtd3->SetLineWidth(1);
   ftem_rtd3->SetLineColor(4);
   
   grtem->Fit(ftem_rtd3, "R");
   
//    new TCanvas;
//    ftem_rtd3->Draw();
   
   Int_t npMax = 10000;
   Float_t* t  = new Float_t[npMax];
   Float_t* dt = new Float_t[npMax];
   Float_t* a  = new Float_t[npMax];
   Float_t* da = new Float_t[npMax];
  
   TTree* tree = dcutree(ifname_dat);
   if (!tree) return;
   
   Tree::connect(tree);
   Int_t np = 0;
   for (Int_t ientry=0; ientry<tree->GetEntries(); ++ientry) {
      tree->GetEntry(ientry);
      //if (Tree::n < ipoint_start) continue;
      //if (Tree::n > ipoint_end) break;
      if (Tree::n < ftem_rtd3->GetXmin()) continue;
      if (Tree::n > ftem_rtd3->GetXmax()) break;
      
      // HIR mode
      if (Tree::HIR == 0) continue;
      
      a[np]    = Tree::rtd3*2500./Tree::Vdd;
      da[np]   = 0.5;
      t[np]    = ftem_rtd3->Eval(Tree::n);
      dt[np]   = 0.01;
      //cout<< "np = " << np << "\t t[np] = " << t[np] <<endl;
      ++np;
   }
   cout<< "np = " << np << " t[0] = " << t[0] << " t[np] = " << t[np-1] <<endl;
   
//    Float_t* x  = t;
//    Float_t* y  = a;
//    Float_t* dx = dt;
//    Float_t* dy = da;
   Float_t* x  = a;
   Float_t* y  = t;
   Float_t* dx = da;
   Float_t* dy = dt;
   cout<< "np = " << np << " x[0] = " << x[0] << " x[np] = " << x[np-1] <<endl;
   
   TGraphErrors* grcal_rtd3 = new TGraphErrors(np, x, y, dx, dy);
   grcal_rtd3->SetName("grcal_rtd3");
   grcal_rtd3->SetTitle("Temperature calibration rtd3;ADC counts;T,^{o}C");
   // grcal_rtd3->SetMarkerStyle(6);
   grcal_rtd3->SetMarkerStyle(1);
   grcal_rtd3->SetMarkerColor(2);
   grcal_rtd3->SetLineColor(2);
  
   new TCanvas;
   grcal_rtd3->Draw("AWP");
   
   TF1* fcal_rtd3 = new TF1("fcal_rtd3", "pol1", x[0], x[np-1]);
   fcal_rtd3->SetLineWidth(2);
   fcal_rtd3->SetLineColor(8);
   
   grcal_rtd3->Fit(fcal_rtd3, "R");
   
   TGraph* grcal_rtd3_tgraph = new TGraph(*grcal_rtd3);
   new TCanvas;
   grcal_rtd3_tgraph->Draw("AWP");
   
   // fcal_rtd3->SetRange(0,25);
   //fcal_rtd3->SetRange(1800, 2000);
   
   new TCanvas;
   fcal_rtd3->Draw();
}

/*
.q
root -l
.L dcutree.C
calib_rtd3_test("dcu-glass-7.64-18.35-3010points-161min_temperature.dat", "dcu-glass-7.64-18.35-3010points-161min.dat", 0, 1, 100)

calib_rtd3_test("dcu-glass-5.59-17.70-2530points-135min_temperature.dat", "dcu-glass-5.59-17.70-2530points-135min.dat", 0, 2)
*/
void calib_rtd3_test
      (
      const char ifname_tem[] = "dcu-glass-7.64-18.35-3010points-161min_temperature.dat", const char ifname_dat[] = "dcu-glass-7.64-18.35-3010points-161min.dat"
      , Int_t modeLIR = 0             // modeLIR = 0: HIR mode, modeLIR = 1: LIR mode
      , Int_t dataset = 0
      , Int_t ipoint_start = 0      // start calibration from ipoint=nstart
      , Int_t ipoint_end = 0        // end of calibration
      )
{
   // Get temperature graph
   
   TGraph* grtem = new TGraph(ifname_tem);
   grtem->SetName(Form("grtem%d",dataset));
   grtem->SetMarkerStyle(6);
   //grtem->SetMarkerStyle(1);
   new TCanvas;
   grtem->Draw("AWP");
   
   if (ipoint_start == 0)  ipoint_start   = grtem->GetXaxis()->GetXmin();
   if (ipoint_end == 0)    ipoint_end     = grtem->GetXaxis()->GetXmax();
   
   TF1* ftem = new TF1(Form("ftem%d",dataset), "pol4", ipoint_start, ipoint_end);
   ftem->SetLineWidth(1);
   ftem->SetLineColor(4);
   
   grtem->Fit(ftem, "R");
   
   //
   // get graph with rtd
   //
   Float_t* rtd = &Tree::rtd3;
   
   Int_t npMax = 10000;
   Float_t* t  = new Float_t[npMax];
   Float_t* dt = new Float_t[npMax];
   Float_t* a  = new Float_t[npMax];
   Float_t* da = new Float_t[npMax];
  
   TTree* tree = dcutree(ifname_dat);
   if (!tree) return;
   
   Tree::connect(tree);
   Int_t np = 0;
   for (Int_t ientry=0; ientry<tree->GetEntries(); ++ientry) {
      tree->GetEntry(ientry);
      //if (Tree::n < ipoint_start) continue;
      //if (Tree::n > ipoint_end) break;
      if (Tree::n < ftem->GetXmin()) continue;
      if (Tree::n > ftem->GetXmax()) break;
      
      // mode
      if (Tree::LIR != modeLIR) continue;
      
      a[np]    = (*rtd)*2500./Tree::Vdd;        //-- access to rtd
      da[np]   = 0.5;
      t[np]    = ftem->Eval(Tree::n);
      dt[np]   = 0.01;
      //cout<< "np = " << np << "\t t[np] = " << t[np] <<endl;
      ++np;
   }
   cout<< "np = " << np << " t[0] = " << t[0] << " t[np] = " << t[np-1] <<endl;
   
//    Float_t* x  = t;
//    Float_t* y  = a;
//    Float_t* dx = dt;
//    Float_t* dy = da;
   Float_t* x  = a;
   Float_t* y  = t;
   Float_t* dx = da;
   Float_t* dy = dt;
   cout<< "np = " << np << " x[0] = " << x[0] << " x[np] = " << x[np-1] <<endl;
   
   TGraphErrors* grcal = new TGraphErrors(np, x, y, dx, dy);
   grcal->SetName(Form("grcal%d",dataset));
   grcal->SetTitle(Form("Temperature calibration rtd, dataset %d;ADC counts;T,^{o}C",dataset));
   // grcal->SetMarkerStyle(6);
   grcal->SetMarkerStyle(1);
   grcal->SetMarkerColor(2);
   grcal->SetLineColor(2);
  
   new TCanvas;
   grcal->Draw("AWP");
   
   TF1* fcal = new TF1(Form("fcal%d",dataset), "pol1", x[0], x[np-1]);
   fcal->SetLineWidth(2);
   fcal->SetLineColor(8);
   
   grcal->Fit(fcal, "R");
   
   TGraph* grcal_tgraph = new TGraph(*grcal);
   grcal_tgraph->SetName(Form("grcal_tgraph%d",dataset));
   new TCanvas;
   grcal_tgraph->Draw("AWP");
   
   // fcal->SetRange(0,25);
   //fcal->SetRange(1800, 2000);
   
   new TCanvas;
   fcal->Draw();
}

///////////////////////////////////////////////////////
//
//    Norm on Vdd
//
///////////////////////////////////////////////////////

/*
.q
root -l
.L dcutree.C
calib_rtd3_Vdd("dcu-glass-7.64-18.35-3010points-161min_temperature.dat", "dcu-glass-7.64-18.35-3010points-161min.dat", 1, 1, 100, 0, 4)

calib_rtd3_Vdd("dcu-glass-5.59-17.70-2530points-135min_temperature.dat", "dcu-glass-5.59-17.70-2530points-135min.dat", 1, 2, 0, 0, 8)
*/
void calib_rtd3_Vdd
      (
      const char ifname_tem[] = "dcu-glass-7.64-18.35-3010points-161min_temperature.dat", const char ifname_dat[] = "dcu-glass-7.64-18.35-3010points-161min.dat"
      , Int_t modeLIR = 0             // modeLIR = 0: HIR mode, modeLIR = 1: LIR mode
      , Int_t dataset = 0
      , Int_t ipoint_start = 0      // start calibration from ipoint=nstart
      , Int_t ipoint_end = 0        // end of calibration
      , Int_t color = 8
      )
{
   // Get temperature graph
   
   TGraph* grtem = new TGraph(ifname_tem);
   grtem->SetName(Form("grtem%d",dataset));
   grtem->SetMarkerStyle(6);
   //grtem->SetMarkerStyle(1);
   new TCanvas;
   grtem->Draw("AWP");
   
   if (ipoint_start == 0)  ipoint_start   = grtem->GetXaxis()->GetXmin();
   if (ipoint_end == 0)    ipoint_end     = grtem->GetXaxis()->GetXmax();
   
   TF1* ftem = new TF1(Form("ftem%d",dataset), "pol4", ipoint_start, ipoint_end);
   ftem->SetLineWidth(1);
   //ftem->SetLineColor(color);
   
   grtem->Fit(ftem, "R");
   
   //
   // get graph with rtd
   //
   Float_t* rtd = &Tree::rtd3;
   //
   // norm on Vdd
   //
   Float_t* Vnorm = &Tree::Vdd;
   
   Int_t npMax = 10000;
   Float_t* t  = new Float_t[npMax];
   Float_t* dt = new Float_t[npMax];
   Float_t* a  = new Float_t[npMax];
   Float_t* da = new Float_t[npMax];
  
   TTree* tree = dcutree(ifname_dat);
   if (!tree) return;
   
   Tree::connect(tree);
   Int_t np = 0;
   for (Int_t ientry=0; ientry<tree->GetEntries(); ++ientry) {
      tree->GetEntry(ientry);
      //if (Tree::n < ipoint_start) continue;
      //if (Tree::n > ipoint_end) break;
      if (Tree::n < ftem->GetXmin()) continue;
      if (Tree::n > ftem->GetXmax()) break;
      
      // mode
      if (Tree::LIR != modeLIR) continue;
      
      a[np]    = (*rtd)*2500./(*Vnorm);        //-- access to rtd
      da[np]   = 0.5;
      t[np]    = ftem->Eval(Tree::n);
      dt[np]   = 0.01;
      //cout<< "np = " << np << "\t t[np] = " << t[np] <<endl;
      ++np;
   }
   cout<< "np = " << np << " t[0] = " << t[0] << " t[np] = " << t[np-1] <<endl;
   
//    Float_t* x  = t;
//    Float_t* y  = a;
//    Float_t* dx = dt;
//    Float_t* dy = da;
   Float_t* x  = a;
   Float_t* y  = t;
   Float_t* dx = da;
   Float_t* dy = dt;
   cout<< "np = " << np << " x[0] = " << x[0] << " x[np] = " << x[np-1] <<endl;
   
   TGraphErrors* grcal = new TGraphErrors(np, x, y, dx, dy);
   grcal->SetName(Form("grcal%d",dataset));
   grcal->SetTitle(Form("Temperature calibration rtd, dataset %d;ADC counts;T,^{o}C",dataset));
   // grcal->SetMarkerStyle(6);
   grcal->SetMarkerStyle(1);
   grcal->SetMarkerColor(2);
   grcal->SetLineColor(2);
  
   new TCanvas;
   grcal->Draw("AWP");
   
   TF1* fcal = new TF1(Form("fcal%d",dataset), "pol1", x[0], x[np-1]);
   fcal->SetTitle(Form("fcal%d",dataset));
   fcal->SetLineWidth(2);
   fcal->SetLineColor(color);
   
   grcal->Fit(fcal, "R");
   
   TGraph* grcal_tgraph = new TGraph(*grcal);
   grcal_tgraph->SetName(Form("grcal_tgraph%d",dataset));
   new TCanvas;
   grcal_tgraph->Draw("AWP");
   
   // fcal->SetRange(0,25);
   //fcal->SetRange(1800, 2000);
   
   new TCanvas;
   fcal->Draw();
}

///////////////////////////////////////////////////////
//
//    Norm on Vpc
//
///////////////////////////////////////////////////////

/*
.q
root -l
.L dcutree.C
calib_rtd3_Vpc("dcu-glass-7.64-18.35-3010points-161min_temperature.dat", "dcu-glass-7.64-18.35-3010points-161min.dat", 1, 1, 100, 0, 4)

calib_rtd3_Vpc("dcu-glass-5.59-17.70-2530points-135min_temperature.dat", "dcu-glass-5.59-17.70-2530points-135min.dat", 1, 2, 0, 0, 8)
*/
void calib_rtd3_Vpc
      (
      const char ifname_tem[] = "dcu-glass-7.64-18.35-3010points-161min_temperature.dat", const char ifname_dat[] = "dcu-glass-7.64-18.35-3010points-161min.dat"
      , Int_t modeLIR = 0             // modeLIR = 0: HIR mode, modeLIR = 1: LIR mode
      , Int_t dataset = 0
      , Int_t ipoint_start = 0      // start calibration from ipoint=nstart
      , Int_t ipoint_end = 0        // end of calibration
      , Int_t color = 8
      )
{
   // Get temperature graph
   
   TGraph* grtem = new TGraph(ifname_tem);
   grtem->SetName(Form("grtem%d",dataset));
   grtem->SetMarkerStyle(6);
   grtem->SetMarkerColor(2);
   //grtem->SetMarkerStyle(1);
   new TCanvas;
   grtem->Draw("AWP");
   
   if (ipoint_start == 0)  ipoint_start   = grtem->GetXaxis()->GetXmin();
   if (ipoint_end == 0)    ipoint_end     = grtem->GetXaxis()->GetXmax();
   
   TF1* ftem = new TF1(Form("ftem%d",dataset), "pol4", ipoint_start, ipoint_end);
   ftem->SetLineWidth(1);
   //ftem->SetLineColor(color);
   
   grtem->Fit(ftem, "R");
   
   //
   // get graph with rtd
   //
   Float_t* rtd = &Tree::rtd3;
   //
   // norm on Vpc
   //
   Float_t* Vnorm = &Tree::Vpc;
   
   Int_t npMax = 10000;
   Float_t* t  = new Float_t[npMax];
   Float_t* dt = new Float_t[npMax];
   Float_t* a  = new Float_t[npMax];
   Float_t* da = new Float_t[npMax];
  
   TTree* tree = dcutree(ifname_dat);
   if (!tree) return;
   
   Tree::connect(tree);
   Int_t np = 0;
   for (Int_t ientry=0; ientry<tree->GetEntries(); ++ientry) {
      tree->GetEntry(ientry);
      //if (Tree::n < ipoint_start) continue;
      //if (Tree::n > ipoint_end) break;
      if (Tree::n < ftem->GetXmin()) continue;
      if (Tree::n > ftem->GetXmax()) break;
      
      // mode
      if (Tree::LIR != modeLIR) continue;
      
      a[np]    = (*rtd)*2500./(*Vnorm);        //-- access to rtd
      da[np]   = 0.5;
      t[np]    = ftem->Eval(Tree::n);
      dt[np]   = 0.01;
      //cout<< "np = " << np << "\t t[np] = " << t[np] <<endl;
      ++np;
   }
   cout<< "np = " << np << " t[0] = " << t[0] << " t[np] = " << t[np-1] <<endl;
   
//    Float_t* x  = t;
//    Float_t* y  = a;
//    Float_t* dx = dt;
//    Float_t* dy = da;
   Float_t* x  = a;
   Float_t* y  = t;
   Float_t* dx = da;
   Float_t* dy = dt;
   cout<< "np = " << np << " x[0] = " << x[0] << " x[np] = " << x[np-1] <<endl;
   
   TGraphErrors* grcal = new TGraphErrors(np, x, y, dx, dy);
   grcal->SetName(Form("grcal%d",dataset));
   grcal->SetTitle(Form("Temperature calibration rtd, dataset %d;ADC counts;T,^{o}C",dataset));
   // grcal->SetMarkerStyle(6);
   grcal->SetMarkerStyle(1);
   grcal->SetMarkerColor(2);
   grcal->SetLineColor(2);
  
   new TCanvas;
   grcal->Draw("AWP");
   
   TF1* fcal = new TF1(Form("fcal%d",dataset), "pol1", x[0], x[np-1]);
   fcal->SetTitle(Form("fcal%d",dataset));
   fcal->SetLineWidth(2);
   fcal->SetLineColor(color);
   fcal->SetMarkerColor(color);
   fcal->SetFillColor(0);        // for TLegend
   
   grcal->Fit(fcal, "R");
   
   TGraph* grcal_tgraph = new TGraph(*grcal);
   grcal_tgraph->SetName(Form("grcal_tgraph%d",dataset));
   new TCanvas;
   grcal_tgraph->Draw("AWP");
   
   // fcal->SetRange(0,25);
   //fcal->SetRange(1800, 2000);
   
   // fit results
   Double_t offset = fcal->GetParameter(2);
   Double_t slope = fcal->GetParameter(1);
   
   TH1F* h_res = new TH1F(Form("h_res%d",dataset), Form("Residuals for dataset %d;#DeltaT, ^{o}C",dataset), 100, -5, 5);
   h_res->SetFillColor(color);
   h_res->SetLineColor(color);
   h_res->SetMarkerColor(color);
   for (int i=0; i<grcal_tgraph->GetN(); ++i) {
//       Float_t adc = (*grcal_tgraph->GetX())[i];
//       Float_t tem = (*grcal_tgraph->GetY())[i];
      Double_t adc, tem;
      grcal_tgraph->GetPoint(i, adc, tem);
      Float_t tcal = fcal->Eval(adc);
      //cout<< i << "\t adc = " << adc << "\t tem = " << tem << " tcal = " << tcal <<endl;
      h_res->Fill(tem - tcal);
   }
   new TCanvas;
   h_res->Draw();
   
   new TCanvas;
   fcal->Draw();
}

/////////////////////////////

/*
.q
root -l
.L tvdcu.C
.L dcutree.C
calib_newformat()
*/

void calib_newformat()
{
   std::string str;
   
   Int_t np = 0;
   Float_t a[1000];
   Float_t da[1000];
   Float_t t[1000];
   Float_t dt[1000];
   
   TTree* tree;
   TH1* h;
   Float_t amean, arms, tmean, trms;
   
   new TCanvas;
   
   //-- tvdcu.C format
   
//    str = "";
//    tmean = 0.0;
//    tree = tvdcu(str.c_str());
//    // new TCanvas;
//    tree->Draw("rtd3*2500/Vpc");
//    h = (TH1*) htemp();
//    trms = 0.1;
//    amean = h->GetMean();
//    arms = h->GetRMS();
//    a[np] = amean;
//    da[np] = arms;
//    t[np] = tmean;
//    dt[np] = trms;
//    cout<< "amean = " << amean << " arms = " << arms << " tmean = " << tmean <<endl;
//    ++np;
//    
//    str = "";
//    tmean = 0.0;
//    tree = tvdcu(str.c_str());
//    // new TCanvas;
//    tree->Draw("rtd3*2500/Vpc");
//    h = (TH1*) htemp();
//    trms = 0.1;
//    amean = h->GetMean();
//    arms = h->GetRMS();
//    a[np] = amean;
//    da[np] = arms;
//    t[np] = tmean;
//    dt[np] = trms;
//    cout<< "amean = " << amean << " arms = " << arms << " tmean = " << tmean <<endl;
//    ++np;
   
   str = "tvdcu_LIR-bag-0C.dat";
   tmean = 0.0;
   tree = tvdcu(str.c_str());
   // new TCanvas;
   tree->Draw("rtd3*2500/Vpc");
   h = (TH1*) htemp();
   trms = 0.1;
   amean = h->GetMean();
   arms = h->GetRMS();
   a[np] = amean;
   da[np] = arms;
   t[np] = tmean;
   dt[np] = trms;
   cout<< "amean = " << amean << " arms = " << arms << " tmean = " << tmean <<endl;
   ++np;
   
   //-- dcutree.C format
   
   str = "dcu-icebath-0.03C.dat";
   tmean = 0.03;
   tree = dcutree(str.c_str());
   // new TCanvas;
   tree->Draw("rtd3*2500/Vpc","LIR");
   h = (TH1*) htemp();
   trms = 0.1;
   amean = h->GetMean();
   arms = h->GetRMS();
   a[np] = amean;
   da[np] = arms;
   t[np] = tmean;
   dt[np] = trms;
   cout<< "amean = " << amean << " arms = " << arms << " tmean = " << tmean <<endl;
   ++np;
   
   str = "dcu-icebath-0.03Ca.dat";
   tmean = 0.03;
   tree = dcutree(str.c_str());
   // new TCanvas;
   tree->Draw("rtd3*2500/Vpc","LIR");
   h = (TH1*) htemp();
   trms = 0.1;
   amean = h->GetMean();
   arms = h->GetRMS();
   a[np] = amean;
   da[np] = arms;
   t[np] = tmean;
   dt[np] = trms;
   cout<< "amean = " << amean << " arms = " << arms << " tmean = " << tmean <<endl;
   ++np;
   
   str = "dcu-water-20.00-20.24C.dat";
   tmean = 20.12;
   tree = dcutree(str.c_str());
   // new TCanvas;
   tree->Draw("rtd3*2500/Vpc","LIR");
   h = (TH1*) htemp();
   trms = 0.1;
   amean = h->GetMean();
   arms = h->GetRMS();
   a[np] = amean;
   da[np] = arms;
   t[np] = tmean;
   dt[np] = trms;
   cout<< "amean = " << amean << " arms = " << arms << " tmean = " << tmean <<endl;
   ++np;
   
   str = "dcu-21.6-plato.dat";
   tmean = 21.6;
   tree = dcutree(str.c_str());
   // new TCanvas;
   tree->Draw("rtd3*2500/Vpc","LIR");
   h = (TH1*) htemp();
   trms = 0.1;
   amean = h->GetMean();
   arms = h->GetRMS();
   a[np] = amean;
   da[np] = arms;
   t[np] = tmean;
   dt[np] = trms;
   cout<< "amean = " << amean << " arms = " << arms << " tmean = " << tmean <<endl;
   ++np;
   
   str = "dcu-22.2C.dat";
   tmean = 22.2;
   tree = dcutree(str.c_str());
   // new TCanvas;
   tree->Draw("rtd3*2500/Vpc","LIR");
   h = (TH1*) htemp();
   trms = 0.1;
   amean = h->GetMean();
   arms = h->GetRMS();
   a[np] = amean;
   da[np] = arms;
   t[np] = tmean;
   dt[np] = trms;
   cout<< "amean = " << amean << " arms = " << arms << " tmean = " << tmean <<endl;
   ++np;
   
   TGraphErrors* gr_calib = new TGraphErrors(np, a, t, da, dt);
   gr_calib->SetNameTitle("gr_calib","RTD calibration;ADC amplitude, arb. units;T,^{o}C");
   gr_calib->SetMarkerStyle(24);
   gr_calib->SetMarkerColor(2);
   gr_calib->SetFillColor(0);    // for TLegend
   new TCanvas;
   gr_calib->Draw("AWP");
   
   Int_t opt_stat = gStyle->GetOptStat();
   Int_t opt_fit  = gStyle->GetOptFit();
   gStyle->SetOptStat(0);
   gStyle->SetOptFit(0);
   cout<< "before fit: gStyle->GetOptFit() = " << gStyle->GetOptFit() <<endl;
   gr_calib->Fit("pol1");
   cout<< "after fit:  gStyle->GetOptFit() = " << gStyle->GetOptFit() <<endl;
   gStyle->SetOptFit(opt_fit);
   gStyle->SetOptStat(opt_stat);
}


/*
.q
root -l
.L tvdcu.C
.L dcutree.C
calib_sum()
*/
void calib_sum()
{
   calib_rtd3_Vpc("dcu-glass-7.64-18.35-3010points-161min_temperature.dat", "dcu-glass-7.64-18.35-3010points-161min.dat", 1, 1, 100, 0, 4);
   TF1* fcal1 = (TF1*) gROOT->FindObject("fcal1");
   calib_rtd3_Vpc("dcu-glass-5.59-17.70-2530points-135min_temperature.dat", "dcu-glass-5.59-17.70-2530points-135min.dat", 1, 2, 0, 0, 8);
   TF1* fcal2 = (TF1*) gROOT->FindObject("fcal2");
   
   //gStyle->SetOptFit(0);
   calib_newformat();
   TGraphErrors* gr_calib = (TGraphErrors*) gROOT->FindObject("gr_calib");
   gr_calib->SetMarkerStyle(20);
   
   new TCanvas();
   gr_calib->SetTitle("RTD calibration summary");
   gr_calib->Draw("AWP");
   
   fcal1->SetRange(3210,3270);
   fcal2->SetRange(3210,3270);
   
   fcal2->Draw("same");
   fcal1->Draw("same");
   
   gr_calib->Draw("P");
   
   TLegend* legend = new TLegend(0.60,0.50, 0.98,0.75);
   legend->SetFillColor(0);
   legend->AddEntry(gr_calib, "standalone meas.");
   legend->AddEntry(fcal1, "foam glass 1");
   legend->AddEntry(fcal2, "foam glass 2");
   legend->Draw();
   
}














