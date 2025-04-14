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
#include "myHelper.h"

using namespace std;

int main(int argc, char** argv) {

    std::string input = *(argv + 1);
    std::string output = *(argv + 2);
    std::string name = *(argv + 3);

    TFile *f_Double = new TFile(input.c_str());
    cout<<"XXXXXXXXXXXXX "<<input.c_str()<<" XXXXXXXXXXXX"<<endl;
    TTree *arbre = (TTree*) f_Double->Get("Events");

    arbre->SetBranchAddress("nL1KBMTFSkimmed", &nL1KBMTFSkimmed);
    arbre->SetBranchAddress("nstub1", &nstub1);
    arbre->SetBranchAddress("nstub2", &nstub2);
    arbre->SetBranchAddress("bxspread1", &bxspread1);
    arbre->SetBranchAddress("bxspread2", &bxspread2);
    arbre->SetBranchAddress("stationspread1", &stationspread1);
    arbre->SetBranchAddress("stationspread2", &stationspread2);
    arbre->SetBranchAddress("firstbx1", &firstbx1);
    arbre->SetBranchAddress("firstbx2", &firstbx2);
    arbre->SetBranchAddress("charge1", &charge1);
    arbre->SetBranchAddress("charge2", &charge2);
    arbre->SetBranchAddress("dxy1", &dxy1);
    arbre->SetBranchAddress("dxy2", &dxy2);
    arbre->SetBranchAddress("qual1", &qual1);
    arbre->SetBranchAddress("qual2", &qual2);
    arbre->SetBranchAddress("pt1", &pt1);
    arbre->SetBranchAddress("pt2", &pt2);
    arbre->SetBranchAddress("eta1", &eta1);
    arbre->SetBranchAddress("eta2", &eta2);
    arbre->SetBranchAddress("phi1", &phi1);
    arbre->SetBranchAddress("phi2", &phi2);
    arbre->SetBranchAddress("L1MET_pt", &L1MET_pt);
    arbre->SetBranchAddress("met_bx0", &met_bx0);
    arbre->SetBranchAddress("met_bxm1", &met_bxm1);
    arbre->SetBranchAddress("met_bxm2", &met_bxm2);
    arbre->SetBranchAddress("met_bxm3", &met_bxm3);
    arbre->SetBranchAddress("met_bxm4", &met_bxm4);
    arbre->SetBranchAddress("met_bxm5", &met_bxm5);
    /*arbre->SetBranchAddress("met_bx0_1", &met_bx0_1);
    arbre->SetBranchAddress("met_bxm1_1", &met_bxm1_1);
    arbre->SetBranchAddress("met_bxm2_1", &met_bxm2_1);
    arbre->SetBranchAddress("met_bxm3_1", &met_bxm3_1);
    arbre->SetBranchAddress("met_bxm4_1", &met_bxm4_1);
    arbre->SetBranchAddress("met_bxm5_1", &met_bxm5_1);
    arbre->SetBranchAddress("met_bx0_2", &met_bx0_2);
    arbre->SetBranchAddress("met_bxm1_2", &met_bxm1_2);
    arbre->SetBranchAddress("met_bxm2_2", &met_bxm2_2);
    arbre->SetBranchAddress("met_bxm3_2", &met_bxm3_2);
    arbre->SetBranchAddress("met_bxm4_2", &met_bxm4_2);
    arbre->SetBranchAddress("met_bxm5_2", &met_bxm5_2);*/

    TH1F* h_spread0 = new TH1F("h_spread0","h_spread0",8,0,8); h_spread0->Sumw2();
    TH1F* h_spread1 = new TH1F("h_spread1","h_spread1",8,0,8); h_spread1->Sumw2();
    TH1F* h_spread2 = new TH1F("h_spread2","h_spread2",3,0,3); h_spread2->Sumw2();

    TH1F* h_spread1_met1 = new TH1F("h_spread1_met1","h_spread1_met1",8,0,8); h_spread1_met1->Sumw2();
    TH1F* h_spread2_met1 = new TH1F("h_spread2_met1","h_spread2_met1",3,0,3); h_spread2_met1->Sumw2();

    TH1F* h_spread1_met2 = new TH1F("h_spread1_met2","h_spread1_met2",8,0,8); h_spread1_met2->Sumw2();
    TH1F* h_spread2_met2 = new TH1F("h_spread2_met2","h_spread2_met2",3,0,3); h_spread2_met2->Sumw2();

    TH1F* h_qual_nstub2 = new TH1F("h_qual_nstub2","h_qual_nstub2",4,12,16); h_qual_nstub2->Sumw2();
    TH1F* h_qual_nstub3 = new TH1F("h_qual_nstub3","h_qual_nstub3",4,12,16); h_qual_nstub3->Sumw2();
    TH1F* h_qual_nstub4 = new TH1F("h_qual_nstub4","h_qual_nstub4",4,12,16); h_qual_nstub4->Sumw2();
    TH1F* h_dxy = new TH1F("h_dxy","h_dxy",4,0,4); h_dxy->Sumw2();
    TH1F* h_nstub = new TH1F("h_nstub","h_nstub",3,2,5); h_nstub->Sumw2();

    TH1F* h_metbx0_mu0 = new TH1F("h_metbx0_mu0", "h_metbx0_mu0", 40,0,200); h_metbx0_mu0->Sumw2();
    TH1F* h_metbxm1_mu0 = new TH1F("h_metbxm1_mu0", "h_metbxm1_mu0", 40,0,200); h_metbxm1_mu0->Sumw2();
    TH1F* h_metbxm2_mu0 = new TH1F("h_metbxm2_mu0", "h_metbxm2_mu0", 40,0,200); h_metbxm2_mu0->Sumw2();
    TH1F* h_metbxm3_mu0 = new TH1F("h_metbxm3_mu0", "h_metbxm3_mu0", 40,0,200); h_metbxm3_mu0->Sumw2();
    TH1F* h_metbxm4_mu0 = new TH1F("h_metbxm4_mu0", "h_metbxm4_mu0", 40,0,200); h_metbxm4_mu0->Sumw2();
    TH1F* h_metbxm5_mu0 = new TH1F("h_metbxm5_mu0", "h_metbxm5_mu0", 40,0,200); h_metbxm5_mu0->Sumw2();

    TH1F* h_metbx0_mu0fail = new TH1F("h_metbx0_mu0fail", "h_metbx0_mu0fail", 40,0,200); h_metbx0_mu0fail->Sumw2();
    TH1F* h_metbxm1_mu0fail = new TH1F("h_metbxm1_mu0fail", "h_metbxm1_mu0fail", 40,0,200); h_metbxm1_mu0fail->Sumw2();
    TH1F* h_metbxm2_mu0fail = new TH1F("h_metbxm2_mu0fail", "h_metbxm2_mu0fail", 40,0,200); h_metbxm2_mu0fail->Sumw2();
    TH1F* h_metbxm3_mu0fail = new TH1F("h_metbxm3_mu0fail", "h_metbxm3_mu0fail", 40,0,200); h_metbxm3_mu0fail->Sumw2();
    TH1F* h_metbxm4_mu0fail = new TH1F("h_metbxm4_mu0fail", "h_metbxm4_mu0fail", 40,0,200); h_metbxm4_mu0fail->Sumw2();
    TH1F* h_metbxm5_mu0fail = new TH1F("h_metbxm5_mu0fail", "h_metbxm5_mu0fail", 40,0,200); h_metbxm5_mu0fail->Sumw2();

    TH1F* h_metbx0_mu01 = new TH1F("h_metbx0_mu01", "h_metbx0_mu01", 21,0,21); h_metbx0_mu01->Sumw2();
    TH1F* h_metbxm1_mu01 = new TH1F("h_metbxm1_mu01", "h_metbxm1_mu01", 21,0,21); h_metbxm1_mu01->Sumw2();
    TH1F* h_metbxm2_mu01 = new TH1F("h_metbxm2_mu01", "h_metbxm2_mu01", 21,0,21); h_metbxm2_mu01->Sumw2();
    TH1F* h_metbxm3_mu01 = new TH1F("h_metbxm3_mu01", "h_metbxm3_mu01", 21,0,21); h_metbxm3_mu01->Sumw2();
    TH1F* h_metbxm4_mu01 = new TH1F("h_metbxm4_mu01", "h_metbxm4_mu01", 21,0,21); h_metbxm4_mu01->Sumw2();
    TH1F* h_metbxm5_mu01 = new TH1F("h_metbxm5_mu01", "h_metbxm5_mu01", 21,0,21); h_metbxm5_mu01->Sumw2();

    TH1F* h_metbx0_mu01fail = new TH1F("h_metbx0_mu01fail", "h_metbx0_mu01fail", 21,0,21); h_metbx0_mu01fail->Sumw2();
    TH1F* h_metbxm1_mu01fail = new TH1F("h_metbxm1_mu01fail", "h_metbxm1_mu01fail", 21,0,21); h_metbxm1_mu01fail->Sumw2();
    TH1F* h_metbxm2_mu01fail = new TH1F("h_metbxm2_mu01fail", "h_metbxm2_mu01fail", 21,0,21); h_metbxm2_mu01fail->Sumw2();
    TH1F* h_metbxm3_mu01fail = new TH1F("h_metbxm3_mu01fail", "h_metbxm3_mu01fail", 21,0,21); h_metbxm3_mu01fail->Sumw2();
    TH1F* h_metbxm4_mu01fail = new TH1F("h_metbxm4_mu01fail", "h_metbxm4_mu01fail", 21,0,21); h_metbxm4_mu01fail->Sumw2();
    TH1F* h_metbxm5_mu01fail = new TH1F("h_metbxm5_mu01fail", "h_metbxm5_mu01fail", 21,0,21); h_metbxm5_mu01fail->Sumw2();

    float bins_pt_extra_coarse[] = {10,20,30,50,100};
   int  binnum_pt_extra_coarse = sizeof(bins_pt_extra_coarse)/sizeof(Float_t) - 1;

   float bins_pt_coarse[] = {100,150,200,250,260,500,520};
   int  binnum_pt_coarse = sizeof(bins_pt_coarse)/sizeof(Float_t) - 1;

   float bins_pt_fine[] = {100,150,200,250,260,500,520};
   int  binnum_pt_fine = sizeof(bins_pt_fine)/sizeof(Float_t) - 1;

   float bins_pt_extrafine[] = {100,150,200,250,260,500,520};
   int  binnum_pt_extrafine = sizeof(bins_pt_extrafine)/sizeof(Float_t) - 1;


   TH1F* h_stub4_bx1234 = new TH1F("h_stub4_bx1234", "h_stub4_bx1234", binnum_pt_extra_coarse, bins_pt_extra_coarse); h_stub4_bx1234->Sumw2();
   TH1F* h_stub4_bx1234_wrong = new TH1F("h_stub4_bx1234_wrong", "h_stub4_bx1234_wrong", binnum_pt_extra_coarse, bins_pt_extra_coarse); h_stub4_bx1234_wrong->Sumw2();
   TH1F* h_stub4_bx1234_fail = new TH1F("h_stub4_bx1234_fail", "h_stub4_bx1234_fail", binnum_pt_extra_coarse, bins_pt_extra_coarse); h_stub4_bx1234_fail->Sumw2();
   TH1F* h_stub4_bx1234_wrong_fail = new TH1F("h_stub4_bx1234_wrong_fail", "h_stub4_bx1234_wrong_fail", binnum_pt_extra_coarse, bins_pt_extra_coarse); h_stub4_bx1234_wrong_fail->Sumw2();

   TH1F* h_stub4_bx1245 = new TH1F("h_stub4_bx1245", "h_stub4_bx1245", binnum_pt_extra_coarse, bins_pt_extra_coarse); h_stub4_bx1245->Sumw2();
   TH1F* h_stub4_bx1245_wrong = new TH1F("h_stub4_bx1245_wrong", "h_stub4_bx1245_wrong", binnum_pt_extra_coarse, bins_pt_extra_coarse); h_stub4_bx1245_wrong->Sumw2();
   TH1F* h_stub4_bx1245_fail = new TH1F("h_stub4_bx1245_fail", "h_stub4_bx1245_fail", binnum_pt_extra_coarse, bins_pt_extra_coarse); h_stub4_bx1245_fail->Sumw2();
   TH1F* h_stub4_bx1245_wrong_fail = new TH1F("h_stub4_bx1245_wrong_fail", "h_stub4_bx1245_wrong_fail", binnum_pt_extra_coarse, bins_pt_extra_coarse); h_stub4_bx1245_wrong_fail->Sumw2();

   TH1F* h_stub3_bx124 = new TH1F("h_stub3_bx124", "h_stub3_bx124", binnum_pt_coarse, bins_pt_coarse); h_stub3_bx124->Sumw2();
   TH1F* h_stub3_bx124_wrong = new TH1F("h_stub3_bx124_wrong", "h_stub3_bx124_wrong", binnum_pt_coarse, bins_pt_coarse); h_stub3_bx124_wrong->Sumw2();
   TH1F* h_stub3_bx124_fail = new TH1F("h_stub3_bx124_fail", "h_stub3_bx124_fail", binnum_pt_coarse, bins_pt_coarse); h_stub3_bx124_fail->Sumw2();
   TH1F* h_stub3_bx124_wrong_fail = new TH1F("h_stub3_bx124_wrong_fail", "h_stub3_bx124_wrong_fail", binnum_pt_coarse, bins_pt_coarse); h_stub3_bx124_wrong_fail->Sumw2();

   TH1F* h_stub3_bx123_slow = new TH1F("h_stub3_bx123_slow", "h_stub3_bx123_slow", binnum_pt_fine, bins_pt_fine); h_stub3_bx123_slow->Sumw2();
   TH1F* h_stub3_bx123_slow_wrong = new TH1F("h_stub3_bx123_slow_wrong", "h_stub3_bx123_slow_wrong", binnum_pt_fine, bins_pt_fine); h_stub3_bx123_slow_wrong->Sumw2();
   TH1F* h_stub3_bx123_slow_fail = new TH1F("h_stub3_bx123_slow_fail", "h_stub3_bx123_slow_fail", binnum_pt_fine, bins_pt_fine); h_stub3_bx123_slow_fail->Sumw2();
   TH1F* h_stub3_bx123_slow_wrong_fail = new TH1F("h_stub3_bx123_slow_wrong_fail", "h_stub3_bx123_slow_wrong_fail", binnum_pt_fine, bins_pt_fine); h_stub3_bx123_slow_wrong_fail->Sumw2();

   TH1F* h_stub3_bx123_fast = new TH1F("h_stub3_bx123_fast", "h_stub3_bx123_fast", binnum_pt_fine, bins_pt_fine); h_stub3_bx123_fast->Sumw2();
   TH1F* h_stub3_bx123_fast_wrong = new TH1F("h_stub3_bx123_fast_wrong", "h_stub3_bx123_fast_wrong", binnum_pt_fine, bins_pt_fine); h_stub3_bx123_fast_wrong->Sumw2();
   TH1F* h_stub3_bx123_fast_fail = new TH1F("h_stub3_bx123_fast_fail", "h_stub3_bx123_fast_fail", binnum_pt_fine, bins_pt_fine); h_stub3_bx123_fast_fail->Sumw2();
   TH1F* h_stub3_bx123_fast_wrong_fail = new TH1F("h_stub3_bx123_fast_wrong_fail", "h_stub3_bx123_fast_wrong_fail", binnum_pt_fine, bins_pt_fine); h_stub3_bx123_fast_wrong_fail->Sumw2();

   TH1F* h_stub4_bx123 = new TH1F("h_stub4_bx123", "h_stub4_bx123", binnum_pt_coarse, bins_pt_coarse); h_stub4_bx123->Sumw2();
   TH1F* h_stub4_bx123_wrong = new TH1F("h_stub4_bx123_wrong", "h_stub4_bx123_wrong", binnum_pt_coarse, bins_pt_coarse); h_stub4_bx123_wrong->Sumw2();
   TH1F* h_stub4_bx123_fail = new TH1F("h_stub4_bx123_fail", "h_stub4_bx123_fail", binnum_pt_coarse, bins_pt_coarse); h_stub4_bx123_fail->Sumw2();
   TH1F* h_stub4_bx123_wrong_fail = new TH1F("h_stub4_bx123_wrong_fail", "h_stub4_bx123_wrong_fail", binnum_pt_coarse, bins_pt_coarse); h_stub4_bx123_wrong_fail->Sumw2();

   TH1F* h_stub4_bx124 = new TH1F("h_stub4_bx124", "h_stub4_bx124", binnum_pt_coarse, bins_pt_coarse); h_stub4_bx124->Sumw2();
   TH1F* h_stub4_bx124_wrong = new TH1F("h_stub4_bx124_wrong", "h_stub4_bx124_wrong", binnum_pt_coarse, bins_pt_coarse); h_stub4_bx124_wrong->Sumw2();
   TH1F* h_stub4_bx124_fail = new TH1F("h_stub4_bx124_fail", "h_stub4_bx124_fail", binnum_pt_coarse, bins_pt_coarse); h_stub4_bx124_fail->Sumw2();
   TH1F* h_stub4_bx124_wrong_fail = new TH1F("h_stub4_bx124_wrong_fail", "h_stub4_bx124_wrong_fail", binnum_pt_coarse, bins_pt_coarse); h_stub4_bx124_wrong_fail->Sumw2();


   TH1F* h_stub4_bx1122 = new TH1F("h_stub4_bx1122", "h_stub4_bx1122", binnum_pt_extrafine, bins_pt_extrafine); h_stub4_bx1122->Sumw2();
   TH1F* h_stub4_bx1122_wrong = new TH1F("h_stub4_bx1122_wrong", "h_stub4_bx1122_wrong", binnum_pt_extrafine, bins_pt_extrafine); h_stub4_bx1122_wrong->Sumw2();
   TH1F* h_stub4_bx1122_fail = new TH1F("h_stub4_bx1122_fail", "h_stub4_bx1122_fail", binnum_pt_extrafine, bins_pt_extrafine); h_stub4_bx1122_fail->Sumw2();
   TH1F* h_stub4_bx1122_wrong_fail = new TH1F("h_stub4_bx1122_wrong_fail", "h_stub4_bx1122_wrong_fail", binnum_pt_extrafine, bins_pt_extrafine); h_stub4_bx1122_wrong_fail->Sumw2();

   TH1F* h_stub4_bx1112 = new TH1F("h_stub4_bx1112", "h_stub4_bx1112", binnum_pt_extrafine, bins_pt_extrafine); h_stub4_bx1112->Sumw2();
   TH1F* h_stub4_bx1112_wrong = new TH1F("h_stub4_bx1112_wrong", "h_stub4_bx1112_wrong", binnum_pt_extrafine, bins_pt_extrafine); h_stub4_bx1112_wrong->Sumw2();
   TH1F* h_stub4_bx1112_fail = new TH1F("h_stub4_bx1112_fail", "h_stub4_bx1112_fail", binnum_pt_extrafine, bins_pt_extrafine); h_stub4_bx1112_fail->Sumw2();
   TH1F* h_stub4_bx1112_wrong_fail = new TH1F("h_stub4_bx1112_wrong_fail", "h_stub4_bx1112_wrong_fail", binnum_pt_extrafine, bins_pt_extrafine); h_stub4_bx1112_wrong_fail->Sumw2();

   TH1F* h_stub4_bx1222 = new TH1F("h_stub4_bx1222", "h_stub4_bx1222", binnum_pt_extrafine, bins_pt_extrafine); h_stub4_bx1222->Sumw2();
   TH1F* h_stub4_bx1222_wrong = new TH1F("h_stub4_bx1222_wrong", "h_stub4_bx1222_wrong", binnum_pt_extrafine, bins_pt_extrafine); h_stub4_bx1222_wrong->Sumw2();
   TH1F* h_stub4_bx1222_fail = new TH1F("h_stub4_bx1222_fail", "h_stub4_bx1222_fail", binnum_pt_extrafine, bins_pt_extrafine); h_stub4_bx1222_fail->Sumw2();
   TH1F* h_stub4_bx1222_wrong_fail = new TH1F("h_stub4_bx1222_wrong_fail", "h_stub4_bx1222_wrong_fail", binnum_pt_extrafine, bins_pt_extrafine); h_stub4_bx1222_wrong_fail->Sumw2();

   TH1F* h_stub3_bx112 = new TH1F("h_stub3_bx112", "h_stub3_bx112", binnum_pt_extrafine, bins_pt_extrafine); h_stub3_bx112->Sumw2();
   TH1F* h_stub3_bx112_wrong = new TH1F("h_stub3_bx112_wrong", "h_stub3_bx112_wrong", binnum_pt_extrafine, bins_pt_extrafine); h_stub3_bx112_wrong->Sumw2();
   TH1F* h_stub3_bx112_fail = new TH1F("h_stub3_bx112_fail", "h_stub3_bx112_fail", binnum_pt_extrafine, bins_pt_extrafine); h_stub3_bx112_fail->Sumw2();
   TH1F* h_stub3_bx112_wrong_fail = new TH1F("h_stub3_bx112_wrong_fail", "h_stub3_bx112_wrong_fail", binnum_pt_extrafine, bins_pt_extrafine); h_stub3_bx112_wrong_fail->Sumw2();

   TH1F* h_stub3_bx122 = new TH1F("h_stub3_bx122", "h_stub3_bx122", binnum_pt_extrafine, bins_pt_extrafine); h_stub3_bx122->Sumw2();
   TH1F* h_stub3_bx122_wrong = new TH1F("h_stub3_bx122_wrong", "h_stub3_bx122_wrong", binnum_pt_extrafine, bins_pt_extrafine); h_stub3_bx122_wrong->Sumw2();
   TH1F* h_stub3_bx122_fail = new TH1F("h_stub3_bx122_fail", "h_stub3_bx122_fail", binnum_pt_extrafine, bins_pt_extrafine); h_stub3_bx122_fail->Sumw2();
   TH1F* h_stub3_bx122_wrong_fail = new TH1F("h_stub3_bx122_wrong_fail", "h_stub3_bx122_wrong_fail", binnum_pt_extrafine, bins_pt_extrafine); h_stub3_bx122_wrong_fail->Sumw2();

   TH1F* h_stub2_bx12 = new TH1F("h_stub2_bx12", "h_stub2_bx12", binnum_pt_extrafine, bins_pt_extrafine); h_stub2_bx12->Sumw2();
   TH1F* h_stub2_bx12_wrong = new TH1F("h_stub2_bx12_wrong", "h_stub2_bx12_wrong", binnum_pt_extrafine, bins_pt_extrafine); h_stub2_bx12_wrong->Sumw2();
   TH1F* h_stub2_bx12_fail = new TH1F("h_stub2_bx12_fail", "h_stub2_bx12_fail", binnum_pt_extrafine, bins_pt_extrafine); h_stub2_bx12_fail->Sumw2();
   TH1F* h_stub2_bx12_wrong_fail = new TH1F("h_stub2_bx12_wrong_fail", "h_stub2_bx12_wrong_fail", binnum_pt_extrafine, bins_pt_extrafine); h_stub2_bx12_wrong_fail->Sumw2();

   TH1F* h_stub2_bx12_station12 = new TH1F("h_stub2_bx12_station12", "h_stub2_bx12_station12", binnum_pt_extrafine, bins_pt_extrafine); h_stub2_bx12_station12->Sumw2();
   TH1F* h_stub2_bx12_station12_wrong = new TH1F("h_stub2_bx12_station12_wrong", "h_stub2_bx12_station12_wrong", binnum_pt_extrafine, bins_pt_extrafine); h_stub2_bx12_station12_wrong->Sumw2();
   TH1F* h_stub2_bx12_station12_fail = new TH1F("h_stub2_bx12_station12_fail", "h_stub2_bx12_station12_fail", binnum_pt_extrafine, bins_pt_extrafine); h_stub2_bx12_station12_fail->Sumw2();
   TH1F* h_stub2_bx12_station12_wrong_fail = new TH1F("h_stub2_bx12_station12_wrong_fail", "h_stub2_bx12_station12_wrong_fail", binnum_pt_extrafine, bins_pt_extrafine); h_stub2_bx12_station12_wrong_fail->Sumw2();

   float bins_met[] = {0,10,20,30,40,50,100,200};
   int  binnum_met = sizeof(bins_met)/sizeof(Float_t) - 1;
   TH1F* h_samebx_metm1 = new TH1F("h_samebx_metm1", "h_samebx_metm1", binnum_met, bins_met); h_samebx_metm1->Sumw2();
   TH1F* h_samebx_metm1_fail = new TH1F("h_samebx_metm1_fail", "h_samebx_metm1_fail", binnum_met, bins_met); h_samebx_metm1_fail->Sumw2();

   TH1F* h_samebx_metm2 = new TH1F("h_samebx_metm2", "h_samebx_metm2", binnum_met, bins_met); h_samebx_metm2->Sumw2();
   TH1F* h_samebx_metm2_fail = new TH1F("h_samebx_metm2_fail", "h_samebx_metm2_fail", binnum_met, bins_met); h_samebx_metm2_fail->Sumw2();

   TH1F* h_samebx_metm3 = new TH1F("h_samebx_metm3", "h_samebx_metm3", binnum_met, bins_met); h_samebx_metm3->Sumw2();
   TH1F* h_samebx_metm3_fail = new TH1F("h_samebx_metm3_fail", "h_samebx_metm3_fail", binnum_met, bins_met); h_samebx_metm3_fail->Sumw2();

   TH1F* h_samebx_metm4 = new TH1F("h_samebx_metm4", "h_samebx_metm4", binnum_met, bins_met); h_samebx_metm4->Sumw2();
   TH1F* h_samebx_metm4_fail = new TH1F("h_samebx_metm4_fail", "h_samebx_metm4_fail", binnum_met, bins_met); h_samebx_metm4_fail->Sumw2();

   TH1F* h_stub2bx12_metm1 = new TH1F("h_stub2bx12_metm1", "h_stub2bx12_metm1", binnum_met, bins_met); h_stub2bx12_metm1->Sumw2();
   TH1F* h_stub2bx12_metm1_fail = new TH1F("h_stub2bx12_metm1_fail", "h_stub2bx12_metm1_fail", binnum_met, bins_met); h_stub2bx12_metm1_fail->Sumw2();

   TH1F* h_stub2bx12_metm2 = new TH1F("h_stub2bx12_metm2", "h_stub2bx12_metm2", binnum_met, bins_met); h_stub2bx12_metm2->Sumw2();
   TH1F* h_stub2bx12_metm2_fail = new TH1F("h_stub2bx12_metm2_fail", "h_stub2bx12_metm2_fail", binnum_met, bins_met); h_stub2bx12_metm2_fail->Sumw2();

   TH1F* h_stub2bx12_metm3 = new TH1F("h_stub2bx12_metm3", "h_stub2bx12_metm3", binnum_met, bins_met); h_stub2bx12_metm3->Sumw2();
   TH1F* h_stub2bx12_metm3_fail = new TH1F("h_stub2bx12_metm3_fail", "h_stub2bx12_metm3_fail", binnum_met, bins_met); h_stub2bx12_metm3_fail->Sumw2();

   TH1F* h_stub2bx12_metm4 = new TH1F("h_stub2bx12_metm4", "h_stub2bx12_metm4", binnum_met, bins_met); h_stub2bx12_metm4->Sumw2();
   TH1F* h_stub2bx12_metm4_fail = new TH1F("h_stub2bx12_metm4_fail", "h_stub2bx12_metm4_fail", binnum_met, bins_met); h_stub2bx12_metm4_fail->Sumw2();


   float lumiweight= (37770.0/15.046) + (5440.0/15.060) + (11470.0/15.048);
   float xsweight=1.000 * lumiweight/20000; //20000 gen events
   if (name=="data_obs") xsweight=1.0;
   static TRandom3 randGen(1234);

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();
   for (Int_t i = 0; i < nentries_wtn; i++) {
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

	//float weight = 1.0/2580;
	float weight = 1.0/1447;
	if (name=="data_obs") weight=1.0;
	if (name=="HSCP2600") weight = 1.0/2580;
	if (name=="Jian") weight=1.0;

	float met0=0.0;
        if (name=="data_obs") met0=met_bx0;
        else if (firstbx1==0) met0=L1MET_pt[0];

	float metm1=0.0;
	if (name=="data_obs") metm1=met_bxm1;
	else if (firstbx1==1) metm1=L1MET_pt[0];

	float metm2=0.0;
        if (name=="data_obs") metm2=met_bxm2;
        else if (firstbx1==2) metm2=L1MET_pt[0];

	float metm3=0.0;
        if (name=="data_obs") metm3=met_bxm3;
        else if (firstbx1==3) metm3=L1MET_pt[0];

	float metm4=0.0;
        if (name=="data_obs") metm4=met_bxm4;
        else if (firstbx1==4) metm4=L1MET_pt[0];

        float metm5=0.0;
        if (name=="data_obs") metm5=met_bxm5;
        else if (firstbx1==5) metm5=L1MET_pt[0];

	if (name=="data_obs") firstbx1=-1; //dummy value because we cannot know in data

	//###########################################################
	//############## CHECK QUALITY CRITERIA #####################
	//###########################################################
	
	if (nstub1==2) h_qual_nstub2->Fill(qual1);
	if (nstub1==3) h_qual_nstub3->Fill(qual1);
	if (nstub1==4) h_qual_nstub4->Fill(qual1);
	h_nstub->Fill(nstub1);
	h_dxy->Fill(dxy1);

	bool pass_quality_1=true;
	if (nstub1==2 and qual1<13) pass_quality_1=false;
	if (nstub1==3 and qual1<14) pass_quality_1=false;
	if (nstub1==4 and qual1<15) pass_quality_1=false;
	if (dxy1>0) pass_quality_1=false;
	if (dxy1>0) continue;
	//if (pt1<50) continue;

	//#####################################################################################
	
	bool is_cat1=false;
	bool is_cat2=false;
	bool is_cat3=false;
	bool is_cat4=false;
	bool is_cat5=false;

	if (bxspread1==0 or bxspread1==1000){
	   is_cat1=(metm1>=metm2 and metm1>=metm3 and metm1>=metm4 and metm1>=metm5);
	   is_cat2=(!is_cat1 and metm2>=metm1 and metm2>=metm3 and metm2>=metm4 and metm2>=metm5);
	   is_cat3=(!is_cat1 and !is_cat2 and metm3>=metm1 and metm3>=metm2 and metm3>=metm4 and metm3>=metm5);
	   is_cat4=(!is_cat1 and !is_cat2 and !is_cat3 and metm4>=metm1 and metm4>=metm2 and metm4>=metm3 and metm4>=metm5);
	   is_cat5=(!is_cat1 and !is_cat2 and !is_cat3 and !is_cat4);
	   if (firstbx1==0) h_spread0->Fill(0.5,weight);
	   else if (pt1>500 and metm1>50) h_spread0->Fill(1.5,weight);
	   else if (firstbx1==1) h_spread0->Fill(2.5,weight);
	   else if (pt1>500 and metm2>50) h_spread0->Fill(3.5,weight);
           else if (firstbx1==2) h_spread0->Fill(4.5,weight);
	   else if (pt1>500 and metm3>50) h_spread0->Fill(5.5,weight);
           else if (firstbx1==3) h_spread0->Fill(6.5,weight);
	   else h_spread0->Fill(7.5,weight);

	   if (pass_quality_1){
	      h_metbx0_mu0->Fill(met_bx0);
	      if (is_cat1) h_metbxm1_mu0->Fill(metm1);
	      if (is_cat2) h_metbxm2_mu0->Fill(metm2);
	      if (is_cat3) h_metbxm3_mu0->Fill(metm3);
	      if (is_cat4) h_metbxm4_mu0->Fill(metm4);
	      if (is_cat5) h_metbxm5_mu0->Fill(metm5);
	   }

	   if (!pass_quality_1){
              h_metbx0_mu0fail->Fill(met_bx0);
              if (is_cat1) h_metbxm1_mu0fail->Fill(metm1);
              if (is_cat2) h_metbxm2_mu0fail->Fill(metm2);
              if (is_cat3) h_metbxm3_mu0fail->Fill(metm3);
              if (is_cat4) h_metbxm4_mu0fail->Fill(metm4);
              if (is_cat5) h_metbxm5_mu0fail->Fill(metm5);
	   }
	}

	if (nstub1==4 and bxspread1==1100) h_spread1->Fill(0.5,weight);
	else if (nstub1==4 and bxspread1==1000) h_spread1->Fill(1.5,weight);
	else if (nstub1==4 and bxspread1==1110) h_spread1->Fill(2.5,weight);
	else if (nstub1==3 and bxspread1==1000) h_spread1->Fill(3.5,weight);
	else if (nstub1==3 and bxspread1==1100) h_spread1->Fill(4.5,weight);
	else if (nstub1==2 and bxspread1==1000 and stationspread1==2100) h_spread1->Fill(5.5,weight);
	else if (nstub1==2 and bxspread1==1000) h_spread1->Fill(6.5,weight);
	else if (bxspread1==1000 or bxspread1==1100 or bxspread1==1110) h_spread1->Fill(7.5,weight);

	if (pass_quality_1){
	   if (nstub1==4 and bxspread1==1110){ 
	      if (metm3<25) h_metbxm1_mu01->Fill(0);
	      else if (metm3<50) h_metbxm1_mu01->Fill(1);
	      else h_metbxm3_mu01->Fill(2);
	   }
	   else if (nstub1==4 and bxspread1==1100){ 
              if (metm3<25) h_metbxm1_mu01->Fill(3);
              else if (metm3<50) h_metbxm1_mu01->Fill(4);
              else h_metbxm3_mu01->Fill(5);
           }
	   else if (nstub1==4 and bxspread1==1000){
              if (metm3<25) h_metbxm1_mu01->Fill(6);
              else if (metm3<50) h_metbxm1_mu01->Fill(7);
              else h_metbxm3_mu01->Fill(8);
           }
	   else if (nstub1==3 and bxspread1==1100){
              if (metm3<25) h_metbxm1_mu01->Fill(9);
              else if (metm3<50) h_metbxm1_mu01->Fill(10);
              else h_metbxm3_mu01->Fill(11);
           }
	   else if (nstub1==3 and bxspread1==1000){
              if (metm3<25) h_metbxm1_mu01->Fill(12);
              else if (metm3<50) h_metbxm1_mu01->Fill(13);
              else h_metbxm3_mu01->Fill(14);
           }
	   else if (nstub1==2 and bxspread1==1000 and stationspread1==2100){ 
              if (metm3<25) h_metbxm1_mu01->Fill(15);
              else if (metm3<50) h_metbxm1_mu01->Fill(16);
              else h_metbxm3_mu01->Fill(17);
           }
	   else if (nstub1==2 and bxspread1==1000){ 
              if (metm3<25) h_metbxm1_mu01->Fill(18);
              else if (metm3<50) h_metbxm1_mu01->Fill(19);
              else h_metbxm3_mu01->Fill(20);
           }
	}
	if (!pass_quality_1){
           if (nstub1==4 and bxspread1==1110){
              if (metm3<25) h_metbxm1_mu01fail->Fill(0);
              else if (metm3<50) h_metbxm1_mu01fail->Fill(1);
              else h_metbxm3_mu01fail->Fill(2);
           }
           else if (nstub1==4 and bxspread1==1100){
              if (metm3<25) h_metbxm1_mu01fail->Fill(3);
              else if (metm3<50) h_metbxm1_mu01fail->Fill(4);
              else h_metbxm3_mu01fail->Fill(5);
           }
           else if (nstub1==4 and bxspread1==1000){
              if (metm3<25) h_metbxm1_mu01fail->Fill(6);
              else if (metm3<50) h_metbxm1_mu01fail->Fill(7);
              else h_metbxm3_mu01fail->Fill(8);
           }
           else if (nstub1==3 and bxspread1==1100){
              if (metm3<25) h_metbxm1_mu01fail->Fill(9);
              else if (metm3<50) h_metbxm1_mu01fail->Fill(10);
              else h_metbxm3_mu01fail->Fill(11);
           }
           else if (nstub1==3 and bxspread1==1000){
              if (metm3<25) h_metbxm1_mu01fail->Fill(12);
              else if (metm3<50) h_metbxm1_mu01fail->Fill(13);
              else h_metbxm3_mu01fail->Fill(14);
           }
           else if (nstub1==2 and bxspread1==1000 and stationspread1==2100){
              if (metm3<25) h_metbxm1_mu01fail->Fill(15);
              else if (metm3<50) h_metbxm1_mu01fail->Fill(16);
              else h_metbxm3_mu01fail->Fill(17);
           }
           else if (nstub1==2 and bxspread1==1000){
              if (metm3<25) h_metbxm1_mu01fail->Fill(18);
              else if (metm3<50) h_metbxm1_mu01fail->Fill(19);
              else h_metbxm3_mu01fail->Fill(20);
           }
        }

	//if (nstub1==3 and bxspread1==1100) cout<<firstbx1<<" "<<pt1<<" "<<L1MET_pt[0]<<endl;

	if (metm1>30 and pt1>250){
           if (nstub1==4 and bxspread1==1100) h_spread1_met1->Fill(0.5,weight);
           else if (nstub1==4 and bxspread1==1000) h_spread1_met1->Fill(1.5,weight);
           else if (nstub1==4 and bxspread1==1110) h_spread1_met1->Fill(2.5,weight);
           else if (nstub1==3 and bxspread1==1000) h_spread1_met1->Fill(3.5,weight);
           else if (nstub1==3 and bxspread1==1100) h_spread1_met1->Fill(4.5,weight);
           else if (nstub1==2 and bxspread1==1000 and stationspread1==2100) h_spread1_met1->Fill(5.5,weight);
           else if (nstub1==2 and bxspread1==1000) h_spread1_met1->Fill(6.5,weight);
           else if (bxspread1==1000 or bxspread1==1100 or bxspread1==1110) h_spread1_met1->Fill(7.5,weight);
	}

	if (metm2>30 and pt1>250){
           if (nstub1==4 and bxspread1==1100) h_spread1_met2->Fill(0.5,weight);
           else if (nstub1==4 and bxspread1==1000) h_spread1_met2->Fill(1.5,weight);
           else if (nstub1==4 and bxspread1==1110) h_spread1_met2->Fill(2.5,weight);
           else if (nstub1==3 and bxspread1==1000) h_spread1_met2->Fill(3.5,weight);
           else if (nstub1==3 and bxspread1==1100) h_spread1_met2->Fill(4.5,weight);
           else if (nstub1==2 and bxspread1==1000 and stationspread1==2100) h_spread1_met2->Fill(5.5,weight);
           else if (nstub1==2 and bxspread1==1000) h_spread1_met2->Fill(6.5,weight);
           else if (bxspread1==1000 or bxspread1==1100 or bxspread1==1110) h_spread1_met2->Fill(7.5,weight);
        }

	////////////////
	if (bxspread1==2100 or bxspread1==2110 or bxspread1==2210 or bxspread1==2000 or bxspread1==2200 or bxspread1==2220){
	   if (nstub1==4) h_spread2->Fill(0.5,weight);
	   else if (nstub1==3) h_spread2->Fill(1.5,weight);
	   else if (nstub1==2) h_spread2->Fill(2.5,weight);
        }

	if (metm1>30 and pt1>250){
	   if (bxspread1==2100 or bxspread1==2110 or bxspread1==2210 or bxspread1==2000 or bxspread1==2200 or bxspread1==2220){
              if (nstub1==4) h_spread2_met1->Fill(0.5,weight);
              else if (nstub1==3) h_spread2_met1->Fill(1.5,weight);
              else if (nstub1==2) h_spread2_met1->Fill(2.5,weight);
           }
	}

	if (metm2>30 and pt1>250){
           if (bxspread1==2100 or bxspread1==2110 or bxspread1==2210 or bxspread1==2000 or bxspread1==2200 or bxspread1==2220){
              if (nstub1==4) h_spread2_met2->Fill(0.5,weight);
              else if (nstub1==3) h_spread2_met2->Fill(1.5,weight);
              else if (nstub1==2) h_spread2_met2->Fill(2.5,weight);
           }
        }

	//########################################################################
	//############################### ANALYSIS ###############################
	//########################################################################
	bool is_accepted=false;

	/*if (name=="data_obs"){
           pt1=0.84*pt1;
        }
        else{
           pt1=0.84*pt1;
        }

        // Muon energy resolution
        double smearFactor1 = randGen.Gaus(1.0, 0.11);
        double smearFactor2 = randGen.Gaus(1.0, 0.11);
        if (name!="data_obs"){
           pt1 = pt1 * smearFactor1;
           pt2 = pt2 * smearFactor2;
        }*/

        // Muon reconstruction efficiency
        float musf=0.98;
	float aweight=1.0;
        aweight = aweight*musf;
	if (name=="data_obs") aweight=1.0;

	
	// ############### Across 3 or 4 BXs ################
	
	bool is_1234_1 = (nstub1==4 and (bxspread1==3210 or bxspread1==3120 or bxspread1==3201 or bxspread1==3102 or bxspread1==3012 or bxspread1==3021 or bxspread1==1230 or bxspread1==1320 or bxspread1==2130 or bxspread1==2310));
	if (is_1234_1){
	   if (bxspread1==3210){
	      if (qual1>=15) {h_stub4_bx1234->Fill(pt1,xsweight*aweight); is_accepted=true;}
	      else if (qual1>=1) {h_stub4_bx1234_fail->Fill(pt1,xsweight*aweight); is_accepted=true;}
	   }
	   else{
              if (qual1>=15) {h_stub4_bx1234_wrong->Fill(pt1,xsweight*aweight); is_accepted=true;}
              else if (qual1>=1) {h_stub4_bx1234_wrong_fail->Fill(pt1,xsweight*aweight); is_accepted=true;}
           }
	}

	bool is_123_3stubs_slow_1 = (nstub1==3 and (bxspread1==2100 or bxspread1==2010 or bxspread1==1200) and (stationspread1==4310 or stationspread1==4210));
	if (is_123_3stubs_slow_1){
           if (bxspread1==2100){
              if (qual1>=14) {h_stub3_bx123_slow->Fill(pt1,xsweight*aweight); is_accepted=true;}
              else {h_stub3_bx123_slow_fail->Fill(pt1,xsweight*aweight); is_accepted=true;}
           }
           else{
              if (qual1>=14) {h_stub3_bx123_slow_wrong->Fill(pt1,xsweight*aweight); is_accepted=true;}
              else {h_stub3_bx123_slow_wrong_fail->Fill(pt1,xsweight*aweight); is_accepted=true;}
           }
        }

	bool is_123_3stubs_fast_1 = (nstub1==3 and (bxspread1==2100 or bxspread1==2010 or bxspread1==1200) and (stationspread1==4320 or stationspread1==3210));
        if (is_123_3stubs_fast_1){
           if (bxspread1==2100){
              if (qual1>=14) {h_stub3_bx123_fast->Fill(pt1,xsweight*aweight); is_accepted=true;}
              else {h_stub3_bx123_fast_fail->Fill(pt1,xsweight*aweight); is_accepted=true;}
           }
           else{
              if (qual1>=14) {h_stub3_bx123_fast_wrong->Fill(pt1,xsweight*aweight); is_accepted=true;}
              else {h_stub3_bx123_fast_wrong_fail->Fill(pt1,xsweight*aweight); is_accepted=true;}
           }
        }

	bool is_123_4stubs_1 = (nstub1==4 and (bxspread1==2100 or bxspread1==2110 or bxspread1==2210 or bxspread1==2120 or bxspread1==2102 or bxspread1==2101 or bxspread1==2201 or bxspread1==2001 or bxspread1==2010 or bxspread1==2012 or bxspread1==2021 or bxspread1==2011 or (bxspread1==120 or bxspread1==210 or bxspread1==1120 or bxspread1==1210 or bxspread1==1220 or bxspread1==1020 or bxspread1==1200)));
        if (is_123_4stubs_1){
           if (bxspread1==2100 or bxspread1==2110 or bxspread1==2210){
              if (qual1>=15) {h_stub4_bx123->Fill(pt1,xsweight*aweight); is_accepted=true;}
              else if (qual1>=1) {h_stub4_bx123_fail->Fill(pt1,xsweight*aweight); is_accepted=true;}
           }
           else{
              if (qual1>=15) {h_stub4_bx123_wrong->Fill(pt1,xsweight*aweight); is_accepted=true;}
              else if (qual1>=1) {h_stub4_bx123_wrong_fail->Fill(pt1,xsweight*aweight); is_accepted=true;}
           }
        }

	bool is_124_4stubs_1 = (nstub1==4 and ((bxspread1==3100 or bxspread1==3110 or bxspread1==3310 or bxspread1==3011 or bxspread1==3101 or bxspread1==3001 or bxspread1==3010 or bxspread1==3031 or bxspread1==3013 or bxspread1==3130 or bxspread1==3103 or bxspread1==3031 or bxspread1==3301) or (bxspread1==3200 or bxspread1==3220 or bxspread1==3320 or bxspread1==3022 or bxspread1==3202 or bxspread1==3002 or bxspread1==3020 or bxspread1==3032 or bxspread1==3023 or bxspread1==3230 or bxspread1==3203 or bxspread1==3032 or bxspread1==3302) or (bxspread1==1330 or bxspread1==1130 or bxspread1==1030 or bxspread1==1300 or bxspread1==2330 or bxspread1==2230 or bxspread1==2030 or bxspread1==2300 or bxspread1==130 or bxspread1==310 or bxspread1==230 or bxspread1==320)));
        if (is_124_4stubs_1){
           if (bxspread1==3100 or bxspread1==3110 or bxspread1==3310 or bxspread1==3200 or bxspread1==3220 or bxspread1==3320){
              if (qual1>=15) {h_stub4_bx124->Fill(pt1,xsweight*aweight); is_accepted=true;}
              else if (qual1>=1) {h_stub4_bx124_fail->Fill(pt1,xsweight*aweight); is_accepted=true;}
           }
           else{
              if (qual1>=15) {h_stub4_bx124_wrong->Fill(pt1,xsweight*aweight); is_accepted=true;}
              else if (qual1>=1) {h_stub4_bx124_wrong_fail->Fill(pt1,xsweight*aweight); is_accepted=true;}
           }
        }

	//if (nstub1==4 and (bxspread1==4320 or bxspread1==4310 or bxspread1==4210)) cout<<"1: "<<bxspread1<<" "<<qual1<<" "<<bxspread2<<endl;
	//if (nstub2==4 and (bxspread2==4320 or bxspread2==4310 or bxspread2==4210)) cout<<"2: "<<bxspread2<<" "<<qual2<<" "<<bxspread1<<endl;
	//if (bxspread1==0) cout<<bxspread2<<endl;

	bool is_1245_1 = (nstub1==4 and (bxspread1==4320 or bxspread1==4310 or bxspread1==4210 or bxspread1==4012 or bxspread1==4021 or bxspread1==4013 or bxspread1==4031 or bxspread1==4023 or bxspread1==4032 or bxspread1==4102 or bxspread1==4120 or bxspread1==4103 or bxspread1==4130 or bxspread1==4201 or bxspread1==4203 or bxspread1==4230 or bxspread1==4301 or bxspread1==4302 or (bxspread1==3420 or bxspread1==3240 or bxspread1==3410 or bxspread1==3140 or bxspread1==2340 or bxspread1==2430 or bxspread1==2140 or bxspread1==2410 or bxspread1==1340 or bxspread1==1430 or bxspread1==1240 or bxspread1==1420)));
        if (is_1245_1){
           if (bxspread1==4320 or bxspread1==4310 or bxspread1==4210){
              if (qual1>=15) {h_stub4_bx1245->Fill(pt1,xsweight*aweight); is_accepted=true;}
              else if (qual1>=1) {h_stub4_bx1245_fail->Fill(pt1,xsweight*aweight); is_accepted=true;}
           }
           else{
              if (qual1>=15) {h_stub4_bx1245_wrong->Fill(pt1,xsweight*aweight); is_accepted=true;}
              else if (qual1>=1) {h_stub4_bx1245_wrong_fail->Fill(pt1,xsweight*aweight); is_accepted=true;}
           }
        }


	bool is_124_3stubs_1 = (nstub1==3 and (bxspread1==3200 or bxspread1==3100 or bxspread1==3020 or bxspread1==3010 or (bxspread1==2300 or bxspread1==1300)));
        if (is_124_3stubs_1){
           if (bxspread1==3200 or bxspread1==3100){
              if (qual1>=14) {h_stub3_bx124->Fill(pt1,xsweight*aweight); is_accepted=true;}
              else {h_stub3_bx124_fail->Fill(pt1,xsweight*aweight); is_accepted=true;}
           }
           else{
              if (qual1>=14) {h_stub3_bx124_wrong->Fill(pt1,xsweight*aweight); is_accepted=true;}
              else {h_stub3_bx124_wrong_fail->Fill(pt1,xsweight*aweight); is_accepted=true;}
           }
        }

	//################ Across 2 BX ################

        bool is_1122_4stubs_1 = (nstub1==4 and (bxspread1==1100 or bxspread1==1001 or bxspread1==1010 or (bxspread1==110)));
        if (is_1122_4stubs_1){
           if (bxspread1==1100){
              if (qual1>=15) {h_stub4_bx1122->Fill(pt1,xsweight*aweight); is_accepted=true;}
              else if (qual1>=1) {h_stub4_bx1122_fail->Fill(pt1,xsweight*aweight); is_accepted=true;}
           }
           else{
              if (qual1>=15) {h_stub4_bx1122_wrong->Fill(pt1,xsweight*aweight); is_accepted=true;}
              else if (qual1>=1) {h_stub4_bx1122_wrong_fail->Fill(pt1,xsweight*aweight); is_accepted=true;}
           }
        }

	bool is_1112_4stubs_1 = (nstub1==4 and (bxspread1==1000 or bxspread1==100)); //FIXME
        if (is_1112_4stubs_1){
           if (bxspread1==1000){
              if (qual1>=15) {h_stub4_bx1112->Fill(pt1,xsweight*aweight); is_accepted=true;}
              else if (qual1>=1) {h_stub4_bx1112_fail->Fill(pt1,xsweight*aweight); is_accepted=true;}
           }
           else{
              if (qual1>=15) {h_stub4_bx1112_wrong->Fill(pt1,xsweight*aweight); is_accepted=true;}
              else if (qual1>=1) {h_stub4_bx1112_wrong_fail->Fill(pt1,xsweight*aweight); is_accepted=true;}
           }
        }

	bool is_1222_4stubs_1 = (nstub1==4 and (bxspread1==1110 or bxspread1==1011 or bxspread1==1101));
        if (is_1222_4stubs_1){
           if (bxspread1==1110){
              if (qual1>=15) {h_stub4_bx1222->Fill(pt1,xsweight*aweight); is_accepted=true;}
              else if (qual1>=1) {h_stub4_bx1222_fail->Fill(pt1,xsweight*aweight); is_accepted=true;} //FIXME added min qual
           }
           else{
              if (qual1>=15) {h_stub4_bx1222_wrong->Fill(pt1,xsweight*aweight); is_accepted=true;}
              else if (qual1>=1) {h_stub4_bx1222_wrong_fail->Fill(pt1,xsweight*aweight); is_accepted=true;} // FIXME added min qual
           }
        }

	bool is_112_3stubs_1 = (nstub1==3 and (bxspread1==1000 or bxspread1==100));
        if (is_112_3stubs_1){
           if (bxspread1==1000){
              if (qual1>=14) {h_stub3_bx112->Fill(pt1,xsweight*aweight); is_accepted=true;}
              else {h_stub3_bx112_fail->Fill(pt1,xsweight*aweight); is_accepted=true;}
           }
           else{
              if (qual1>=14) {h_stub3_bx112_wrong->Fill(pt1,xsweight*aweight); is_accepted=true;}
              else {h_stub3_bx112_wrong_fail->Fill(pt1,xsweight*aweight); is_accepted=true;}
           }
        }

	bool is_122_3stubs_1 = (nstub1==3 and (bxspread1==1100 or bxspread1==1010));
        if (is_122_3stubs_1){
           if (bxspread1==1100){
              if (qual1>=14) {h_stub3_bx122->Fill(pt1,xsweight*aweight); is_accepted=true;}
              else {h_stub3_bx122_fail->Fill(pt1,xsweight*aweight); is_accepted=true;}
           }
           else{
              if (qual1>=14) {h_stub3_bx122_wrong->Fill(pt1,xsweight*aweight); is_accepted=true;}
              else {h_stub3_bx122_wrong_fail->Fill(pt1,xsweight*aweight); is_accepted=true;}
           }
        }

	bool is_12_2stubs_1 = (nstub1==2 and (bxspread1==1000 or bxspread1==100) and stationspread1!=2100);
	//if (nstub1==2 and bxspread1==1000 and qual1>=13) cout<<qual1<<" "<<stationspread1<<endl;
        if (is_12_2stubs_1){
           if (bxspread1==1000){
              if (qual1>=13) {h_stub2_bx12->Fill(pt1,xsweight*aweight); is_accepted=true;}
              else {h_stub2_bx12_fail->Fill(pt1,xsweight*aweight); is_accepted=true;}
           }
           else{
              if (qual1>=13) {h_stub2_bx12_wrong->Fill(pt1,xsweight*aweight); is_accepted=true;}
              else {h_stub2_bx12_wrong_fail->Fill(pt1,xsweight*aweight); is_accepted=true;}
           }
        }

	bool is_12_2stubs_station12_1 = (nstub1==2 and (bxspread1==1000 or bxspread1==100) and stationspread1==2100);
        if (is_12_2stubs_station12_1){
           if (bxspread1==1000){
              if (qual1>=13) {h_stub2_bx12_station12->Fill(pt1,xsweight*aweight); is_accepted=true;}
              else {h_stub2_bx12_station12_fail->Fill(pt1,xsweight*aweight); is_accepted=true;}
           }
           else{
              if (qual1>=13) {h_stub2_bx12_station12_wrong->Fill(pt1,xsweight*aweight); is_accepted=true;}
              else {h_stub2_bx12_station12_wrong_fail->Fill(pt1,xsweight*aweight); is_accepted=true;}
           }
        }

	//################# Same BX ###################
	bool is_samebx_metm1_1 = (is_cat1 and bxspread1==0 and pt1>500);
	if (is_samebx_metm1_1){
	   if (pass_quality_1) {h_samebx_metm1->Fill(metm1,xsweight*aweight); is_accepted=true;}
	   else {h_samebx_metm1_fail->Fill(metm1,xsweight*aweight); is_accepted=true;}
	}

	bool is_samebx_metm2_1 = (is_cat2 and bxspread1==0 and pt1>500);
        if (is_samebx_metm2_1){
           if (pass_quality_1) h_samebx_metm2->Fill(metm2,xsweight*aweight);
           else h_samebx_metm2_fail->Fill(metm2,xsweight*aweight);
	   is_accepted=true;
        }

	bool is_samebx_metm3_1 = (is_cat3 and bxspread1==0 and pt1>500);
        if (is_samebx_metm3_1){
           if (pass_quality_1) h_samebx_metm3->Fill(metm3,xsweight*aweight);
           else h_samebx_metm3_fail->Fill(metm3,xsweight*aweight);
	   is_accepted=true;
        }

	bool is_samebx_metm4_1 = (is_cat4 and bxspread1==0 and pt1>500);
        if (is_samebx_metm4_1){
           if (pass_quality_1) h_samebx_metm4->Fill(metm4,xsweight*aweight);
           else h_samebx_metm4_fail->Fill(metm4,xsweight*aweight);
	   is_accepted=true;
        }


	bool is_stub2bx12_metm1_1 = (is_cat1 and bxspread1==1000 and nstub1==2 and pt1>500);
        if (is_stub2bx12_metm1_1){
           if (pass_quality_1) {h_stub2bx12_metm1->Fill(metm1,xsweight*aweight); is_accepted=true;}
           else {h_stub2bx12_metm1_fail->Fill(metm1,xsweight*aweight); is_accepted=true;}
        }

        bool is_stub2bx12_metm2_1 = (is_cat2 and bxspread1==1000 and nstub1==2 and pt1>500);
        if (is_stub2bx12_metm2_1){
           if (pass_quality_1) h_stub2bx12_metm2->Fill(metm2,xsweight*aweight);
           else h_stub2bx12_metm2_fail->Fill(metm2,xsweight*aweight);
           is_accepted=true;
        }

        bool is_stub2bx12_metm3_1 = (is_cat3 and bxspread1==1000 and nstub1==2 and pt1>500);
        if (is_stub2bx12_metm3_1){
           if (pass_quality_1) h_stub2bx12_metm3->Fill(metm3,xsweight*aweight);
           else h_stub2bx12_metm3_fail->Fill(metm3,xsweight*aweight);
           is_accepted=true;
        }

        bool is_stub2bx12_metm4_1 = (is_cat4 and bxspread1==1000 and nstub1==2 and pt1>500);
        if (is_stub2bx12_metm4_1){
           if (pass_quality_1) h_stub2bx12_metm4->Fill(metm4,xsweight*aweight);
           else h_stub2bx12_metm4_fail->Fill(metm4,xsweight*aweight);
           is_accepted=true;
        }

	//if (!is_accepted) cout<<is_accepted<<" "<<bxspread1<<" "<<firstbx1<<" "<<nstub1<<endl;


    } // end of loop over events

    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();

    h_metbx0_mu0->Write();
    h_metbxm1_mu0->Write();
    h_metbxm2_mu0->Write();
    h_metbxm3_mu0->Write();
    h_metbxm4_mu0->Write();
    h_metbxm5_mu0->Write();
    h_metbx0_mu0fail->Write();
    h_metbxm1_mu0fail->Write();
    h_metbxm2_mu0fail->Write();
    h_metbxm3_mu0fail->Write();
    h_metbxm4_mu0fail->Write();
    h_metbxm5_mu0fail->Write();

    h_metbxm1_mu01->Write();
    h_metbxm1_mu01fail->Write();

    h_qual_nstub2->Write();
    h_qual_nstub3->Write();
    h_qual_nstub4->Write();
    h_dxy->Write();
    h_nstub->Write();

    h_spread0->Write();
    h_spread1->Write();
    h_spread2->Write();

    h_spread1_met1->Write();
    h_spread2_met1->Write();

    h_spread1_met2->Write();
    h_spread2_met2->Write();

    /*TDirectory* dir1=fout->mkdir("stub4_bx1234");
    dir1->cd();
    h_stub4_bx1234->SetName(name.c_str());
    h_stub4_bx1234->Write();*/

    WriteHistToFile(fout,h_stub4_bx1234,name,"stub4_bx1234");
    WriteHistToFile(fout,h_stub4_bx1234_wrong,name,"stub4_bx1234_wrong");
    WriteHistToFile(fout,h_stub4_bx1234_fail,name,"stub4_bx1234_fail");
    WriteHistToFile(fout,h_stub4_bx1234_wrong_fail,name,"stub4_bx1234_wrong_fail");

    WriteHistToFile(fout,h_stub3_bx123_slow,name,"stub3_bx123_slow");
    WriteHistToFile(fout,h_stub3_bx123_slow_wrong,name,"stub3_bx123_slow_wrong");
    WriteHistToFile(fout,h_stub3_bx123_slow_fail,name,"stub3_bx123_slow_fail");
    WriteHistToFile(fout,h_stub3_bx123_slow_wrong_fail,name,"stub3_bx123_slow_wrong_fail");

    WriteHistToFile(fout,h_stub3_bx123_fast,name,"stub3_bx123_fast");
    WriteHistToFile(fout,h_stub3_bx123_fast_wrong,name,"stub3_bx123_fast_wrong");
    WriteHistToFile(fout,h_stub3_bx123_fast_fail,name,"stub3_bx123_fast_fail");
    WriteHistToFile(fout,h_stub3_bx123_fast_wrong_fail,name,"stub3_bx123_fast_wrong_fail");

    WriteHistToFile(fout,h_stub4_bx123,name,"stub4_bx123");
    WriteHistToFile(fout,h_stub4_bx123_wrong,name,"stub4_bx123_wrong");
    WriteHistToFile(fout,h_stub4_bx123_fail,name,"stub4_bx123_fail");
    WriteHistToFile(fout,h_stub4_bx123_wrong_fail,name,"stub4_bx123_wrong_fail");

    WriteHistToFile(fout,h_stub4_bx1245,name,"stub4_bx1245");
    WriteHistToFile(fout,h_stub4_bx1245_wrong,name,"stub4_bx1245_wrong");
    WriteHistToFile(fout,h_stub4_bx1245_fail,name,"stub4_bx1245_fail");
    WriteHistToFile(fout,h_stub4_bx1245_wrong_fail,name,"stub4_bx1245_wrong_fail");

    WriteHistToFile(fout,h_stub3_bx124,name,"stub3_bx124");
    WriteHistToFile(fout,h_stub3_bx124_wrong,name,"stub3_bx124_wrong");
    WriteHistToFile(fout,h_stub3_bx124_fail,name,"stub3_bx124_fail");
    WriteHistToFile(fout,h_stub3_bx124_wrong_fail,name,"stub3_bx124_wrong_fail");

    WriteHistToFile(fout,h_stub4_bx124,name,"stub4_bx124");
    WriteHistToFile(fout,h_stub4_bx124_wrong,name,"stub4_bx124_wrong");
    WriteHistToFile(fout,h_stub4_bx124_fail,name,"stub4_bx124_fail");
    WriteHistToFile(fout,h_stub4_bx124_wrong_fail,name,"stub4_bx124_wrong_fail");

    WriteHistToFile(fout,h_stub2_bx12,name,"stub2_bx12");
    WriteHistToFile(fout,h_stub2_bx12_wrong,name,"stub2_bx12_wrong");
    WriteHistToFile(fout,h_stub2_bx12_fail,name,"stub2_bx12_fail");
    WriteHistToFile(fout,h_stub2_bx12_wrong_fail,name,"stub2_bx12_wrong_fail");

    WriteHistToFile(fout,h_stub2_bx12_station12,name,"stub2_bx12_station12");
    WriteHistToFile(fout,h_stub2_bx12_station12_wrong,name,"stub2_bx12_station12_wrong");
    WriteHistToFile(fout,h_stub2_bx12_station12_fail,name,"stub2_bx12_station12_fail");
    WriteHistToFile(fout,h_stub2_bx12_station12_wrong_fail,name,"stub2_bx12_station12_wrong_fail");

    WriteHistToFile(fout,h_stub3_bx112,name,"stub3_bx112");
    WriteHistToFile(fout,h_stub3_bx112_wrong,name,"stub3_bx112_wrong");
    WriteHistToFile(fout,h_stub3_bx112_fail,name,"stub3_bx112_fail");
    WriteHistToFile(fout,h_stub3_bx112_wrong_fail,name,"stub3_bx112_wrong_fail");

    WriteHistToFile(fout,h_stub3_bx122,name,"stub3_bx122");
    WriteHistToFile(fout,h_stub3_bx122_wrong,name,"stub3_bx122_wrong");
    WriteHistToFile(fout,h_stub3_bx122_fail,name,"stub3_bx122_fail");
    WriteHistToFile(fout,h_stub3_bx122_wrong_fail,name,"stub3_bx122_wrong_fail");

    WriteHistToFile(fout,h_stub4_bx1122,name,"stub4_bx1122");
    WriteHistToFile(fout,h_stub4_bx1122_wrong,name,"stub4_bx1122_wrong");
    WriteHistToFile(fout,h_stub4_bx1122_fail,name,"stub4_bx1122_fail");
    WriteHistToFile(fout,h_stub4_bx1122_wrong_fail,name,"stub4_bx1122_wrong_fail");

    WriteHistToFile(fout,h_stub4_bx1112,name,"stub4_bx1112");
    WriteHistToFile(fout,h_stub4_bx1112_wrong,name,"stub4_bx1112_wrong");
    WriteHistToFile(fout,h_stub4_bx1112_fail,name,"stub4_bx1112_fail");
    WriteHistToFile(fout,h_stub4_bx1112_wrong_fail,name,"stub4_bx1112_wrong_fail");

    WriteHistToFile(fout,h_stub4_bx1222,name,"stub4_bx1222");
    WriteHistToFile(fout,h_stub4_bx1222_wrong,name,"stub4_bx1222_wrong");
    WriteHistToFile(fout,h_stub4_bx1222_fail,name,"stub4_bx1222_fail");
    WriteHistToFile(fout,h_stub4_bx1222_wrong_fail,name,"stub4_bx1222_wrong_fail");

    /////////////////////////////////////////////////////////////////
    
    WriteHistToFile(fout,h_samebx_metm1,name,"samebx_metm1");
    WriteHistToFile(fout,h_samebx_metm1_fail,name,"samebx_metm1_fail");

    WriteHistToFile(fout,h_samebx_metm2,name,"samebx_metm2");
    WriteHistToFile(fout,h_samebx_metm2_fail,name,"samebx_metm2_fail");

    WriteHistToFile(fout,h_samebx_metm3,name,"samebx_metm3");
    WriteHistToFile(fout,h_samebx_metm3_fail,name,"samebx_metm3_fail");

    WriteHistToFile(fout,h_samebx_metm4,name,"samebx_metm4");
    WriteHistToFile(fout,h_samebx_metm4_fail,name,"samebx_metm4_fail");

    WriteHistToFile(fout,h_stub2bx12_metm1,name,"stub2bx12_metm1");
    WriteHistToFile(fout,h_stub2bx12_metm1_fail,name,"stub2bx12_metm1_fail");

    WriteHistToFile(fout,h_stub2bx12_metm2,name,"stub2bx12_metm2");
    WriteHistToFile(fout,h_stub2bx12_metm2_fail,name,"stub2bx12_metm2_fail");

    WriteHistToFile(fout,h_stub2bx12_metm3,name,"stub2bx12_metm3");
    WriteHistToFile(fout,h_stub2bx12_metm3_fail,name,"stub2bx12_metm3_fail");

    WriteHistToFile(fout,h_stub2bx12_metm4,name,"stub2bx12_metm4");
    WriteHistToFile(fout,h_stub2bx12_metm4_fail,name,"stub2bx12_metm4_fail");
    
    fout->Close();
}

