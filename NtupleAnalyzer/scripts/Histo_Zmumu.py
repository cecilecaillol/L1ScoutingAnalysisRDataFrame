import sys
sys.path.append("..")
from pyFunc.gethisto import variable,gethisto,getdf
from ROOT import TFile
import numpy as np

varname = sys.argv[1]
sample = sys.argv[2]
print (varname)

mmumu=variable("mmumu","m_{#mu#mu}",int(20),np.arange(0,220,10,dtype=float))

my_df = getdf("testL1Mu_{}".format(sample))
h_OS = gethisto(my_df,"data_obs","isOS","OS","xsweight",mmumu)
h_SS = gethisto(my_df,"data_obs","!isOS","SS","xsweight",mmumu)
#h_OS = gethisto(my_df,"data_obs","isOS && SkimmedL1Mu_hwQual[0]>12 && SkimmedL1Mu_hwQual[1]>12","OS","xsweight",mmumu)
#h_SS = gethisto(my_df,"data_obs","!isOS && SkimmedL1Mu_hwQual[0]>12 && SkimmedL1Mu_hwQual[1]>12","SS","xsweight",mmumu)


fout = TFile("output_Zmumu/{}.root".format(sample),"recreate")
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
fout.Close()

