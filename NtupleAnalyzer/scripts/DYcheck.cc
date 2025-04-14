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
#include "dy_Tree.h"

using namespace std;

int main(int argc, char** argv) {

    std::string input = *(argv + 1);
    std::string output = *(argv + 2);

    TFile *f_Double = new TFile(input.c_str());
    cout<<"XXXXXXXXXXXXX "<<input.c_str()<<" XXXXXXXXXXXX"<<endl;
    TTree *arbre = (TTree*) f_Double->Get("Events");

    arbre->SetBranchAddress("nL1KBMTFSkimmed", &nL1KBMTFSkimmed);
    arbre->SetBranchAddress("L1KBMTFSkimmed_hwCharge", &L1KBMTFSkimmed_hwCharge);
    arbre->SetBranchAddress("L1KBMTFSkimmed_hwQual", &L1KBMTFSkimmed_hwQual);
    arbre->SetBranchAddress("L1KBMTFSkimmed_hwDXY", &L1KBMTFSkimmed_hwDXY);
    arbre->SetBranchAddress("L1KBMTFSkimmed_processor", &L1KBMTFSkimmed_processor);
    arbre->SetBranchAddress("L1KBMTFSkimmed_nStub", &L1KBMTFSkimmed_nStub);
    arbre->SetBranchAddress("L1KBMTFSkimmed_s1Station", &L1KBMTFSkimmed_s1Station);
    arbre->SetBranchAddress("L1KBMTFSkimmed_s1Sector", &L1KBMTFSkimmed_s1Sector);
    arbre->SetBranchAddress("L1KBMTFSkimmed_s1Wheel", &L1KBMTFSkimmed_s1Wheel);
    arbre->SetBranchAddress("L1KBMTFSkimmed_s1Bx", &L1KBMTFSkimmed_s1Bx);
    arbre->SetBranchAddress("L1KBMTFSkimmed_s2Station", &L1KBMTFSkimmed_s2Station);
    arbre->SetBranchAddress("L1KBMTFSkimmed_s2Sector", &L1KBMTFSkimmed_s2Sector);
    arbre->SetBranchAddress("L1KBMTFSkimmed_s2Wheel", &L1KBMTFSkimmed_s2Wheel);
    arbre->SetBranchAddress("L1KBMTFSkimmed_s2Bx", &L1KBMTFSkimmed_s2Bx);
    arbre->SetBranchAddress("L1KBMTFSkimmed_s3Station", &L1KBMTFSkimmed_s3Station);
    arbre->SetBranchAddress("L1KBMTFSkimmed_s3Sector", &L1KBMTFSkimmed_s3Sector);
    arbre->SetBranchAddress("L1KBMTFSkimmed_s3Wheel", &L1KBMTFSkimmed_s3Wheel);
    arbre->SetBranchAddress("L1KBMTFSkimmed_s3Bx", &L1KBMTFSkimmed_s3Bx);
    arbre->SetBranchAddress("L1KBMTFSkimmed_s4Station", &L1KBMTFSkimmed_s4Station);
    arbre->SetBranchAddress("L1KBMTFSkimmed_s4Sector", &L1KBMTFSkimmed_s4Sector);
    arbre->SetBranchAddress("L1KBMTFSkimmed_s4Wheel", &L1KBMTFSkimmed_s4Wheel);
    arbre->SetBranchAddress("L1KBMTFSkimmed_s4Bx", &L1KBMTFSkimmed_s4Bx);
    arbre->SetBranchAddress("L1KBMTFSkimmed_pt", &L1KBMTFSkimmed_pt);
    arbre->SetBranchAddress("L1KBMTFSkimmed_eta", &L1KBMTFSkimmed_eta);
    arbre->SetBranchAddress("L1KBMTFSkimmed_phi", &L1KBMTFSkimmed_phi);
    arbre->SetBranchAddress("L1KBMTFSkimmed_ptUnconstrained", &L1KBMTFSkimmed_ptUnconstrained);
    arbre->SetBranchAddress("L1KBMTFSkimmed_etaAtVtx", &L1KBMTFSkimmed_etaAtVtx);
    arbre->SetBranchAddress("L1KBMTFSkimmed_phiAtVtx", &L1KBMTFSkimmed_phiAtVtx);
    arbre->SetBranchAddress("nSkimmedL1Mu", &nSkimmedL1Mu);
    arbre->SetBranchAddress("SkimmedL1Mu_hwCharge", &SkimmedL1Mu_hwCharge);
    arbre->SetBranchAddress("SkimmedL1Mu_hwQual", &SkimmedL1Mu_hwQual);
    arbre->SetBranchAddress("SkimmedL1Mu_hwDXY", &SkimmedL1Mu_hwDXY);
    arbre->SetBranchAddress("SkimmedL1Mu_processor", &SkimmedL1Mu_processor);
    arbre->SetBranchAddress("SkimmedL1Mu_pt", &SkimmedL1Mu_pt);
    arbre->SetBranchAddress("SkimmedL1Mu_eta", &SkimmedL1Mu_eta);
    arbre->SetBranchAddress("SkimmedL1Mu_phi", &SkimmedL1Mu_phi);
    arbre->SetBranchAddress("SkimmedL1Mu_ptUnconstrained", &SkimmedL1Mu_ptUnconstrained);
    arbre->SetBranchAddress("SkimmedL1Mu_etaAtVtx", &SkimmedL1Mu_etaAtVtx);
    arbre->SetBranchAddress("SkimmedL1Mu_phiAtVtx", &SkimmedL1Mu_phiAtVtx);


   TH1F* h_ZL1mu = new TH1F("h_ZL1mu","h_ZL1mu",20,0,200); h_ZL1mu->Sumw2();
   TH1F* h_ZKBMTF = new TH1F("h_ZKBMTF","h_ZKBMTF",20,0,200); h_ZKBMTF->Sumw2();

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();
   for (Int_t i = 0; i < nentries_wtn; i++) {
        arbre->LoadTree(i);
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

	int idx1=0; int idx2=0;
	bool foundL1Mu=false;
	if (nSkimmedL1Mu>1){
	   TLorentzVector my_mu1; my_mu1.SetPtEtaPhiM(0.,0.,0.,0.);
	   TLorentzVector my_mu2; my_mu2.SetPtEtaPhiM(0.,0.,0.,0.);
	   float mu1pt=0.; float mu2pt=0.;
	   for (int k=0; k<nSkimmedL1Mu; ++k){
	      if (SkimmedL1Mu_pt[k]>mu1pt){ idx1=k; mu2pt=mu1pt; mu1pt=SkimmedL1Mu_pt[k];}  
	      else if (SkimmedL1Mu_pt[k]>mu2pt) {idx2=k; mu2pt=SkimmedL1Mu_pt[k];}
	   }
	   my_mu1.SetPtEtaPhiM(SkimmedL1Mu_pt[idx1], SkimmedL1Mu_eta[idx1], SkimmedL1Mu_phi[idx1],0.105);
	   my_mu2.SetPtEtaPhiM(SkimmedL1Mu_pt[idx2], SkimmedL1Mu_eta[idx2], SkimmedL1Mu_phi[idx2],0.105);
	   if (my_mu1.Pt()>8 and my_mu2.Pt()>8 and fabs(my_mu1.Eta())<0.83 and fabs(my_mu2.Eta())<0.83 and (my_mu1+my_mu2).M()>50 and my_mu1.DeltaR(my_mu2)>0.3 and SkimmedL1Mu_hwCharge[idx1]*SkimmedL1Mu_hwCharge[idx2]<0) {h_ZL1mu->Fill((my_mu1+my_mu2).M()); foundL1Mu=true;}
	}

	bool foundKBMTF=false;
	int idxK1=0; int idxK2=0;
	if (nL1KBMTFSkimmed>1){
           TLorentzVector my_mu1; my_mu1.SetPtEtaPhiM(0.,0.,0.,0.);
           TLorentzVector my_mu2; my_mu2.SetPtEtaPhiM(0.,0.,0.,0.);
	   TLorentzVector tmp_mu;
	   float mu1pt=0.; float mu2pt=0.;
           for (int k=0; k<nL1KBMTFSkimmed; ++k){
	      tmp_mu.SetPtEtaPhiM(L1KBMTFSkimmed_pt[k], L1KBMTFSkimmed_eta[k], L1KBMTFSkimmed_phi[k],0.105);
              if (L1KBMTFSkimmed_pt[k]>mu1pt) {
	         if (mu1pt>0 and my_mu1.DeltaR(tmp_mu)>0.30){ 
	            my_mu2=my_mu1; mu2pt=mu1pt; idxK2 = idxK1; 
		 }
		 my_mu1=tmp_mu; 
		 idxK1=k;
		 mu1pt=L1KBMTFSkimmed_pt[k];
	      }
              else if (my_mu1.DeltaR(tmp_mu)>0.30 and L1KBMTFSkimmed_pt[k]>mu2pt) { 
	         my_mu2=tmp_mu; 
		 idxK2=k; 
		 mu2pt=L1KBMTFSkimmed_pt[k];
	      }
           }
	   cout<<"selected KBMTF: "<<L1KBMTFSkimmed_pt[idxK1]<<" "<<L1KBMTFSkimmed_eta[idxK1]<<" "<<L1KBMTFSkimmed_phi[idxK1]<<"), ("<<L1KBMTFSkimmed_pt[idxK2]<<" "<<L1KBMTFSkimmed_eta[idxK2]<<" "<<L1KBMTFSkimmed_phi[idxK2]<<endl;
           if (my_mu1.Pt()>8 and my_mu2.Pt()>8 and fabs(my_mu1.Eta())<0.83 and fabs(my_mu2.Eta())<0.83 and (my_mu1+my_mu2).M()>50 and my_mu1.DeltaR(my_mu2)>0.3 and L1KBMTFSkimmed_hwCharge[idxK1]*L1KBMTFSkimmed_hwCharge[idxK2]<0) {h_ZKBMTF->Fill((my_mu1+my_mu2).M()); foundKBMTF=true;}
        }

	if (foundL1Mu && !foundKBMTF){
	   cout<<"KBMTF not found"<<endl;
	   cout<<"L1Mu: ("<<SkimmedL1Mu_pt[idx1]<<" "<<SkimmedL1Mu_eta[idx1]<<" "<<SkimmedL1Mu_phi[idx1]<<"), ("<<SkimmedL1Mu_pt[idx2]<<" "<<SkimmedL1Mu_eta[idx2]<<" "<<SkimmedL1Mu_phi[idx2]<<endl;
	   cout<<"KBMTF: "<<endl;
	   for (int k=0; k<nL1KBMTFSkimmed; ++k) cout<<L1KBMTFSkimmed_pt[k]<<" "<<L1KBMTFSkimmed_eta[k]<<" "<<L1KBMTFSkimmed_phi[k]<<endl;
	}

	if (!foundL1Mu && foundKBMTF) cout<<"L1Mu not found"<<endl;

    } // end of loop over events

    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();
    h_ZL1mu->Write();
    h_ZKBMTF->Write();

    fout->Close();
}

