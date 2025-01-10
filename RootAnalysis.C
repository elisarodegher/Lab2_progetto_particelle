// mi da problemi con le cose di c++ tipo vector e std library
#include <iostream>
void RootAnalysis()
{

  gSystem->Load("libHist.so");
  gSystem->Load("libTree.so");
  // Controllo della generazione
  std::cout << "Part 1: control of generation proportions" << std::endl;
  TFile *FileData = new TFile("Histograms2.root");

  TH1F *hparticletypes = (TH1F *)FileData->Get("Particle types"); // leggo i 4 istogrammi
  TH1F *htheta = (TH1F *)FileData->Get("Theta angle");
  TH1F *hphi = (TH1F *)FileData->Get("Phi angle");
  TH1F *himpulse = (TH1F *)FileData->Get("Impulse");

  if (!hparticletypes || !htheta || !hphi || !himpulse)
  { // controllo che esistanp
    std::cerr << "Errore: impossibile trovare uno o più istogrammi!" << std::endl;
    return;
  }
  // check sul conteggio delle particelle

  std::cout << "PARTICLE OCCURRENCES" << std::endl;

  int N_tot_conteggi = hparticletypes->GetEntries();
  if (N_tot_conteggi < 1E7 ||
      N_tot_conteggi > 1.1E7)
  { // 100 particles * 1E5 events: we expect a bit more than 1E7 particles
    std::cout << "Warning: the number of generated particles does not follow the prevision!" << std::endl;
  }
  std::cout << "Number of occurrences: " << N_tot_conteggi << std::endl;

  // check aspettative sulle proporzioni di generazione dei tipi di particelle

  std::vector<double> aspettative = {0.4, 0.4, 0.05, 0.05, 0.045, 0.045, 0.01};
  bool error;
  for (int i{0}; hparticletypes->GetBinContent(i) != 0; ++i)
  {
    double mean = hparticletypes->GetBinContent(i) / N_tot_conteggi;
    double sigma = hparticletypes->GetBinError(i);
    if (aspettative[i] <= mean + sigma && mean - sigma <= aspettative[i])
    {
      error = false;
    }
    else
    {
      error = true;
    }
    std::cout << "Particle index: " << i << ", fraction expected: " << aspettative[i] << ", fraction found: " << mean << " +/- " << sigma << std::endl;
  }
  if (error)
  {
    std::cout << "Warning: particles are not generated following the prevision!" << std::endl;
  }

  std::cout << "End of part 1\n\n\n";

  // Creazione della canvas divisa in 4
  TCanvas *multiCanvas = new TCanvas("multiCanvas", "Distribuzioni", 800, 800);
  multiCanvas->Divide(2, 2);

  // Abbondanza delle particelle
  multiCanvas->cd(1);
  hparticletypes->SetLineColor(kBlue);
  hparticletypes->SetLineWidth(2);
  hparticletypes->SetXTitle("Particle Type");
  hparticletypes->SetYTitle("Counts");
  hparticletypes->GetXaxis()->CenterTitle();
  hparticletypes->GetYaxis()->CenterTitle();
  hparticletypes->Draw(); // istogramma dei tipi di particelle

  // Angolo polare
  multiCanvas->cd(2);
  double pi = TMath::Pi();
  TF1 *FitTheta = new TF1("FitTheta", "[0]", 0., pi); // fit di theta
  htheta->SetLineColor(kRed);
  htheta->SetLineWidth(2);
  htheta->SetXTitle("Theta (rad)");
  htheta->SetYTitle("Counts");
  htheta->GetXaxis()->CenterTitle();
  htheta->GetYaxis()->CenterTitle();
  htheta->Fit("FitTheta");
  htheta->Draw();

  // Angolo azimutale
  multiCanvas->cd(3);
  TF1 *FitPhi = new TF1("FitPhi", "[0]", 0., 2 * pi); // fit di phi
  hphi->SetLineColor(kGreen);
  hphi->SetLineWidth(2);
  hphi->SetXTitle("Phi (rad)");
  hphi->SetYTitle("Counts");
  hphi->GetXaxis()->CenterTitle();
  hphi->GetYaxis()->CenterTitle();
  hphi->Fit("FitPhi");
  hphi->Draw();

  // Impulso
  multiCanvas->cd(4);
  TF1 *FitImpulse = new TF1("FitImpulse", "expo(0)", 0., 6.); // fit dell'impulso
  himpulse->SetLineColor(kMagenta);
  himpulse->SetLineWidth(2);
  himpulse->SetXTitle("Impulse (GeV/c)");
  himpulse->SetYTitle("Counts");
  himpulse->GetXaxis()->CenterTitle();
  himpulse->GetYaxis()->CenterTitle();
  himpulse->Fit("FitImpulse");
  himpulse->Draw();

  gStyle->SetOptStat(1111);
  gStyle->SetOptFit(1111);

  // stampa a schermo dei parametri
  std::cout << "Theta angle parameters: " << FitTheta->GetParameter(0) << " +/- "
            << FitTheta->GetParError(0) << std::endl
            << "Chisquare: " << FitTheta->GetChisquare() << std::endl
            << "NDF: " << FitTheta->GetNDF() << std::endl
            << "Reduced chisquare: "
            << (FitTheta->GetChisquare() / FitTheta->GetNDF()) << std::endl
            << "Probability: " << FitTheta->GetProb() << std::endl;

  std::cout << "Phi angle parameters: " << FitPhi->GetParameter(0) << " +/- "
            << FitPhi->GetParError(0) << std::endl
            << "Chisquare: " << FitPhi->GetChisquare() << std::endl
            << "NDF: " << FitPhi->GetNDF() << std::endl
            << "Reduced chisquare: "
            << (FitPhi->GetChisquare() / FitPhi->GetNDF()) << std::endl
            << "Probability: " << FitPhi->GetProb() << std::endl;

  std::cout << "Impulse parameters: " << FitImpulse->GetParameter(0)
            << " +/- " << FitImpulse->GetParError(0) << std::endl
            << "Chisquare: " << FitImpulse->GetChisquare() << std::endl
            << "NDF: " << FitImpulse->GetNDF() << std::endl
            << "Reduced chisquare: "
            << (FitImpulse->GetChisquare() / FitImpulse->GetNDF()) << std::endl
            << "Probability: " << FitImpulse->GetProb() << std::endl;
  std::cout << "End of part 2\n\n\n";

  // Invariant mass analysis
  std::cout << "Part 3: Invariant Mass Analysis" << std::endl;
  TH1F *h_samecharge_invmass = (TH1F *)FileData->Get("Invariant Mass of particles with concordant charge sign");
  TH1F *h_diffcharge_invmass = (TH1F *)FileData->Get("Invariant Mass of particles with discordant charge sign");
  TH1F *h_pk_samesign_invmass = (TH1F *)FileData->Get("InvMass, pk particles, same sign");
  TH1F *h_pk_diffsign_invmass = (TH1F *)FileData->Get("InvMass, pk particles, different sign");
  TH1F *h_decayed_invmass = (TH1F *)FileData->Get("Invariant Mass of decayed particles");

  // Invariant mass canvas creation
  TCanvas *multiCanvas2 = new TCanvas("multiCanvas2", "Distribuzioni", 800, 800);
  multiCanvas2->Divide(2, 2);

  // Invariant mass - all particles
  multiCanvas2->cd(1);
  TH1F *sub12 = new TH1F("sub12", "sub12", 200, 0, 2);
  sub12->Add(h_diffcharge_invmass, 1);
  sub12->Add(h_samecharge_invmass, -1);
  TF1 *sub12Fit = new TF1("sub12Fit", "gaus", 0.4, 2);
  sub12->Fit(sub12Fit);
  sub12->SetLineColor(kBlue);
  sub12->SetLineWidth(2);
  sub12->SetXTitle("Inv Mass (GeV/c^2)");
  sub12->SetYTitle("Counts");
  sub12->GetXaxis()->CenterTitle();
  sub12->GetYaxis()->CenterTitle();

  sub12->Draw();
  sub12->Draw("E,P,SAME");

  // Invariant mass - pion/kaon couple of particles
  multiCanvas2->cd(2);
  TH1F *sub34 = new TH1F("sub34", "sub34", 200, 0, 2);

  sub34->Add(h_pk_diffsign_invmass, 1);
  sub34->Add(h_pk_samesign_invmass, -1);
  TF1 *sub34Fit = new TF1("sub34Fit", "gaus", 0.6, 1.6);
  sub34->Fit(sub34Fit);
  sub34->SetLineColor(kBlue);
  sub34->SetLineWidth(2);
  sub34->SetXTitle("Inv Mass (GeV/c^2)");
  sub34->SetYTitle("Counts");
  sub34->GetXaxis()->CenterTitle();
  sub34->GetYaxis()->CenterTitle();

  sub34->Draw();
  sub34->Draw("E,P,SAME");

  // Invariant mass - decayed particles
  multiCanvas2->cd(3);
  TF1 *h5Fit = new TF1("h5Fit", "gaus", 0.6, 1.6);
  h_decayed_invmass->Fit(h5Fit);
  h_decayed_invmass->SetLineColor(kBlue);
  h_decayed_invmass->SetLineWidth(2);
  h_decayed_invmass->SetXTitle("Inv Mass (GeV/c^2)");
  h_decayed_invmass->SetYTitle("Counts");
  h_decayed_invmass->GetXaxis()->CenterTitle();
  h_decayed_invmass->GetYaxis()->CenterTitle();

  h_decayed_invmass->Draw();
  h_decayed_invmass->Draw("E,P,SAME");

  // Screen prints
  // Invariant Mass - all particles
  std::cout << "Parameters from the subtraction of histograms of Invariant Mass from all particles" << std::endl;
  std::cout << "Mean: " << sub12Fit->GetParameter(1) << " +/- " << sub12Fit->GetParError(1) << std::endl;
  std::cout << "Sigma: " << sub12Fit->GetParameter(2) << " +/- " << sub12Fit->GetParError(2) << std::endl;
  std::cout << "Amplitude: " << sub12Fit->GetParameter(0) << " +/- " << sub12Fit->GetParError(0) << std::endl;
  std::cout << "Reduced chisquare: " << sub12Fit->GetChisquare() / sub12Fit->GetNDF() << std::endl;
  std::cout << "Probability: " << sub12Fit->GetProb() << std::endl;

  // Invariant Mass - pion/kaon couple of particles
  std::cout << "Parameters from the subtraction of histograms of Invariant Mass from pion/kaon couple of particles" << std::endl;
  std::cout << "Mean: " << sub34Fit->GetParameter(1) << " +/- " << sub34Fit->GetParError(1) << std::endl;
  std::cout << "Sigma: " << sub34Fit->GetParameter(2) << " +/- " << sub34Fit->GetParError(2) << std::endl;
  std::cout << "Amplitude: " << sub34Fit->GetParameter(0) << " +/- " << sub34Fit->GetParError(0) << std::endl;
  std::cout << "Reduced chisquare: " << sub34Fit->GetChisquare() / sub34Fit->GetNDF() << std::endl;
  std::cout << "Probability: " << sub34Fit->GetProb() << std::endl;

  // Invariant Mass - decayed particles
  std::cout << "Parameters from the histogram of Invariant Mass of decayed particles" << std::endl;
  std::cout << "Mean: " << h5Fit->GetParameter(1) << " +/- " << h5Fit->GetParError(1) << std::endl;
  std::cout << "Sigma: " << h5Fit->GetParameter(2) << " +/- " << h5Fit->GetParError(2) << std::endl;
  std::cout << "Amplitude: " << h5Fit->GetParameter(0) << " +/- " << h5Fit->GetParError(0) << std::endl;
  std::cout << "Reduced chisquare: " << h5Fit->GetChisquare() / h5Fit->GetNDF() << std::endl;
  std::cout << "Probability: " << h5Fit->GetProb() << std::endl;

  multiCanvas->SaveAs("Distributions.pdf");
  multiCanvas->SaveAs("Distributions.root");
  multiCanvas->SaveAs("Distributions.C");

  multiCanvas2->SaveAs("InvMassCanvas.pdf");
  multiCanvas2->SaveAs("InvMassCanvas.root");
  multiCanvas2->SaveAs("InvMassCanvas.C");
}

