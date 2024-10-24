#include "ParticleType.h"
#ifndef RESONANCETYPE_H
#define RESONANCETYPE_H

class ResonanceType : public ParticleType
{

private:
    double const fwidth_;

public:
    ResonanceType(char *const fname, double const fmass, int const fcharge, double const fwidth) : ParticleType(fname, fmass, fcharge), fwidth_(fwidth) {};
    double GetResonanceTypeWidth() const {};
    void Print() const;
};
#endif