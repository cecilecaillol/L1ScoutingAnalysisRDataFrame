from ROOT import RDataFrame, TFile, TChain, TTree, TFile, TH1D, TLorentzVector,TCanvas
import numpy as np
import sys
from math import cos,sin,sqrt,pi
import ROOT
import time as timer
time_start=timer.time()
ROOT.gInterpreter.AddIncludePath('/afs/cern.ch/work/c/ccaillol/L1ScoutingAnalysisRDataFrame/CMSSW_14_0_12/src/L1ScoutingAnalysisRDataFrame/NtupleAnalyzer/lib')
ROOT.gInterpreter.Declare('#include "basic_sel.h"')
ROOT.gSystem.Load('/afs/cern.ch/work/c/ccaillol/L1ScoutingAnalysisRDataFrame/CMSSW_14_0_12/src/L1ScoutingAnalysisRDataFrame/NtupleAnalyzer/lib/RDFfunc.so')

### sample: output root file name
input_file = sys.argv[1]
output_file = sys.argv[2]

isdata = True
ngen=1.

df = RDataFrame(0)

weight=1.0

if ("Scouting" not in input_file):
    isdata=False
    #df = RDataFrame("Events","/afs/cern.ch/work/c/ccaillol/KBMTFemulation/CMSSW_14_0_12/src/L1TriggerScouting/Utilities/python/DY_nano.root".format(sample))
    df = RDataFrame("Events","/eos/cms/store/group/cmst3/group/slowmuons/DYgen/DY.root")
    #ngen = rdf2.Sum("genEventCount").GetValue()
    #ngen = rdf2.Sum("genEventSumw").GetValue()
    #weight=((6346.0*(1.0/3)*5440.0*(1.0/25)*(553.0/1000))/df.Count().GetValue())
    #weight=((6346.0*5440.0*(1.0/15.2))/df.Count().GetValue())
    weight=(6346.0/df.Count().GetValue())
else:
    #df = RDataFrame("Events","/eos/cms/store/group/cmst3/user/ccaillol/L1Scouting/Mu8Skim/L1Scouting/{}.root".format(sample))
    #df = RDataFrame("Events","/eos/cms/store/group/cmst3/group/slowmuons/Mu8Skim/L1Scouting/{}.root".format(sample))
    df = RDataFrame("Events",input_file)

nentries = df.Count().GetValue()

print ("isdata ", isdata)

if (isdata):
    weight = 1.0

print ("Before selection total entries", nentries)

df = df.Filter("nL1KBMTFSkimmed>1")

df_var=df.Define("idx1","GetIndex_nostub(1,nL1KBMTFSkimmed, L1KBMTFSkimmed_pt, L1KBMTFSkimmed_eta, L1KBMTFSkimmed_phi)").Define("idx2","GetIndex_nostub(2,nL1KBMTFSkimmed, L1KBMTFSkimmed_pt, L1KBMTFSkimmed_eta, L1KBMTFSkimmed_phi)")

df_var=df_var.Define("my_mu1","GetLepVector(idx1,L1KBMTFSkimmed_pt,L1KBMTFSkimmed_eta,L1KBMTFSkimmed_phi)").Define("my_mu2","GetLepVector(idx2,L1KBMTFSkimmed_pt,L1KBMTFSkimmed_eta,L1KBMTFSkimmed_phi)").Define("isOS","L1KBMTFSkimmed_hwCharge[idx1]*L1KBMTFSkimmed_hwCharge[idx2]<0")

df_var = df_var.Filter("idx1!=idx2 && my_mu1.Pt()>8 && my_mu2.Pt()>8 && fabs(my_mu1.Eta())<0.83 && fabs(my_mu2.Eta())<0.83")

df_var = df_var.Define("mmumu","(my_mu1+my_mu2).M()").Define("DRmumu","my_mu1.DeltaR(my_mu2)")

df = df_var.Filter("mmumu>50 && DRmumu>0.3").Define("xsweight","{}".format(weight))

df = df.Define("bxspread1", "GetBxSpread(nL1KBMTFSkimmed, idx1, L1KBMTFSkimmed_nStub, L1KBMTFSkimmed_s1Bx, L1KBMTFSkimmed_s2Bx, L1KBMTFSkimmed_s3Bx, L1KBMTFSkimmed_s4Bx)")\
        .Define("bxspread2", "GetBxSpread(nL1KBMTFSkimmed, idx2, L1KBMTFSkimmed_nStub, L1KBMTFSkimmed_s1Bx, L1KBMTFSkimmed_s2Bx, L1KBMTFSkimmed_s3Bx, L1KBMTFSkimmed_s4Bx)")\
        .Define("isL1MuMatched1", "IsL1MuMatched(nL1KBMTFSkimmed, idx1,L1KBMTFSkimmed_pt,L1KBMTFSkimmed_eta,L1KBMTFSkimmed_phi,nSkimmedL1Mu,SkimmedL1Mu_pt,SkimmedL1Mu_eta,SkimmedL1Mu_phi)")\
        .Define("isL1MuMatched2", "IsL1MuMatched(nL1KBMTFSkimmed, idx2,L1KBMTFSkimmed_pt,L1KBMTFSkimmed_eta,L1KBMTFSkimmed_phi,nSkimmedL1Mu,SkimmedL1Mu_pt,SkimmedL1Mu_eta,SkimmedL1Mu_phi)")\
        .Define("nstub1", "GetNstub(nL1KBMTFSkimmed, idx1, L1KBMTFSkimmed_nStub)")\
        .Define("nstub2", "GetNstub(nL1KBMTFSkimmed, idx2, L1KBMTFSkimmed_nStub)")\
        .Define("pt1","my_mu1.Pt()").Define("eta1","my_mu1.Eta()").Define("phi1","my_mu1.Phi()") \
        .Define("charge1","L1KBMTFSkimmed_hwCharge[idx1]").Define("qual1","L1KBMTFSkimmed_hwQual[idx1]") \
        .Define("dxy1","L1KBMTFSkimmed_hwDXY[idx1]") \
        .Define("pt2","my_mu2.Pt()").Define("eta2","my_mu2.Eta()").Define("phi2","my_mu2.Phi()") \
        .Define("charge2","L1KBMTFSkimmed_hwCharge[idx2]").Define("qual2","L1KBMTFSkimmed_hwQual[idx2]") \
        .Define("dxy2","L1KBMTFSkimmed_hwDXY[idx2]")

if (isdata):
    df = df.Define("met","L1KBMTFSkimmed_met_bx0[idx1]") 
else:
    df = df.Define("met","L1MET_pt[0]")


columns = ROOT.std.vector("string")()
for c in ("run", "luminosityBlock", "bunchCrossing", "orbitNumber", \
        "mmumu", "isOS", "DRmumu", "xsweight", "met", \
        "bxspread1", "bxspread2", "isL1MuMatched1", "isL1MuMatched2", "nstub1", "nstub2",\
        "pt1","eta1","phi1","charge1","qual1","dxy1","pt2","eta2","phi2","charge2","qual2","dxy2"):
    columns.push_back(c)

#df.Snapshot("Events","/eos/cms/store/cmst3/group/taug2/AnalysisXuelong/ntuples_mutau_2018_basicsel/{}.root".format(sample),columns)
df.Snapshot("Events",output_file,columns)

nentries = df.Count().GetValue()
print ("After selection entries", nentries)

time_end=timer.time()
print('totally cost',time_end-time_start)
