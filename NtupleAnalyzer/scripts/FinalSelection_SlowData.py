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

#if ("Scouting" not in sample):
#    isdata=False
#    rdf2 = RDataFrame("Runs","/eos/cms/store/group/cmst3/group/taug2/AnalysisXuelong/ntuples_mutau_2018/{}.root".format(sample))
#    #ngen = rdf2.Sum("genEventCount").GetValue()
#    ngen = rdf2.Sum("genEventSumw").GetValue()

print ("isdata ", isdata)

weight = 1.0

if (isdata):
    weight = 1.0

df = RDataFrame(0)
#df = RDataFrame("Events","/eos/cms/store/group/cmst3/group/taug2/AnalysisXuelong/ntuples_mutau_2018/{}.root".format(sample))
#df = RDataFrame("Events","/afs/cern.ch/work/c/ccaillol/KBMTFemulation/CMSSW_14_0_12/src/L1TriggerScouting/Utilities/python/output.root")
#df = RDataFrame("Events","/eos/cms/store/group/cmst3/user/ccaillol/L1Scouting/Mu8Skim/L1Scouting/Scouting_2024H_9.root")
#df = RDataFrame("Events","/eos/cms/store/group/cmst3/user/ccaillol/L1Scouting/Mu8Skim/L1Scouting/{}.root".format(sample))
#df = RDataFrame("Events","/eos/cms/store/group/cmst3/group/slowmuons/Mu8Skim/L1Scouting/{}.root".format(sample))
#df = RDataFrame("Events","/afs/cern.ch/work/c/ccaillol/KBMTFemulation/CMSSW_14_0_12/src/L1TriggerScouting/Utilities/python/HSCPtauPrimeCharge1eM2600.root")
#df = RDataFrame("Events","/afs/cern.ch/work/c/ccaillol/KBMTFemulation/CMSSW_14_0_12/src/L1TriggerScouting/Utilities/python/HSCPtauPrimeCharge1eM1400.root")
df = RDataFrame("Events",input_file)
nentries = df.Count().GetValue()

print ("Before selection total entries", nentries)

df = df.Filter("nL1KBMTFSkimmed>0")

df = df.Define("idx1", "GetIndex(1, nL1KBMTFSkimmed, L1KBMTFSkimmed_pt, L1KBMTFSkimmed_eta, L1KBMTFSkimmed_phi, L1KBMTFSkimmed_nStub, L1KBMTFSkimmed_s1Bx, L1KBMTFSkimmed_s2Bx, L1KBMTFSkimmed_s3Bx, L1KBMTFSkimmed_s4Bx, L1KBMTFSkimmed_hwK)").Define("idx2", "GetIndex(2, nL1KBMTFSkimmed, L1KBMTFSkimmed_pt, L1KBMTFSkimmed_eta, L1KBMTFSkimmed_phi, L1KBMTFSkimmed_nStub, L1KBMTFSkimmed_s1Bx, L1KBMTFSkimmed_s2Bx, L1KBMTFSkimmed_s3Bx, L1KBMTFSkimmed_s4Bx, L1KBMTFSkimmed_hwK)")

#df = df.Define("nstub1", "GetNstub(nL1KBMTFSkimmed, idx1, L1KBMTFSkimmed_nStub)").Define("nstub2", "GetNstub(nL1KBMTFSkimmed, idx2, L1KBMTFSkimmed_nStub)")
df = df.Define("nstub1","L1KBMTFSkimmed_nStub[idx1]").Define("nstub2","L1KBMTFSkimmed_nStub[idx2]") 

#df = df.Filter("(nstub1>2 || nstub2>2)")

df = df.Define("bxspread1", "GetBxSpread(nL1KBMTFSkimmed, idx1, L1KBMTFSkimmed_nStub, L1KBMTFSkimmed_s1Bx, L1KBMTFSkimmed_s2Bx, L1KBMTFSkimmed_s3Bx, L1KBMTFSkimmed_s4Bx)") \
       .Define("bxspread2", "GetBxSpread(nL1KBMTFSkimmed, idx2, L1KBMTFSkimmed_nStub, L1KBMTFSkimmed_s1Bx, L1KBMTFSkimmed_s2Bx, L1KBMTFSkimmed_s3Bx, L1KBMTFSkimmed_s4Bx)") \
       .Define("isL1MuMatched1", "IsL1MuMatched(nL1KBMTFSkimmed, idx1,L1KBMTFSkimmed_pt,L1KBMTFSkimmed_eta,L1KBMTFSkimmed_phi,nSkimmedL1Mu,SkimmedL1Mu_pt,SkimmedL1Mu_eta,SkimmedL1Mu_phi)") \
       .Define("isL1MuMatched2", "IsL1MuMatched(nL1KBMTFSkimmed, idx2,L1KBMTFSkimmed_pt,L1KBMTFSkimmed_eta,L1KBMTFSkimmed_phi,nSkimmedL1Mu,SkimmedL1Mu_pt,SkimmedL1Mu_eta,SkimmedL1Mu_phi)") \
       .Define("stationspread1", "GetStationSpread(nL1KBMTFSkimmed, idx1, L1KBMTFSkimmed_nStub, L1KBMTFSkimmed_s1Station, L1KBMTFSkimmed_s2Station, L1KBMTFSkimmed_s3Station, L1KBMTFSkimmed_s4Station)") \
       .Define("stationspread2", "GetStationSpread(nL1KBMTFSkimmed, idx2, L1KBMTFSkimmed_nStub, L1KBMTFSkimmed_s1Station, L1KBMTFSkimmed_s2Station, L1KBMTFSkimmed_s3Station, L1KBMTFSkimmed_s4Station)") \
       .Define("firstbx1", "GetFirstBx(nL1KBMTFSkimmed, idx1, L1KBMTFSkimmed_nStub, L1KBMTFSkimmed_s1Bx, L1KBMTFSkimmed_s2Bx, L1KBMTFSkimmed_s3Bx, L1KBMTFSkimmed_s4Bx)") \
       .Define("firstbx2", "GetFirstBx(nL1KBMTFSkimmed, idx2, L1KBMTFSkimmed_nStub, L1KBMTFSkimmed_s1Bx, L1KBMTFSkimmed_s2Bx, L1KBMTFSkimmed_s3Bx, L1KBMTFSkimmed_s4Bx)") \
       .Define("pt1","Get_newpt(L1KBMTFSkimmed_hwK[idx1])").Define("pt2","Get_newpt(L1KBMTFSkimmed_hwK[idx2])") \
       .Define("eta1","L1KBMTFSkimmed_eta[idx1]").Define("eta2","L1KBMTFSkimmed_eta[idx2]") \
       .Define("phi1","L1KBMTFSkimmed_phi[idx1]").Define("phi2","L1KBMTFSkimmed_phi[idx2]") \
       .Define("dxy1","L1KBMTFSkimmed_hwDXY[idx1]").Define("dxy2","L1KBMTFSkimmed_hwDXY[idx2]") \
       .Define("qual1","L1KBMTFSkimmed_hwQual[idx1]").Define("qual2","L1KBMTFSkimmed_hwQual[idx2]") \
       .Define("charge1","L1KBMTFSkimmed_hwCharge[idx1]").Define("charge2","L1KBMTFSkimmed_hwCharge[idx2]") \
       .Define("met_bx0", "GetMET(0,firstbx1,L1KBMTFSkimmed_bx[idx1],L1KBMTFSkimmed_met_bx0[idx1],L1KBMTFSkimmed_met_bxm1[idx1],L1KBMTFSkimmed_met_bxm2[idx1],L1KBMTFSkimmed_met_bxm3[idx1],L1KBMTFSkimmed_met_bxm4[idx1],L1KBMTFSkimmed_met_bxm5[idx1],L1KBMTFSkimmed_met_bxm6[idx1],L1KBMTFSkimmed_met_bxm7[idx1],L1KBMTFSkimmed_met_bxm8[idx1],L1KBMTFSkimmed_met_bxm9[idx1])") \
       .Define("met_bxm1", "GetMET(1,firstbx1,L1KBMTFSkimmed_bx[idx1],L1KBMTFSkimmed_met_bx0[idx1],L1KBMTFSkimmed_met_bxm1[idx1],L1KBMTFSkimmed_met_bxm2[idx1],L1KBMTFSkimmed_met_bxm3[idx1],L1KBMTFSkimmed_met_bxm4[idx1],L1KBMTFSkimmed_met_bxm5[idx1],L1KBMTFSkimmed_met_bxm6[idx1],L1KBMTFSkimmed_met_bxm7[idx1],L1KBMTFSkimmed_met_bxm8[idx1],L1KBMTFSkimmed_met_bxm9[idx1])") \
       .Define("met_bxm2", "GetMET(2,firstbx1,L1KBMTFSkimmed_bx[idx1],L1KBMTFSkimmed_met_bx0[idx1],L1KBMTFSkimmed_met_bxm1[idx1],L1KBMTFSkimmed_met_bxm2[idx1],L1KBMTFSkimmed_met_bxm3[idx1],L1KBMTFSkimmed_met_bxm4[idx1],L1KBMTFSkimmed_met_bxm5[idx1],L1KBMTFSkimmed_met_bxm6[idx1],L1KBMTFSkimmed_met_bxm7[idx1],L1KBMTFSkimmed_met_bxm8[idx1],L1KBMTFSkimmed_met_bxm9[idx1])") \
       .Define("met_bxm3", "GetMET(3,firstbx1,L1KBMTFSkimmed_bx[idx1],L1KBMTFSkimmed_met_bx0[idx1],L1KBMTFSkimmed_met_bxm1[idx1],L1KBMTFSkimmed_met_bxm2[idx1],L1KBMTFSkimmed_met_bxm3[idx1],L1KBMTFSkimmed_met_bxm4[idx1],L1KBMTFSkimmed_met_bxm5[idx1],L1KBMTFSkimmed_met_bxm6[idx1],L1KBMTFSkimmed_met_bxm7[idx1],L1KBMTFSkimmed_met_bxm8[idx1],L1KBMTFSkimmed_met_bxm9[idx1])") \
       .Define("met_bxm4", "GetMET(4,firstbx1,L1KBMTFSkimmed_bx[idx1],L1KBMTFSkimmed_met_bx0[idx1],L1KBMTFSkimmed_met_bxm1[idx1],L1KBMTFSkimmed_met_bxm2[idx1],L1KBMTFSkimmed_met_bxm3[idx1],L1KBMTFSkimmed_met_bxm4[idx1],L1KBMTFSkimmed_met_bxm5[idx1],L1KBMTFSkimmed_met_bxm6[idx1],L1KBMTFSkimmed_met_bxm7[idx1],L1KBMTFSkimmed_met_bxm8[idx1],L1KBMTFSkimmed_met_bxm9[idx1])") \
       .Define("met_bxm5", "GetMET(5,firstbx1,L1KBMTFSkimmed_bx[idx1],L1KBMTFSkimmed_met_bx0[idx1],L1KBMTFSkimmed_met_bxm1[idx1],L1KBMTFSkimmed_met_bxm2[idx1],L1KBMTFSkimmed_met_bxm3[idx1],L1KBMTFSkimmed_met_bxm4[idx1],L1KBMTFSkimmed_met_bxm5[idx1],L1KBMTFSkimmed_met_bxm6[idx1],L1KBMTFSkimmed_met_bxm7[idx1],L1KBMTFSkimmed_met_bxm8[idx1],L1KBMTFSkimmed_met_bxm9[idx1])")
       #.Define("met_bx0_1","L1KBMTFSkimmed_met_bx0[idx1]").Define("met_bx0_2","L1KBMTFSkimmed_met_bx0[idx2]") \
       #.Define("met_bxm1_1","L1KBMTFSkimmed_met_bxm1[idx1]").Define("met_bxm1_2","L1KBMTFSkimmed_met_bxm1[idx2]") \
       #.Define("met_bxm2_1","L1KBMTFSkimmed_met_bxm2[idx1]").Define("met_bxm2_2","L1KBMTFSkimmed_met_bxm2[idx2]") \
       #.Define("met_bxm3_1","L1KBMTFSkimmed_met_bxm3[idx1]").Define("met_bxm3_2","L1KBMTFSkimmed_met_bxm3[idx2]") \
       #.Define("met_bxm4_1","L1KBMTFSkimmed_met_bxm4[idx1]").Define("met_bxm4_2","L1KBMTFSkimmed_met_bxm4[idx2]") \
       #.Define("met_bxm5_1","L1KBMTFSkimmed_met_bxm5[idx1]").Define("met_bxm5_2","L1KBMTFSkimmed_met_bxm5[idx2]") \
       #.Define("met_bxm6_1","L1KBMTFSkimmed_met_bxm6[idx1]").Define("met_bxm6_2","L1KBMTFSkimmed_met_bxm6[idx2]") \
       #.Define("met_bxm7_1","L1KBMTFSkimmed_met_bxm7[idx1]").Define("met_bxm7_2","L1KBMTFSkimmed_met_bxm7[idx2]") \
       #.Define("met_bxm8_1","L1KBMTFSkimmed_met_bxm8[idx1]").Define("met_bxm8_2","L1KBMTFSkimmed_met_bxm8[idx2]") \
       #.Define("met_bxm9_1","L1KBMTFSkimmed_met_bxm9[idx1]").Define("met_bxm9_2","L1KBMTFSkimmed_met_bxm9[idx2]")

df = df.Filter("(bxspread1>0 or pt1>500) || (bxspread2>0 || pt2>500)")

df = df.Define("is_colliding", "IsColliding(run,firstbx1)")

df = df.Define("is_earlier_colliding", "IsEarlierColliding(run,firstbx1,4,is_colliding)")

columns = ROOT.std.vector("string")()
for c in ("run", "luminosityBlock", "bunchCrossing", "orbitNumber", "is_colliding", "is_earlier_colliding", \
        #"nL1KBMTFSkimmed", "L1KBMTFSkimmed_hwCharge", "L1KBMTFSkimmed_hwQual", \
        "idx1", "idx2", \
        "bxspread1", "bxspread2", "stationspread1", "stationspread2", "nstub1", "nstub2", "isL1MuMatched1", "isL1MuMatched2", \
        "firstbx1","firstbx2", "pt1", "pt2", "eta1", "eta2", "phi1", "phi2", "dxy1", "dxy2", "qual1", "qual2", "charge1", "charge2", \
        "met_bx0","met_bxm1","met_bxm2","met_bxm3","met_bxm4","met_bxm5"):
        #"met_bx0_1","met_bxm1_1","met_bxm2_1","met_bxm3_1","met_bxm4_1","met_bxm5_1", \
        #"met_bx0_2","met_bxm1_2","met_bxm2_2","met_bxm3_2","met_bxm4_2","met_bxm5_2", \
        #"met_bx6_1","met_bxm7_1","met_bxm8_1","met_bxm9_1", \
        #"met_bx6_2","met_bxm7_2","met_bxm8_2","met_bxm9_2"):
        #"L1KBMTFSkimmed_hwDXY", "L1KBMTFSkimmed_nStub", "L1KBMTFSkimmed_pt", \
        #"L1KBMTFSkimmed_s1Station", "L1KBMTFSkimmed_s1Wheel", "L1KBMTFSkimmed_s1Sector", "L1KBMTFSkimmed_s1Bx", \
        #"L1KBMTFSkimmed_s2Station", "L1KBMTFSkimmed_s2Wheel", "L1KBMTFSkimmed_s2Sector", "L1KBMTFSkimmed_s2Bx",
        #"L1KBMTFSkimmed_s3Station", "L1KBMTFSkimmed_s3Wheel", "L1KBMTFSkimmed_s3Sector", "L1KBMTFSkimmed_s3Bx",
        #"L1KBMTFSkimmed_s4Station", "L1KBMTFSkimmed_s4Wheel", "L1KBMTFSkimmed_s4Sector", "L1KBMTFSkimmed_s4Bx"):
    columns.push_back(c)

df.Snapshot("Events",output_file,columns)

nentries = df.Count().GetValue()
print ("After selection entries", nentries)

time_end=timer.time()
print('totally cost',time_end-time_start)
