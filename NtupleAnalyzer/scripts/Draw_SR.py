#!/usr/bin/env python
import ROOT
import re
import argparse
from array import array

is_datadriven=1

def add_lumi():
    lowX=0.55
    lowY=0.825
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.SetTextSize(0.06)
    lumi.SetTextFont (   42 )
    lumi.AddText("ZB 2024GHI (13.6 TeV)")
    return lumi

def add_CMS():
    lowX=0.16
    lowY=0.825
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(61)
    lumi.SetTextSize(0.06)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("CMS")
    return lumi

def add_Preliminary():
    lowX=0.28
    lowY=0.825
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(52)
    lumi.SetTextSize(0.06)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("Internal")
    return lumi

def make_legend():
        output = ROOT.TLegend(0.5, 0.65, 0.92, 0.86, "", "brNDC")
        output.SetNColumns(2)
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
        output.SetTextFont(62)
        return output

def make_legend2():
        output = ROOT.TLegend(0.45, 0.6, 0.92, 0.86, "", "brNDC")
        output.SetNColumns(2)
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
        output.SetTextFont(62)
        return output

ROOT.gStyle.SetOptStat(0)
ROOT.gROOT.SetBatch(True)

#parser = argparse.ArgumentParser()
#parser.add_argument('--year', '-y', default=None, help='Output name')
#parser.add_argument('--channel', '-c', default=None, help='Output name')
#args = parser.parse_args()


c=ROOT.TCanvas("canvas","",0,0,800,800)
c.cd()
#c.SetLogy()

file=ROOT.TFile("datacard.root","r")

adapt=ROOT.gROOT.GetColor(12)
new_idx=ROOT.gROOT.GetListOfColors().GetSize() + 1
trans=ROOT.TColor(new_idx, adapt.GetRed(), adapt.GetGreen(),adapt.GetBlue(), "",0.5)

categories=["stub4_bx1234", "stub4_bx1234_fail","stub3_bx123_slow", "stub3_bx123_slow_fail","stub3_bx123_fast", "stub3_bx123_fast_fail","stub4_bx123", "stub4_bx123_fail","stub3_bx124", "stub3_bx124_fail","samebx_metm1","samebx_metm2","samebx_metm3","samebx_metm4","stub4_bx1245", "stub4_bx1245_fail","stub4_bx1122", "stub4_bx1122_fail","stub4_bx1112", "stub4_bx1112_fail","stub4_bx1222", "stub4_bx1222_fail","stub3_bx112", "stub3_bx112_fail","stub3_bx122", "stub3_bx122_fail","stub2_bx12", "stub2_bx12_fail","stub2_bx12_station12", "stub2_bx12_station12_fail","stub4_bx124", "stub4_bx124_fail","stub2bx12_metm1","stub2bx12_metm2","stub2bx12_metm3","stub2bx12_metm4"]
name=["stub4_bx1234", "stub4_bx1234_fail","stub3_bx123_slow", "stub3_bx123_slow_fail","stub3_bx123_fast", "stub3_bx123_fast_fail","stub4_bx123", "stub4_bx123_fail","stub3_bx124", "stub3_bx124_fail", "samebx_metm1","samebx_metm2","samebx_metm3","samebx_metm4","stub4_bx1245", "stub4_bx1245_fail","stub4_bx1122", "stub4_bx1122_fail","stub4_bx1112", "stub4_bx1112_fail","stub4_bx1222", "stub4_bx1222_fail","stub3_bx112", "stub3_bx112_fail","stub3_bx122", "stub3_bx122_fail","stub2_bx12", "stub2_bx12_fail","stub2_bx12_station12", "stub2_bx12_station12_fail","stub4_bx124", "stub4_bx124_fail","stub2bx12_metm1","stub2bx12_metm2","stub2bx12_metm3","stub2bx12_metm4"]
title=["p_{T} (GeV)","p_{T} (GeV)","p_{T} (GeV)","p_{T} (GeV)","p_{T} (GeV)","p_{T} (GeV)","p_{T} (GeV)","p_{T} (GeV)", "MET (GeV)", "MET (GeV)", "MET (GeV)", "MET (GeV)","p_{T} (GeV)","p_{T} (GeV)","p_{T} (GeV)","p_{T} (GeV)","p_{T} (GeV)","p_{T} (GeV)","p_{T} (GeV)","p_{T} (GeV)","p_{T} (GeV)","p_{T} (GeV)","p_{T} (GeV)","p_{T} (GeV)","p_{T} (GeV)","p_{T} (GeV)","p_{T} (GeV)","p_{T} (GeV)","p_{T} (GeV)","p_{T} (GeV)","p_{T} (GeV)","p_{T} (GeV)","MET (GeV)", "MET (GeV)", "MET (GeV)", "MET (GeV)"]
ncat=len(name)

for i in range (0,ncat):
   print(categories[i])
   Data=file.Get(categories[i]).Get("data_obs")
   Fake=file.Get(categories[i]).Get("Fake")
   Signal = file.Get(categories[i]).Get("Jian")
   HSCP2600 = file.Get(categories[i]).Get("HSCP2600")
   HSCP4000 = file.Get(categories[i]).Get("HSCP4000")
   HSCP6000 = file.Get(categories[i]).Get("HSCP6000")

   #if "wrong" not in categories[i] and "fail" not in categories[i] and "metm3" not in categories[i] and "metm4" not in categories[i]:
   #    for k in range(4,Data.GetNbinsX()+1):
   #        Data.SetBinContent(k,0)
   #        Data.SetBinError(k,0)

   #    if Data.GetNbinsX()+1<6:
   #        for k in range(3,Data.GetNbinsX()+1):
   #           Data.SetBinContent(k,0)
   #           Data.SetBinError(k,0)

   Data.GetXaxis().SetTitle("")
   Data.GetXaxis().SetTitleSize(0)
   Data.GetXaxis().SetNdivisions(505)
   Data.GetYaxis().SetLabelFont(42)
   Data.GetYaxis().SetLabelOffset(0.01)
   Data.GetYaxis().SetLabelSize(0.06)
   Data.GetYaxis().SetTitleSize(0.075)
   Data.GetYaxis().SetTitleOffset(1.04)
   Data.SetTitle("")
   Data.GetYaxis().SetTitle("Events/bin")
   Data.SetMinimum(0.0)

   Fake.SetFillColor(ROOT.TColor.GetColor("#5790fc"))

   Data.SetMarkerStyle(20)
   Data.SetMarkerSize(1)
   Fake.SetLineColor(1)
   Data.SetLineColor(1)
   Data.SetLineWidth(2)
   Signal.SetLineColor(2)
   Signal.SetLineWidth(5)
   HSCP2600.SetLineColor(ROOT.TColor.GetColor("#f89c20"))
   HSCP2600.SetLineWidth(5)
   HSCP4000.SetLineColor(ROOT.TColor.GetColor("#964a8b"))
   HSCP4000.SetLineWidth(5)
   HSCP6000.SetLineColor(ROOT.TColor.GetColor("#e42536"))
   HSCP6000.SetLineWidth(5)

   stack=ROOT.THStack("stack","stack")
   stack.Add(Fake)

   errorBand = Fake.Clone()

   errorBand.SetMarkerSize(0)
   errorBand.SetFillColor(new_idx)
   errorBand.SetFillStyle(3001)
   errorBand.SetLineWidth(1)

   pad1 = ROOT.TPad("pad1","pad1",0,0.35,1,1)
   pad1.Draw()
   pad1.cd()
   pad1.SetFillColor(0)
   pad1.SetBorderMode(0)
   pad1.SetBorderSize(10)
   pad1.SetTickx(1)
   pad1.SetTicky(1)
   pad1.SetLeftMargin(0.18)
   pad1.SetRightMargin(0.05)
   pad1.SetTopMargin(0.122)
   pad1.SetBottomMargin(0.026)
   pad1.SetFrameFillStyle(0)
   pad1.SetFrameLineStyle(0)
   pad1.SetFrameBorderMode(0)
   pad1.SetFrameBorderSize(10)
   pad1.SetLogy()

   Data.GetXaxis().SetLabelSize(0)
   Data.SetMinimum(0.1)
   Data.SetMaximum(20.0*max(Data.GetMaximum(),HSCP4000.GetMaximum()))
   Data.Draw("e")
   stack.Draw("histsame")
   errorBand.Draw("e2same")
   Data.Draw("esame")
   #Signal.Draw("histsame")
   HSCP2600.Draw("histsame")
   HSCP4000.Draw("histsame")
   HSCP6000.Draw("histsame")

   legende=make_legend()
   if "inverted" in name[i]:
      legende=make_legend2()
   legende.AddEntry(Data,"Observed","elp")
   legende.AddEntry(Fake,"Background","f")
   #legende.AddEntry(Signal,"Signal","l")
   legende.AddEntry(HSCP2600,"m = 2.6 TeV","l")
   legende.AddEntry(HSCP4000,"m = 4 TeV","l")
   legende.AddEntry(HSCP6000,"m = 6 TeV","l")
   legende.AddEntry(errorBand,"Uncertainty","f")
   legende.Draw()

   l1=add_lumi()
   l1.Draw("same")
   l2=add_CMS()
   l2.Draw("same")
   l3=add_Preliminary()
   l3.Draw("same")

   lumixs  = ROOT.TPaveText(0.2, 0.78, 0.5, 0.85, "NDC")
   lumixs.SetTextFont(42)
   lumixs.SetTextSize(0.04)
   lumixs.SetBorderSize(   0 )
   lumixs.SetFillStyle(    0 )
   lumixs.SetTextAlign(   12 )
   lumixs.SetTextColor(    1 )
   lumixs.AddText("#sigma(HSCP) = 1 pb")
   lumixs.Draw("same")

   pad1.RedrawAxis()

   c.cd()
   pad2 = ROOT.TPad("pad2","pad2",0,0,1,0.35);
   pad2.SetTopMargin(0.05);
   pad2.SetBottomMargin(0.35);
   pad2.SetLeftMargin(0.18);
   pad2.SetRightMargin(0.05);
   pad2.SetTickx(1)
   pad2.SetTicky(1)
   pad2.SetGridx()
   pad2.SetGridy()
   pad2.Draw()
   pad2.cd()
   h1=Data.Clone()
   h1.SetMaximum(1.7)
   h1.SetMinimum(0.3)
   h1.SetMarkerStyle(20)
   h3=errorBand.Clone()
   hwoE=errorBand.Clone()
   for iii in range (1,hwoE.GetSize()-1):
     hwoE.SetBinError(iii,0)
   h3.Sumw2()
   h1.Sumw2()
   h1.SetStats(0)
   h1.Divide(hwoE)
   h3.Divide(hwoE)
   h1.GetXaxis().SetTitle(title[i])
   h1.GetXaxis().SetLabelSize(0.08)
   h1.GetYaxis().SetLabelSize(0.08)
   h1.GetYaxis().SetTitle("Obs./Exp.")
   h1.GetXaxis().SetNdivisions(505)
   h1.GetYaxis().SetNdivisions(5)

   h1.GetXaxis().SetTitleSize(0.15)
   h1.GetYaxis().SetTitleSize(0.15)
   h1.GetYaxis().SetTitleOffset(0.56)
   h1.GetXaxis().SetTitleOffset(1.04)
   h1.GetXaxis().SetLabelSize(0.11)
   h1.GetYaxis().SetLabelSize(0.11)
   h1.GetXaxis().SetTitleFont(42)
   h1.GetYaxis().SetTitleFont(42)

   h1.Draw("e0p")
   h3.Draw("e2same")

   c.cd()
   pad1.Draw()

   ROOT.gPad.RedrawAxis()

   c.Modified()
   c.SaveAs("plots/"+name[i]+".pdf")
   c.SaveAs("plots/"+name[i]+".png")

