//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Apr  8 10:45:27 2025 by ROOT version 6.30/03
// from TTree Events/Events
// found on file: root://eoscms.cern.ch//eos/cms/store/cmst3/group/slowmuons/ZmumuKBMTFSkims/Scouting_2024G_part1.root
//////////////////////////////////////////////////////////

#ifndef zmumuclasse_h
#define zmumuclasse_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class zmumuclasse {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          run;
   UInt_t          luminosityBlock;
   UInt_t          bunchCrossing;
   UInt_t          orbitNumber;
   Double_t        mmumu;
   Bool_t          isOS;
   Double_t        DRmumu;
   Double_t        xsweight;
   Float_t         met;
   Int_t           bxspread1;
   Int_t           bxspread2;
   Bool_t          isL1MuMatched1;
   Bool_t          isL1MuMatched2;
   Int_t           nstub1;
   Int_t           nstub2;
   Double_t        pt1;
   Double_t        eta1;
   Double_t        phi1;
   Short_t         charge1;
   Short_t         qual1;
   Short_t         dxy1;
   Double_t        pt2;
   Double_t        eta2;
   Double_t        phi2;
   Short_t         charge2;
   Short_t         qual2;
   Short_t         dxy2;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_luminosityBlock;   //!
   TBranch        *b_bunchCrossing;   //!
   TBranch        *b_orbitNumber;   //!
   TBranch        *b_mmumu;   //!
   TBranch        *b_isOS;   //!
   TBranch        *b_DRmumu;   //!
   TBranch        *b_xsweight;   //!
   TBranch        *b_met;   //!
   TBranch        *b_bxspread1;   //!
   TBranch        *b_bxspread2;   //!
   TBranch        *b_isL1MuMatched1;   //!
   TBranch        *b_isL1MuMatched2;   //!
   TBranch        *b_nstub1;   //!
   TBranch        *b_nstub2;   //!
   TBranch        *b_pt1;   //!
   TBranch        *b_eta1;   //!
   TBranch        *b_phi1;   //!
   TBranch        *b_charge1;   //!
   TBranch        *b_qual1;   //!
   TBranch        *b_dxy1;   //!
   TBranch        *b_pt2;   //!
   TBranch        *b_eta2;   //!
   TBranch        *b_phi2;   //!
   TBranch        *b_charge2;   //!
   TBranch        *b_qual2;   //!
   TBranch        *b_dxy2;   //!

   zmumuclasse(TTree *tree=0);
   virtual ~zmumuclasse();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef zmumuclasse_cxx
zmumuclasse::zmumuclasse(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("root://eoscms.cern.ch//eos/cms/store/cmst3/group/slowmuons/ZmumuKBMTFSkims/Scouting_2024G_part1.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("root://eoscms.cern.ch//eos/cms/store/cmst3/group/slowmuons/ZmumuKBMTFSkims/Scouting_2024G_part1.root");
      }
      f->GetObject("Events",tree);

   }
   Init(tree);
}

zmumuclasse::~zmumuclasse()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t zmumuclasse::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t zmumuclasse::LoadTree(Long64_t entry)
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

void zmumuclasse::Init(TTree *tree)
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
   fChain->SetBranchAddress("bunchCrossing", &bunchCrossing, &b_bunchCrossing);
   fChain->SetBranchAddress("orbitNumber", &orbitNumber, &b_orbitNumber);
   fChain->SetBranchAddress("mmumu", &mmumu, &b_mmumu);
   fChain->SetBranchAddress("isOS", &isOS, &b_isOS);
   fChain->SetBranchAddress("DRmumu", &DRmumu, &b_DRmumu);
   fChain->SetBranchAddress("xsweight", &xsweight, &b_xsweight);
   fChain->SetBranchAddress("met", &met, &b_met);
   fChain->SetBranchAddress("bxspread1", &bxspread1, &b_bxspread1);
   fChain->SetBranchAddress("bxspread2", &bxspread2, &b_bxspread2);
   fChain->SetBranchAddress("isL1MuMatched1", &isL1MuMatched1, &b_isL1MuMatched1);
   fChain->SetBranchAddress("isL1MuMatched2", &isL1MuMatched2, &b_isL1MuMatched2);
   fChain->SetBranchAddress("nstub1", &nstub1, &b_nstub1);
   fChain->SetBranchAddress("nstub2", &nstub2, &b_nstub2);
   fChain->SetBranchAddress("pt1", &pt1, &b_pt1);
   fChain->SetBranchAddress("eta1", &eta1, &b_eta1);
   fChain->SetBranchAddress("phi1", &phi1, &b_phi1);
   fChain->SetBranchAddress("charge1", &charge1, &b_charge1);
   fChain->SetBranchAddress("qual1", &qual1, &b_qual1);
   fChain->SetBranchAddress("dxy1", &dxy1, &b_dxy1);
   fChain->SetBranchAddress("pt2", &pt2, &b_pt2);
   fChain->SetBranchAddress("eta2", &eta2, &b_eta2);
   fChain->SetBranchAddress("phi2", &phi2, &b_phi2);
   fChain->SetBranchAddress("charge2", &charge2, &b_charge2);
   fChain->SetBranchAddress("qual2", &qual2, &b_qual2);
   fChain->SetBranchAddress("dxy2", &dxy2, &b_dxy2);
   Notify();
}

Bool_t zmumuclasse::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void zmumuclasse::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t zmumuclasse::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef zmumuclasse_cxx
