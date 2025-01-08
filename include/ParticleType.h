#ifndef PARTICLETYPE_H
#define PARTICLETYPE_H
#include <iostream>
class ParticleType
{

private:
    const char* fname_;
    double const fmass_;
    int const fcharge_;

public:
    ParticleType(const char *fname, double fmass, int fcharge);
    char GetParticleName() const;
    double GetParticleMass() const;
    int GetParticleCharge() const;

    void virtual Print() const;
    double virtual GetResonanceTypeWidth() const;
};

#endif