#ifndef RESONANCETYPE_H
#define RESONANCETYPE_H

#include "ParticleType.h"


class ResonanceType : public ParticleType
{

private:
    double const fwidth_;

public:
    ResonanceType( const char *fname, double const fmass, int const fcharge, double const fwidth);
    double GetResonanceTypeWidth() const;
    void virtual Print() const;
};
#endif