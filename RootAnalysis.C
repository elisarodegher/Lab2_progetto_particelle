// mi da problemi con le cose di c++ tipo vector e std library

#include <iostream>
void RootAnalysis() {
  // Controllo se le percentuali hanno senso
  TFile *FileData = new TFile("Histograms2.root");
  if (!FileData || FileData->IsZombie()) {
    std::cerr << "Errore: impossibile aprire il file ROOT!" << std::endl;
    return;
  }
  TH1F *hparticletypes = (TH1F *)FileData->Get("Particle types");
  if (!hparticletypes) {
     std::cerr << "Errore: impossibile trovare l'istogramma hparticletypes!"
               << std::endl;
     return;
   } 
  int N_tot_conteggi = hparticletypes->GetEntries();

  if (N_tot_conteggi < 1E7 ||
      N_tot_conteggi > 1.1E7) { // 100 particelle per 1E5 eventi -> ci
                                // aspettiamo 1E7 particelle in totale
    std::cout << "Non va per niente bene!!";
  }
  TCanvas *particle_types = new TCanvas("Particle Types", "Particle Types distribution", 200, 10, 600, 400);
  hparticletypes->Draw();
  std::vector<double> aspettative = {0.4, 0.4, 0.05, 0.05, 0.045, 0.045, 0.01};
  for (int i{1}; hparticletypes->GetBinContent(i) != 0; ++i) {
    double mean = hparticletypes->GetBinContent(i) / N_tot_conteggi;
    double sigma = hparticletypes->GetBinError(i);
    if (aspettative[i] <= mean + sigma && mean - sigma <= aspettative[i]) {
      std::cout << "Il programma genera le particelle secondo le proporzioni "
                   "richieste "
                << std::endl;
    } else {
      std::cout << "Il programma e` no bueno :(" << std::endl;
      std::cout << "aspettative: " << aspettative[i]
                << " e media effettiva: " << mean << "ed errore" << sigma
                << std::endl;
    }
    // Ne balzate una mi sa
  }
  std::cout << "END OF 1 PUNTO\n\n\n";

  // Fit degli angoli
  TH1F *htheta = (TH1F *)FileData->Get("Theta angle");
  TH1F *hphi = (TH1F *)FileData->Get("Phi angle");

  double pi = TMath::Pi();
  TF1 *FitTheta = new TF1("FitTheta", "[0]", 0., pi);
  TF1 *FitPhi = new TF1("FitPhi", "[0]", 0., 2 * pi);

  TCanvas *c1 = new TCanvas("c1", "htheta", 200, 10, 600, 400);
  htheta->Draw();
  htheta->Fit("FitTheta");

  // a GetParameter() penso vada messo per forza un argomento in input, forse è
  // il parametro 0 ma non sono sicura (da eli)

  std::cout << "Parametri di Theta: " << FitTheta->GetParameter(0) << " +/- "
            << FitTheta->GetParError(0) << std::endl
            << "Chi quadro ridotto: "
            << (FitTheta->GetChisquare() / FitTheta->GetNDF()) << std::endl
            << "Probabilita`: " << FitTheta->GetProb() << std::endl;

  TCanvas *c2 = new TCanvas("c2", "hphi", 200, 10, 600, 400);
  hphi->Draw();
  hphi->Fit("FitPhi");

  std::cout << "Parametri di Phi: " << FitPhi->GetParameter(0) << " +/- "
            << FitPhi->GetParError(0) << std::endl
            << "Chi quadro ridotto: "
            << (FitPhi->GetChisquare() / FitPhi->GetNDF()) << std::endl
            << "Probabilita`: " << FitPhi->GetProb() << std::endl;
  std::cout << "END OF 2 PUNTO\n\n\n";

  // Fit dell'impulso
  TH1F *himpulse = (TH1F *)FileData->Get("Impulse");

  TF1 *FitImpulse = new TF1("FitImpulse", "expo(0)", 0., 6.);

  TCanvas *c3 = new TCanvas("c3", "himpulse", 200, 10, 600, 400);
  himpulse->Draw();
  himpulse->Fit("FitImpulse");

  std::cout << "Parametri dell'impulso: " << FitImpulse->GetParameter(0)
            << " +/- " << FitImpulse->GetParError(0) << std::endl
            << "Chi quadro ridotto: "
            << (FitImpulse->GetChisquare() / FitImpulse->GetNDF()) << std::endl
            << "Probabilita`: " << FitImpulse->GetProb() << std::endl;
  std::cout << "END OF 3 PUNTO\n\n\n";

  TH1F *h_samecharge_invmass = (TH1F *)FileData->Get("Invariant Mass of particles with concordant charge sign");
  TH1F *h_diffcharge_invmass = (TH1F *)FileData->Get("Invariant Mass of particles with discordant charge sign");
  TH1F *h_pk_samesign_invmass = (TH1F *)FileData->Get("InvMass, pk particles, same sign");
  TH1F *h_pk_diffsign_invmass = (TH1F *)FileData->Get("InvMass, pk particles, different sign");
  TH1F *h_decayed_invmass = (TH1F *)FileData->Get("Invariant Mass of decayed particles");

  TH1F *sub12 = new TH1F("sub12", "sub12", 200, 0, 2);

  sub12->Add(h_samecharge_invmass, 1);
  sub12->Add(h_diffcharge_invmass, -1);
  TCanvas *c5 = new TCanvas("c5", "Subtraction 1 - 2", 200, 10, 600, 400);
  TF1 *sub12Fit = new TF1("sub12Fit", "gaus", 0.4, 2);

  sub12->Draw();
  sub12->Draw("E,P,SAME");
  sub12->Fit(sub12Fit);
  // Printare i parametri quiI

  TH1F *sub34 = new TH1F("sub34", "sub34", 200, 0, 2);

  sub34->Add(h_pk_samesign_invmass, 1);
  sub34->Add(h_pk_diffsign_invmass, -1);
  TCanvas *c6 = new TCanvas("c6", "Subtraction 3 - 4", 200, 10, 600, 400);
  TF1 *sub34Fit = new TF1("sub34Fit", "gaus", 0.6, 1.6);
  sub34->Fit(sub34Fit);
  // Printare i parametri qui

  sub34->Draw();
  sub34->Draw("E,P,SAME");

  TCanvas *c7 = new TCanvas("c7", "Invariant Mass Decad", 200, 10, 600, 400);
  TF1 *h5Fit = new TF1("h5Fit", "gaus", 0.6, 1.6);
  h_decayed_invmass->Fit(h5Fit);
  // Printare i parametri qui

  h_decayed_invmass->Draw();
}

/*  InvMassCanvas->SaveAs("InvMassCanvas.pdf");
  PkInvMassCanvas->SaveAs("PkInvMassCanvas.pdf");
  DecInvMassCanvas->SaveAs("DecInvMassCanvas.pdf");

  InvMassCanvas->SaveAs("InvMassCanvas.root");
  PkInvMassCanvas->SaveAs("PkInvMassCanvas.root");
  DecInvMassCanvas->SaveAs("DecInvMassCanvas.root");

  InvMassCanvas->SaveAs("InvMassCanvas.C");
  PkInvMassCanvas->SaveAs("PkInvMassCanvas.C");
  DecInvMassCanvas->SaveAs("DecInvMassCanvas.C"); */