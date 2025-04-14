#include <TH2.h>
#include <TH2F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include "TMultiGraph.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <stdio.h>
#include <TF1.h>
#include <TDirectoryFile.h>
#include <TRandom3.h>
#include "TLorentzVector.h"
#include "TString.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TKey.h"
#include "THashList.h"
#include "THStack.h"
#include "TPaveLabel.h"
#include "TFile.h"
#include "TTree.h"
#include "zmumu_Tree.h"
#include <TRandom3.h>

using namespace std;

int main(int argc, char** argv) {

    std::string input = *(argv + 1);
    std::string output = *(argv + 2);
    std::string name = *(argv + 3);
    std::string muobject = *(argv + 4);

    TFile *f_Double = new TFile(input.c_str());
    cout<<"XXXXXXXXXXXXX "<<input.c_str()<<" XXXXXXXXXXXX"<<endl;
    TTree *arbre1 = (TTree*) f_Double->Get("Events");
    TTree *arbre2 = (TTree*) f_Double->Get("Events");


    /*arbre1->SetBranchAddress("run", &run);
    arbre1->SetBranchAddress("luminosityBlock", &luminosityBlock);
    arbre1->SetBranchAddress("bunchCrossing", &bunchCrossing);
    arbre1->SetBranchAddress("orbitNumber", &orbitNumber);*/

    arbre1->SetBranchAddress("mmumu", &mmumu);
    arbre1->SetBranchAddress("DRmumu", &DRmumu);
    arbre1->SetBranchAddress("xsweight", &xsweight);
    arbre1->SetBranchAddress("met", &met);
    arbre1->SetBranchAddress("bxspread1", &bxspread1);
    arbre1->SetBranchAddress("bxspread2", &bxspread2);
    arbre1->SetBranchAddress("isL1MuMatched1", &isL1MuMatched1);
    arbre1->SetBranchAddress("isL1MuMatched2", &isL1MuMatched2);
    arbre1->SetBranchAddress("nstub1", &nstub1);
    arbre1->SetBranchAddress("nstub2", &nstub2);
    arbre1->SetBranchAddress("pt1", &pt1);
    arbre1->SetBranchAddress("eta1", &eta1);
    arbre1->SetBranchAddress("phi1", &phi1);
    arbre1->SetBranchAddress("charge1", &charge1_short);
    arbre1->SetBranchAddress("qual1", &qual1_short);
    arbre1->SetBranchAddress("dxy1", &dxy1_short);
    arbre1->SetBranchAddress("pt2", &pt2);
    arbre1->SetBranchAddress("eta2", &eta2);
    arbre1->SetBranchAddress("phi2", &phi2);
    arbre1->SetBranchAddress("charge2", &charge2_short);
    arbre1->SetBranchAddress("qual2", &qual2_short);
    arbre1->SetBranchAddress("dxy2", &dxy2_short);

    arbre2->SetBranchAddress("mmumu", &mmumu);
    arbre2->SetBranchAddress("DRmumu", &DRmumu);
    arbre2->SetBranchAddress("xsweight", &xsweight);
    arbre2->SetBranchAddress("met", &met);
    arbre2->SetBranchAddress("bxspread1", &bxspread1);
    arbre2->SetBranchAddress("bxspread2", &bxspread2);
    arbre2->SetBranchAddress("isL1MuMatched1", &isL1MuMatched1);
    arbre2->SetBranchAddress("isL1MuMatched2", &isL1MuMatched2);
    arbre2->SetBranchAddress("nstub1", &nstub1);
    arbre2->SetBranchAddress("nstub2", &nstub2);
    arbre2->SetBranchAddress("pt1", &pt1);
    arbre2->SetBranchAddress("eta1", &eta1);
    arbre2->SetBranchAddress("phi1", &phi1);
    arbre2->SetBranchAddress("charge1", &charge1);
    arbre2->SetBranchAddress("qual1", &qual1);
    arbre2->SetBranchAddress("dxy1", &dxy1);
    arbre2->SetBranchAddress("pt2", &pt2);
    arbre2->SetBranchAddress("eta2", &eta2);
    arbre2->SetBranchAddress("phi2", &phi2);
    arbre2->SetBranchAddress("charge2", &charge2);
    arbre2->SetBranchAddress("qual2", &qual2);
    arbre2->SetBranchAddress("dxy2", &dxy2);

    TH1F* h_mmumu_OS=new TH1F("h_mmumu_OS", "h_mmumu_OS", 50,50,150); h_mmumu_OS->Sumw2();
    TH1F* h_mmumu_SS=new TH1F("h_mmumu_SS", "h_mmumu_SS", 50,50,150); h_mmumu_SS->Sumw2();

    TH1F* h_nstub_OS=new TH1F("h_nstub_OS", "h_nstub_OS", 3,2,5); h_nstub_OS->Sumw2();
    TH1F* h_nstub_SS=new TH1F("h_nstub_SS", "h_nstub_SS", 3,2,5); h_nstub_SS->Sumw2();

    TH1F* h_met_OS=new TH1F("h_met_OS", "h_met_OS", 20,0,100); h_met_OS->Sumw2();
    TH1F* h_met_SS=new TH1F("h_met_SS", "h_met_SS", 20,0,100); h_met_SS->Sumw2();

    float lumiweight= (37770.0/15.046) + (5440.0/15.060) + (11470.0/15.048);

    static TRandom3 randGen(1234);

    Int_t nentries_wtn = (Int_t) arbre1->GetEntries();
    for (Int_t i = 0; i < nentries_wtn; i++) {
	if (name=="data_obs" and muobject!="KBMTF"){ 
	   arbre2->GetEntry(i);
	}
	else{
	   arbre1->GetEntry(i);
	   dxy1 = static_cast<int>(dxy1_short);
	   qual1 = static_cast<int>(qual1_short);
	   charge1 = static_cast<int>(charge1_short);
	   dxy2 = static_cast<int>(dxy2_short);
           qual2 = static_cast<int>(qual2_short);
           charge2 = static_cast<int>(charge2_short);
	}
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

	float aweight=xsweight*lumiweight;

	
	// Muon energy calibration
	if (name=="data_obs"){
	   pt1=0.84*pt1;
	   pt2=0.84*pt2;
	}
	else{
	   pt1=0.84*pt1;
           pt2=0.84*pt2;
        }

	// Muon energy resolution
        double smearFactor1 = randGen.Gaus(1.0, 0.11);
	double smearFactor2 = randGen.Gaus(1.0, 0.11);
	if (name!="data_obs"){
	   pt1 = pt1 * smearFactor1;
	   pt2 = pt2 * smearFactor2;
	}

	// Muon reconstruction efficiency
	float musf=0.98;
	aweight = aweight*musf*musf;
	
	

	TLorentzVector my_mu1; my_mu1.SetPtEtaPhiM(pt1,eta1,phi1,0.105);
        TLorentzVector my_mu2; my_mu2.SetPtEtaPhiM(pt2,eta2,phi2,0.105);

	if (dxy1>0 or dxy2>0) continue;
	if (pt1<15 or pt2<15) continue;
	if (qual1<12 or qual2<12) continue;

	if (name=="data_obs") aweight=1.0;

	float new_mmumu=(my_mu1+my_mu2).M();
	if (charge1*charge2<0){
	   h_mmumu_OS->Fill(new_mmumu, aweight);
	   //cout<<run<<" "<<luminosityBlock<<" "<<orbitNumber<<" "<<bunchCrossing<<endl;
	   if (new_mmumu>70){
	      h_nstub_OS->Fill(nstub1, aweight);
	      h_nstub_OS->Fill(nstub2, aweight);
	      h_met_OS->Fill(met, aweight);
	   }
	}
	else{
	   h_mmumu_SS->Fill(new_mmumu, aweight);
	   if (new_mmumu>70){
	      h_nstub_SS->Fill(nstub1, aweight);
	      h_nstub_SS->Fill(nstub2, aweight);
	      h_met_SS->Fill(met, aweight);
	   }
	}
    } // end of loop over events

    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();

    TDirectory* dir1=fout->mkdir("OS");
    dir1->cd();
    h_mmumu_OS->SetName(name.c_str());
    h_mmumu_OS->Write();

    TDirectory* dir2=fout->mkdir("SS");
    dir2->cd();
    h_mmumu_SS->SetName(name.c_str());
    h_mmumu_SS->Write();

    if (muobject=="KBMTF"){
       TDirectory* dir3=fout->mkdir("met_OS");
       dir3->cd();
       h_met_OS->SetName(name.c_str());
       h_met_OS->Write();

       TDirectory* dir4=fout->mkdir("met_SS");
       dir4->cd();
       h_met_SS->SetName(name.c_str());
       h_met_SS->Write();

       TDirectory* dir5=fout->mkdir("nstub_OS");
       dir5->cd();
       h_nstub_OS->SetName(name.c_str());
       h_nstub_OS->Write();

       TDirectory* dir6=fout->mkdir("nstub_SS");
       dir6->cd();
       h_nstub_SS->SetName(name.c_str());
       h_nstub_SS->Write();
    }

    cout<< h_mmumu_OS->Integral()<<endl;

    fout->Close();
}

