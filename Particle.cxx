#include "Particle.h"
#include "ParticleType.h"
#include <cassert>
#include <cmath>

Particle::Particle(char *fname, double fPx, double fPy, double fPz) : fPx_(fPx), fPy_(fPy), fPz_(fPz)
{
    if (FindParticle(fname) == 11)
    {
        std::cout << "no correspondence found!\n";
    }
    else
    {
        fIndex_ = FindParticle(fname); // parte del costruttore che dato un nome assegna un indice usando la funzione Find Particle
    }
}

int Particle::FindParticle(char *fname) // dato il nome della particella mi restituisce l'indice (cioè il tipo corrispondente)
{
    for (int i = 0; i < fParticleType.size(); i++) // qui ho messo il vector size
    {
        char p_name = (fParticleType[i])->GetParticleName();
        if (p_name == *fname)
        {
            return i;
        }
        else
        {
            return 11;
        }
    }
}

void Particle::AddParticleType(char *fname, double fmass, int fcharge, double const fwidth) // boh forse da risistemare con vettore vedi sotto il second try
{

    if (fwidth == 0)
    {
        ParticleType ptype(fname, fmass, fcharge);
        assert(FindParticle(fname) == 11);
    }
    else
    {
        ResonanceType rtype(fname, fmass, fcharge, fwidth);
    }
};

int Particle::GetIndex()
{
    return fIndex_;
}

// second try

void Particle::AddParticleType(ResonanceType *rtype) // forse da fare con particle e non resonance
{
    fParticleType.push_back(rtype);
};

void Particle::SetIndex(int index)
{ // setter versione con indice in input
    if (index >= 0 && index < static_cast<int>(fParticleType.size()))
    { // static cast serve per motivi di conversione implicita
        fIndex_ = index;
    }
    else
    {
        std::cout << "Indice non valido!" << std::endl;
    }
}

// Setter per il codice della particella (versione con nome)
void Particle::SetIndex(char *name)
{ // boh mi da problemi con  l'overload
    int index = FindParticle(name);
    if (index != 11)
    {
        fIndex_ = index;
    }
    else
    {
        std::cout << "Tipo di particella \"" << name << "\" non trovato!" << std::endl;
    }
}

double const Particle::GetPx() { return fPx_; }
double const Particle::GetPy() { return fPy_; }
double const Particle::GetPz() { return fPz_; }

// Getter per la massa della particella
double const Particle::GetMass()
{

    return fParticleType[fIndex_]->GetParticleMass();
}

// Calcolo dell'energia totale della particella
double const Particle::GetEnergy()
{
    double mass = GetMass();
    double momentum2 = fPx_ * fPx_ + fPy_ * fPy_ + fPz_ * fPz_;
    return std::sqrt(mass * mass + momentum2);
}

double const Particle::GetInvMass(Particle &p)
{
    double e1 = GetEnergy();   // en della particella corrente
    double e2 = p.GetEnergy(); // en della seconda particella, quella data in input
    double P1x = GetPx();
    double P1y = GetPy();
    double P1z = GetPz();
    double P2x = p.GetPx();
    double P2y = p.GetPy();               // ommioddio quanto fa cagare sorrry :((((
    double P2z = p.GetPz();

    double InvMass = std::sqrt((e1 + e2) * (e1 + e2) + (P1x + P2x) * (P1x + P2x) + (P1y + P2y) * (P1y + P2y) + (P1z + P2z) * (P1z + P2z))
};