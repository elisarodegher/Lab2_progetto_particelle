#include "Particle.h"
#include "ParticleType.h"
#include "ResonanceType.h"
#include <array>
#include <cmath>
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include "TRandom.h"
#include <TApplication.h>
#include <TFile.h>
#include <TH1.h>

int main()
{

    double pi = TMath::Pi();

    Particle::AddParticleType("p+", 0.13957, 1, 0.);
    Particle::AddParticleType("p-", 0.13957, -1, 0.);
    Particle::AddParticleType("k+", 0.49367, 1, 0.);
    Particle::AddParticleType("k-", 0.49367, -1, 0.);
    Particle::AddParticleType("pr+", 0.93827, 1, 0.);
    Particle::AddParticleType("pr-", 0.93827, -1, 0.);
    Particle::AddParticleType("k*", 0.89166, 0, 0.05);

    gRandom->SetSeed();

    int N_events{1E5};

    TH1F *hparticletypes = new TH1F("Particle types", "Particle type distribution", 6., 0., 6.);
    TH1F *hphi = new TH1F("Phi angle", "Phi angle distribution", 360., 0., 6.283);
    TH1F *htheta = new TH1F("Theta angle", "Theta angle distribution", 180., 0., 3.1415);
    TH1F *himpulse = new TH1F("Impulse", "Impulse distribution", 60., 0., 6.);
    TH1F *htrimp = new TH1F("Trasverse Impulse", "Trasverse impulse distribution", 60., 0., 6.);
    TH1F *henergy = new TH1F("Energy", "Energy distrbution", 70., 0., 7.);
    TH1F *h_all_invmass = new TH1F("Invariant Mass of all particles", "Invariant Mass distribution", 200., 0., 20.);
    TH1F *h_samecharge_invmass = new TH1F("Invariant Mass of particles with concordant charge sign", "Invariant Mass of particles with concordant charge sign distribution", 200., 0., 20.);
    TH1F *h_diffcharge_invmass = new TH1F("Invariant Mass of particles with discordant charge sign", "Invariant Mass of particles with discordant charge sign distribution", 200., 0., 20.);
    TH1F *h_pk_samesign_invmass = new TH1F("Invariant Mass of .... particles with concordant charge sign", "Invariant Mass of ... particles with concordant charge sign distribution", 200., 0., 20.);
    TH1F *h_pk_diffsign_invmass = new TH1F("Invariant Mass of ... different charge sign", "Invariant Mass of ... particles with discordant charge sign distribution", 200., 0., 20.);
    TH1F *h_decayed_invmass = new TH1F("Invariant Mass of decayed particles", "Invariant Mass of decayed particles distribution", 200., 0., 20.); // valori messi a caso raga
                                                                                                                                                  // senza pedice : tutte le particelle
                                                                                                                                                  // pedice 1 : particelle escludendo le k*
                                                                                                                                                  // pedice 2 : solo particelle k*

    for (int i = 0; i < N_events; ++i)
    {

        std::vector<Particle> ParticleArray;
        Particle particle;

        for (int j = 0; j < 100; ++j)
        {
            // generazione coordinate polari
            double Phi = gRandom->Rndm() * 2 * pi;
            double Theta = gRandom->Rndm() * pi;
            double Impulse = gRandom->Exp(1.);
            // conversione coordinate cartesiane
            double fPx = Impulse * sin(Theta) * sin(Phi);
            double fPy = Impulse * sin(Theta) * cos(Phi);
            double fPz = Impulse * cos(Theta);

            particle.SetP(fPx, fPy, fPz);

            double type{0};
            type = gRandom->Rndm(); // numero random tra 0 e 1, ad ogni estrazione corrisponderà un tipo di particella
            if (type < 0.4)
            {
                particle.SetIndex(0); // pione +
            }
            else if (type < 0.8)
            {
                particle.SetIndex(1); // pione -
            }
            else if (type < 0.85)
            {
                particle.SetIndex(2); // kaone +
            }
            else if (type < 0.9)
            {
                particle.SetIndex(3); // kaone -
            }
            else if (type < 0.945)
            {
                particle.SetIndex(4); // protone +
            }
            else if (type < 0.99)
            {
                particle.SetIndex(5); // protone -
            }
            else
            {
                particle.SetIndex(6); // risonanza k*
            } // forse è possible mettere uno switch?

            double trasverse_impulse = std::sqrt(fPx * fPx + fPy * fPy); // impulso trasverso
            double energy = particle.GetEnergy();                        // energia

            // riempimento istogrammi
            hparticletypes->Fill(particle.GetIndex());
            hphi->Fill(Phi);
            htheta->Fill(Theta);
            himpulse->Fill(Impulse);
            htrimp->Fill(trasverse_impulse);
            henergy->Fill(energy);

            // gestione della risonanza k*
            if (particle.GetIndex() == 6)
            {
                double x = gRandom->Rndm();
                Particle figlia1;
                Particle figlia2;
                if (x < 0.5)
                {
                    Particle pione_pos("p+", 0., 0., 0.);
                    Particle kaone_neg("k-", 0., 0., 0.);
                    particle.Decay2body(pione_pos, kaone_neg);
                    ParticleArray.push_back(pione_pos);
                    ParticleArray.push_back(kaone_neg);
                    figlia1 = pione_pos;
                    figlia2 = kaone_neg;
                }
                else
                {
                    Particle pione_neg("p-", 0., 0., 0.);
                    Particle kaone_pos("k+", 0., 0., 0.);
                    particle.Decay2body(pione_neg, kaone_pos);
                    ParticleArray.push_back(pione_neg);
                    ParticleArray.push_back(kaone_pos);
                    figlia1 = pione_neg;
                    figlia2 = kaone_pos;
                }
                double InvMass_decayed = figlia1.GetInvMass(figlia2);
                h_decayed_invmass->Fill(InvMass_decayed);
            }
            else // se non è una k*, non la faccio decadere e la agg. direttamente
            {
                ParticleArray.push_back(particle);
            }
        } // fine ciclo di un singolo evento (100 particelle)

        for (int j = 0; j < ParticleArray.size(); j++) // esterni dal ciclo del singolo evento
        {
            hparticletypes->Fill(ParticleArray[j].GetIndex()); // riempimento istogramma tipi di particelle

            for (int k = j + 1; k < (ParticleArray.size() - 1); k++)
            {

                double InvMass = ParticleArray[j].GetInvMass(ParticleArray[k]); // massa invariante

                // controllo carica concorde/ discorde
                if (ParticleArray[j].GetCharge() * ParticleArray[k].GetCharge() > 0)
                {
                    h_samecharge_invmass->Fill(InvMass);
                }
                else
                {
                    h_diffcharge_invmass->Fill(InvMass);
                }

                // Massa invariante di combinazioni (Pione+ / Kaone- e Pione- / Kaone+)
                if ((ParticleArray[j].GetIndex() == 0 && ParticleArray[k].GetIndex() == 3) ||
                    (ParticleArray[j].GetIndex() == 1 && ParticleArray[k].GetIndex() == 2))
                {
                    h_pk_diffsign_invmass->Fill(InvMass); // Massa invariante tra pion+/Kaone- e pion-/Kaone+
                }

                // Massa invariante di combinazioni specifiche (Pione+ / Kaone+ e Pione- / Kaone-)
                if ((ParticleArray[j].GetIndex() == 0 && ParticleArray[k].GetIndex() == 2) ||
                    (ParticleArray[j].GetIndex() == 1 && ParticleArray[k].GetIndex() == 3))
                {
                    h_pk_samesign_invmass->Fill(InvMass); // Massa invariante tra pion+/Kaone+ e pion-/Kaone-
                } // eli qua le avevi invertite? ho corretto

                h_all_invmass->Fill(InvMass); // Massa invariante di tutte le particelle
            }
        }
    }

    TFile *FileData = new TFile("Histograms.root", "RECREATE");
    hparticletypes->Write();
    hphi->Write();
    htheta->Write();
    himpulse->Write();
    htrimp->Write();
    henergy->Write();
    h_all_invmass->Write();
    h_samecharge_invmass->Write();
    h_diffcharge_invmass->Write();
    h_pk_samesign_invmass->Write();
    h_pk_diffsign_invmass->Write();
    h_decayed_invmass->Write();
    FileData->Close();
}
