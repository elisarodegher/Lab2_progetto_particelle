#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <vector>
#include <array>

#include <cassert>
#include <cmath>
#include "ResonanceType.h"

class Particle
{
private:
  static int const fMaxNumParticleType_;
  static std::vector<ParticleType *> fParticleType;
  static int fNParticleType_;
  int fIndex_;
  double fPx_{0};
  double fPy_{0};
  double fPz_{0};
  static int FindParticle(const char *fName);

public:
  Particle();
  Particle(const char *fName, double fPx, double fPy, double fPz);
  int GetIndex() const;

  static void AddParticleType(const char *fName, double fMass, int fCharge, double fWidth);
  void SetIndex(int index);
  void SetIndex(char *name);

  double GetPx() const;
  double GetPy() const;
  double GetPz() const;

  static void PrintArray();
  void PrintParticle();

  double GetCharge() const;
  double GetMass() const;
  double GetEnergy() const;
  double GetInvMass(Particle &p) const;
  void SetP(double fPx, double fPy, double fPz);

  int Decay2body(Particle &dau1, Particle &dau2) const;

private:
  void Boost(double bx, double by, double bz);
};
#endif
