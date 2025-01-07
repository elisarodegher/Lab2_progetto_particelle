#include "Particle.h"
#include "ParticleType.h"
#include "ResonanceType.h"
#include <array>
#include <cmath>
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"

void ReadMyRootData()
{
    // Controllo se le percentuali hanno senso
    TFile *FileData = new TFile("Histograms.root");
    TH1F *hparticletypes = (TH1F *)FileData->Get("hparticletypes");
    int N_tot_conteggi = hparticletypes->GetEntries();

    if (N_tot_conteggi < 1E7 || N_tot_conteggi > 1.1E7)
    { // 100 particelle per 1E5 eventi -> ci aspettiamo 1E7 particelle in totale
        std::cout << "Non va per niente bene!!";
    }

    std::vector<double> aspettative = {0., 0.4, 0.4, 0.045, 0.045, 0.01};
    for (int i{1}; hparticletypes->GetBinContent(i) != 0; ++i)
    {
        double mean = hparticletypes->GetBinContent(i);
        double sigma = hparticletypes->GetBinError(i);
        if (aspettative[i] <= mean + sigma && mean - sigma <= aspettative[i])
        {
            std::cout << "Il programma genera le particelle secondo le proporzioni richieste " << std::endl;
        }
        else
        {
            std::cout << "Il programma e` no bueno :(" << std::endl;
        }
        ++i;
    }

    // Fit degli angoli
    TH1F *htheta = (TH1F *)FileData->Get("htheta");
    TH1F *hphi = (TH1F *)FileData->Get("hphi");

    TF1 *FitTheta = new TF1("FitTheta", "[0]", 0., 2 * TMath::Pi);
    TF1 *FitPhi = new TF1("FitPhi", "[0]", 0., 2 * TMath::Pi);

    htheta->Fit("FitTheta");
    hphi->Fit("FitPhi");

    std::cout << "Parametri di Theta: " << FitTheta->GetParameter() << " +/- " << FitTheta->GetParError() << std::endl
              << "Chi quadro ridotto: " << FitTheta->GetChisquare() << std::endl
              << "Probabilita`: " << FitTheta->GetProb() << std::endl;

    std::cout << "Parametri di Phi: " << FitPhi->GetParameter() << " +/- " << FitPhi->GetParError() << std::endl
              << "Chi quadro ridotto: " << FitPhi->GetChisquare() << std::endl
              << "Probabilita`: " << FitPhi->GetProb() << std::endl;

    // Fit dell'impulso
    TH1F *himpulse = (TH1F *)FileData->Get("himpulse");

    TF1 *FitImpulse = new TF1("FitImpulse", "expo(0)", 0., 6.);

    himpulse->Fit("FitImpulse");

    std::cout << "Parametri dell'impulso: " << FitImpulse->GetParameter() << " +/- " << FitImpulse->GetParError() << std::endl
              << "Chi quadro ridotto: " << FitImpulse->GetChisquare() << std::endl
              << "Probabilita`: " << FitImpulse->GetProb() << std::endl;
}

void AnalyseInvMass() {
    TFile *FileData = new TFile("Histograms.root");

    TH1F *h_samecharge_invmass = (TH1F *)FileData->Get("h_samecharge_invmass");
    TH1F *h_diffcharge_invmass = (TH1F *)FileData->Get("h_diffcharge_invmass");
    TH1F *h_pk_samesign_invmass = (TH1F *)FileData->Get("h_pk_samesign_invmass");
    TH1F *h_pk_diffsign_invmass = (TH1F *)FileData->Get("h_diffsign_invmass");
    TH1F *h_decayed_invmass = (TH1F *)FileData->Get("h_decayed_invmass");

    TH1F *h_invmass_difference = new TH1F(*h_samecharge_invmass);
    h_invmass_difference -> Add(h_samecharge_invmass, h_diffcharge_invmass, 1, -1);
    TH1F *h_pk_difference = new TH1F(*h_pk_samesign_invmass);
    h_pk_difference -> Add(h_pk_samesign_invmass, h_pk_diffsign_invmass, 1, -1);

    TF1 *FitInvMass = new TF1("FitInvMass", "gaus", 0., 20.);
    TF1 *FitPkInvMass = new TF1("FitPkInvMass", "gaus", 0., 20.);
    TF1 *FitDecayedInvMass = new TF1("FitDecayedInvMass", "gaus", 0., 20.);

    h_invmass_difference -> Fit("FitInvMass");
    h_pk_difference -> Fit("FitPkInvMass");
    h_decayed_invmass -> Fit("FitDecayedInvmass");

    std::cout << "Invariant mass difference data: " << std::endl;
    std::cout << "K* mass(mean) = " << FitInvMass -> GetParameter(1) << " +/- " << FitInvMass -> GetParError(1) << std::endl;
    std::cout << "K* lenght(sigma) = " << FitInvMass -> GetParameter(2) << " +/- " << FitInvMass -> GetParError(2) << std::endl;
    std::cout << "Chisquare = " << FitInvMass -> GetChisquare() << std::endl;
    std::cout << "Probability of chisquare = " << FitInvMass -> GetProb() << std::endl;

    std::cout << "Invariant mass pion/kaon difference data: " << std::endl;
    std::cout << "K* mass(mean) = " << FitPkInvMass -> GetParameter(1) << " +/- " << FitPkInvMass -> GetParError(1) << std::endl;
    std::cout << "K* lenght(sigma) = " << FitPkInvMass -> GetParameter(2) << " +/- " << FitPkInvMass -> GetParError(2) << std::endl;
    std::cout << "Chisquare = " << FitPkInvMass -> GetChisquare() << std::endl;
    std::cout << "Probability of chisquare = " << FitPkInvMass -> GetProb() << std::endl;

    std::cout << "Invariant mass decayed particles data: " << std::endl;
    std::cout << "K* mass(mean) = " << FitDecayedInvMass -> GetParameter(1) << " +/- " << FitDecayedInvMass -> GetParError(1) << std::endl;
    std::cout << "K* lenght(sigma) = " << FitDecayedInvMass -> GetParameter(2) << " +/- " << FitDecayedInvMass -> GetParError(2) << std::endl;
    std::cout << "Chisquare = " << FitDecayedInvMass -> GetChisquare() << std::endl;
    std::cout << "Probability of chisquare = " << FitDecayedInvMass -> GetProb() << std::endl;
}