if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--year')
    options = parser.parse_args()

    fin=ROOT.TFile("out_data.root","r")
    fout=ROOT.TFile("out_fake.root","recreate")

    categories=["stub4_bx1234","stub4_bx1245","stub3_bx123_fast","stub3_bx123_slow","stub4_bx123","stub3_bx124","stub2_bx12","stub2_bx12_station12","stub3_bx112","stub3_bx122","stub4_bx1122","stub4_bx1112","stub4_bx1222","stub4_bx124"]

    categories_met=["samebx_metm1","samebx_metm2","samebx_metm3","samebx_metm4",
            "stub2bx12_metm1","stub2bx12_metm2","stub2bx12_metm3","stub2bx12_metm4"]

    for categ in categories:

       h_right=fin.Get(categ).Get("data_obs")
       h_wrong=fin.Get(categ+"_wrong").Get("data_obs")
       h_right_fail=fin.Get(categ+"_fail").Get("data_obs")
       h_wrong_fail=fin.Get(categ+"_wrong_fail").Get("data_obs")

       if h_wrong.GetBinContent(1)>0: print(categ,h_right.GetBinContent(1)/h_wrong.GetBinContent(1))
       if h_wrong_fail.GetBinContent(1)>0: print(categ,"fail",h_right_fail.GetBinContent(1)/h_wrong_fail.GetBinContent(1))
       if h_wrong.GetBinContent(1)>0: h_wrong.Scale(h_right.GetBinContent(1)/h_wrong.GetBinContent(1))
       if h_wrong_fail.GetBinContent(1)>0: h_wrong_fail.Scale(h_right_fail.GetBinContent(1)/h_wrong_fail.GetBinContent(1))

       dir1=fout.mkdir(categ)
       dir1.cd()
       h_wrong.SetName("Fake")
       h_wrong.Write()

       dir2=fout.mkdir(categ+"_fail")
       dir2.cd()
       h_wrong_fail.SetName("Fake")
       h_wrong_fail.Write()

    for categm in categories_met:

       h_right=fin.Get(categm).Get("data_obs")
       h_right_fail=fin.Get(categm+"_fail").Get("data_obs")

       print(h_right.GetBinContent(3)/(h_right_fail.GetBinContent(3)+0.1))
       h_right_fail.Scale(h_right.GetBinContent(3)/(h_right_fail.GetBinContent(3)+0.1))

       dir1=fout.mkdir(categm)
       dir1.cd()
       h_right_fail.SetName("Fake")
       h_right_fail.Write()

