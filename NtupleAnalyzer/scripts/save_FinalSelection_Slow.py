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
sample = sys.argv[1]

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
df = RDataFrame("Events","/eos/cms/store/group/cmst3/group/slowmuons/Mu8Skim/L1Scouting/{}.root".format(sample))
nentries = df.Count().GetValue()

print ("Before selection total entries", nentries)

df = df.Filter("nL1KBMTFSkimmed>0")

df = df.Define("nstub1", "GetNstub(nL1KBMTFSkimmed, 0, L1KBMTFSkimmed_nStub)").Define("nstub2", "GetNstub(nL1KBMTFSkimmed, 1, L1KBMTFSkimmed_nStub)")

df = df.Filter("(nstub1>2 || nstub2>2)")

df = df.Define("bxspread1", "GetBxSpread(nL1KBMTFSkimmed, 0, L1KBMTFSkimmed_nStub, L1KBMTFSkimmed_s1Bx, L1KBMTFSkimmed_s2Bx, L1KBMTFSkimmed_s3Bx, L1KBMTFSkimmed_s4Bx)") \
       .Define("bxspread2", "GetBxSpread(nL1KBMTFSkimmed, 1, L1KBMTFSkimmed_nStub, L1KBMTFSkimmed_s1Bx, L1KBMTFSkimmed_s2Bx, L1KBMTFSkimmed_s3Bx, L1KBMTFSkimmed_s4Bx)") \
       .Define("isL1MuMatched1", "IsL1MuMatched(nL1KBMTFSkimmed, 0,L1KBMTFSkimmed_pt,L1KBMTFSkimmed_eta,L1KBMTFSkimmed_phi,nSkimmedL1Mu,SkimmedL1Mu_pt,SkimmedL1Mu_eta,SkimmedL1Mu_phi)") \
       .Define("isL1MuMatched2", "IsL1MuMatched(nL1KBMTFSkimmed, 1,L1KBMTFSkimmed_pt,L1KBMTFSkimmed_eta,L1KBMTFSkimmed_phi,nSkimmedL1Mu,SkimmedL1Mu_pt,SkimmedL1Mu_eta,SkimmedL1Mu_phi)") \
       .Define("stationspread1", "GetStationSpread(nL1KBMTFSkimmed, 0, L1KBMTFSkimmed_nStub, L1KBMTFSkimmed_s1Station, L1KBMTFSkimmed_s2Station, L1KBMTFSkimmed_s3Station, L1KBMTFSkimmed_s4Station)") \
       .Define("stationspread2", "GetStationSpread(nL1KBMTFSkimmed, 1, L1KBMTFSkimmed_nStub, L1KBMTFSkimmed_s1Station, L1KBMTFSkimmed_s2Station, L1KBMTFSkimmed_s3Station, L1KBMTFSkimmed_s4Station)")

df = df.Filter("(bxspread1>0 && nstub1>2) || (bxspread2>0 && nstub2>2)")

columns = ROOT.std.vector("string")()
for c in ("run", "luminosityBlock", "bunchCrossing", "orbitNumber", \
        "nL1KBMTFSkimmed", "L1KBMTFSkimmed_hwCharge", "L1KBMTFSkimmed_hwQual", \
        "bxspread1", "bxspread2", "stationspread1", "stationspread2", "nstub1", "nstub2", "isL1MuMatched1", "isL1MuMatched2", \
        "L1KBMTFSkimmed_hwDXY", "L1KBMTFSkimmed_nStub", "L1KBMTFSkimmed_pt", \
        "L1KBMTFSkimmed_s1Station", "L1KBMTFSkimmed_s1Wheel", "L1KBMTFSkimmed_s1Sector", "L1KBMTFSkimmed_s1Bx", \
        "L1KBMTFSkimmed_s2Station", "L1KBMTFSkimmed_s2Wheel", "L1KBMTFSkimmed_s2Sector", "L1KBMTFSkimmed_s2Bx",
        "L1KBMTFSkimmed_s3Station", "L1KBMTFSkimmed_s3Wheel", "L1KBMTFSkimmed_s3Sector", "L1KBMTFSkimmed_s3Bx",
        "L1KBMTFSkimmed_s4Station", "L1KBMTFSkimmed_s4Wheel", "L1KBMTFSkimmed_s4Sector", "L1KBMTFSkimmed_s4Bx"):
    columns.push_back(c)

df.Snapshot("Events","slow_{}.root".format(sample),columns)

nentries = df.Count().GetValue()
print ("After selection entries", nentries)

time_end=timer.time()
print('totally cost',time_end-time_start)
