from ROOT import RDataFrame, TFile, TChain, TTree, TFile, TH1D, TLorentzVector,TCanvas,TH1F,TPaveText,TH2F
from ROOT.RDF import TH1DModel, TH2DModel
import numpy as np
import sys
from math import cos,sin,sqrt,pi
import ROOT
import time as timer
time_start=timer.time()
import sys
sys.path.append("..")

ROOT.gInterpreter.AddIncludePath('../lib/')
ROOT.gSystem.Load('../lib/RDFfunc.so')

class variable:
    def __init__(self, name, title, nbins, binning):
        self.name=name
        self.title = title
        self.nbins=nbins
        self.binning = binning

def gethisto(df,sample,cut,cutname,weight,variable):
    print ("generate histogram of ", sample , " cut ", cut, " weight ", weight)
    hmodel = TH1DModel("h_{}_{}_{}".format(variable.name,cutname,sample),"",variable.nbins,variable.binning)
    histo = df.Filter(cut).Define("totalweight",weight).Histo1D(hmodel,variable.name,"totalweight").GetPtr()
    histo.Sumw2()
    return histo

def getdf(name):
    df=RDataFrame("Events","/afs/cern.ch/work/c/ccaillol/L1ScoutingAnalysisRDataFrame/CMSSW_14_0_12/src/L1ScoutingAnalysisRDataFrame/NtupleAnalyzer/scripts/{}.root".format(name))
    return df
