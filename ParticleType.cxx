#include <iostream>
#include "ParticleType.h"

ParticleType::ParticleType(char *const fname, double const fmass, int const fcharge) : fname_(fname), fmass_(fmass), fcharge_(fcharge) {};
char ParticleType::GetParticleName() const
{
    return *fname_;
}
int ParticleType::GetParticleCharge() const
{
    return fcharge_;
}
double ParticleType::GetParticleMass() const
{
    return fmass_;
}
void ParticleType::Print() const
{
    std::cout << "Particle: " << fname_ << "\nMass = " << fmass_ << "\nCharge = " << fcharge_ << '\n';
}

double ParticleType::GetResonanceTypeWidth() const { return 0.;}   //   quello richiesto alla fine del punto 7 che chiama "GetWidth"