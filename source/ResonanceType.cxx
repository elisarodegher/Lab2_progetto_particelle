#include <iostream>
#include "../include/ResonanceType.h"


ResonanceType::ResonanceType(const char *fname, double const fmass, int const fcharge, double const fwidth) :
               ParticleType(fname, fmass, fcharge), fwidth_(fwidth) {};


double ResonanceType::GetResonanceTypeWidth() const {
    return fwidth_;
}


void ResonanceType::Print() const {
    ParticleType::Print();
    std::cout << "Resonance: " << fwidth_ << '\n';
}
