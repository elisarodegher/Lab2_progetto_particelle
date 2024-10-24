#include <iostream>
#include "ResonanceType.h"


ResonanceType::ResonanceType(char* const fname, double const fmass, int const fcharge, double const fwidth) :
               ParticleType(fname, fmass, fcharge), fwidth_(fwidth) {};


double ResonanceType::GetResonanceTypeWidth() const {
    return fwidth_;
}


void ResonanceType::Print() const override {
    ParticleType::Print();
    std::cout << fwidth_ << '\n';
}