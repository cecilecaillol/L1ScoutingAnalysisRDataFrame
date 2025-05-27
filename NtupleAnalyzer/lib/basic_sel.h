#ifndef basic_sel_H
#define basic_sel_H

#include <ROOT/RDataFrame.hxx>
#include "TLorentzVector.h"

#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TMath.h"
#include <cmath>
#include "ROOT/RVec.hxx"
#include "ROOT/RDF/RInterface.hxx"
using namespace std;
using namespace ROOT;
using namespace ROOT::VecOps;

int GetIndex_nostub(int rank, int ncand, ROOT::VecOps::RVec<Float_t> &LepCand_pt, ROOT::VecOps::RVec<Float_t> &LepCand_eta, ROOT::VecOps::RVec<Float_t> &LepCand_phi);

int GetIndex(int rank, int ncand, ROOT::VecOps::RVec<Float_t> &LepCand_pt, ROOT::VecOps::RVec<Float_t> &LepCand_eta, ROOT::VecOps::RVec<Float_t> &LepCand_phi, ROOT::VecOps::RVec<Short_t> &nstub, ROOT::VecOps::RVec<Short_t> &bx1, ROOT::VecOps::RVec<Short_t> &bx2, ROOT::VecOps::RVec<Short_t> &bx3, ROOT::VecOps::RVec<Short_t> &bx4, ROOT::VecOps::RVec<Short_t> &LepCand_hwK);

int GetIndex_nostub_hwK(int rank, int ncand, ROOT::VecOps::RVec<Float_t> &LepCand_pt, ROOT::VecOps::RVec<Float_t> &LepCand_eta, ROOT::VecOps::RVec<Float_t> &LepCand_phi, ROOT::VecOps::RVec<Short_t> &LepCand_hwK);

TLorentzVector GetLepVector(int index, ROOT::VecOps::RVec<Float_t> &LepCand_pt, ROOT::VecOps::RVec<Float_t> &LepCand_eta,ROOT::VecOps::RVec<Float_t> &LepCand_phi);

TLorentzVector GetLepVector_hwK(int index, ROOT::VecOps::RVec<Float_t> &LepCand_eta,ROOT::VecOps::RVec<Float_t> &LepCand_phi, ROOT::VecOps::RVec<Short_t> &LepCand_hwK);

int GetBxSpread(int ncand, int index, ROOT::VecOps::RVec<Short_t> &nstub, ROOT::VecOps::RVec<Short_t> &bx1, ROOT::VecOps::RVec<Short_t> &bx2, ROOT::VecOps::RVec<Short_t> &bx3, ROOT::VecOps::RVec<Short_t> &bx4);

int GetFirstBx(int ncand, int index, ROOT::VecOps::RVec<Short_t> &nstub, ROOT::VecOps::RVec<Short_t> &bx1, ROOT::VecOps::RVec<Short_t> &bx2, ROOT::VecOps::RVec<Short_t> &bx3, ROOT::VecOps::RVec<Short_t> &bx4);

int GetStationSpread(int ncand, int index, ROOT::VecOps::RVec<Short_t> &nstub, ROOT::VecOps::RVec<Short_t> &st1, ROOT::VecOps::RVec<Short_t> &st2, ROOT::VecOps::RVec<Short_t> &st3, ROOT::VecOps::RVec<Short_t> &st4);

int GetNstub(int ncand, int index, ROOT::VecOps::RVec<Short_t> &nstub);

bool IsL1MuMatched(int ncand, int index, ROOT::VecOps::RVec<Float_t> &pt, ROOT::VecOps::RVec<Float_t> &eta,ROOT::VecOps::RVec<Float_t> &phi, int nl1, ROOT::VecOps::RVec<Float_t> &l1pt, ROOT::VecOps::RVec<Float_t> &l1eta,ROOT::VecOps::RVec<Float_t> &l1phi);

float GetMET(int diff, int firstbx, int track_bx, float met0, float metm1, float metm2, float metm3, float metm4, float metm5, float metm6, float metm7, float metm8, float metm9);

bool IsColliding(int run, int bx);

bool IsEarlierColliding(int run, int bx, int interval, bool is_colliding);

float Get_newpt(int oldK);


#endif
