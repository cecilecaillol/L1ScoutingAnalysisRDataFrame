if __name__ == "__main__":

    import ROOT
    import argparse

    is_control=0

    parser = argparse.ArgumentParser()
    parser.add_argument('--selection')
    options = parser.parse_args()

    fDY=ROOT.TFile("output_"+options.selection+"/DY.root","r")
    fData=ROOT.TFile("output_"+options.selection+"/Scouting_2024.root","r")
    fout=ROOT.TFile("output_"+options.selection+"/Fake.root","recreate")

    dirOS=["OS"]
    dirSS=["SS"]
    if options.selection=="ZmumuKBMTF":
        dirOS=["OS","met_OS","nstub_OS", "pt_OS"]
        dirSS=["SS","met_SS","nstub_SS", "pt_SS"]
        
    for k in range(0,len(dirOS)):
       dir0=fout.mkdir(dirOS[k])
       h0=fData.Get(dirSS[k]+"/data_obs").Clone()
       #h0.Add(fDY.Get("SS/DY"),-1) #FIXME
       h0.SetName("Fake")
       #h0.Scale(5.12)
       #h0.Scale(6.81)
       h0.Scale(2.42)
       dir0.cd()
       h0.Write()

    fout.Close()


