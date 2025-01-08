#ifdef __CLING__
#pragma cling optimize(0)
#endif
void DecInvMassCanvas()
{
//=========Macro generated from canvas: DecInvMassCanvas/Decayed particles invariant mass histogram
//=========  (Wed Jan  8 12:01:27 2025) by ROOT version 6.28/06
   TCanvas *DecInvMassCanvas = new TCanvas("DecInvMassCanvas", "Decayed particles invariant mass histogram",0,0,900,600);
   DecInvMassCanvas->SetHighLightColor(2);
   DecInvMassCanvas->Range(-2.5,-6967.538,22.5,62707.84);
   DecInvMassCanvas->SetFillColor(0);
   DecInvMassCanvas->SetBorderMode(0);
   DecInvMassCanvas->SetBorderSize(2);
   DecInvMassCanvas->SetFrameBorderMode(0);
   DecInvMassCanvas->SetFrameBorderMode(0);
   
   TH1F *InvariantsPMasssPofsPdecayedsPparticles__3 = new TH1F("InvariantsPMasssPofsPdecayedsPparticles__3","Invariant Mass of decayed particles distribution",200,0,20);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(7,5);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(8,3439);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(9,53086);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(10,41590);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(11,1518);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(12,1);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetEntries(99639);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("Invariant Mass of decayed particles");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 99639  ");
   ptstats_LaTex = ptstats->AddText("Mean  = 0.8916");
   ptstats_LaTex = ptstats->AddText("Std Dev   = 0.05008");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   InvariantsPMasssPofsPdecayedsPparticles__3->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(InvariantsPMasssPofsPdecayedsPparticles__3);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   InvariantsPMasssPofsPdecayedsPparticles__3->SetLineColor(ci);
   InvariantsPMasssPofsPdecayedsPparticles__3->GetXaxis()->SetLabelFont(42);
   InvariantsPMasssPofsPdecayedsPparticles__3->GetXaxis()->SetTitleOffset(1);
   InvariantsPMasssPofsPdecayedsPparticles__3->GetXaxis()->SetTitleFont(42);
   InvariantsPMasssPofsPdecayedsPparticles__3->GetYaxis()->SetLabelFont(42);
   InvariantsPMasssPofsPdecayedsPparticles__3->GetYaxis()->SetTitleFont(42);
   InvariantsPMasssPofsPdecayedsPparticles__3->GetZaxis()->SetLabelFont(42);
   InvariantsPMasssPofsPdecayedsPparticles__3->GetZaxis()->SetTitleOffset(1);
   InvariantsPMasssPofsPdecayedsPparticles__3->GetZaxis()->SetTitleFont(42);
   InvariantsPMasssPofsPdecayedsPparticles__3->Draw("");
   
   TPaveText *pt = new TPaveText(0.15,0.9341608,0.85,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("Invariant Mass of decayed particles distribution");
   pt->Draw();
   DecInvMassCanvas->Modified();
   DecInvMassCanvas->cd();
   DecInvMassCanvas->SetSelected(DecInvMassCanvas);
}
