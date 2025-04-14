import sys
sys.path.append("..")
from pyFunc.gethisto import variable,gethisto,getdf
from ROOT import TFile
import numpy as np

varname = sys.argv[1]
sample = sys.argv[2]
print (varname)

mmumu=variable("mmumu","m_{#mu#mu}",int(20),np.arange(0,220,10,dtype=float))
#nstub1 = variable("nstub1","nstubs",int(4),np.arange(1,6,1,dtype=float))
#nstub2 = variable("nstub2","nstubs2",int(4),np.arange(1,6,1,dtype=float))

my_df = getdf("ZmumuKBMTF_{}".format(sample))
h_OS = gethisto(my_df,"data_obs","isOS","OS","xsweight",mmumu)
h_SS = gethisto(my_df,"data_obs","!isOS","SS","xsweight",mmumu)
#h_OS = gethisto(my_df,"data_obs","isOS && bxspread1==0 && bxspread2==0","OS","xsweight",mmumu)
#h_SS = gethisto(my_df,"data_obs","!isOS && bxspread1==0 && bxspread2==0","SS","xsweight",mmumu)
#h_OS = gethisto(my_df,"data_obs","isOS && L1KBMTFSkimmed_hwQual[0]>11 && L1KBMTFSkimmed_hwQual[1]>11 && bxspread1==0 && bxspread2==0","OS","xsweight",mmumu)
#h_SS = gethisto(my_df,"data_obs","!isOS && L1KBMTFSkimmed_hwQual[0]>11 && L1KBMTFSkimmed_hwQual[1]>11 && bxspread1==0 && bxspread2==0","SS","xsweight",mmumu)

#h_nstub_OS = gethisto(my_df,"data_obs","isOS && L1KBMTFSkimmed_hwQual[0]>11 && L1KBMTFSkimmed_hwQual[1]>11 && bxspread1==0 && bxspread2==0","OS","xsweight",nstub1)
#h_nstub_SS = gethisto(my_df,"data_obs","!isOS && L1KBMTFSkimmed_hwQual[0]>11 && L1KBMTFSkimmed_hwQual[1]>11 && bxspread1==0 && bxspread2==0","SS","xsweight",nstub1)
#h_nstub2_OS = gethisto(my_df,"data_obs","isOS && L1KBMTFSkimmed_hwQual[0]>11 && L1KBMTFSkimmed_hwQual[1]>11 && bxspread1==0 && bxspread2==0","OS","xsweight",nstub2)
#h_nstub2_SS = gethisto(my_df,"data_obs","!isOS && L1KBMTFSkimmed_hwQual[0]>11 && L1KBMTFSkimmed_hwQual[1]>11 && bxspread1==0 && bxspread2==0","SS","xsweight",nstub2)
#h_nstub_OS.Add(h_nstub2_OS)
#h_nstub_SS.Add(h_nstub2_SS)

fout = TFile("output_ZmumuKBMTF/{}.root".format(sample),"recreate")
dir_OS=fout.mkdir("OS")
dir_OS.cd()
if "Scouting" in sample: h_OS.SetName("data_obs")
else: h_OS.SetName(sample)
h_OS.Write()
dir_SS=fout.mkdir("SS")
dir_SS.cd()
if "Scouting" in sample: h_SS.SetName("data_obs")
else: h_SS.SetName(sample)
h_SS.Write()

#dir_nstub_OS=fout.mkdir("nstub_OS")
#dir_nstub_OS.cd()
#if "Scouting" in sample: h_nstub_OS.SetName("data_obs")
#else: h_nstub_OS.SetName(sample)
#h_nstub_OS.Write()
#dir_nstub_SS=fout.mkdir("nstub_SS")
#dir_nstub_SS.cd()
#if "Scouting" in sample: h_nstub_SS.SetName("data_obs")
#else: h_nstub_SS.SetName(sample)
#h_nstub_SS.Write()

fout.Close()

