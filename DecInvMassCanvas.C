#ifdef __CLING__
#pragma cling optimize(0)
#endif
void DecInvMassCanvas()
{
//=========Macro generated from canvas: DecInvMassCanvas/Decayed particles invariant mass histogram
//=========  (Wed Jan  8 13:11:29 2025) by ROOT version 6.28/06
   TCanvas *DecInvMassCanvas = new TCanvas("DecInvMassCanvas", "Decayed particles invariant mass histogram",0,0,900,600);
   DecInvMassCanvas->SetHighLightColor(2);
   DecInvMassCanvas->Range(-0.5,-2088.319,4.5,18794.87);
   DecInvMassCanvas->SetFillColor(0);
   DecInvMassCanvas->SetBorderMode(0);
   DecInvMassCanvas->SetBorderSize(2);
   DecInvMassCanvas->SetFrameBorderMode(0);
   DecInvMassCanvas->SetFrameBorderMode(0);
   
   TH1F *InvariantsPMasssPofsPdecayedsPparticles__3 = new TH1F("InvariantsPMasssPofsPdecayedsPparticles__3","Invariant Mass of decayed particles distribution",200,0,4);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(34,2);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(35,7);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(36,21);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(37,83);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(38,273);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(39,805);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(40,2047);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(41,4362);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(42,7398);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(43,11248);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(44,14280);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(45,15911);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(46,14533);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(47,12046);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(48,8262);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(49,4672);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(50,2279);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(51,1008);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(52,389);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(53,114);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(54,28);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(55,8);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetEntries(99776);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("Invariant Mass of decayed particles");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 99776  ");
   ptstats_LaTex = ptstats->AddText("Mean  = 0.8918");
   ptstats_LaTex = ptstats->AddText("Std Dev   = 0.04995");
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
