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
#include "tr_Tree.h"

using namespace std;

int main(int argc, char** argv) {

    std::string input = *(argv + 1);
    std::string output = *(argv + 2);

    TFile *f_Double = new TFile(input.c_str());
    cout<<"XXXXXXXXXXXXX "<<input.c_str()<<" XXXXXXXXXXXX"<<endl;
    TTree *arbre = (TTree*) f_Double->Get("Events");

    arbre->SetBranchAddress("nL1KBMTFSkimmed", &nL1KBMTFSkimmed);
    arbre->SetBranchAddress("nstub1", &nstub1);
    arbre->SetBranchAddress("nstub2", &nstub2);
    arbre->SetBranchAddress("bxspread1", &bxspread1);
    arbre->SetBranchAddress("bxspread2", &bxspread2);
    arbre->SetBranchAddress("L1KBMTFSkimmed_pt",L1KBMTFSkimmed_pt);
    arbre->SetBranchAddress("L1KBMTFSkimmed_hwQual",L1KBMTFSkimmed_hwQual);

    TH1F* h_permutation0123 = new TH1F("h_permutation0123","h_permutation0123",24,1,25); h_permutation0123->Sumw2();
    TH1F* h_permutation0124 = new TH1F("h_permutation0124","h_permutation0124",24,1,25); h_permutation0124->Sumw2();
    TH1F* h_permutation012 = new TH1F("h_permutation012","h_permutation012",6,1,7); h_permutation012->Sumw2();
    TH1F* h_permutation013 = new TH1F("h_permutation013","h_permutation013",6,1,7); h_permutation013->Sumw2();
    TH1F* h_permutation024 = new TH1F("h_permutation024","h_permutation024",6,1,7); h_permutation013->Sumw2();

    TH1F* h_pt_0123 = new TH1F("h_pt_0123","h_pt_0123",54,0,540); h_pt_0123->Sumw2();
    TH1F* h_pt_0132 = new TH1F("h_pt_0132","h_pt_0132",54,0,540); h_pt_0132->Sumw2();
    TH1F* h_pt_0213 = new TH1F("h_pt_0213","h_pt_0213",54,0,540); h_pt_0213->Sumw2();
    TH1F* h_pt_0231 = new TH1F("h_pt_0231","h_pt_0231",54,0,540); h_pt_0231->Sumw2();
    TH1F* h_pt_0321 = new TH1F("h_pt_0321","h_pt_0321",54,0,540); h_pt_0321->Sumw2();
    TH1F* h_pt_0312 = new TH1F("h_pt_0312","h_pt_0312",54,0,540); h_pt_0312->Sumw2();

    TH1F* h_pt_120 = new TH1F("h_pt_120","h_pt_120",50,0,100); h_pt_120->Sumw2();
    TH1F* h_pt_210 = new TH1F("h_pt_210","h_pt_210",50,0,100); h_pt_210->Sumw2();
    TH1F* h_pt_1200 = new TH1F("h_pt_1200","h_pt_1200",50,0,100); h_pt_1200->Sumw2();
    TH1F* h_pt_1020 = new TH1F("h_pt_1020","h_pt_1020",50,0,100); h_pt_1020->Sumw2();
    TH1F* h_pt_2100 = new TH1F("h_pt_2100","h_pt_2100",50,0,100); h_pt_2100->Sumw2();
    TH1F* h_pt_2010 = new TH1F("h_pt_2010","h_pt_2010",50,0,100); h_pt_2010->Sumw2();

    TH1F* h_ratio = new TH1F("h_ratio", "h_ratio", 4,0,4); h_ratio->Sumw2();

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();
   for (Int_t i = 0; i < nentries_wtn; i++) {
        arbre->LoadTree(i);
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

	if (nstub1==4 and L1KBMTFSkimmed_pt[0]<20){
	   if (bxspread1==123) h_pt_0123->Fill(L1KBMTFSkimmed_pt[0]);
	   if (bxspread1==132) h_pt_0132->Fill(L1KBMTFSkimmed_pt[0]);
	   if (bxspread1==213) h_pt_0213->Fill(L1KBMTFSkimmed_pt[0]);
	   if (bxspread1==231) h_pt_0231->Fill(L1KBMTFSkimmed_pt[0]);
	   if (bxspread1==321) h_pt_0321->Fill(L1KBMTFSkimmed_pt[0]);
	   if (bxspread1==312) h_pt_0312->Fill(L1KBMTFSkimmed_pt[0]);
	   if (bxspread1==123 or bxspread1==132 or bxspread1==213 or bxspread1==231 or bxspread1==321 or bxspread1==312) h_ratio->Fill(0);

	   if (bxspread1==123) h_permutation0123->Fill(1);
	   if (bxspread1==132) h_permutation0123->Fill(2);
	   if (bxspread1==213) h_permutation0123->Fill(3);
	   if (bxspread1==231) h_permutation0123->Fill(4);
	   if (bxspread1==321) h_permutation0123->Fill(5);
	   if (bxspread1==312) h_permutation0123->Fill(6);

	   if (bxspread1==1023) h_permutation0123->Fill(7);
           if (bxspread1==1032) h_permutation0123->Fill(8);
           if (bxspread1==1230) h_permutation0123->Fill(9);
           if (bxspread1==1203) h_permutation0123->Fill(10);
           if (bxspread1==1302) h_permutation0123->Fill(11);
           if (bxspread1==1320) h_permutation0123->Fill(12);
	   if (bxspread1==1023 or bxspread1==1032 or bxspread1==1230 or bxspread1==1203 or bxspread1==1302 or bxspread1==1320) h_ratio->Fill(1);
	   if (bxspread1==2013) h_permutation0123->Fill(13);
           if (bxspread1==2031) h_permutation0123->Fill(14);
           if (bxspread1==2103) h_permutation0123->Fill(15);
           if (bxspread1==2130) h_permutation0123->Fill(16);
           if (bxspread1==2301) h_permutation0123->Fill(17);
           if (bxspread1==2310) h_permutation0123->Fill(18);
	   if (bxspread1==2013 or bxspread1==2031 or bxspread1==2103 or bxspread1==2130 or bxspread1==2301 or bxspread1==2310) h_ratio->Fill(2);
	   if (bxspread1==3012) h_permutation0123->Fill(19);
           if (bxspread1==3021) h_permutation0123->Fill(20);
           if (bxspread1==3102) h_permutation0123->Fill(21);
           if (bxspread1==3120) h_permutation0123->Fill(22);
           if (bxspread1==3201) h_permutation0123->Fill(23);
           if (bxspread1==3210) h_permutation0123->Fill(24);
	   if (bxspread1==3012 or bxspread1==3021 or bxspread1==3102 or bxspread1==3120 or bxspread1==3201 or bxspread1==3210) h_ratio->Fill(3);
	   /////////////////////////////////////////////////////////
	   if (bxspread1==124) h_permutation0124->Fill(1);
           if (bxspread1==142) h_permutation0124->Fill(2);
           if (bxspread1==214) h_permutation0124->Fill(3);
           if (bxspread1==241) h_permutation0124->Fill(4);
           if (bxspread1==421) h_permutation0124->Fill(5);
           if (bxspread1==412) h_permutation0124->Fill(6);

           if (bxspread1==1024) h_permutation0124->Fill(7);
           if (bxspread1==1042) h_permutation0124->Fill(8);
           if (bxspread1==1240) h_permutation0124->Fill(9);
           if (bxspread1==1204) h_permutation0124->Fill(10);
           if (bxspread1==1402) h_permutation0124->Fill(11);
           if (bxspread1==1420) h_permutation0124->Fill(12);

           if (bxspread1==2014) h_permutation0124->Fill(13);
           if (bxspread1==2041) h_permutation0124->Fill(14);
           if (bxspread1==2104) h_permutation0124->Fill(15);
           if (bxspread1==2140) h_permutation0124->Fill(16);
           if (bxspread1==2401) h_permutation0124->Fill(17);
           if (bxspread1==2410) h_permutation0124->Fill(18);

           if (bxspread1==4012) h_permutation0124->Fill(19);
           if (bxspread1==4021) h_permutation0124->Fill(20);
           if (bxspread1==4102) h_permutation0124->Fill(21);
           if (bxspread1==4120) h_permutation0124->Fill(22);
           if (bxspread1==4201) h_permutation0124->Fill(23);
           if (bxspread1==4210) h_permutation0124->Fill(24);
	}
	if (nstub1==3  and L1KBMTFSkimmed_pt[0]<20){
	   if (bxspread1==120) h_permutation012->Fill(1);
           if (bxspread1==210) h_permutation012->Fill(2);
           if (bxspread1==1200) h_permutation012->Fill(3);
           if (bxspread1==1020) h_permutation012->Fill(4);
           if (bxspread1==2100) h_permutation012->Fill(5);
           if (bxspread1==2010) h_permutation012->Fill(6);

	   if (bxspread1==130) h_permutation013->Fill(1);
           if (bxspread1==310) h_permutation013->Fill(2);
           if (bxspread1==1300) h_permutation013->Fill(3);
           if (bxspread1==1030) h_permutation013->Fill(4);
           if (bxspread1==3100) h_permutation013->Fill(5);
           if (bxspread1==3010) h_permutation013->Fill(6);

	   if (bxspread1==240) h_permutation024->Fill(1);
           if (bxspread1==420) h_permutation024->Fill(2);
           if (bxspread1==2400) h_permutation024->Fill(3);
           if (bxspread1==2040) h_permutation024->Fill(4);
           if (bxspread1==4200) h_permutation024->Fill(5);
           if (bxspread1==4020) h_permutation024->Fill(6);

	   if (bxspread1==120) h_pt_120->Fill(L1KBMTFSkimmed_pt[0]);
	   if (bxspread1==210) h_pt_210->Fill(L1KBMTFSkimmed_pt[0]);
	   if (bxspread1==1200) h_pt_1200->Fill(L1KBMTFSkimmed_pt[0]);
	   if (bxspread1==1020) h_pt_1020->Fill(L1KBMTFSkimmed_pt[0]);
	   if (bxspread1==2100) h_pt_2100->Fill(L1KBMTFSkimmed_pt[0]);
	   if (bxspread1==2010) h_pt_2010->Fill(L1KBMTFSkimmed_pt[0]);
	}

	if (nstub2==4 and L1KBMTFSkimmed_pt[1]<20){
           if (bxspread2==123) h_permutation0123->Fill(1);
           if (bxspread2==132) h_permutation0123->Fill(2);
           if (bxspread2==213) h_permutation0123->Fill(3);
           if (bxspread2==231) h_permutation0123->Fill(4);
           if (bxspread2==321) h_permutation0123->Fill(5);
           if (bxspread2==312) h_permutation0123->Fill(6);

           if (bxspread2==1023) h_permutation0123->Fill(7);
           if (bxspread2==1032) h_permutation0123->Fill(8);
           if (bxspread2==1230) h_permutation0123->Fill(9);
           if (bxspread2==1203) h_permutation0123->Fill(10);
           if (bxspread2==1302) h_permutation0123->Fill(11);
           if (bxspread2==1320) h_permutation0123->Fill(12);

           if (bxspread2==2013) h_permutation0123->Fill(13);
           if (bxspread2==2031) h_permutation0123->Fill(14);
           if (bxspread2==2103) h_permutation0123->Fill(15);
           if (bxspread2==2130) h_permutation0123->Fill(16);
           if (bxspread2==2301) h_permutation0123->Fill(17);
           if (bxspread2==2310) h_permutation0123->Fill(18);

           if (bxspread2==3012) h_permutation0123->Fill(19);
           if (bxspread2==3021) h_permutation0123->Fill(20);
           if (bxspread2==3102) h_permutation0123->Fill(21);
           if (bxspread2==3120) h_permutation0123->Fill(22);
           if (bxspread2==3201) h_permutation0123->Fill(23);
           if (bxspread2==3210) h_permutation0123->Fill(24);
        }
    } // end of loop over events

    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();
    h_permutation0123->Write();
    h_permutation0124->Write();
    h_permutation012->Write();
    h_permutation013->Write();
    h_permutation024->Write();
    h_ratio->Write();

    h_pt_0123->Write();
    h_pt_0312->Write();
    h_pt_0321->Write();
    h_pt_0231->Write();
    h_pt_0213->Write();
    h_pt_0132->Write();

    h_pt_120->Write();
    h_pt_1200->Write();
    h_pt_2100->Write();
    h_pt_1020->Write();
    h_pt_2010->Write();
    h_pt_210->Write();

    fout->Close();
}

