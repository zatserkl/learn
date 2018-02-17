TH1F* h200_h100()
{
	 // histograms with 1 per bin
	 TH1F* h200 = new TH1F("h200","h200", 20, -10, 10);
	 h200->SetLineColor(4);
	 TH1F* h100 = new TH1F("h100","h100", 10, -5, 5);
	 h100->SetLineColor(2);

	 for (int i=1; i<=h200->GetNbinsX(); ++i) {
	 		h200->SetBinContent(i,i);
	 }

	 // copy (-5,5) part into h100

	 int shift = (h200->GetNbinsX() - h100->GetNbinsX())/2;
	 for (int i=1; i<=h100->GetNbinsX(); ++i) {
	 		int i200 = shift + i;
	 		h100->SetBinContent(i, h200->GetBinContent(i200));
	 }

	 new TCanvas;
	 h200->Draw();
	 h100->Draw("same");
}
