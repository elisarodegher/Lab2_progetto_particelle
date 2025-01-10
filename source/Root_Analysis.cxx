#include "../include/RootAnalysis.h"


void ReadMyRootData()
{
    gSystem->ChangeDirectory("macros/Lab2_progetto_particelle");
    // Controllo se le percentuali hanno senso
    TFile *FileData = new TFile("Histograms2.root", "READ");
    if (!FileData || FileData->IsZombie()) {
    std::cerr << "Errore: impossibile aprire il file ROOT!" << std::endl;
    return;
}
    TH1F *hparticletypes = (TH1F *)FileData->Get("Particle types");
    if (!hparticletypes) {
    std::cerr << "Errore: impossibile trovare l'istogramma hparticletypes!" << std::endl;
    return;
} 
    //(*)(*) Artan
    TCanvas *c0 = new TCanvas("c1","c1",900,600); // Qui ho inizializzato il primo canvas con i 4 istogrammi (numero di particelle, angolo theta, angolo phi, impulso), Artan
    c0->Divide(2,2);
    c0->cd(1);
    hparticletypes->Draw();

    
    int N_tot_conteggi = hparticletypes->GetEntries();

    if (N_tot_conteggi < 1E7 || N_tot_conteggi > 1.1E7)
    { // 100 particelle per 1E5 eventi -> ci aspettiamo 1E7 particelle in totale
        std::cout << "Non va per niente bene!!";
    }

    std::vector<double> aspettative = {0.4, 0.4, 0.05, 0.05, 0.045, 0.045, 0.01};
    for (int i{1}; hparticletypes->GetBinContent(i) != 0; ++i)
    {
        double mean = hparticletypes->GetBinContent(i) / N_tot_conteggi;
        double sigma = hparticletypes->GetBinError(i);
        if (aspettative[i] <= mean + sigma && mean - sigma <= aspettative[i])
        {
            std::cout << "Il programma genera le particelle secondo le proporzioni richieste " << std::endl;
        }
        else
        {
            std::cout << "Il programma e` no bueno :(" << std::endl;
            std::cout << "aspettative: " << aspettative[i] << " e media effettiva: " << mean << "ed errore" << sigma << std::endl;
        }
        
    }

    // Fit degli angoli
    TH1F *htheta = (TH1F *)FileData->Get("Theta angle");
    TH1F *hphi = (TH1F *)FileData->Get("Phi angle");

    double pi = TMath::Pi();
    TF1 *FitTheta = new TF1("FitTheta", "[0]", 0., pi);
    TF1 *FitPhi = new TF1("FitPhi", "[0]", 0., 2 * pi);

    htheta->Fit("FitTheta");
    hphi->Fit("FitPhi");
    //(*)(*) Artan
    c0->cd(2);
    htheta->GetXaxis()->SetTitle("Angolo theta");
    htheta->GetYaxis()->SetTitle("Occorrenze");
    htheta->Draw();
    htheta->Draw("SAME");
    //(*)(*) Artan
    c0->cd(3);
    hphi->GetXaxis()->SetTitle("Angolo phi");
    hphi->GetYaxis()->SetTitle("Occorrenze");
    hphi->Draw();
    hphi->Draw("SAME");

    
    // Le altre funzioni (*) le lasciate nel caso le funzioni Divide() e cd() non funzionino

   //(*) TCanvas *htheta_Canvas = new TCanvas("htheta_Canvas","Distribuzione degli angoli Theta",900,600);
   // htheta->Draw();

   //(*) TCanvas *hphi_Canvas = new TCanvas("hphi_Canvas","Distribuzione degli angoli Phi",900,600);
   // hphi->Draw();
    // Artan

    

    // a GetParameter() penso vada messo per forza un argomento in input, forse è il parametro 0 ma non sono sicura (da eli)

    std::cout << "Parametri di Theta: " << FitTheta->GetParameter(0) << " +/- " << FitTheta->GetParError(0) << std::endl
              << "Chi quadro ridotto: " << (FitTheta->GetChisquare()/FitTheta->GetNDF()) << std::endl
              << "Probabilita`: " << FitTheta->GetProb() << std::endl;

    std::cout << "Parametri di Phi: " << FitPhi->GetParameter(0) << " +/- " << FitPhi->GetParError(0) << std::endl
              << "Chi quadro ridotto: " << (FitPhi->GetChisquare() / FitPhi->GetNDF()) << std::endl
              << "Probabilita`: " << FitPhi->GetProb() << std::endl;

    // Fit dell'impulso
    TH1F *himpulse = (TH1F *)FileData->Get("Impulse");

    TF1 *FitImpulse = new TF1("FitImpulse", "expo(0)", 0., 6.);

    himpulse->Fit("FitImpulse");
    //(*)(*) Artan
    c0->cd(4);
    himpulse->GetXaxis()->SetTitle("Impulso");
    himpulse->GetYaxis()->SetTitle("Occorrenze");
    himpulse->Draw();
    himpulse->Draw("SAME");

    // (*)TCanvas *himpulse_Canvas = new TCanvas("himpulse_Canvas","Distribuzione degli impulsi",900,600);
    // himpulse->Draw();
    //Artan

    std::cout << "Parametri dell'impulso: " << FitImpulse->GetParameter(0) << " +/- " << FitImpulse->GetParError(0) << std::endl
              << "Chi quadro ridotto: " << (FitImpulse->GetChisquare()/FitImpulse->GetNDF()) << std::endl
              << "Probabilita`: " << FitImpulse->GetProb() << std::endl;

    FileData -> Close();
}

void AnalyseInvMass()
{
    TFile *FileData = new TFile("Histograms.root");
    //(*)(*) Artan
    TCanvas *c1 = new TCanvas("c1","c1" ,900,600);
    c1->Divide(2,1);

    TH1F *h_samecharge_invmass = (TH1F *)FileData->Get("Invariant Mass of particles with concordant charge sign");
    TH1F *h_diffcharge_invmass = (TH1F *)FileData->Get("Invariant Mass of particles with discordant charge sign");
    TH1F *h_pk_samesign_invmass = (TH1F *)FileData->Get("InvMass, pk particles, same sign");
    TH1F *h_pk_diffsign_invmass = (TH1F *)FileData->Get("InvMass, pk particles, different sign");
    TH1F *h_decayed_invmass = (TH1F *)FileData->Get("Invariant Mass of decayed particles");

    TH1F *h_invmass_difference = new TH1F(*h_diffcharge_invmass);
    h_invmass_difference->Add(h_diffcharge_invmass, h_samecharge_invmass, 1, -1);
    TH1F *h_pk_difference = new TH1F(*h_pk_diffsign_invmass);
    h_pk_difference->Add(h_pk_diffsign_invmass, h_pk_samesign_invmass, 1, -1);

    TF1 *FitInvMass = new TF1("FitInvMass", "gaus", 0.6, 1.6);
    TF1 *FitPkInvMass = new TF1("FitPkInvMass", "gaus", 0.6, 1.6);
    TF1 *FitDecayedInvMass = new TF1("FitDecayedInvMass", "gaus", 0.6, 1.6);

    h_invmass_difference->Fit("FitInvMass");
    h_pk_difference->Fit("FitPkInvMass");
    h_decayed_invmass->Fit("FitDecayedInvMass");
    //(*)(*) Artan
    c1->cd(1);
    h_invmass_difference->GetXaxis()->SetTitle("Differenza di massa invariante tra particelle di stesso segno e particelle di segno discorde");
    h_invmass_difference->GetYaxis()->SetTitle("Occorrenze");
    h_invmass_difference->Draw();
    h_invmass_difference->Draw("SAME");
    //(*)(*) Artan
    c1->cd(2);
    h_pk_difference->GetXaxis()->SetTitle("Differenza di massa invariante tra pioni e kaoni di stesso segno e pioni e kaoni di segno discorde");
    h_pk_difference->GetYaxis()->SetTitle("Occorrenze");
    h_pk_difference->Draw();
    h_pk_difference->Draw("SAME");
    //(*)(*) Artan
    c1->cd(3);
    h_decayed_invmass->GetXaxis()->SetTitle("Massa invariante delle K* decadute");
    h_decayed_invmass->GetYaxis()->SetTitle("Occorrenze");
    h_decayed_invmass->Draw();
    h_decayed_invmass->Draw("SAME");

    std::cout << "Invariant mass difference data: " << std::endl;
    std::cout << "K* mass(mean) = " << FitInvMass->GetParameter(1) << " +/- " << FitInvMass->GetParError(1) << std::endl;
    std::cout << "K* lenght(sigma) = " << FitInvMass->GetParameter(2) << " +/- " << FitInvMass->GetParError(2) << std::endl;
    std::cout << "Chisquare = " << (FitInvMass->GetChisquare() / FitInvMass->GetNDF()) << std::endl;
    std::cout << "Probability of chisquare = " << FitInvMass->GetProb() << std::endl;

    std::cout << "Invariant mass pion/kaon difference data: " << std::endl;
    std::cout << "K* mass(mean) = " << FitPkInvMass->GetParameter(1) << " +/- " << FitPkInvMass->GetParError(1) << std::endl;
    std::cout << "K* lenght(sigma) = " << FitPkInvMass->GetParameter(2) << " +/- " << FitPkInvMass->GetParError(2) << std::endl;
    std::cout << "Chisquare = " << (FitPkInvMass->GetChisquare() / FitPkInvMass->GetNDF()) << std::endl;
    std::cout << "Probability of chisquare = " << FitPkInvMass->GetProb() << std::endl;

    std::cout << "Invariant mass decayed particles data: " << std::endl;
    std::cout << "K* mass(mean) = " << FitDecayedInvMass->GetParameter(1) << " +/- " << FitDecayedInvMass->GetParError(1) << std::endl;
    std::cout << "K* lenght(sigma) = " << FitDecayedInvMass->GetParameter(2) << " +/- " << FitDecayedInvMass->GetParError(2) << std::endl;
    std::cout << "Chisquare = " << (FitDecayedInvMass->GetChisquare() / FitDecayedInvMass->GetNDF())<< std::endl;
    std::cout << "Probability of chisquare = " << FitDecayedInvMass->GetProb() << std::endl;
    //(*)(*) Artan
    InvMassCanvas->SaveAs("InvMassCanvas.pdf");
    PkInvMassCanvas->SaveAs("PkInvMassCanvas.pdf");
    DecInvMassCanvas->SaveAs("DecInvMassCanvas.pdf");

    InvMassCanvas->SaveAs("InvMassCanvas.root");
    PkInvMassCanvas->SaveAs("PkInvMassCanvas.root");
    DecInvMassCanvas->SaveAs("DecInvMassCanvas.root");

    InvMassCanvas->SaveAs("InvMassCanvas.C");
    PkInvMassCanvas->SaveAs("PkInvMassCanvas.C");
    DecInvMassCanvas->SaveAs("DecInvMassCanvas.C");

    FileData -> Close();
}

void ShowInvMassDiagrams()
{
    TFile *FileData = new TFile("Histograms2.root");

    TH1F *h_samecharge_invmass = (TH1F *)FileData->Get("Invariant Mass of particles with concordant charge sign");
    TH1F *h_diffcharge_invmass = (TH1F *)FileData->Get("Invariant Mass of particles with discordant charge sign");
    TH1F *h_pk_samesign_invmass = (TH1F *)FileData->Get("InvMass, pk particles, same sign");
    TH1F *h_pk_diffsign_invmass = (TH1F *)FileData->Get("InvMass, pk particles, different sign");
    TH1F *h_decayed_invmass = (TH1F *)FileData->Get("Invariant Mass of decayed particles");

    TH1F *h_invmass_difference = new TH1F(*h_samecharge_invmass);
    h_invmass_difference->Add(h_diffcharge_invmass, -1);
     
    
    TH1F *h_pk_difference = new TH1F(*h_pk_samesign_invmass);
    h_pk_difference->Add(h_pk_diffsign_invmass, -1);

    // modifiche alla cosmetica da fare vedendo il programma eseguito

    TCanvas *InvMassCanvas = new TCanvas("InvMassCanvas", "General invariant mass histogram", 900, 600);
    TCanvas *PkInvMassCanvas = new TCanvas("PkInvMassCanvas", "Pion/kaon invariant mass histogram", 900, 600);
    TCanvas *DecInvMassCanvas = new TCanvas("DecInvMassCanvas", "Decayed particles invariant mass histogram", 900, 600);

    InvMassCanvas->cd();
    h_invmass_difference->Draw();

    PkInvMassCanvas->cd();
    h_pk_difference->Draw();

    DecInvMassCanvas->cd();
    h_decayed_invmass->Draw();

    InvMassCanvas->SaveAs("InvMassCanvas.pdf");
    PkInvMassCanvas->SaveAs("PkInvMassCanvas.pdf");
    DecInvMassCanvas->SaveAs("DecInvMassCanvas.pdf");

    InvMassCanvas->SaveAs("InvMassCanvas.root");
    PkInvMassCanvas->SaveAs("PkInvMassCanvas.root");
    DecInvMassCanvas->SaveAs("DecInvMassCanvas.root");

    InvMassCanvas->SaveAs("InvMassCanvas.C");
    PkInvMassCanvas->SaveAs("PkInvMassCanvas.C");
    DecInvMassCanvas->SaveAs("DecInvMassCanvas.C");

    FileData -> Close();
}

void LemmeseeTheGraphs() {
    TFile *FileData = new TFile("Histograms2.root");

    TH1F *h_samecharge_invmass = (TH1F *)FileData->Get("Invariant Mass of particles with concordant charge sign");
    TH1F *h_diffcharge_invmass = (TH1F *)FileData->Get("Invariant Mass of particles with discordant charge sign");
    TH1F *h_pk_samesign_invmass = (TH1F *)FileData->Get("InvMass, pk particles, same sign");
    TH1F *h_pk_diffsign_invmass = (TH1F *)FileData->Get("InvMass, pk particles, different sign");
    TH1F *h_decayed_invmass = (TH1F *)FileData->Get("Invariant Mass of decayed particles");

    TH1F *h_invmass_difference = new TH1F(*h_samecharge_invmass);
    h_invmass_difference->Add(h_samecharge_invmass, h_diffcharge_invmass, 1, -1);
    TH1F *h_pk_difference = new TH1F(*h_pk_samesign_invmass);
    h_pk_difference->Add(h_pk_samesign_invmass, h_pk_diffsign_invmass, 1, -1);

    // modifiche alla cosmetica da fare vedendo il programma eseguito

    TCanvas *InvMassCanvas = new TCanvas("InvMassCanvas", "General invariant mass histogram", 900, 600);
    TCanvas *PkInvMassCanvas = new TCanvas("PkInvMassCanvas", "Pion/kaon invariant mass histogram", 900, 600);
    TCanvas *DecInvMassCanvas = new TCanvas("DecInvMassCanvas", "Decayed particles invariant mass histogram", 900, 600);

    InvMassCanvas->cd();
    h_invmass_difference->Draw();

    PkInvMassCanvas->cd();
    h_pk_difference->Draw();

    DecInvMassCanvas->cd();
    h_decayed_invmass->Draw();

    

}
