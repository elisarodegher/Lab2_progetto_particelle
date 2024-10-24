#ifndef PARTICLETYPE_H
#define PARTICLETYPE_H
#include <iostream>
class ParticleType
{

private:
    char* const fname_;
    double const fmass_;
    int const fcharge_;

public:
    ParticleType(char *fname, double fmass, int fcharge);
    char GetParticleName() const;
    double GetParticleMass() const;
    int GetParticleCharge() const;

    void Print() const;
};

#endif