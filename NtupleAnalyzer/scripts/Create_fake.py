#if __name__ == "__main__":

import ROOT
import argparse

def add_Poisson(hist_in):
    hist_out=hist_in.Clone()
    for k in range(1,hist_in.GetSize()):
        if hist_out.GetBinContent(k)<1:
            hist_out.SetBinContent(k,0.1)
            hist_out.SetBinError(k,1.8)
    return hist_out


parser = argparse.ArgumentParser()
parser.add_argument('--year')
options = parser.parse_args()

fin=ROOT.TFile("out_data.root","r")
fout=ROOT.TFile("out_fake.root","recreate")

categories=["stub4_bx1234","stub4_bx123","stub4_bx1122","stub4_bx1112","stub4_bx1222","stub4_bx124","stub3_bx123_fast","stub3_bx123_slow","stub3_bx124_fast","stub3_bx124_slow","stub3_bx112_fast","stub3_bx112_slow","stub3_bx122_fast","stub3_bx122_slow",
        "stub4_bx1122_2tracks","stub4_bx1112_2tracks","stub4_bx1222_2tracks","stub3_bx112_fast_2tracks","stub3_bx112_slow_2tracks","stub3_bx122_fast_2tracks","stub3_bx122_slow_2tracks"]

for categ in categories:

   h_right=fin.Get(categ).Get("data_obs")
   h_wrong=fin.Get(categ+"_wrong").Get("data_obs")
   h_right_fail=fin.Get(categ+"_fail").Get("data_obs")
   h_wrong_fail=fin.Get(categ+"_wrong_fail").Get("data_obs")

   h_wrongU=h_wrong.Clone()
   h_wrongD=h_wrong.Clone()
   h_wrongU_fail=h_wrong_fail.Clone()
   h_wrongD_fail=h_wrong_fail.Clone()

   h_right=add_Poisson(h_right)
   h_wrong=add_Poisson(h_wrong)
   h_right_fail=add_Poisson(h_right_fail)
   h_wrong_fail=add_Poisson(h_wrong_fail)
   h_wrongU=add_Poisson(h_wrongU)
   h_wrongD=add_Poisson(h_wrongD)
   h_wrongU_fail=add_Poisson(h_wrongU_fail)
   h_wrongD_fail=add_Poisson(h_wrongD_fail)

   if fin.Get(categ+"_wrongU"):
      h_wrongU=fin.Get(categ+"_wrongU").Get("data_obs")
      h_wrongU_fail=fin.Get(categ+"_wrongU_fail").Get("data_obs")
      h_wrongD=fin.Get(categ+"_wrongD").Get("data_obs")
      h_wrongD_fail=fin.Get(categ+"_wrongD_fail").Get("data_obs")

   #if h_wrong.GetBinContent(2)>0: print(categ,h_right.GetBinContent(2)/h_wrong.GetBinContent(2))
   #if h_wrong_fail.GetBinContent(2)>0: print(categ,"fail",h_right_fail.GetBinContent(2)/h_wrong_fail.GetBinContent(2))
   #if h_wrong.GetBinContent(2)>0: h_wrong.Scale(h_right.GetBinContent(2)/h_wrong.GetBinContent(2))
   #if h_wrong_fail.GetBinContent(2)>0: h_wrong_fail.Scale(h_right_fail.GetBinContent(2)/h_wrong_fail.GetBinContent(2))
   print(categ," & ",h_right.Integral()/(h_wrong.Integral()+0.0001)," & ",h_right_fail.Integral()/(h_wrong_fail.Integral()+0.0001))
   h_wrong.Scale(h_right.Integral()/(h_wrong.Integral()+0.0001))
   h_wrong_fail.Scale(h_right_fail.Integral()/(h_wrong_fail.Integral()+0.0001))

   dir1=fout.mkdir(categ)
   dir1.cd()
   h_wrong.SetName("Fake")
   h_wrong.Write()
   if h_wrongU and not h_wrongU.IsZombie():
       if h_wrongU.GetEntries()==h_wrongD.GetEntries():
           h_wrongD = h_wrong_fail.Clone()
           h_wrongD.Scale(h_wrong.Integral()/(0.0001+h_wrongD.Integral()))
           for j in range(1,h_wrongD.GetSize()-1):
               h_wrongU.SetBinContent(j,2*h_wrong.GetBinContent(j)-h_wrongD.GetBinContent(j))
       else:
           h_wrongU.Scale(h_wrong.Integral()/(0.0001+h_wrongU.Integral()))
           h_wrongD.Scale(h_wrong.Integral()/(0.0001+h_wrongD.Integral()))
       h_wrongU.SetName("Fake_CMS_EXO25010_shape_"+categ+"Up")
       h_wrongD.SetName("Fake_CMS_EXO25010_shape_"+categ+"Down")
       h_wrongU.Write()
       h_wrongD.Write()

   dir2=fout.mkdir(categ+"_fail")
   dir2.cd()
   h_wrong_fail.SetName("Fake")
   h_wrong_fail.Write()
   if h_wrongU_fail and not h_wrongU_fail.IsZombie():
       if h_wrongU_fail.GetEntries()==h_wrongD_fail.GetEntries():
           h_wrongD_fail = h_wrong.Clone()
           h_wrongD_fail.Scale(h_wrong_fail.Integral()/(0.0001+h_wrongD_fail.Integral()))
           for j in range(1,h_wrongD_fail.GetSize()-1):
               h_wrongU_fail.SetBinContent(j,2*h_wrong_fail.GetBinContent(j)-h_wrongD_fail.GetBinContent(j))
       else:
           h_wrongU_fail.Scale(h_wrong_fail.Integral()/(0.00001+h_wrongU_fail.Integral()))
           h_wrongD_fail.Scale(h_wrong_fail.Integral()/(0.00001+h_wrongD_fail.Integral()))
       h_wrongU_fail.SetName("Fake_CMS_EXO25010_shape_"+categ+"Up")
       h_wrongD_fail.SetName("Fake_CMS_EXO25010_shape_"+categ+"Down")
       h_wrongU_fail.Write()
       h_wrongD_fail.Write()

