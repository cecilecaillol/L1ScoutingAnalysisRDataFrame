#!/usr/bin/env python
import ROOT
import re
import argparse
from array import array
import ctypes

is_datadriven=1

def add_lumi():
    lowX=0.6
    lowY=0.83
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
    lowX=0.21
    lowY=0.70
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(62)
    lumi.SetTextSize(0.08)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("CMS")
    return lumi

def add_Preliminary():
    lowX=0.21
    lowY=0.6
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(52)
    lumi.SetTextSize(0.06)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("Internal")
    #lumi.AddText("")
    return lumi

def make_legend():
        output = ROOT.TLegend(0.36, 0.65, 0.9, 0.87, "", "brNDC")
        output.SetNColumns(2)
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
        output.SetTextFont(62)
        return output

ROOT.gStyle.SetOptStat(0)
ROOT.gROOT.SetBatch(True)

parser = argparse.ArgumentParser()
parser.add_argument('--selection', '-s', default=None, help='Output name')
args = parser.parse_args()


c=ROOT.TCanvas("canvas","",0,0,800,800)
c.cd()
c.SetLogy()

myfile=ROOT.TFile("datacard_"+args.selection+".root","r")

adapt=ROOT.gROOT.GetColor(12)
new_idx=ROOT.gROOT.GetListOfColors().GetSize() + 1
trans=ROOT.TColor(new_idx, adapt.GetRed(), adapt.GetGreen(),adapt.GetBlue(), "",0.5)

dirOS=["OS"]
name=["mmumu"]
xaxis=["m_{#mu#mu} (GeV)"]
if args.selection=="ZmumuKBMTF":
    dirOS=["OS","met_OS","nstub_OS"]
    name=["mmumu","met","nstub"]
    xaxis=["m_{#mu#mu} (GeV)","MET (GeV)","N(stub)"]

sf=1.0
for k in range(0,len(dirOS)):
   Data=myfile.Get(dirOS[k]).Get("data_obs").Clone()
   DY=myfile.Get(dirOS[k]).Get("DY").Clone()
   Fake=myfile.Get(dirOS[k]).Get("Fake").Clone()
   
   if k==0 and Fake.GetBinContent(1)>0: 
       sf=(Data.GetBinContent(1)-DY.GetBinContent(1))/(Fake.GetBinContent(1))
       print(sf)
       #Fake.Scale(sf)
       print((Data.Integral()-Fake.Integral())/DY.Integral())
   Fake.Scale(sf)
   print((Data.Integral()-Fake.Integral())/DY.Integral())
   
   Data.GetXaxis().SetTitle("")
   Data.GetXaxis().SetTitleSize(0)
   Data.GetXaxis().SetNdivisions(505)
   Data.GetYaxis().SetLabelFont(42)
   Data.GetYaxis().SetLabelOffset(0.01)
   Data.GetYaxis().SetLabelSize(0.06)
   Data.GetYaxis().SetTitleSize(0.08)
   Data.GetYaxis().SetTitleOffset(1.1)
   Data.SetTitle("")
   Data.GetYaxis().SetTitle("Events")
   Data.SetMinimum(0.1)

   #print((Data.GetBinContent(1)-Fake.GetBinContent(1))/DY.GetBinContent(1))
   #print((Data.GetBinContent(2)-Fake.GetBinContent(2))/DY.GetBinContent(2))
   #print((Data.GetBinContent(3)-Fake.GetBinContent(3))/DY.GetBinContent(3))
   
   
   DY.SetFillColor(ROOT.TColor.GetColor("#5790fc"))
   Fake.SetFillColor(ROOT.TColor.GetColor("#e42536"))
   
   Data.SetMarkerStyle(20)
   Data.SetMarkerSize(1)
   DY.SetLineColor(1)
   Fake.SetLineColor(1)
   Data.SetLineColor(1)
   Data.SetLineWidth(2)
   
   
   stack=ROOT.THStack("stack","stack")
   stack.Add(Fake)
   stack.Add(DY)
   
   Total=DY.Clone()
   Total.Add(Fake)
   
   errorBand = Total.Clone()
   
   errorBand.SetMarkerSize(0)
   errorBand.SetFillColor(new_idx)
   errorBand.SetFillStyle(3001)
   errorBand.SetLineWidth(1)
   errorBand.SetLineColor(1)
   
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
   #pad1.SetLogy()
   
   Data.GetXaxis().SetLabelSize(0)
   Data.SetMaximum(max(Data.GetMaximum()*1.55,errorBand.GetMaximum()*1.55))
   Data.SetMinimum(0.1)
   Data.Draw("e")
   stack.Draw("histsame")
   errorBand.Draw("e2same")
   Data.Draw("esame")
   
   legende=make_legend()
   legende.AddEntry(Data,"Observed ","elp")
   legende.AddEntry(Fake,"Nonprompt","f")
   legende.AddEntry(DY,"Z/#gamma* #rightarrow #mu#mu","f")
   legende.AddEntry(errorBand,"Stat. unc. ","f")
   legende.Draw()
   
   l1=add_lumi()
   l1.Draw("same")
   l2=add_CMS()
   l2.Draw("same")
   l3=add_Preliminary()
   l3.Draw("same")
   
   lowX=0.06
   lowY=0.85
   lumi1  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
   lumi1.SetBorderSize(   0 )
   lumi1.SetFillStyle(    0 )
   lumi1.SetTextAlign(   12 )
   lumi1.SetTextColor(    1 )
   lumi1.SetTextSize(0.05)
   lumi1.SetTextFont (   42 )
   if args.selection=="ZmumuKBMTF": 
       lumi1.AddText("re-KBMTF, |#eta| < 0.83, p_{T} > 15 GeV")
   else:
       lumi1.AddText("L1 muons, |#eta| < 0.83, p_{T} > 15 GeV")
   lumi1.Draw("same")
   
   pad1.RedrawAxis()
   
   c.cd()
   pad2 = ROOT.TPad("pad2","pad2",0,0,1,0.35);
   pad2.SetTopMargin(0.05);
   pad2.SetBottomMargin(0.35);
   pad2.SetLeftMargin(0.18);
   pad2.SetRightMargin(0.05);
   pad2.SetTickx(1)
   pad2.SetTicky(1)
   pad2.Draw()
   pad2.cd()
   
   h1=Data.Clone()
   h1.SetMaximum(1.8)
   h1.SetMinimum(0.2)
   h1.SetMarkerStyle(20)
   h3=errorBand.Clone()
   hwoE=errorBand.Clone()
   for iii in range (1,hwoE.GetSize()-1):
     hwoE.SetBinError(iii,0)
   #h3.Sumw2()
   #h1.Sumw2()
   h1.SetStats(0)
   h1.Divide(hwoE)
   h3.Divide(hwoE)
   h1.GetXaxis().SetTitle(xaxis[k])
   h1.GetXaxis().SetLabelSize(0.08)
   h1.GetYaxis().SetLabelSize(0.08)
   h1.GetYaxis().SetTitle("Obs./Exp.")
   h1.GetXaxis().SetNdivisions(505)#was 505
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
   h1.Draw("e0psame")
   
   ROOT.gPad.RedrawAxis()
   c.cd()
   pad1.Draw()
   ROOT.gPad.RedrawAxis()
   c.Modified()
   c.SaveAs("plots/"+args.selection+"_"+name[k]+".pdf")
   c.SaveAs("plots/"+args.selection+"_"+name[k]+".png")

