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
    TH1F *FileData = new TH1F("Histograms.root");
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