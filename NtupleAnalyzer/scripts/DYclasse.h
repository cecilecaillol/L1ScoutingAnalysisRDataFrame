//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jan 23 09:26:15 2025 by ROOT version 6.30/03
// from TTree Events/Events
// found on file: /afs/cern.ch/work/c/ccaillol/KBMTFemulation/CMSSW_14_0_12/src/L1TriggerScouting/Utilities/python/DY_nano.root
//////////////////////////////////////////////////////////

#ifndef DYclasse_h
#define DYclasse_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class DYclasse {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          run;
   UInt_t          luminosityBlock;
   ULong64_t       event;
   UInt_t          bunchCrossing;
   UInt_t          orbitNumber;
   Int_t           nGen;
   Short_t         Gen_pdgid[919];   //[nGen]
   Short_t         Gen_charge[919];   //[nGen]
   Float_t         Gen_pt[919];   //[nGen]
   Float_t         Gen_eta[919];   //[nGen]
   Float_t         Gen_phi[919];   //[nGen]
   Float_t         Gen_beta[919];   //[nGen]
   Int_t           nHLT;
   Int_t           HLT_IsoMu24[1];   //[nHLT]
   Int_t           nL1KBMTFOff;
   Short_t         L1KBMTFOff_hwCharge[6];   //[nL1KBMTFOff]
   Short_t         L1KBMTFOff_hwQual[6];   //[nL1KBMTFOff]
   Short_t         L1KBMTFOff_hwDXY[6];   //[nL1KBMTFOff]
   Short_t         L1KBMTFOff_processor[6];   //[nL1KBMTFOff]
   Short_t         L1KBMTFOff_nStub[6];   //[nL1KBMTFOff]
   Short_t         L1KBMTFOff_s1Station[6];   //[nL1KBMTFOff]
   Short_t         L1KBMTFOff_s1Sector[6];   //[nL1KBMTFOff]
   Short_t         L1KBMTFOff_s1Wheel[6];   //[nL1KBMTFOff]
   Short_t         L1KBMTFOff_s1Bx[6];   //[nL1KBMTFOff]
   Short_t         L1KBMTFOff_s2Station[6];   //[nL1KBMTFOff]
   Short_t         L1KBMTFOff_s2Sector[6];   //[nL1KBMTFOff]
   Short_t         L1KBMTFOff_s2Wheel[6];   //[nL1KBMTFOff]
   Short_t         L1KBMTFOff_s2Bx[6];   //[nL1KBMTFOff]
   Short_t         L1KBMTFOff_s3Station[6];   //[nL1KBMTFOff]
   Short_t         L1KBMTFOff_s3Sector[6];   //[nL1KBMTFOff]
   Short_t         L1KBMTFOff_s3Wheel[6];   //[nL1KBMTFOff]
   Short_t         L1KBMTFOff_s3Bx[6];   //[nL1KBMTFOff]
   Short_t         L1KBMTFOff_s4Station[6];   //[nL1KBMTFOff]
   Short_t         L1KBMTFOff_s4Sector[6];   //[nL1KBMTFOff]
   Short_t         L1KBMTFOff_s4Wheel[6];   //[nL1KBMTFOff]
   Short_t         L1KBMTFOff_s4Bx[6];   //[nL1KBMTFOff]
   Float_t         L1KBMTFOff_pt[6];   //[nL1KBMTFOff]
   Float_t         L1KBMTFOff_eta[6];   //[nL1KBMTFOff]
   Float_t         L1KBMTFOff_phi[6];   //[nL1KBMTFOff]
   Float_t         L1KBMTFOff_ptUnconstrained[6];   //[nL1KBMTFOff]
   Float_t         L1KBMTFOff_etaAtVtx[6];   //[nL1KBMTFOff]
   Float_t         L1KBMTFOff_phiAtVtx[6];   //[nL1KBMTFOff]
   Int_t           nL1KBMTFSkimmed;
   Short_t         L1KBMTFSkimmed_hwCharge[6];   //[nL1KBMTFSkimmed]
   Short_t         L1KBMTFSkimmed_hwQual[6];   //[nL1KBMTFSkimmed]
   Short_t         L1KBMTFSkimmed_hwDXY[6];   //[nL1KBMTFSkimmed]
   Short_t         L1KBMTFSkimmed_processor[6];   //[nL1KBMTFSkimmed]
   Short_t         L1KBMTFSkimmed_nStub[6];   //[nL1KBMTFSkimmed]
   Short_t         L1KBMTFSkimmed_s1Station[6];   //[nL1KBMTFSkimmed]
   Short_t         L1KBMTFSkimmed_s1Sector[6];   //[nL1KBMTFSkimmed]
   Short_t         L1KBMTFSkimmed_s1Wheel[6];   //[nL1KBMTFSkimmed]
   Short_t         L1KBMTFSkimmed_s1Bx[6];   //[nL1KBMTFSkimmed]
   Short_t         L1KBMTFSkimmed_s2Station[6];   //[nL1KBMTFSkimmed]
   Short_t         L1KBMTFSkimmed_s2Sector[6];   //[nL1KBMTFSkimmed]
   Short_t         L1KBMTFSkimmed_s2Wheel[6];   //[nL1KBMTFSkimmed]
   Short_t         L1KBMTFSkimmed_s2Bx[6];   //[nL1KBMTFSkimmed]
   Short_t         L1KBMTFSkimmed_s3Station[6];   //[nL1KBMTFSkimmed]
   Short_t         L1KBMTFSkimmed_s3Sector[6];   //[nL1KBMTFSkimmed]
   Short_t         L1KBMTFSkimmed_s3Wheel[6];   //[nL1KBMTFSkimmed]
   Short_t         L1KBMTFSkimmed_s3Bx[6];   //[nL1KBMTFSkimmed]
   Short_t         L1KBMTFSkimmed_s4Station[6];   //[nL1KBMTFSkimmed]
   Short_t         L1KBMTFSkimmed_s4Sector[6];   //[nL1KBMTFSkimmed]
   Short_t         L1KBMTFSkimmed_s4Wheel[6];   //[nL1KBMTFSkimmed]
   Short_t         L1KBMTFSkimmed_s4Bx[6];   //[nL1KBMTFSkimmed]
   Float_t         L1KBMTFSkimmed_pt[6];   //[nL1KBMTFSkimmed]
   Float_t         L1KBMTFSkimmed_eta[6];   //[nL1KBMTFSkimmed]
   Float_t         L1KBMTFSkimmed_phi[6];   //[nL1KBMTFSkimmed]
   Float_t         L1KBMTFSkimmed_ptUnconstrained[6];   //[nL1KBMTFSkimmed]
   Float_t         L1KBMTFSkimmed_etaAtVtx[6];   //[nL1KBMTFSkimmed]
   Float_t         L1KBMTFSkimmed_phiAtVtx[6];   //[nL1KBMTFSkimmed]
   Int_t           nSkimmedL1Mu;
   Short_t         SkimmedL1Mu_hwCharge[4];   //[nSkimmedL1Mu]
   Short_t         SkimmedL1Mu_hwQual[4];   //[nSkimmedL1Mu]
   Short_t         SkimmedL1Mu_hwDXY[4];   //[nSkimmedL1Mu]
   Short_t         SkimmedL1Mu_processor[4];   //[nSkimmedL1Mu]
   Float_t         SkimmedL1Mu_pt[4];   //[nSkimmedL1Mu]
   Float_t         SkimmedL1Mu_eta[4];   //[nSkimmedL1Mu]
   Float_t         SkimmedL1Mu_phi[4];   //[nSkimmedL1Mu]
   Float_t         SkimmedL1Mu_ptUnconstrained[4];   //[nSkimmedL1Mu]
   Float_t         SkimmedL1Mu_etaAtVtx[4];   //[nSkimmedL1Mu]
   Float_t         SkimmedL1Mu_phiAtVtx[4];   //[nSkimmedL1Mu]
   Int_t           nL1Stubs;
   Short_t         L1Stubs_phi[15];   //[nL1Stubs]
   Short_t         L1Stubs_phiB[15];   //[nL1Stubs]
   Short_t         L1Stubs_qual[15];   //[nL1Stubs]
   Short_t         L1Stubs_eta[15];   //[nL1Stubs]
   Short_t         L1Stubs_qeta[15];   //[nL1Stubs]
   Short_t         L1Stubs_station[15];   //[nL1Stubs]
   Short_t         L1Stubs_wheel[15];   //[nL1Stubs]
   Short_t         L1Stubs_sector[15];   //[nL1Stubs]
   Short_t         L1Stubs_tag[15];   //[nL1Stubs]
   Short_t         L1Stubs_bx[15];   //[nL1Stubs]
   Int_t           nTriggerObjects;
   Float_t         TriggerObjects_pt[3];   //[nTriggerObjects]
   Float_t         TriggerObjects_eta[3];   //[nTriggerObjects]
   Float_t         TriggerObjects_phi[3];   //[nTriggerObjects]

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_luminosityBlock;   //!
   TBranch        *b_event;   //!
   TBranch        *b_bunchCrossing;   //!
   TBranch        *b_orbitNumber;   //!
   TBranch        *b_nGen;   //!
   TBranch        *b_Gen_pdgid;   //!
   TBranch        *b_Gen_charge;   //!
   TBranch        *b_Gen_pt;   //!
   TBranch        *b_Gen_eta;   //!
   TBranch        *b_Gen_phi;   //!
   TBranch        *b_Gen_beta;   //!
   TBranch        *b_nHLT;   //!
   TBranch        *b_HLT_IsoMu24;   //!
   TBranch        *b_nL1KBMTFOff;   //!
   TBranch        *b_L1KBMTFOff_hwCharge;   //!
   TBranch        *b_L1KBMTFOff_hwQual;   //!
   TBranch        *b_L1KBMTFOff_hwDXY;   //!
   TBranch        *b_L1KBMTFOff_processor;   //!
   TBranch        *b_L1KBMTFOff_nStub;   //!
   TBranch        *b_L1KBMTFOff_s1Station;   //!
   TBranch        *b_L1KBMTFOff_s1Sector;   //!
   TBranch        *b_L1KBMTFOff_s1Wheel;   //!
   TBranch        *b_L1KBMTFOff_s1Bx;   //!
   TBranch        *b_L1KBMTFOff_s2Station;   //!
   TBranch        *b_L1KBMTFOff_s2Sector;   //!
   TBranch        *b_L1KBMTFOff_s2Wheel;   //!
   TBranch        *b_L1KBMTFOff_s2Bx;   //!
   TBranch        *b_L1KBMTFOff_s3Station;   //!
   TBranch        *b_L1KBMTFOff_s3Sector;   //!
   TBranch        *b_L1KBMTFOff_s3Wheel;   //!
   TBranch        *b_L1KBMTFOff_s3Bx;   //!
   TBranch        *b_L1KBMTFOff_s4Station;   //!
   TBranch        *b_L1KBMTFOff_s4Sector;   //!
   TBranch        *b_L1KBMTFOff_s4Wheel;   //!
   TBranch        *b_L1KBMTFOff_s4Bx;   //!
   TBranch        *b_L1KBMTFOff_pt;   //!
   TBranch        *b_L1KBMTFOff_eta;   //!
   TBranch        *b_L1KBMTFOff_phi;   //!
   TBranch        *b_L1KBMTFOff_ptUnconstrained;   //!
   TBranch        *b_L1KBMTFOff_etaAtVtx;   //!
   TBranch        *b_L1KBMTFOff_phiAtVtx;   //!
   TBranch        *b_nL1KBMTFSkimmed;   //!
   TBranch        *b_L1KBMTFSkimmed_hwCharge;   //!
   TBranch        *b_L1KBMTFSkimmed_hwQual;   //!
   TBranch        *b_L1KBMTFSkimmed_hwDXY;   //!
   TBranch        *b_L1KBMTFSkimmed_processor;   //!
   TBranch        *b_L1KBMTFSkimmed_nStub;   //!
   TBranch        *b_L1KBMTFSkimmed_s1Station;   //!
   TBranch        *b_L1KBMTFSkimmed_s1Sector;   //!
   TBranch        *b_L1KBMTFSkimmed_s1Wheel;   //!
   TBranch        *b_L1KBMTFSkimmed_s1Bx;   //!
   TBranch        *b_L1KBMTFSkimmed_s2Station;   //!
   TBranch        *b_L1KBMTFSkimmed_s2Sector;   //!
   TBranch        *b_L1KBMTFSkimmed_s2Wheel;   //!
   TBranch        *b_L1KBMTFSkimmed_s2Bx;   //!
   TBranch        *b_L1KBMTFSkimmed_s3Station;   //!
   TBranch        *b_L1KBMTFSkimmed_s3Sector;   //!
   TBranch        *b_L1KBMTFSkimmed_s3Wheel;   //!
   TBranch        *b_L1KBMTFSkimmed_s3Bx;   //!
   TBranch        *b_L1KBMTFSkimmed_s4Station;   //!
   TBranch        *b_L1KBMTFSkimmed_s4Sector;   //!
   TBranch        *b_L1KBMTFSkimmed_s4Wheel;   //!
   TBranch        *b_L1KBMTFSkimmed_s4Bx;   //!
   TBranch        *b_L1KBMTFSkimmed_pt;   //!
   TBranch        *b_L1KBMTFSkimmed_eta;   //!
   TBranch        *b_L1KBMTFSkimmed_phi;   //!
   TBranch        *b_L1KBMTFSkimmed_ptUnconstrained;   //!
   TBranch        *b_L1KBMTFSkimmed_etaAtVtx;   //!
   TBranch        *b_L1KBMTFSkimmed_phiAtVtx;   //!
   TBranch        *b_nSkimmedL1Mu;   //!
   TBranch        *b_SkimmedL1Mu_hwCharge;   //!
   TBranch        *b_SkimmedL1Mu_hwQual;   //!
   TBranch        *b_SkimmedL1Mu_hwDXY;   //!
   TBranch        *b_SkimmedL1Mu_processor;   //!
   TBranch        *b_SkimmedL1Mu_pt;   //!
   TBranch        *b_SkimmedL1Mu_eta;   //!
   TBranch        *b_SkimmedL1Mu_phi;   //!
   TBranch        *b_SkimmedL1Mu_ptUnconstrained;   //!
   TBranch        *b_SkimmedL1Mu_etaAtVtx;   //!
   TBranch        *b_SkimmedL1Mu_phiAtVtx;   //!
   TBranch        *b_nL1Stubs;   //!
   TBranch        *b_L1Stubs_phi;   //!
   TBranch        *b_L1Stubs_phiB;   //!
   TBranch        *b_L1Stubs_qual;   //!
   TBranch        *b_L1Stubs_eta;   //!
   TBranch        *b_L1Stubs_qeta;   //!
   TBranch        *b_L1Stubs_station;   //!
   TBranch        *b_L1Stubs_wheel;   //!
   TBranch        *b_L1Stubs_sector;   //!
   TBranch        *b_L1Stubs_tag;   //!
   TBranch        *b_L1Stubs_bx;   //!
   TBranch        *b_nTriggerObjects;   //!
   TBranch        *b_TriggerObjects_pt;   //!
   TBranch        *b_TriggerObjects_eta;   //!
   TBranch        *b_TriggerObjects_phi;   //!

   DYclasse(TTree *tree=0);
   virtual ~DYclasse();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef DYclasse_cxx
DYclasse::DYclasse(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/afs/cern.ch/work/c/ccaillol/KBMTFemulation/CMSSW_14_0_12/src/L1TriggerScouting/Utilities/python/DY_nano.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/afs/cern.ch/work/c/ccaillol/KBMTFemulation/CMSSW_14_0_12/src/L1TriggerScouting/Utilities/python/DY_nano.root");
      }
      f->GetObject("Events",tree);

   }
   Init(tree);
}

DYclasse::~DYclasse()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t DYclasse::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t DYclasse::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void DYclasse::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("luminosityBlock", &luminosityBlock, &b_luminosityBlock);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("bunchCrossing", &bunchCrossing, &b_bunchCrossing);
   fChain->SetBranchAddress("orbitNumber", &orbitNumber, &b_orbitNumber);
   fChain->SetBranchAddress("nGen", &nGen, &b_nGen);
   fChain->SetBranchAddress("Gen_pdgid", Gen_pdgid, &b_Gen_pdgid);
   fChain->SetBranchAddress("Gen_charge", Gen_charge, &b_Gen_charge);
   fChain->SetBranchAddress("Gen_pt", Gen_pt, &b_Gen_pt);
   fChain->SetBranchAddress("Gen_eta", Gen_eta, &b_Gen_eta);
   fChain->SetBranchAddress("Gen_phi", Gen_phi, &b_Gen_phi);
   fChain->SetBranchAddress("Gen_beta", Gen_beta, &b_Gen_beta);
   fChain->SetBranchAddress("nHLT", &nHLT, &b_nHLT);
   fChain->SetBranchAddress("HLT_IsoMu24", HLT_IsoMu24, &b_HLT_IsoMu24);
   fChain->SetBranchAddress("nL1KBMTFOff", &nL1KBMTFOff, &b_nL1KBMTFOff);
   fChain->SetBranchAddress("L1KBMTFOff_hwCharge", L1KBMTFOff_hwCharge, &b_L1KBMTFOff_hwCharge);
   fChain->SetBranchAddress("L1KBMTFOff_hwQual", L1KBMTFOff_hwQual, &b_L1KBMTFOff_hwQual);
   fChain->SetBranchAddress("L1KBMTFOff_hwDXY", L1KBMTFOff_hwDXY, &b_L1KBMTFOff_hwDXY);
   fChain->SetBranchAddress("L1KBMTFOff_processor", L1KBMTFOff_processor, &b_L1KBMTFOff_processor);
   fChain->SetBranchAddress("L1KBMTFOff_nStub", L1KBMTFOff_nStub, &b_L1KBMTFOff_nStub);
   fChain->SetBranchAddress("L1KBMTFOff_s1Station", L1KBMTFOff_s1Station, &b_L1KBMTFOff_s1Station);
   fChain->SetBranchAddress("L1KBMTFOff_s1Sector", L1KBMTFOff_s1Sector, &b_L1KBMTFOff_s1Sector);
   fChain->SetBranchAddress("L1KBMTFOff_s1Wheel", L1KBMTFOff_s1Wheel, &b_L1KBMTFOff_s1Wheel);
   fChain->SetBranchAddress("L1KBMTFOff_s1Bx", L1KBMTFOff_s1Bx, &b_L1KBMTFOff_s1Bx);
   fChain->SetBranchAddress("L1KBMTFOff_s2Station", L1KBMTFOff_s2Station, &b_L1KBMTFOff_s2Station);
   fChain->SetBranchAddress("L1KBMTFOff_s2Sector", L1KBMTFOff_s2Sector, &b_L1KBMTFOff_s2Sector);
   fChain->SetBranchAddress("L1KBMTFOff_s2Wheel", L1KBMTFOff_s2Wheel, &b_L1KBMTFOff_s2Wheel);
   fChain->SetBranchAddress("L1KBMTFOff_s2Bx", L1KBMTFOff_s2Bx, &b_L1KBMTFOff_s2Bx);
   fChain->SetBranchAddress("L1KBMTFOff_s3Station", L1KBMTFOff_s3Station, &b_L1KBMTFOff_s3Station);
   fChain->SetBranchAddress("L1KBMTFOff_s3Sector", L1KBMTFOff_s3Sector, &b_L1KBMTFOff_s3Sector);
   fChain->SetBranchAddress("L1KBMTFOff_s3Wheel", L1KBMTFOff_s3Wheel, &b_L1KBMTFOff_s3Wheel);
   fChain->SetBranchAddress("L1KBMTFOff_s3Bx", L1KBMTFOff_s3Bx, &b_L1KBMTFOff_s3Bx);
   fChain->SetBranchAddress("L1KBMTFOff_s4Station", L1KBMTFOff_s4Station, &b_L1KBMTFOff_s4Station);
   fChain->SetBranchAddress("L1KBMTFOff_s4Sector", L1KBMTFOff_s4Sector, &b_L1KBMTFOff_s4Sector);
   fChain->SetBranchAddress("L1KBMTFOff_s4Wheel", L1KBMTFOff_s4Wheel, &b_L1KBMTFOff_s4Wheel);
   fChain->SetBranchAddress("L1KBMTFOff_s4Bx", L1KBMTFOff_s4Bx, &b_L1KBMTFOff_s4Bx);
   fChain->SetBranchAddress("L1KBMTFOff_pt", L1KBMTFOff_pt, &b_L1KBMTFOff_pt);
   fChain->SetBranchAddress("L1KBMTFOff_eta", L1KBMTFOff_eta, &b_L1KBMTFOff_eta);
   fChain->SetBranchAddress("L1KBMTFOff_phi", L1KBMTFOff_phi, &b_L1KBMTFOff_phi);
   fChain->SetBranchAddress("L1KBMTFOff_ptUnconstrained", L1KBMTFOff_ptUnconstrained, &b_L1KBMTFOff_ptUnconstrained);
   fChain->SetBranchAddress("L1KBMTFOff_etaAtVtx", L1KBMTFOff_etaAtVtx, &b_L1KBMTFOff_etaAtVtx);
   fChain->SetBranchAddress("L1KBMTFOff_phiAtVtx", L1KBMTFOff_phiAtVtx, &b_L1KBMTFOff_phiAtVtx);
   fChain->SetBranchAddress("nL1KBMTFSkimmed", &nL1KBMTFSkimmed, &b_nL1KBMTFSkimmed);
   fChain->SetBranchAddress("L1KBMTFSkimmed_hwCharge", L1KBMTFSkimmed_hwCharge, &b_L1KBMTFSkimmed_hwCharge);
   fChain->SetBranchAddress("L1KBMTFSkimmed_hwQual", L1KBMTFSkimmed_hwQual, &b_L1KBMTFSkimmed_hwQual);
   fChain->SetBranchAddress("L1KBMTFSkimmed_hwDXY", L1KBMTFSkimmed_hwDXY, &b_L1KBMTFSkimmed_hwDXY);
   fChain->SetBranchAddress("L1KBMTFSkimmed_processor", L1KBMTFSkimmed_processor, &b_L1KBMTFSkimmed_processor);
   fChain->SetBranchAddress("L1KBMTFSkimmed_nStub", L1KBMTFSkimmed_nStub, &b_L1KBMTFSkimmed_nStub);
   fChain->SetBranchAddress("L1KBMTFSkimmed_s1Station", L1KBMTFSkimmed_s1Station, &b_L1KBMTFSkimmed_s1Station);
   fChain->SetBranchAddress("L1KBMTFSkimmed_s1Sector", L1KBMTFSkimmed_s1Sector, &b_L1KBMTFSkimmed_s1Sector);
   fChain->SetBranchAddress("L1KBMTFSkimmed_s1Wheel", L1KBMTFSkimmed_s1Wheel, &b_L1KBMTFSkimmed_s1Wheel);
   fChain->SetBranchAddress("L1KBMTFSkimmed_s1Bx", L1KBMTFSkimmed_s1Bx, &b_L1KBMTFSkimmed_s1Bx);
   fChain->SetBranchAddress("L1KBMTFSkimmed_s2Station", L1KBMTFSkimmed_s2Station, &b_L1KBMTFSkimmed_s2Station);
   fChain->SetBranchAddress("L1KBMTFSkimmed_s2Sector", L1KBMTFSkimmed_s2Sector, &b_L1KBMTFSkimmed_s2Sector);
   fChain->SetBranchAddress("L1KBMTFSkimmed_s2Wheel", L1KBMTFSkimmed_s2Wheel, &b_L1KBMTFSkimmed_s2Wheel);
   fChain->SetBranchAddress("L1KBMTFSkimmed_s2Bx", L1KBMTFSkimmed_s2Bx, &b_L1KBMTFSkimmed_s2Bx);
   fChain->SetBranchAddress("L1KBMTFSkimmed_s3Station", L1KBMTFSkimmed_s3Station, &b_L1KBMTFSkimmed_s3Station);
   fChain->SetBranchAddress("L1KBMTFSkimmed_s3Sector", L1KBMTFSkimmed_s3Sector, &b_L1KBMTFSkimmed_s3Sector);
   fChain->SetBranchAddress("L1KBMTFSkimmed_s3Wheel", L1KBMTFSkimmed_s3Wheel, &b_L1KBMTFSkimmed_s3Wheel);
   fChain->SetBranchAddress("L1KBMTFSkimmed_s3Bx", L1KBMTFSkimmed_s3Bx, &b_L1KBMTFSkimmed_s3Bx);
   fChain->SetBranchAddress("L1KBMTFSkimmed_s4Station", L1KBMTFSkimmed_s4Station, &b_L1KBMTFSkimmed_s4Station);
   fChain->SetBranchAddress("L1KBMTFSkimmed_s4Sector", L1KBMTFSkimmed_s4Sector, &b_L1KBMTFSkimmed_s4Sector);
   fChain->SetBranchAddress("L1KBMTFSkimmed_s4Wheel", L1KBMTFSkimmed_s4Wheel, &b_L1KBMTFSkimmed_s4Wheel);
   fChain->SetBranchAddress("L1KBMTFSkimmed_s4Bx", L1KBMTFSkimmed_s4Bx, &b_L1KBMTFSkimmed_s4Bx);
   fChain->SetBranchAddress("L1KBMTFSkimmed_pt", L1KBMTFSkimmed_pt, &b_L1KBMTFSkimmed_pt);
   fChain->SetBranchAddress("L1KBMTFSkimmed_eta", L1KBMTFSkimmed_eta, &b_L1KBMTFSkimmed_eta);
   fChain->SetBranchAddress("L1KBMTFSkimmed_phi", L1KBMTFSkimmed_phi, &b_L1KBMTFSkimmed_phi);
   fChain->SetBranchAddress("L1KBMTFSkimmed_ptUnconstrained", L1KBMTFSkimmed_ptUnconstrained, &b_L1KBMTFSkimmed_ptUnconstrained);
   fChain->SetBranchAddress("L1KBMTFSkimmed_etaAtVtx", L1KBMTFSkimmed_etaAtVtx, &b_L1KBMTFSkimmed_etaAtVtx);
   fChain->SetBranchAddress("L1KBMTFSkimmed_phiAtVtx", L1KBMTFSkimmed_phiAtVtx, &b_L1KBMTFSkimmed_phiAtVtx);
   fChain->SetBranchAddress("nSkimmedL1Mu", &nSkimmedL1Mu, &b_nSkimmedL1Mu);
   fChain->SetBranchAddress("SkimmedL1Mu_hwCharge", SkimmedL1Mu_hwCharge, &b_SkimmedL1Mu_hwCharge);
   fChain->SetBranchAddress("SkimmedL1Mu_hwQual", SkimmedL1Mu_hwQual, &b_SkimmedL1Mu_hwQual);
   fChain->SetBranchAddress("SkimmedL1Mu_hwDXY", SkimmedL1Mu_hwDXY, &b_SkimmedL1Mu_hwDXY);
   fChain->SetBranchAddress("SkimmedL1Mu_processor", SkimmedL1Mu_processor, &b_SkimmedL1Mu_processor);
   fChain->SetBranchAddress("SkimmedL1Mu_pt", SkimmedL1Mu_pt, &b_SkimmedL1Mu_pt);
   fChain->SetBranchAddress("SkimmedL1Mu_eta", SkimmedL1Mu_eta, &b_SkimmedL1Mu_eta);
   fChain->SetBranchAddress("SkimmedL1Mu_phi", SkimmedL1Mu_phi, &b_SkimmedL1Mu_phi);
   fChain->SetBranchAddress("SkimmedL1Mu_ptUnconstrained", SkimmedL1Mu_ptUnconstrained, &b_SkimmedL1Mu_ptUnconstrained);
   fChain->SetBranchAddress("SkimmedL1Mu_etaAtVtx", SkimmedL1Mu_etaAtVtx, &b_SkimmedL1Mu_etaAtVtx);
   fChain->SetBranchAddress("SkimmedL1Mu_phiAtVtx", SkimmedL1Mu_phiAtVtx, &b_SkimmedL1Mu_phiAtVtx);
   fChain->SetBranchAddress("nL1Stubs", &nL1Stubs, &b_nL1Stubs);
   fChain->SetBranchAddress("L1Stubs_phi", L1Stubs_phi, &b_L1Stubs_phi);
   fChain->SetBranchAddress("L1Stubs_phiB", L1Stubs_phiB, &b_L1Stubs_phiB);
   fChain->SetBranchAddress("L1Stubs_qual", L1Stubs_qual, &b_L1Stubs_qual);
   fChain->SetBranchAddress("L1Stubs_eta", L1Stubs_eta, &b_L1Stubs_eta);
   fChain->SetBranchAddress("L1Stubs_qeta", L1Stubs_qeta, &b_L1Stubs_qeta);
   fChain->SetBranchAddress("L1Stubs_station", L1Stubs_station, &b_L1Stubs_station);
   fChain->SetBranchAddress("L1Stubs_wheel", L1Stubs_wheel, &b_L1Stubs_wheel);
   fChain->SetBranchAddress("L1Stubs_sector", L1Stubs_sector, &b_L1Stubs_sector);
   fChain->SetBranchAddress("L1Stubs_tag", L1Stubs_tag, &b_L1Stubs_tag);
   fChain->SetBranchAddress("L1Stubs_bx", L1Stubs_bx, &b_L1Stubs_bx);
   fChain->SetBranchAddress("nTriggerObjects", &nTriggerObjects, &b_nTriggerObjects);
   fChain->SetBranchAddress("TriggerObjects_pt", TriggerObjects_pt, &b_TriggerObjects_pt);
   fChain->SetBranchAddress("TriggerObjects_eta", TriggerObjects_eta, &b_TriggerObjects_eta);
   fChain->SetBranchAddress("TriggerObjects_phi", TriggerObjects_phi, &b_TriggerObjects_phi);
   Notify();
}

Bool_t DYclasse::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void DYclasse::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t DYclasse::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef DYclasse_cxx
