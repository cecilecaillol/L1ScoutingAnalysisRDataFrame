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

input_file = sys.argv[1]
output_file = sys.argv[2]

isdata = True
ngen=1.

df = RDataFrame(0)

weight=1.0

if ("Scouting" not in input_file):
    isdata=False
    df = RDataFrame("Events","/eos/cms/store/group/cmst3/group/slowmuons/DYgen/DY.root")
    #weight=((6346.0*5440.0*(1.0/15.2))/df.Count().GetValue())
    weight=((6346.0)/df.Count().GetValue())
else:
    df = RDataFrame("Events",input_file)

nentries = df.Count().GetValue()
print(nentries)

print ("isdata ", isdata)

if (isdata):
    weight = 1.0

print ("Before selection total entries", nentries)

df = df.Filter("nSkimmedL1Mu>1")

df_var=df.Define("idx1","GetIndex_nostub(1,nSkimmedL1Mu, SkimmedL1Mu_pt, SkimmedL1Mu_eta, SkimmedL1Mu_phi)").Define("idx2","GetIndex_nostub(2,nSkimmedL1Mu, SkimmedL1Mu_pt, SkimmedL1Mu_eta, SkimmedL1Mu_phi)")

df_var=df_var.Define("my_mu1","GetLepVector(idx1,SkimmedL1Mu_pt,SkimmedL1Mu_eta,SkimmedL1Mu_phi)")\
        .Define("my_mu2","GetLepVector(idx2,SkimmedL1Mu_pt,SkimmedL1Mu_eta,SkimmedL1Mu_phi)")\
        .Define("isOS","SkimmedL1Mu_hwCharge[idx1]*SkimmedL1Mu_hwCharge[idx2]<0")

df_var = df_var.Filter("my_mu1.Pt()>8 && my_mu2.Pt()>8 && fabs(my_mu1.Eta())<0.83 && fabs(my_mu2.Eta())<0.83")

df_var = df_var.Define("mmumu","(my_mu1+my_mu2).M()").Define("DRmumu","my_mu1.DeltaR(my_mu2)") \
               .Define("pt1","my_mu1.Pt()").Define("eta1","my_mu1.Eta()").Define("phi1","my_mu1.Phi()") \
               .Define("charge1","SkimmedL1Mu_hwCharge[idx1]").Define("qual1","SkimmedL1Mu_hwQual[idx1]") \
               .Define("dxy1","SkimmedL1Mu_hwDXY[idx1]") \
               .Define("pt2","my_mu2.Pt()").Define("eta2","my_mu2.Eta()").Define("phi2","my_mu2.Phi()") \
               .Define("charge2","SkimmedL1Mu_hwCharge[idx2]").Define("qual2","SkimmedL1Mu_hwQual[idx2]") \
               .Define("dxy2","SkimmedL1Mu_hwDXY[idx2]")

df = df_var.Filter("mmumu>50 && DRmumu>0.3").Define("xsweight","{}".format(weight))

if isdata: 
   df = df.Define("is_colliding", "IsColliding(run,bunchCrossing)")
   df = df.Define("is_earlier_colliding", "IsEarlierColliding(run,bunchCrossing,1,is_colliding)")
else:
   df = df.Define("is_colliding", "true").Define("is_earlier_colliding", "true")

columns = ROOT.std.vector("string")()
for c in ("run", "luminosityBlock", "bunchCrossing", "orbitNumber", "xsweight", "is_colliding", "is_earlier_colliding", \
        "pt1","eta1","phi1","charge1","qual1","dxy1","pt2","eta2","phi2","charge2","qual2","dxy2", \
        "mmumu", "isOS", "DRmumu"):
    columns.push_back(c)

df.Snapshot("Events",output_file,columns)

nentries = df.Count().GetValue()
print ("After selection entries", nentries)

time_end=timer.time()
print('totally cost',time_end-time_start)
