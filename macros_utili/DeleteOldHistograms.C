#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TGraph.h>



void DeleteOldHistograms() {
    // Apri il file ROOT in modalità UPDATE
    TFile *FileData = TFile::Open("Histograms.root", "UPDATE");
    if (!FileData || FileData->IsZombie()) {
        std::cerr << "Errore: impossibile aprire il file ROOT!" << std::endl;
        return;
    }

    // Elimina i vecchi istogrammi
    FileData->Delete("Invariant Mass of .... particles with concordant charge sign;*");
    FileData->Delete("Invariant Mass of ... different charge sign;*");

    // Chiudi il file ROOT
    FileData->Close();
}


/*root [0]
Attaching file Histograms.root as _file0...
(TFile *) 0x56184cada910
root [1] .ls
TFile**         Histograms.root
 TFile*         Histograms.root
  KEY: TH1F     Particle types;1        Particle type distribution
  KEY: TH1F     Phi angle;1     Phi angle distribution
  KEY: TH1F     Theta angle;1   Theta angle distribution
  KEY: TH1F     Impulse;1       Impulse distribution
  KEY: TH1F     Trasverse Impulse;1     Trasverse impulse distribution
  KEY: TH1F     Energy;1        Energy distrbution
  KEY: TH1F     Invariant Mass of all particles;1       Invariant Mass distribution
  KEY: TH1F     Invariant Mass of particles with concordant charge sign;1       Invariant Mass of particles with concordant charge sign distribution
  KEY: TH1F     Invariant Mass of particles with discordant charge sign;1       Invariant Mass of particles with discordant charge sign distribution
  KEY: TH1F     Invariant Mass of decayed particles;1   Invariant Mass of decayed particles distribution
  KEY: TH1F     InvMass, pk particles, same sign;1      Invariant Mass of pk particles with same sign distribution
  KEY: TH1F     InvMass, pk particles, different sign;1 Invariant Mass of pk particles with different sign distribution*/