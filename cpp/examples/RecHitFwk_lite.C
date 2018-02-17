{

//things to use fwlite
 gROOT->Reset();
 gSystem->Load("libFWCoreFWLite.so");
 AutoLibraryLoader::enable();

//File to save Energy histos into
TFile* output = new TFile("blah.root","RECREATE");

//define Vectors
std::vector<CaloRecHit> *caloRecHitsEE = new std::vector<CaloRecHit>;
std::vector<CaloRecHit> *caloRecHitsEB = new std::vector<CaloRecHit>;
std::vector<CaloRecHit> *caloRecHitsHBHE = new std::vector<CaloRecHit>;
std::vector<CaloRecHit> *caloRecHitsHO = new std::vector<CaloRecHit>;
std::vector<CaloRecHit> *caloRecHitsHF = new std::vector<CaloRecHit>;
std::vector<EBDetId> *ebId = new std::vector<EBDetId>;

//define Histos 
/*c1 = new TCanvas("c1", "Energy distributions",200,10,700,500);
pad1 = new TPad("pad1", "This is pad1",0.03,0.62,0.50,0.92,21);
pad2 = new TPad("pad2", "This is pad2",0.03,0.62,0.50,0.92,21);
pad1->Draw();
pad2->Draw();*/

//Define the histos
output->cd();
energyEE = new TH1F("energyEE","EE Energy Distribution",100,-15,80);
energyEE->GetXaxis()->SetTitle("Energy (GeV)");
energyEB = new TH1F("energyEB","EB Energy Distribution",100, -15,80);
energyEB->GetXaxis()->SetTitle("Energy (GeV)");
energyHBHE = new TH1F("energyHBHE", "HE/HB Energy Distribution",100,-15,160);
energyHBHE->GetXaxis()->SetTitle("Energy (GeV)");
energyHO = new TH1F("energyHO", "HO Energy Distribution",100,-15,80);
energyHO->GetXaxis()->SetTitle("Energy (GeV)");
energyHF = new TH1F("energyHF","HF Energy Distribution",100,-15,80);
energyHF->GetXaxis()->SetTitle("Energy (GeV)");
timingEE = new TH1F("timingEE","Timing in EE",300,-20,130);
timingEE->GetXaxis()->SetTitle("Timing (ns)");
timingEB = new TH1F("timingEB","Timing in EB",300,-10,130);
timingEB->GetXaxis()->SetTitle("Timing (ns)");
timingHBHE = new TH1F("timingHBHE","Timing in HBHE",300,-20,120);
timingHBHE->GetXaxis()->SetTitle("Timing (ns)");
timingHF = new TH1F("timingHF","Timing in HF",300,-20,40);
timingHF->GetXaxis()->SetTitle("Timing (ns)");
timingHO = new TH1F("timingHO","Timing in HO",300,-40,100);
timingHO->GetXaxis()->SetTitle("Timing (ns)");

//Looping through the files
for(Int_t i= 0; i<1; i++){

 std::cout<<"file: i= "<<i<<std::endl;
 char* filename="somethingrealllyyyyyyyyyyyylllllllllllllllllllllllllllllllllllllllllllllllllllllllllllongggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg";

 switch(i){
 case 0:
   //std::cout<<"entering 1st file"<<std::endl;
   sprintf(filename,"dccp dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/2/store/mc/CSA08/MuonBeamHalo/GEN-SIM-RECO/CSA08_S156_v1/0002/007F6947-ED2B-DD11-87D9-001E0B5F3142.root");
   break;
 case 1:
   //std::cout<<"entering 2nd file"<<std::endl;
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/00A2DD35-6B7E-DC11-8632-000423D99160.root");
   break;
 case 2:
   //std::cout<<"entering 3rd file"<<std::endl;
   sprintf(filename,"dccp /pnfs/cms/WAX/11/store/mc/CSA08/MuonBeamHalo/GEN-SIM-RECO/CSA08_S156_v1/0002/007F6947-ED2B-DD11-87D9-001E0B5F3142.root");
   break;
 case 3:
   //std::cout<<"entering 4th file"<<std::endl;
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/02C6D1E7-677E-DC11-8338-000423D944F8.root");
   break;
 case 4:
   //std::cout<<"entering 5th file"<<std::endl;
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/02D03676-797E-DC11-840C-001617DBD564.root");
   break;
 case 5:
   //std::cout<<"entering 6th file"<<std::endl;
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/02F5D1DC-7F7E-DC11-9770-001617C3B714.root");
   break;
 case 6:
   //std::cout<<"entering 7th file"<<std::endl;
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/0401F2F3-677E-DC11-A6A3-000423D8F63C.root");
   break;
 case 7:
   //std::cout<<"entering 8th file"<<std::endl;
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/04046D4A-757E-DC11-BD73-0019DB29C614.root");
   break;
 case 8:
   //std::cout<<"entering 9th file"<<std::endl;
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/0676FA84-DE7E-DC11-8AE8-001617E30D28.root");
   break;
 case 9:
   //std::cout<<"entering 10th file"<<std::endl;
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/1094C5D7-617E-DC11-A3CF-00304885A9D6.root");
   break;
 case 10:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/10CE5CA9-7D7E-DC11-829E-000423D655A2.root");
   break;
 case 11:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/14F42004-627E-DC11-BFB6-00304885AA5C.root");
   break;
 case 12:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/1A4BBB3A-6B7E-DC11-9623-000423D6BA18.root");
   break;
 case 13:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/1CA14F49-757E-DC11-9390-001617E30D06.root");
   break;
 case 14:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/1E05FFE7-617E-DC11-B1C3-00304885A74E.root");
   break;
 case 15:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/1EC7A6D3-617E-DC11-88A7-00304885A5A2.root");
   break;
 case 16:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/205DA357-717E-DC11-BEE1-001617DBD288.root");
   break;
 case 17:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/22C504D8-617E-DC11-AFA4-0030488318B4.root");
 break;
 case 18:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/22C55F57-827E-DC11-A297-003048561870.root");
   break;
 case 19:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/24512D8E-817E-DC11-A59C-000423D9864C.root");
   break;
 case 20:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/24E790D7-617E-DC11-9459-00304885AC68.root");
   break;
 case 21:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/24EBEA38-6B7E-DC11-8243-000423D98930.root");
   break;
 case 22:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/26B07DE9-887E-DC11-93F8-000E0C3EFA97.root");
   break;
 case 23:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/26C485E9-677E-DC11-AC93-001617E30D06.root");
   break;
 case 24:
     sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/280BF7E8-677E-DC11-9891-0016177CA7A0.root");
     break;
 case 25:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/2887BB03-627E-DC11-8F83-00304885ABF2.root");
   break;
 case 26:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/2ADA273E-6B7E-DC11-AB2A-003048561926.root");
   break;
 case 27:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/2CF891E9-677E-DC11-B4B6-000423D6B358.root");
   break;
 case 28:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/2E826B35-6B7E-DC11-A64B-000423D98804.root");
   break;
 case 29:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/328509C4-7D7E-DC11-A365-001617C3B778.root");
   break;
 case 30:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/34178595-797E-DC11-A6CF-000423D98760.root");
   break;
 case 31:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/36A5F138-6B7E-DC11-A83D-001617DBD5B2.root");
   break;
 case 32:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/38267693-E07E-DC11-976C-001617C3B762.root");
   break;
 case 33:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/38DF69EC-677E-DC11-849C-000423D9880C.root");
   break;
 case 34:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/3A2765DA-7F7E-DC11-989C-001617DBD248.root");
   break;
 case 35:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/3C8832EA-677E-DC11-9D63-000423D6AF24.root");
   break;
case 36:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/3CE69836-6B7E-DC11-8666-000423D986A8.root");
   break;
 case 37:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/3E23668F-797E-DC11-9DD5-001617C3B642.root");
   break;
 case 38:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/3E993429-6E7E-DC11-8CC7-00304855D4C2.root");
   break;
 case 39:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/401BFB4A-757E-DC11-8B98-000423D9853C.root");
   break;
 case 40:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/425C0FD5-7F7E-DC11-B935-000423D98834.root");
   break;
 case 41:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/4420CCA4-7D7E-DC11-97CB-000423D99B3E.root");
   break;
 case 42:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/445B93C4-F67E-DC11-858F-000423D6A434.root");
   break;
 case 43:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/44C72C04-627E-DC11-8022-00304885B42C.root");
   break;
 case 44:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/48B529CF-617E-DC11-B920-00304885AB64.root");
   break;
 case 45:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/4A06F3A5-7D7E-DC11-B369-00304885AD60.root");
   break;
 case 46:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/4A36DFD7-617E-DC11-972F-00304885AA14.root");
   break;
 case 47:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/4E676FE9-677E-DC11-BBAD-001617DBD41E.root");
   break;
 case 48:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/50C25527-6E7E-DC11-AD6F-00304856288E.root");
   break;
 case 49:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/568FFB55-717E-DC11-B28C-001617E30F56.root");
   break;
 case 50:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/580025EB-677E-DC11-9557-000423D98868.root");
   break;
 case 51:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/581DE92B-6E7E-DC11-BDE1-00304855C510.root");
   break;
 case 52:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/5A1DCF4B-757E-DC11-8775-000423D99996.root");
   break;
 case 53:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/5C2479F1-677E-DC11-9F1D-000423D987E0.root");
   break;
 case 54:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/5EA3A573-797E-DC11-A60B-000423D99F1E.root");
   break;
 case 55:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/6258A6F3-677E-DC11-8C8F-000E0C3F045B.root");
   break;
 case 56:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/6677F2F1-D67E-DC11-A74B-00304855D282.root");
   break;
 case 57:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/6A9B466F-797E-DC11-96A4-001617C3B76A.root");
   break;
 case 58:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/6C797F37-6B7E-DC11-9F89-000423D944FC.root");
   break;
 case 59:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/6C80FC61-717E-DC11-AF17-001617DBD556.root");
   break;
 case 60:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/6E4707E8-677E-DC11-981D-000423D9989E.root");
   break;
 case 61:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/6E4D6D55-757E-DC11-86B5-000423D98DC4.root");
   break;
 case 62:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/74126439-6B7E-DC11-A439-000423D98B28.root");
   break;
 case 63:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/74381BD9-617E-DC11-AEA7-00304885AC64.root");
   break;
 case 64:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/74B27975-797E-DC11-92D2-000423D98C1C.root");
   break;
 case 65:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/76FE2955-827E-DC11-A826-000423D98A20.root");
   break;
 case 66:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/78993DD4-7F7E-DC11-A241-000423D94524.root");
   break;
 case 67:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/78D6B4D9-7F7E-DC11-8A1A-0030485609EC.root");
   break;
 case 68:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/7CC87004-627E-DC11-ACAF-00304885AA88.root");
   break;
 case 69:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/82339EEC-677E-DC11-9FCF-000423D6CA42.root");
   break;
 case 70:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/863B0CEB-677E-DC11-B71F-000423D94524.root");
   break;
 case 71:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/8875D935-AA7E-DC11-A36B-001617E30F58.root");
   break;
 case 72:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/888E6D4A-757E-DC11-8DE2-000423D986A8.root");
   break;
 case 73:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/88C08990-817E-DC11-9F58-000423D98EC8.root");
   break;
 case 74:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/8A98F65E-717E-DC11-B44E-001617C3B728.root");
   break;
 case 75:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/8AC98E37-6B7E-DC11-8936-000423D98E54.root");
   break;
 case 76:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/8C0C1B76-797E-DC11-8D6E-000423D98FE0.root");
   break;
 case 77:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/8CB4FAD3-617E-DC11-92E2-00304885AC4E.root");
   break;
 case 78:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/9079A04E-827E-DC11-9E79-000423D94990.root");
   break;
 case 79:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/943C9BD5-7F7E-DC11-BD47-000423D98800.root");
   break;
 case 80:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/9671DCD0-7F7E-DC11-AA3A-000423D6C8EE.root");
   break;
 case 81:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/9AF97203-DA7E-DC11-A4D6-00304855D496.root");
   break;
 case 82:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/A28BB734-6B7E-DC11-8A7D-000423D99A2A.root");
   break;
 case 83:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/A621FC4D-827E-DC11-A90C-001617C3B70A.root");
   break;
 case 84:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/A831F4A7-7D7E-DC11-8881-001617DBD570.root");
   break;
 case 85:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/A85703D0-7F7E-DC11-A2AC-000423D9880C.root");
   break;
 case 86:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/AA46F54C-757E-DC11-AFB7-000423D94700.root");
   break;
 case 87:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/B4581829-6E7E-DC11-8A88-003048562A60.root");
   break;
 case 88:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/B8BA1BD1-7F7E-DC11-BF7C-000423D990CC.root");
   break;
 case 89:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/BAF70ED1-617E-DC11-BA0B-00304885AA0E.root");
   break;
 case 90:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/BCECB9A9-7D7E-DC11-9E15-000423D6C9BA.root");
   break;
 case 91:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/BCEDD403-627E-DC11-8A5A-00304885AC7A.root");
   break;
 case 92:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/BEE64977-797E-DC11-92F0-001617C3B6AA.root");
   break;
 case 93:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/C0932004-627E-DC11-A622-00304885AA38.root");
   break;
 case 94:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/C0B7472A-6E7E-DC11-9534-00304855D498.root");
   break;
 case 95:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/C2003B3A-6B7E-DC11-BA71-000423D8FA38.root");
   break;
 case 96:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/C21BF2AF-7D7E-DC11-AA7C-000423D9513C.root");
   break;
 case 97:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/C237F450-827E-DC11-A308-000423D98B08.root");
   break;
 case 98:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/C4AE644C-757E-DC11-86DA-000423D9863C.root");
   break;
 case 99:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/C63FA26B-717E-DC11-A95A-000E0C3F0618.root");
   break;
 case 100:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/C6B674EF-677E-DC11-BF46-000423D99B3E.root");
   break;
 case 101:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/C8D89B3C-6B7E-DC11-B922-0030485629A4.root");
   break;
 case 102:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/C8DA72A6-7D7E-DC11-833D-000423D98F78.root");
   break;
 case 103:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/CA953204-627E-DC11-B1C4-00304885B10E.root");
   break;
 case 104:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/CAEB30A8-7D7E-DC11-A677-00304855D50E.root");
   break;
 case 105:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/D21D6E4F-827E-DC11-9634-000423D98930.root");
   break;
 case 106:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/D63D2239-6B7E-DC11-93D0-003048560EF8.root");
   break;
 case 107:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/D6D31F37-6B7E-DC11-B2F8-000423D98DC4.root");
   break;
 case 108:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/D8F47DEB-677E-DC11-87BF-001617C3B794.root");
   break;
 case 109:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/E009BED5-7F7E-DC11-AAD2-000423D6CA42.root");
   break;
 case 110:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/E0456C94-817E-DC11-BC7C-000423D6B4EC.root");
   break;
 case 111:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/E0BA3BA4-7D7E-DC11-8C75-001617E30F50.root");
   break;
 case 112:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/E87B9599-E27E-DC11-BB9E-000423D94A68.root");
   break;
 case 113:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/EA36EB0C-627E-DC11-98FC-00304885AB62.root");
   break;
 case 114:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/EA660B5D-717E-DC11-BB50-000423D9A212.root");
   break;
 case 115:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/EC95F7A6-7D7E-DC11-B23A-001617C3B76E.root");
   break;
 case 116:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/ECAE0DED-677E-DC11-8672-000423D98B5C.root");
   break;
 case 117:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/ECFA874D-827E-DC11-8BB7-000423D9864C.root");
   break;
 case 118:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/EEE143EB-677E-DC11-A0ED-001617C3B6E8.root");
   break;
 case 119:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/EEE18103-627E-DC11-8E5A-00304885B12E.root");
   break;
 case 120:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/F24F097A-797E-DC11-B506-000423D99210.root");
   break;
 case 121:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/F2C18FD5-7F7E-DC11-9536-000423D98FBC.root");
   break;
 case 122:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/F6C263A9-7D7E-DC11-8828-000423D994CC.root");
   break;
 case 123:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/F8875AE8-677E-DC11-A22C-000423D944FC.root");
   break;
 case 124:
   sprintf(filename,"dcap://dcap:22135/pnfs/ihepa.ufl.edu/data/cmsdata/store/mc/2007/10/19/CSA07-BeamHalo_muon_BX0-3164/0003/FAA8E8F0-677E-DC11-83C6-0030485609D0.root");
   break;
 default:
   std::cout<< "damn!"<<std::endl;;
   break;
 }//end switch

  //create tree telling it to look in the "Events" branch of the input files
 TFile* thefile = new TDCacheFile(filename);
 TTree *tree= (TTree*) thefile->Get("Events");



 //grab the RecHits
 TBranch *branchEE = (TBranch*) tree->GetBranch("EcalRecHitsSorted_ecalRecHit_EcalRecHitsEE_Rec1.obj");
 TBranch *branchEB = (TBranch*) tree->GetBranch("EcalRecHitsSorted_ecalRecHit_EcalRecHitsEB_Rec1.obj");
 TBranch *branchHBHE = (TBranch*) (Events->GetBranch("HBHERecHitsSorted_hbhereco__Rec1.obj"));
 TBranch *branchHF = (TBranch*) (Events->GetBranch("HFRecHitsSorted_hfreco__Rec1.obj"));
 TBranch *branchHO = (TBranch*) (Events->GetBranch("HORecHitsSorted_horeco__Rec1.obj"));


 Int_t numEvts = tree->GetEntries();
 //std::cout<<"numEvts= "<<numEvts<<std::endl;

 //Loop over all events in branch
 for(Int_t j= 0; j< numEvts; j++){
   //std::cout<<"event "<<j<<std::endl;

   //set everything up for the event processing
   branchEE->GetEntry(j);
   branchEB->GetEntry(j);
   branchHBHE->GetEntry(j);
   branchHF->GetEntry(j);
   branchHO->GetEntry(j);
   branchEE->SetAddress(caloRecHitsEE);
   branchEB->SetAddress(caloRecHitsEB);
   branchHBHE->SetAddress(caloRecHitsHBHE);
   branchHF->SetAddress(caloRecHitsHF);
   branchHO->SetAddress(caloRecHitsHO);
   //std::cout<<"event #"<<j<<" num rechits  is "<<caloRecHitsEE->size()<<std::endl;

   //Loop over all RecHits in each Event for EE
   for(Int_t k=0; k < caloRecHitsEE->size(); k++){
     //std::cout<<"k= "<<k<<std::endl;



     //get the energy for each RecHit for EE
     float energy_ee = ((*caloRecHitsEE)[k]).energy();
     //energyEE->Fill(energy_ee);
     //std::cout<<"event #"<<j<<" energy of "<<k<<"th rechit is "<<energyx<<std::endl;     

     //get the timing for each RecHit--Making an Energy cut of 3 GeV
     if (energy_ee > 3){
     float timeEE = ((*caloRecHitsEE)[k]).time();
     timingEE->Fill(timeEE);
     }

     else {
       continue;
     }   
    
   } //end of RecHit EE loop

   //std::cout<<"entering EB"<<endl;
      
   //Loop over all RecHits in each Event for EB
   for(Int_t k=0; k < caloRecHitsEB->size(); k++){
     //std::cout<<"k= "<<k<<std::endl;

     //get the energy for each RecHit for EB
     float energy_eb = ((*caloRecHitsEB)[k]).energy();
     //energyEB->Fill(energy_eb);

     //get the phi, eta and towers for each rechit:phi->(1,360), eta->(-85,85), Tphi and Teta in towers
     //EBDetId* detid = (EBDetId*) ebId[k];
     EBDetId* id = (EBDetId*) ebId[k];
     Int_t Tphi = id.tower_iphi();
     //Int_t phi = detid.iphi();
     Int_t Teta = id.tower_ieta();
     //Int_t eta = detid.ieta();     

     //get the timing for each RecHit--Making an Energy cut of 3 GeV.  If rechit energy is above threshold, look at phi, eta
     if (energy_eb > 3){
     float timeEB = ((*caloRecHitsEB)[k]).time();
     timingEB->Fill(timeEB);
     std::cout <<"event #"<< j <<"   "<<"rechit#"<< k <<"   "<< "iphi= " << Tphi <<"   "<<"ieta= "<< Teta <<std::endl;
     }
     else {
       continue;
       //std::cout<<"energy below cut for" << k << "rechit of " << j <<"event" <<endl;
     }
     //std::cout<<"event "<<j<<"time for"<<k<<"rec hit"<<timing<<endl;
   } //end of RecHit  EB Loop



//Loop over all RecHits in each Event for HB/HE
   for(Int_t k=0; k < caloRecHitsHBHE->size(); k++){
     //std::cout<<"k= "<<k<<std::endl;

     //get the energy for each RecHit for HBHE
     float energy_hbhe = ((*caloRecHitsHBHE)[k]).energy();
     //energyHBHE->Fill(energy_hbhe);

     //get the timing for each RecHit--Making an Energy cut of 3 GeV
     if (energy_hbhe > 3){
     float timeHBHE = ((*caloRecHitsHBHE)[k]).time();
     timingHBHE->Fill(timeHBHE);
     }
     else {
       continue;
       //std::cout<<"energy below cut for" << k << "rechit of " << j <<"event" <<endl;
     }
     //std::cout<<"event "<<j<<"time for"<<k<<"rec hit"<<timing<<endl;
   } //end of RecHit  HBHE Loop



//Loop over all RecHits in each Event for HF
   for(Int_t k=0; k < caloRecHitsHF->size(); k++){
     //std::cout<<"k= "<<k<<std::endl;

     //get the energy for each RecHit for HF
     float energy_hf = ((*caloRecHitsHF)[k]).energy();
     //energyHF->Fill(energy_hf);

     //get the timing for each RecHit--Making an Energy cut of 3 GeV
     if (energy_hf > 3){
       float timeHF = ((*caloRecHitsHF)[k]).time();
       timingHF->Fill(timeHF);
     }
     else {
       continue;
       //std::cout<<"energy below cut for" << k << "rechit of " << j <<"event" <<endl;
     }
     
     //std::cout<<"event "<<j<<"time for"<<k<<"rec hit"<<timing<<endl;
   } //end of RecHit  HF Loop



//Loop over all RecHits in each Event for HO
   for(Int_t k=0; k < caloRecHitsHO->size(); k++){
     //std::cout<<"k= "<<k<<std::endl;

     //get the energy for each RecHit for HO
     float energy_ho = ((*caloRecHitsHO)[k]).energy();
     //energyHO->Fill(energy_ho);

     //get the timing for each RecHit--Making an Energy cut of 3 GeV
     if (energy_ho > 3){
     float timeHO = ((*caloRecHitsHO)[k]).time();
     timingHO->Fill(timeHO);
     }
     else {
       continue;
       //std::cout<<"energy below cut for" << k << "rechit of " << j <<"event" <<endl;
     }
     //std::cout<<"event "<<j<<"time for"<<k<<"rec hit"<<timing<<endl;
   } //end of RecHit  HO Loop

   

 }//end event loop
     delete tree;

}//end loop over files

/*
//Draw Energy Histos
energyEE->Draw();
energyEB->Draw();
energyHBHE->Draw();
energyHF->Draw();
energyHO->Draw();
*/

//Draw Timing histos
timingEE->Draw();
timingEB->Draw();
timingHBHE->Draw();
timingHF->Draw();
timingHO->Draw();

//Write All histos to the file
output->cd();
timingEE->Write();
//energyEE->Write();
//energyEB->Write();
timingEB->Write();
//energyHBHE->Write();
timingHBHE->Write();
//energyHF->Write();
timingHF->Write();
//energyHO->Write();
timingHO->Write();
output->Write();


}//end macro


