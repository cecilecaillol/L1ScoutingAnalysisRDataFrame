import ROOT
import os

is_mu=1

# Avoid showing GUI windows
ROOT.gROOT.SetBatch(True)

# Define MASS range
mass_values = range(1000, 6001, 500)

# Create histogram: (nbins, x_min, x_max)
hist = ROOT.TH1F("mean_HLT_IsoMu24", "Mean of HLT_IsoMu24 vs MASS;MASS;Mean(HLT_IsoMu24)", 
                 len(mass_values), 999.5, 6000.5)

# Loop over MASS values
for i, mass in enumerate(mass_values):
    path = f"/eos/cms/store/group/cmst3/group/slowmuons/HSCPtauPrime_{mass}/KBMTFsim_HLT/total.root"
    if not os.path.isfile(path):
        print(f"File not found: {path}")
        continue

    f = ROOT.TFile.Open(path)
    if not f or f.IsZombie():
        print(f"Could not open file: {path}")
        continue

    tree = f.Get("Events")
    if not tree:
        print(f"No 'Events' tree in file: {path}")
        continue

    # Create a temporary histogram to get mean
    if is_mu: tree.Draw("HLT_IsoMu24||HLT_Mu50>>temp(2, -0.5, 1.5)", "", "goff")  # 0/1 values
    else: tree.Draw("HLT_PFMET120_PFMHT120_IDTight||HLT_PFHT500_PFMET100_PFMHT100_IDTight||HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60||HLT_MET105_IsoTrk50>>temp(2, -0.5, 1.5)", "", "goff")  # 0/1 values
    temp_hist = ROOT.gDirectory.Get("temp")
    mean_val = temp_hist.GetMean()

    print(f"MASS {mass}: Mean HLT_IsoMu24 = {mean_val}")
    hist.SetBinContent(i+1, mean_val)

    f.Close()

# Draw histogram
c = ROOT.TCanvas("c", "Canvas", 800, 600)
hist.SetStats(0)
hist.SetMinimum(-0.001)
hist.SetTitle("")
hist.GetXaxis().SetTitle("HSCP mass (GeV)")
hist.GetYaxis().SetTitle("Single muon HLT efficiency")
if not is_mu: hist.GetYaxis().SetTitle("MET-based HLT efficiency")
hist.SetMarkerStyle(20)
hist.SetMarkerSize(1.2)
hist.Draw("P")
if is_mu: c.SaveAs("eff_IsoMu24.png")
else: c.SaveAs("eff_METHLT.png")

