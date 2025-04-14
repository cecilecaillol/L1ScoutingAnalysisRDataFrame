#include "basic_sel.h"

int GetIndex_nostub(int rank, int ncand, ROOT::VecOps::RVec<Float_t> &LepCand_pt, ROOT::VecOps::RVec<Float_t> &LepCand_eta, ROOT::VecOps::RVec<Float_t> &LepCand_phi){
        int idxK1=99; int idxK2=99;
        TLorentzVector my_mu1; my_mu1.SetPtEtaPhiM(0.,0.,0.,0.);
        TLorentzVector my_mu2; my_mu2.SetPtEtaPhiM(0.,0.,0.,0.);
        TLorentzVector tmp_mu;
        if (ncand==1) idxK1=0;
        else if (ncand>1){
           float mu1pt=0.; float mu2pt=0.;
           for (int k=0; k<ncand; ++k){
              tmp_mu.SetPtEtaPhiM(LepCand_pt[k], LepCand_eta[k], LepCand_phi[k],0.105);
              if (LepCand_pt[k]>mu1pt) {
                 if (mu1pt>0 and my_mu1.DeltaR(tmp_mu)>0.30){
                    my_mu2=my_mu1; mu2pt=mu1pt; idxK2 = idxK1;
                 }
                 my_mu1=tmp_mu;
                 idxK1=k;
                 mu1pt=LepCand_pt[k];
              }
              else if (my_mu1.DeltaR(tmp_mu)>0.30 and LepCand_pt[k]>mu2pt) {
                 my_mu2=tmp_mu;
                 idxK2=k;
                 mu2pt=LepCand_pt[k];
              }
           }
        }
        if (rank==1) return idxK1;
        else if (rank==2) return idxK2;
        else return 0;
}

int GetIndex(int rank, int ncand, ROOT::VecOps::RVec<Float_t> &LepCand_pt, ROOT::VecOps::RVec<Float_t> &LepCand_eta, ROOT::VecOps::RVec<Float_t> &LepCand_phi, ROOT::VecOps::RVec<Short_t> &nstub){
	int idxK1=99; int idxK2=99;
	TLorentzVector my_mu1; my_mu1.SetPtEtaPhiM(0.,0.,0.,0.);
        TLorentzVector my_mu2; my_mu2.SetPtEtaPhiM(0.,0.,0.,0.);
        TLorentzVector tmp_mu;
	if (ncand==1) idxK1=0;
	else if (ncand>1){
           float mu1pt=0.; float mu2pt=0.;
           for (int k=0; k<ncand; ++k){
              tmp_mu.SetPtEtaPhiM(LepCand_pt[k], LepCand_eta[k], LepCand_phi[k],0.105);
              if (LepCand_pt[k]>mu1pt) {
                 if (mu1pt>0 and my_mu1.DeltaR(tmp_mu)>0.30){
                    my_mu2=my_mu1; mu2pt=mu1pt; idxK2 = idxK1;
                 }
                 my_mu1=tmp_mu;
                 idxK1=k;
                 mu1pt=LepCand_pt[k];
              }
              else if (my_mu1.DeltaR(tmp_mu)>0.30 and LepCand_pt[k]>mu2pt) {
                 my_mu2=tmp_mu;
                 idxK2=k;
                 mu2pt=LepCand_pt[k];
              }
           }
        }
	if (idxK1<99){
	   int nstub_mu1=nstub[idxK1];
	   for (int k=0; k<ncand; ++k){
              tmp_mu.SetPtEtaPhiM(LepCand_pt[k], LepCand_eta[k], LepCand_phi[k],0.105);
	      if (tmp_mu.DeltaR(my_mu1)<0.30 and nstub[k]>nstub_mu1){
	         my_mu1=tmp_mu;
		 nstub_mu1 = nstub[k];
		 idxK1=k;
	      }
	   }
	}
	if (idxK2<99){
	   TLorentzVector tmp_mu;
           int nstub_mu2=nstub[idxK2];
           for (int k=0; k<ncand; ++k){
              tmp_mu.SetPtEtaPhiM(LepCand_pt[k], LepCand_eta[k], LepCand_phi[k],0.105);
              if (tmp_mu.DeltaR(my_mu2)<0.30 and nstub[k]>nstub_mu2){
                 my_mu2=tmp_mu;
                 nstub_mu2 = nstub[k];
                 idxK2=k;
              }
           }
        }
	if (rank==1) return idxK1;
        else if (rank==2) return idxK2;
        else return 0;
}


TLorentzVector GetLepVector(int index, ROOT::VecOps::RVec<Float_t> &LepCand_pt, ROOT::VecOps::RVec<Float_t> &LepCand_eta,ROOT::VecOps::RVec<Float_t> &LepCand_phi){
    TLorentzVector my_lep;
    if (index<99) my_lep.SetPtEtaPhiM(LepCand_pt[index],LepCand_eta[index],LepCand_phi[index],0.105);
    return my_lep;
}

int GetBxSpread(int ncand, int index, ROOT::VecOps::RVec<Short_t> &nstub, ROOT::VecOps::RVec<Short_t> &bx1, ROOT::VecOps::RVec<Short_t> &bx2, ROOT::VecOps::RVec<Short_t> &bx3, ROOT::VecOps::RVec<Short_t> &bx4){
    int spread = 0;
    if (index<ncand){
       int minbx = bx1[index];
       if (bx2[index]<minbx) minbx = bx2[index];
       if (nstub[index]>2 and bx3[index]<minbx) minbx = bx3[index];
       if (nstub[index]>3 and bx4[index]<minbx) minbx = bx4[index];
       spread = spread + 1000*(bx1[index]-minbx);
       spread = spread + 100*(bx2[index]-minbx);
       if (nstub[index]>2) spread = spread + 10*(bx3[index]-minbx);
       if (nstub[index]>3) spread = spread + 1*(bx4[index]-minbx);
    }
    else spread=-1;
    return spread;
}

int GetFirstBx(int ncand, int index, ROOT::VecOps::RVec<Short_t> &nstub, ROOT::VecOps::RVec<Short_t> &bx1, ROOT::VecOps::RVec<Short_t> &bx2, ROOT::VecOps::RVec<Short_t> &bx3, ROOT::VecOps::RVec<Short_t> &bx4){
    int minbx=-10;
    if (index<ncand){
       minbx = bx1[index];
       if (bx2[index]<minbx) minbx = bx2[index];
       if (nstub[index]>2 and bx3[index]<minbx) minbx = bx3[index];
       if (nstub[index]>3 and bx4[index]<minbx) minbx = bx4[index];
    }
    return minbx;
}

int GetStationSpread(int ncand, int index, ROOT::VecOps::RVec<Short_t> &nstub, ROOT::VecOps::RVec<Short_t> &st1, ROOT::VecOps::RVec<Short_t> &st2, ROOT::VecOps::RVec<Short_t> &st3, ROOT::VecOps::RVec<Short_t> &st4){
    int spread = 0;
    if (index<ncand){
       spread = spread + 1000*st1[index];
       spread = spread + 100*st2[index];
       if (nstub[index]>2) spread = spread + 10*st3[index];
       if (nstub[index]>3) spread = spread + 1*st4[index];
    }
    else spread=-1;
    return spread;
}

int GetNstub(int ncand, int index, ROOT::VecOps::RVec<Short_t> &nstub){
    int n = -1;
    if (index<ncand){
       n = nstub[index];
    }
    return n;
}

bool IsL1MuMatched(int ncand, int index, ROOT::VecOps::RVec<Float_t> &pt, ROOT::VecOps::RVec<Float_t> &eta,ROOT::VecOps::RVec<Float_t> &phi, int nl1, ROOT::VecOps::RVec<Float_t> &l1pt, ROOT::VecOps::RVec<Float_t> &l1eta,ROOT::VecOps::RVec<Float_t> &l1phi){
    bool is_matched = false;
    if (index<ncand){
       TLorentzVector my_lep;
       my_lep.SetPtEtaPhiM(pt[index], eta[index], phi[index],0);
       for (int i = 0; i<nl1; ++i){
               TLorentzVector tmp;
               tmp.SetPtEtaPhiM(l1pt[i], l1eta[i], l1phi[i],0);
               if (tmp.DeltaR(my_lep)<0.1) is_matched = true;
       }
    }
    return is_matched;
}

float GetMET(int diff, int firstbx, int track_bx, float met0, float metm1, float metm2, float metm3, float metm4, float metm5, float metm6, float metm7, float metm8, float metm9){
  float out_met = met0;
  if (diff==0){
	  if ((track_bx-firstbx)==0) out_met=met0;
	  else if ((track_bx-firstbx)==1) out_met=metm1;
	  else if ((track_bx-firstbx)==2) out_met=metm2;
	  else if ((track_bx-firstbx)==3) out_met=metm3;
	  else if ((track_bx-firstbx)==4) out_met=metm4;
	  else if ((track_bx-firstbx)==5) out_met=metm5;
	  else if ((track_bx-firstbx)==6) out_met=metm6;
          else if ((track_bx-firstbx)==7) out_met=metm7;
          else if ((track_bx-firstbx)==8) out_met=metm8;
          else if ((track_bx-firstbx)==9) out_met=metm9;
  }
  else if (diff==1){
	  if ((track_bx-firstbx)==0) out_met=metm1;
          else if ((track_bx-firstbx)==1) out_met=metm2;
          else if ((track_bx-firstbx)==2) out_met=metm3;
          else if ((track_bx-firstbx)==3) out_met=metm4;
          else if ((track_bx-firstbx)==4) out_met=metm5;
          else if ((track_bx-firstbx)==5) out_met=metm6;
          else if ((track_bx-firstbx)==6) out_met=metm7;
          else if ((track_bx-firstbx)==7) out_met=metm8;
          else if ((track_bx-firstbx)==8) out_met=metm9;
  }
  else if (diff==2){
          if ((track_bx-firstbx)==0) out_met=metm2;
          else if ((track_bx-firstbx)==1) out_met=metm3;
          else if ((track_bx-firstbx)==2) out_met=metm4;
          else if ((track_bx-firstbx)==3) out_met=metm5;
          else if ((track_bx-firstbx)==4) out_met=metm6;
          else if ((track_bx-firstbx)==5) out_met=metm7;
          else if ((track_bx-firstbx)==6) out_met=metm8;
          else if ((track_bx-firstbx)==7) out_met=metm9;
  }
  else if (diff==3){
          if ((track_bx-firstbx)==0) out_met=metm3;
          else if ((track_bx-firstbx)==1) out_met=metm4;
          else if ((track_bx-firstbx)==2) out_met=metm5;
          else if ((track_bx-firstbx)==3) out_met=metm6;
          else if ((track_bx-firstbx)==4) out_met=metm7;
          else if ((track_bx-firstbx)==5) out_met=metm8;
          else if ((track_bx-firstbx)==6) out_met=metm9;
  }
  else if (diff==4){
          if ((track_bx-firstbx)==0) out_met=metm4;
          else if ((track_bx-firstbx)==1) out_met=metm5;
          else if ((track_bx-firstbx)==2) out_met=metm6;
          else if ((track_bx-firstbx)==3) out_met=metm7;
          else if ((track_bx-firstbx)==4) out_met=metm8;
          else if ((track_bx-firstbx)==5) out_met=metm9;
  }
  else if (diff==5){
          if ((track_bx-firstbx)==0) out_met=metm5;
          else if ((track_bx-firstbx)==1) out_met=metm6;
          else if ((track_bx-firstbx)==2) out_met=metm7;
          else if ((track_bx-firstbx)==3) out_met=metm8;
          else if ((track_bx-firstbx)==4) out_met=metm9;
  }
  return out_met;
}
