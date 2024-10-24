#include <vector>
#include "ParticleType.h"

#include "ResonanceType.h"

class Particle
{
private:
    static int const fMaxNumParticleType_ = 10;
    static std::vector<ParticleType*> fParticleType;
    static int fNParticleType_;
    int fIndex_;
    double fPx_{0};
    double fPy_{0};
    double fPz_{0};

    static int FindParticle(char *fname);

public:
    Particle(char *fname, double fPx, double fPy, double fPz);
    int GetIndex();
    static void AddParticleType(char *fname_, double fmass_, int fcharge_, double const fwidth_);
    void SetIndex(int fIndex);
    void Setindex(const char* fname);
    double const GetPx();
    double const GetPy();
    double const GetPz();
    double const GetMass();
    double const GetEnergy();
 double const GetInvMass(Particle);


};