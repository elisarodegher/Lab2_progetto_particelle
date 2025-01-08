#ifdef __CLING__
#pragma cling optimize(0)
#endif
void DecInvMassCanvas()
{
//=========Macro generated from canvas: DecInvMassCanvas/Decayed particles invariant mass histogram
//=========  (Wed Jan  8 21:58:44 2025) by ROOT version 6.28/06
   TCanvas *DecInvMassCanvas = new TCanvas("DecInvMassCanvas", "Decayed particles invariant mass histogram",0,0,900,600);
   DecInvMassCanvas->SetHighLightColor(2);
   DecInvMassCanvas->Range(-0.5,-2068.369,4.5,18615.32);
   DecInvMassCanvas->SetFillColor(0);
   DecInvMassCanvas->SetBorderMode(0);
   DecInvMassCanvas->SetBorderSize(2);
   DecInvMassCanvas->SetFrameBorderMode(0);
   DecInvMassCanvas->SetFrameBorderMode(0);
   
   TH1F *InvariantsPMasssPofsPdecayedsPparticles__3 = new TH1F("InvariantsPMasssPofsPdecayedsPparticles__3","Invariant Mass of decayed particles distribution",200,0,4);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(35,7);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(36,31);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(37,86);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(38,325);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(39,852);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(40,2057);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(41,4353);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(42,7654);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(43,11317);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(44,14575);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(45,15759);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(46,15000);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(47,11867);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(48,8044);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(49,4818);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(50,2303);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(51,1013);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(52,343);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(53,100);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(54,29);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(55,9);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(56,1);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetBinContent(57,1);
   InvariantsPMasssPofsPdecayedsPparticles__3->SetEntries(100544);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("Invariant Mass of decayed particles");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 100544 ");
   ptstats_LaTex = ptstats->AddText("Mean  = 0.8914");
   ptstats_LaTex = ptstats->AddText("Std Dev   = 0.05002");
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
