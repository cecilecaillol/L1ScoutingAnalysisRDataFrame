import ROOT
import math
ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetPadTickX(1)
ROOT.gStyle.SetPadTickY(1)

# Canvas
c = ROOT.TCanvas("c", "CMS DT Structure", 600, 669)
#c.SetGrid()

# Frame
frame = ROOT.TH2F("frame", ";z (m);R (m)", 100, 0, 7.0, 100, 0, 8)
frame.GetXaxis().SetTitleSize(0.06)
frame.GetYaxis().SetTitleSize(0.06)
frame.GetXaxis().SetTitleOffset(0.7)
frame.GetYaxis().SetTitleOffset(0.7)
frame.Draw()

# Data
wheel_z = [-5.35, -2.65, 0.0, 2.65, 5.35]
wheel_names = ["Wheel -2", "Wheel -1", "Wheel 0", "Wheel +1", "Wheel +2"]
mb_labels = ["MB4", "MB1", "MB2", "MB3"]
#mb_colors = [ROOT.kRed, ROOT.kOrange+7, ROOT.kGreen+2, ROOT.kBlue]
mb_colors = [ROOT.kOrange+7, ROOT.kOrange+7, ROOT.kOrange+7, ROOT.kOrange+7]

# Geometry
mb_height = 0.3
mb_spacing = 0.01
mb_z_half = 1.275

# Keep references alive
drawn_objects = []

radius=[4.2,5.0, 6.05, 7.1]

rpc_radius=[4.15, 4.50, 4.95, 5.30, 6.0, 7.05]
rpc_height=0.05

# Draw boxes and labels
for i, z_center in enumerate(wheel_z):
    r_base = 4.2
    for j in range(4):
        r1 = radius[j-1]#r_base + j * (mb_height + mb_spacing)
        r2 = r1 + mb_height

        # Box for chamber
        box = ROOT.TBox(max(0.0,z_center - mb_z_half), r1, z_center + mb_z_half, r2)
        box.SetFillColorAlpha(mb_colors[j], 0.3)
        box.SetLineColor(mb_colors[j])
        box.SetLineWidth(2)
        box.Draw("same")
        drawn_objects.append(box)

        # Label for chamber
        if i==3: 
           label = ROOT.TLatex(z_center, (r1 + r2)/2, mb_labels[j])
           label.SetTextAlign(22)
           label.SetTextSize(0.038)
           label.Draw()
           drawn_objects.append(label)

    # Label for wheel
    if (abs(z_center)<0.4): z_center=0.7
    wheel_label = ROOT.TLatex(z_center, r2 + 1.4, wheel_names[i])
    wheel_label.SetTextAlign(22)
    wheel_label.SetTextSize(0.038)
    wheel_label.SetTextColor(ROOT.kBlack)
    wheel_label.Draw()
    drawn_objects.append(wheel_label)

# Draw RPC
for i, z_center in enumerate(wheel_z):
    for j in range(6):
        r1 = rpc_radius[j-1]#r_base + j * (mb_height + mb_spacing)
        r2 = r1 + rpc_height

        # Box for chamber
        box = ROOT.TBox(max(0.0,z_center - mb_z_half), r1, z_center + mb_z_half, r2)
        box.SetFillColorAlpha(ROOT.kBlue, 0.3)
        box.SetLineColor(ROOT.kBlue)
        box.SetLineWidth(2)
        box.Draw("same")
        drawn_objects.append(box)

# Pseudorapidity lines
eta_values = [0.2, 0.4, 0.6, 0.8, 1.0, 1.2]
for eta in eta_values:
    graph = ROOT.TGraph()
    for z in range(-7, 8, 1):
        r = abs(z) * math.tan(2 * math.atan(math.exp(-eta)))
        if r < 80:
            graph.SetPoint(graph.GetN(), z, r)
    graph.SetLineStyle(2)
    graph.SetLineColor(ROOT.kGray + 2)
    graph.SetLineWidth(1)
    graph.Draw("L")
    drawn_objects.append(graph)

    # Label for #
    y_eta = 7 * math.tan(2 * math.atan(math.exp(-eta)))
    x_eta=7.1
    if y_eta>=8: 
        y_eta=8.1
        x_eta=8.0/math.tan(2 * math.atan(math.exp(-eta)))
    else:
        x_eta=7.1
    eta_label = ROOT.TLatex(x_eta, y_eta, f"#eta={eta}")
    eta_label.SetTextSize(0.038)
    eta_label.SetTextColor(ROOT.kGray + 2)
    eta_label.Draw()
    drawn_objects.append(eta_label)

legend = ROOT.TLegend(0.65, 0.2, 0.9, 0.35)
legend.AddEntry(drawn_objects[0],"DTs","f")
legend.AddEntry(drawn_objects[30],"RPCs","f")
legend.Draw("same")

# Final update
c.Update()
c.SaveAs("MB.png")
c.SaveAs("MB.pdf")
