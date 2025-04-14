#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <map>
#include <string>
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include "TSystem.h"
#include "TMath.h" //M_PI is in TMath
#include "TRandom3.h"
#include <TLorentzVector.h>

void WriteHistToFile(TFile* myfile, TH1F* hist, std::string name, TString dir_name){
    TDirectory *dir =myfile->mkdir(dir_name);
    dir->cd();
    for (int j=0; j<hist->GetSize()-1; ++j){
      if (hist->GetBinContent(j)<0) hist->SetBinContent(j,0);
    }
    //include overflow in last bin
    hist->SetBinContent(hist->GetSize()-2,hist->GetBinContent(hist->GetSize()-2)+hist->GetBinContent(hist->GetSize()-1));
    hist->SetBinError(hist->GetSize()-2,pow(hist->GetBinError(hist->GetSize()-2)*hist->GetBinError(hist->GetSize()-2)+hist->GetBinError(hist->GetSize()-1)*hist->GetBinError(hist->GetSize()-1),0.5));
    hist->SetBinContent(hist->GetSize()-1,0);
    hist->SetBinError(hist->GetSize()-1,0);

    hist->SetName(name.c_str());
    hist->Write();
}

