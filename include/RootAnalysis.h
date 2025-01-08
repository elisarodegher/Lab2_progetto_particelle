#ifndef ROOTANALYSIS_HPP
#define ROOTANALYSIS_HPP

#include "../include/Particle.h"
#include "../include/ParticleType.h"
#include "../include/ResonanceType.h"
#include <array>
#include <cmath>
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include "TMath.h"
#include "TRandom.h"
#include <TApplication.h>
#include <TFile.h>
#include <TH1.h>

void ReadMyRootData();
void AnalyseInvMass();
void ShowInvMassDiagrams();
#endif