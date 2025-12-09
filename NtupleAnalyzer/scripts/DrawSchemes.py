import ROOT
import math
ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetPadTickX(1)
ROOT.gStyle.SetPadTickY(1)

# Canvas
c = ROOT.TCanvas("c", "CMS DT Structure", 600, 600)
c.SetGrid()

# Frame
frame = ROOT.TH2F("frame", ";BX;R (m)", 100, 0, 6, 100, 4, 8)
frame.Draw()

# Data
mb_colors = [ROOT.kOrange+7, ROOT.kOrange+7, ROOT.kOrange+7, ROOT.kOrange+7]

# Geometry
mb_height = 0.3

# Keep references alive
drawn_objects = []

radius=[4.2,5.0, 6.05, 7.1]

rpc_radius=[4.15, 4.50, 4.95, 5.30, 6.0, 7.05]
rpc_height=0.05

stubs=[1,1,2,2]

# Draw boxes and labels
r_base = 4.2
for j in range(4):
    r1 = radius[j-1]#r_base + j * (mb_height + mb_spacing)
    r2 = r1 + mb_height

    # Box for chamber
    box = ROOT.TBox(0.0, r1, 6.0, r2)
    box.SetFillColorAlpha(mb_colors[j], 0.3)
    box.SetLineColor(mb_colors[j])
    box.SetLineWidth(2)
    box.Draw("same")
    drawn_objects.append(box)

# Draw RPC
for j in range(6):
    r1 = rpc_radius[j-1]#r_base + j * (mb_height + mb_spacing)
    r2 = r1 + rpc_height

    # Box for chamber
    box = ROOT.TBox(0.0, r1, 6.0, r2)
    box.SetFillColorAlpha(ROOT.kBlue, 0.3)
    box.SetLineColor(ROOT.kBlue)
    box.SetLineWidth(2)
    box.Draw("same")
    drawn_objects.append(box)

for j in range(0,4):
    r1 = radius[j]#r_base + j * (mb_height + mb_spacing)
    r2 = r1 + mb_height

    # Box for chamber
    box = ROOT.TBox(stubs[j]-0.1, r1, stubs[j]+0.1, r2)
    box.SetFillColor(1)
    box.SetLineColor(1)
    box.SetLineWidth(2)
    box.Draw("same")
    drawn_objects.append(box)


# Final update
c.Update()
c.SaveAs("scheme.png")
