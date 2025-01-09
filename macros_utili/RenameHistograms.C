#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TGraph.h>



void RenameHistograms() {
    TFile *FileData = TFile::Open("Histograms.root", "UPDATE");

     if (!FileData || FileData->IsZombie()) {
        std::cerr << "Errore: impossibile aprire il file ROOT!" << std::endl;
        return;
    }
    
    TH1F *h_old = (TH1F *)FileData->Get("Invariant Mass of .... particles with concordant charge sign");
if (h_old) {
    h_old->SetName("InvMass, pk particles, same sign");
     h_old->SetTitle("Invariant Mass of pk particles with same sign distribution"); // Nuovo titolo
    h_old->Write("", TObject::kOverwrite); // Salva e sovrascrivi
} else {
    std::cerr << "Errore: Istogramma 'NomeVecchio' non trovato!" << std::endl;
}

    TH1F *h2_old = (TH1F *)FileData->Get("Invariant Mass of ... different charge sign");
if (h2_old) {
    h2_old->SetName("InvMass, pk particles, different sign");
     h2_old->SetTitle("Invariant Mass of pk particles with different sign distribution"); // Nuovo titolo
    h2_old->Write("", TObject::kOverwrite); // Salva e sovrascrivi
} else {
    std::cerr << "Errore: Istogramma 'NomeVecchio2' non trovato!" << std::endl;
}
    FileData->Close();
}
