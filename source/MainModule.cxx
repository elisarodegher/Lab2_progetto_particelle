#include "Particle.h"
#include "ParticleType.h"
#include "ResonanceType.h"
#include <array>
#include <cmath>

int main()
{

    Particle::AddParticleType("p+", 0.13957, 1, 0.);
    Particle::AddParticleType("p-", 0.13957, -1, 0.);
    Particle::AddParticleType("k+", 0.49367, 1, 0.);
    Particle::AddParticleType("k-", 0.49367, -1, 0.);
    Particle::AddParticleType("pr+", 0.93827, 1, 0.);
    Particle::AddParticleType("pr-", 0.93827, 1, 0.);
    Particle::AddParticleType("k*", 0.89166, 0, 0.05);

    gRandom->SetSeed();

    std::vector<Particle> ParticleArray;

    Particle particle;

    int N_events{1E5};

    TH1F *hparticletypes = new TH1F("Particle types", "Particle type distribution", 6., 0., 6.);
    TH1F *hphi = new TH1F("Phi angle", "Phi angle distribution", 360., 0., 6.283);
    TH1F *htheta = new TH1F("Theta angle", "Theta angle distribution", 180., 0., 3.1415);
    TH1F *himpulse = new TH1F("Impulse", "Impulse distribution", 60., 0., 6.);
    TH1F *htrimp = new TH1F("Trasverse Impulse", "Trasverse impulse distribution", 60., 0., 6.);
    TH1F *henergy = new TH1F("Energy", "Energy distrbution", 70., 0., 7.);
    TH1F *h_all_invmass = new TH1F("Invariant Mass of all particles", "Invariant Mass distribution", 200., 0., 20.);
    TH1F *h1_samecharge_invmass = new TH1F("Invariant Mass of particles with concordant charge sign", "Invariant Mass of particles with concordant charge sign distribution", 200., 0., 20.);
    TH1F *h1_diffcharge_invmass = new TH1F("Invariant Mass of particles with discordant charge sign", "Invariant Mass of particles with discordant charge sign distribution", 200., 0., 20.);
    TH1F *h2_samecharge_invmass = new TH1F("Invariant Mass of k* particles with concordant charge sign", "Invariant Mass of k* particles with concordant charge sign distribution", 200., 0., 20.);
    TH1F *h2_diffcharge_invmass = new TH1F("Invariant Mass of k* particles with discordant charge sign", "Invariant Mass of k* particles with discordant charge sign distribution", 200., 0., 20.);
    // senza pedice : tutte le particelle
    // pedice 1 : particelle escludendo le k*
    // pedice 2 : solo particelle k*

    for (int i = 0; i < N_events; ++i)
    {
        for (int j = 0; j < 100; ++j)
        {
            double Phi = gRandom->Rndm() * 2 * Tmath::Pi();
            double Theta = gRandom->Rndm() * Tmath::Pi();
            double Impulse = gRandom->Exp(1.);
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
            }
            // aggiungo la particella all'array
            ParticleArray.push_back(particle);

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
                if (x < 0.5)
                {
                    Particle pione_pos("p+", 0., 0., 0.);
                    Particle kaone_neg("k-", 0., 0., 0.);
                    particle.Decay2body(pione_pos, kaone_neg);
                    ParticleArray.push_back(pione_pos);
                    ParticleArray.push_back(kaone_neg);
                }
                else
                {
                    Particle pione_neg("p-", 0., 0., 0.);
                    Particle kaone_pos("k+", 0., 0., 0.);
                    particle.Decay2body(pione_neg, kaone_pos);
                    ParticleArray.push_back(pione_neg);
                    ParticleArray.push_back(kaone_pos);
                }
            }
        } // fine ciclo di un singolo evento (100 particelle)

        for (int j = 0; j < ParticleArray.size(); j++)
        {
            hparticletypes->Fill(ParticleArray[j].GetIndex());
        }
    }
}
