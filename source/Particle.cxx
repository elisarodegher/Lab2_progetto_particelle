#include "../include/Particle.h"
#include "../include/ParticleType.h"
#include <cmath>   // for M_PI
#include <cstdlib> //for RAND_MAX

int const Particle::fMaxNumParticleType_ = 10;
std::vector<ParticleType *> Particle::fParticleType;
int Particle::fNParticleType_;

Particle::Particle() {};

Particle::Particle(const char *fname, double fPx, double fPy, double fPz) : fPx_(fPx), fPy_(fPy), fPz_(fPz)
{
    if (FindParticle(fname) == -1)
    {
        std::cout << "no correspondence found!\n";
        fIndex_ = -1;
    }
    else
    {
        fIndex_ = FindParticle(fname);
    }
}

// scorre nel vettore che contiene i tipi di particelle per vedere se trova una corrispondenza di indice con la particella analizzata
//(data in input tramite nome)
int Particle::FindParticle(const char *fname)
{
    for (int i = 0; i < static_cast<int>(fParticleType.size()); i++)
    {
        char p_name = (fParticleType[i])->GetParticleName();
        if (p_name == *fname)
        {
            return i;
        }
    }
    return -1;
}

int Particle::GetIndex() const
{
    return fIndex_;
}

// Aggiunge un nuovo tipo di particella, se la particella non viene trovata nel vector di tipi di particelle. (quindi se l'indice è -1)
// se indice=-1 , controlla se la risonanza è nulla o non nulla per aggiungerla come "resonancetype" o come "particletype"
void Particle::AddParticleType(const char *fName, double fMass, int fCharge, double fWidth)
{
    if (fParticleType.size() >= fMaxNumParticleType_)
    {
        std::cout << "Cannot add more particle types. Maximum limit of " << fMaxNumParticleType_ << "reached\n";
        return;
    }

    if (FindParticle(fName) != -1)
    {
        throw std::runtime_error("Particle type already exists: " + std::string(fName));
    }
    else
    {

        if (fWidth == 0)
        {
            ParticleType *particleptr = new ParticleType{fName, fMass, fCharge};

            fParticleType.push_back(particleptr);
        }
        else
        {
            ParticleType *resonanceptr = new ResonanceType{fName, fMass, fCharge, fWidth};
            fParticleType.push_back(resonanceptr);
        }
    }
}

void Particle::SetIndex(int index)
{ // setter versione con indice in input
    if (index >= 0 && index < static_cast<int>(fParticleType.size()))
    {
        fIndex_ = index;
    }
    else
    {
        std::cout << "Indice non valido!" << std::endl;
    }
}
// Setter per il codice della particella (versione con nome)
void Particle::SetIndex(char *name)
{
    int index = FindParticle(name);
    if (index != -1)
    {
        fIndex_ = index;
    }
    else
    {
        std::cout << "Tipo di particella \"" << name << "\" non trovato!" << std::endl;
    }
}

// Getters per le componenti dell'impulso.
double Particle::GetPx() const { return fPx_; }
double Particle::GetPy() const { return fPy_; }
double Particle::GetPz() const { return fPz_; }

double Particle::GetCharge() const
{
    return fParticleType[fIndex_]->GetParticleCharge();
}

// Getter per la massa della particella
double Particle::GetMass() const
{
    return fParticleType[fIndex_]->GetParticleMass();
}

// Calcolo dell'energia totale della particella
double Particle::GetEnergy() const
{
    double mass = GetMass();                                    // massa
    double momentum2 = fPx_ * fPx_ + fPy_ * fPy_ + fPz_ * fPz_; // impulso al quadrato
    return std::sqrt(mass * mass + momentum2);                  // energia particella
}

// Calcolo della massa invariante
double Particle::GetInvMass(Particle &p) const
{
    double e12 = GetEnergy() + p.GetEnergy(); // somma delle energie di p1(particella corrente) e p2(p)
    double Px12 = GetPx() + p.GetPx();        // componente x dell'impulso P1+P2
    double Py12 = GetPy() + p.GetPy();        // componente y dell'impulso P1+P2
    double Pz12 = GetPz() + p.GetPz();        // componente z dell'impulso P1+P2
    double InvMass = std::sqrt((e12) * (e12) - (Px12) * (Px12) + (Py12) * (Py12) + (Pz12) * (Pz12));
    return InvMass; // massa invariante
};
void Particle::SetP(double fPx, double fPy, double fPz)
{
    fPx_ = fPx;
    fPy_ = fPy;
    fPz_ = fPz;
}

void Particle::PrintArray()
{
    for (int i = 0; i < static_cast<int>(fParticleType.size()); ++i)
    {
        fParticleType[i]->Print();
    }
}

void Particle::PrintParticle()
{
    std::cout << "Index: " << GetIndex() << ", Name: " << fParticleType[fIndex_]->GetParticleName() << ", Impulse: ("
              << GetPx() << ", " << GetPy() << ", " << GetPz() << ")\n";
}
// fin qui fatto da noi

int Particle::Decay2body(Particle &dau1, Particle &dau2) const // metodo che fa decadere una particella in due
{

    double mass = GetMass();
    if (mass == 0.0)
    {
        printf("Decayment cannot be preformed if mass is zero\n");
        return 1; // se la massa è nulla ritorna uno
    }

    double massMot = GetMass(); // massa della "madre"
    double massDau1 = dau1.GetMass();
    double massDau2 = dau2.GetMass();

    if (fIndex_ > -1)
    { // add width effect

        // gaussian random numbers

        float x1, x2, w, y1;

        double invnum = 1. / RAND_MAX;
        do
        {
            x1 = 2.0 * rand() * invnum - 1.0;
            x2 = 2.0 * rand() * invnum - 1.0;
            w = x1 * x1 + x2 * x2;
        } while (w >= 1.0);

        w = sqrt((-2.0 * log(w)) / w);
        y1 = x1 * w;

        massMot += fParticleType[fIndex_]->GetResonanceTypeWidth() * y1; // La massa della particella risonante (massMot) viene perturbata aggiungendo una quantità casuale proporzionale a Γ; imita il comportamento reale delle particelle risonanti
    }

    if (massMot < massDau1 + massDau2) // controlla che sia effettivamente conservata l'energia
    {
        printf("Decayment cannot be preformed because mass is too low in this channel\n");
        return 2;
    }
    // calcola l'impulso delle figlie "pout"
    double pout = sqrt((massMot * massMot - (massDau1 + massDau2) * (massDau1 + massDau2)) * (massMot * massMot - (massDau1 - massDau2) * (massDau1 - massDau2))) / massMot * 0.5;

    double norm = 2 * M_PI / RAND_MAX; // boh

    double phi = rand() * norm;
    double theta = rand() * norm * 0.5 - M_PI / 2.;
    dau1.SetP(pout * sin(theta) * cos(phi), pout * sin(theta) * sin(phi), pout * cos(theta));    // settato l'impulso di p1 con +pout
    dau2.SetP(-pout * sin(theta) * cos(phi), -pout * sin(theta) * sin(phi), -pout * cos(theta)); // settato l'impulso di p2 con -pout

    double energy = sqrt(fPx_ * fPx_ + fPy_ * fPy_ + fPz_ * fPz_ + massMot * massMot);

    double bx = fPx_ / energy;
    double by = fPy_ / energy;
    double bz = fPz_ / energy;

    dau1.Boost(bx, by, bz);
    dau2.Boost(bx, by, bz);

    return 0;
} // fine metodo Decay2Body

// trasformazioni di lorentz per cambiare SDR da quello della madre a quello del laboratorio
// è void quindi non restituisce nulla ma semplicemente modifica
void Particle::Boost(double bx, double by, double bz)
{

    double energy = GetEnergy();

    // Boost this Lorentz vector
    double b2 = bx * bx + by * by + bz * bz;           // modulo della velocità relativa (aggiunta)
    double gamma = 1.0 / sqrt(1.0 - b2);               // gamma relativistica
    double bp = bx * fPx_ + by * fPy_ + bz * fPz_;     // prdotto scalare velocità * impulso
    double gamma2 = b2 > 0 ? (gamma - 1.0) / b2 : 0.0; // altro gamma 2(?)
    // applica la trasformazione
    fPx_ += gamma2 * bp * bx + gamma * bx * energy;
    fPy_ += gamma2 * bp * by + gamma * by * energy;
    fPz_ += gamma2 * bp * bz + gamma * bz * energy;
}
