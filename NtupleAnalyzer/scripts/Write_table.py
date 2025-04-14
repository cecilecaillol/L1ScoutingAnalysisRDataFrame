import ROOT
import os
import csv

def extract_last_bin_content(root_file, hist_name1, hist_name2, output_csv):
    # Open the ROOT file
    file = ROOT.TFile.Open(root_file, "READ")
    if not file or file.IsZombie():
        print(f"Error: Cannot open file {root_file}")
        return
    
    # Prepare output storage
    data = []
    
    # Iterate over keys in the ROOT file
    for key in file.GetListOfKeys():
        obj = key.ReadObj()
        
        # Check if the object is a directory
        if isinstance(obj, ROOT.TDirectory):
            dir_name = obj.GetName()
            
            # Retrieve histograms
            hist1 = obj.Get(hist_name1)
            hist2 = obj.Get(hist_name2)
            
            # Ensure histograms exist and are TH1 types
            if isinstance(hist1, ROOT.TH1) and isinstance(hist2, ROOT.TH1) and "fail" not in dir_name and "wrong" not in dir_name:
                last_bin1 = round(hist1.GetBinContent(hist1.GetNbinsX()),2)
                last_bin2 = round(hist2.GetBinContent(hist2.GetNbinsX()),2)
                significance = round(0.1*last_bin2/((0.1*last_bin2+10*last_bin1)**0.5),2)
                data.append([dir_name, last_bin1, last_bin2, significance])
            #else:
            #    print(f"Warning: Histograms missing in {dir_name}")

    # Close the ROOT file
    file.Close()

    # Write to CSV
    with open(output_csv, mode="w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["Directory", f"{hist_name1}_LastBin", f"{hist_name2}_LastBin"])
        writer.writerows(data)
    
    print(f"Output written to {output_csv}")

# Example usage
extract_last_bin_content("datacard.root", "Fake", "Jian", "output.csv")

