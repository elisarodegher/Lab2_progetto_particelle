// mi da problemi con le cose di c++ tipo vector e std library

#include <iostream>
void RootAnalysis() {
  //Controllo della generazione
  std::cout << "Part 1: control of generation proportions" << std::endl;
  TFile *FileData = new TFile("macros/Lab2_progetto_particelle/Histograms2.root");
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
  std::cout << "PARTICLE OCCURRENCES" << std::endl;

  int N_tot_conteggi = hparticletypes->GetEntries();
  if (N_tot_conteggi < 1E7 ||
      N_tot_conteggi > 1.1E7) { // 100 particles * 1E5 events: we expect a bit more than 1E7 particles
    std::cout << "Warning: the number of generated particles does not follow the prevision!" << std::endl;
  }
  std::cout << "Number of occurrences: " << N_tot_conteggi << std::endl;
  TCanvas *particle_types = new TCanvas("Particle Types", "Particle Types distribution", 200, 10, 600, 400);
  hparticletypes->Draw();
  
  std::vector<double> aspettative = {0.4, 0.4, 0.05, 0.05, 0.045, 0.045, 0.01};
  bool error;
  for (int i{0}; hparticletypes->GetBinContent(i) != 0; ++i) {
    double mean = hparticletypes->GetBinContent(i) / N_tot_conteggi;
    double sigma = hparticletypes->GetBinError(i);
    if (aspettative[i] <= mean + sigma && mean - sigma <= aspettative[i]) {
      error = false;
    } else {
      error = true;
    }
    std::cout << "Particle index: " << i << ", fraction expected: " << aspettative[i] << ", fraction found: " << mean << " +/- " << sigma << std::endl;
  } 
  if (error) {
    std::cout << "Warning: particles are not generated following the prevision!" << std::endl;
  }

  

  std::cout << "End of part 1\n\n\n";

  //Fit degli angoli
  std::cout << "Part 2: Fit of polar coordinates" << std::endl;

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

  std::cout << "Theta angle parameters: " << FitTheta->GetParameter(0) << " +/- "
            << FitTheta->GetParError(0) << std::endl 
            << "Chisquare: " << FitTheta->GetChisquare() << std::endl
            << "NDF: " << FitTheta->GetNDF() << std::endl
            << "Reduced chisquare: "
            << (FitTheta->GetChisquare() / FitTheta->GetNDF()) << std::endl
            << "Probability: " << FitTheta->GetProb() << std::endl;

  TCanvas *c2 = new TCanvas("c2", "hphi", 200, 10, 600, 400);
  hphi->Draw();
  hphi->Fit("FitPhi");

  std::cout << "Phi angle parameters: " << FitPhi->GetParameter(0) << " +/- "
            << FitPhi->GetParError(0) << std::endl
            << "Chisquare: " << FitPhi->GetChisquare() << std::endl
            << "NDF: " << FitPhi->GetNDF() << std::endl
            << "Reduced chisquare: "
            << (FitPhi->GetChisquare() / FitPhi->GetNDF()) << std::endl
            << "Probability: " << FitPhi->GetProb() << std::endl;

  // Fit dell'impulso
  TH1F *himpulse = (TH1F *)FileData->Get("Impulse");

  TF1 *FitImpulse = new TF1("FitImpulse", "expo(0)", 0., 6.);

  TCanvas *c3 = new TCanvas("c3", "himpulse", 200, 10, 600, 400);
  himpulse->Draw();
  himpulse->Fit("FitImpulse");

  std::cout << "Impulse parameters: " << FitImpulse->GetParameter(0)
            << " +/- " << FitImpulse->GetParError(0) << std::endl
            << "Chisquare: " << FitImpulse->GetChisquare() << std::endl
            << "NDF: " << FitImpulse->GetNDF() << std::endl
            << "Reduced chisquare: "
            << (FitImpulse->GetChisquare() / FitImpulse->GetNDF()) << std::endl
            << "Probability: " << FitImpulse->GetProb() << std::endl;
  std::cout << "End of part 2\n\n\n";

  //Invariant mass analysis
  std::cout << "Part 3: Invariant Mass Analysis" << std::endl;
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
  sub12->Fit(sub12Fit);

  sub12->Draw();
  sub12->Draw("E,P,SAME");
  
  
  std::cout << "Parameters from the subtraction of histograms of Invariant Mass from all particles" << std::endl;
  std::cout << "Mean: " << sub12Fit->GetParameter(1) << " +/- " << sub12Fit->GetParError(1) << std::endl;
  std::cout << "Sigma: " << sub12Fit->GetParameter(2) << " +/- " << sub12Fit->GetParError(2) << std::endl;
  std::cout << "Amplitude: " << sub12Fit->GetParameter(0) << " +/- " << sub12Fit->GetParError(0) << std::endl;
  std::cout << "Reduced chisquare: " << sub12Fit->GetChisquare() / sub12Fit->GetNDF() << std::endl;
  std::cout << "Probability: " << sub12Fit->GetProb() << std::endl;

  TH1F *sub34 = new TH1F("sub34", "sub34", 200, 0, 2);

  sub34->Add(h_pk_samesign_invmass, 1);
  sub34->Add(h_pk_diffsign_invmass, -1);
  TCanvas *c6 = new TCanvas("c6", "Subtraction 3 - 4", 200, 10, 600, 400);
  TF1 *sub34Fit = new TF1("sub34Fit", "gaus", 0.6, 1.6);
  sub34->Fit(sub34Fit);
  
  sub34->Draw();
  sub34->Draw("E,P,SAME");

  std::cout << "Parameters from the subtraction of histograms of Invariant Mass from pion/kaon couple of particles" << std::endl;
  std::cout << "Mean: " << sub34Fit->GetParameter(1) << " +/- " << sub34Fit->GetParError(1) << std::endl;
  std::cout << "Sigma: " << sub34Fit->GetParameter(2) << " +/- " << sub34Fit->GetParError(2) << std::endl;
  std::cout << "Amplitude: " << sub34Fit->GetParameter(0) << " +/- " << sub34Fit->GetParError(0) << std::endl;
  std::cout << "Reduced chisquare: " << sub34Fit->GetChisquare() / sub34Fit->GetNDF() << std::endl;
  std::cout << "Probability: " << sub34Fit->GetProb() << std::endl;

  TCanvas *c7 = new TCanvas("c7", "Invariant Mass Decad", 200, 10, 600, 400);
  TF1 *h5Fit = new TF1("h5Fit", "gaus", 0.6, 1.6);
  h_decayed_invmass->Fit(h5Fit);
  h_decayed_invmass->Draw();

  std::cout << "Parameters from the histogram of Invariant Mass of decayed particles" << std::endl;
  std::cout << "Mean: " << h5Fit->GetParameter(1) << " +/- " << h5Fit->GetParError(1) << std::endl;
  std::cout << "Sigma: " << h5Fit->GetParameter(2) << " +/- " << h5Fit->GetParError(2) << std::endl;
  std::cout << "Amplitude: " << h5Fit->GetParameter(0) << " +/- " << h5Fit->GetParError(0) << std::endl;
  std::cout << "Reduced chisquare: " << h5Fit->GetChisquare() / h5Fit->GetNDF() << std::endl;
  std::cout << "Probability: " << h5Fit->GetProb() << std::endl;
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