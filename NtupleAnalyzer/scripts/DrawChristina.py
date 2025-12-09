import ROOT
ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)

# Input ROOT file names
file1_name = "output_ZmumuKBMTF/DY.root"
file2_name = "output_ZmumuKBMTF/Scouting_2024.root"

# Open the ROOT files
file1 = ROOT.TFile.Open(file1_name)
file2 = ROOT.TFile.Open(file2_name)

# Get histograms from each file
h_bxspan_1 = file1.Get("h_bxspan")
h_bxspan_2 = file2.Get("h_bxspan")

h_station_1 = file1.Get("h_station")
h_station_2 = file2.Get("h_station")

# Normalize histograms to unity
def normalize(h):
    integral = h.Integral()
    if integral > 0:
        h.Scale(1.0 / integral)

normalize(h_bxspan_1)
normalize(h_bxspan_2)
normalize(h_station_1)
normalize(h_station_2)

# Style histograms for visual distinction
def style(h, color, marker):
    h.SetLineColor(color)
    h.SetMarkerColor(color)
    h.SetMarkerStyle(marker)

style(h_bxspan_1, ROOT.kBlue, 20)
style(h_bxspan_2, ROOT.kRed, 21)
style(h_station_1, ROOT.kBlue, 20)
style(h_station_2, ROOT.kRed, 21)

# Draw h_bxspan
c1 = ROOT.TCanvas("c1", "", 800, 600)
c1.SetLogy()
h_bxspan_1.GetXaxis().SetTitle("BX spread")
h_bxspan_1.GetYaxis().SetTitle("Probability density")
h_bxspan_1.SetTitle("")
h_bxspan_1.Draw("HIST E")
h_bxspan_2.Draw("HIST E SAME")

legend1 = ROOT.TLegend(0.7, 0.75, 0.89, 0.89)
legend1.AddEntry(h_bxspan_1, "DY MC", "l")
legend1.AddEntry(h_bxspan_2, "Data", "l")
legend1.Draw()

c1.Update()

# Assign alphanumerical labels to h_station
# (Assuming same binning in both histograms)
station_labels = ["1234","234","134","124","123"]
for i, label in enumerate(station_labels, start=1):
    h_station_1.GetXaxis().SetBinLabel(i, label)
    h_station_2.GetXaxis().SetBinLabel(i, label)

# Draw h_station
c2 = ROOT.TCanvas("c2", "", 800, 600)
c2.SetLogy()
h_station_1.GetYaxis().SetTitle("Probability density")
h_station_1.SetTitle("")
h_station_1.Draw("HIST E")
h_station_2.Draw("HIST E SAME")

legend2 = ROOT.TLegend(0.7, 0.75, 0.89, 0.89)
legend2.AddEntry(h_station_1, "DY MC", "l")
legend2.AddEntry(h_station_2, "Data", "l")
legend2.Draw()

c2.Update()

c1.SaveAs("BXspread_ZMM.png")
c2.SaveAs("station_ZMM.png")

for i in range(1,5):
   hist = file1.Get("h_bx"+str(i))
   hist.SetTitle("")
   hist.GetXaxis().SetTitle("BX of stub in station "+str(i))
   hist.GetYaxis().SetTitle("Probability density")
   c1.cd()
   hist.DrawNormalized("hist")
   c1.SaveAs("bx"+str(i)+".png")

c3 = ROOT.TCanvas("c3", "", 800, 600)
h_reso = file1.Get("h_reso")
c3.cd()
h_reso.SetTitle("")
h_reso.GetXaxis().SetTitle("(reco-gen)/gen p_{T}")
h_reso.GetYaxis().SetTitle("Probability density")
h_reso.DrawNormalized("hist")
h_reso.Fit("gaus")
c3.SaveAs("ptreso.png")

