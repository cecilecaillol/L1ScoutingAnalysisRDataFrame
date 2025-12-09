import ROOT
import os

# Load ROOT in batch mode to avoid GUI popups
ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)

# === Configuration ===
input_file_path = "datacard.root"  # Change this to your actual file
output_dir = "plots"
os.makedirs(output_dir, exist_ok=True)

# === Open the ROOT file ===
file = ROOT.TFile.Open(input_file_path)
if not file or file.IsZombie():
    raise RuntimeError(f"Cannot open file: {input_file_path}")

# === Loop through directories in the file ===
#for dirname in ["stub4_bx1234", "stub4_bx1234_fail","stub3_bx123_slow", "stub3_bx123_slow_fail","stub3_bx123_fast", "stub3_bx123_fast_fail","stub4_bx123", "stub4_bx123_fail","stub3_bx124_slow", "stub3_bx124_slow_fail","stub3_bx124_fast", "stub3_bx124_fast_fail","stub4_bx1122", "stub4_bx1122_fail","stub4_bx1112", "stub4_bx1112_fail","stub4_bx1222", "stub4_bx1222_fail","stub3_bx112_slow", "stub3_bx112_slow_fail","stub3_bx112_fast", "stub3_bx112_fast_fail","stub3_bx122_slow", "stub3_bx122_slow_fail","stub3_bx122_fast", "stub3_bx122_fast_fail","stub4_bx124", "stub4_bx124_fail"]:
for dirname in ["stub4_bx1112","stub4_bx1122","stub4_bx1222","stub4_bx123","stub4_bx124","stub4_bx1234", "stub3_bx112_slow","stub3_bx112_fast","stub3_bx122_slow","stub3_bx122_fast", "stub3_bx123_slow","stub3_bx123_fast","stub3_bx124_slow","stub3_bx124_fast", "stub4_bx1112_2tracks","stub4_bx1122_2tracks","stub4_bx1222_2tracks",  "stub3_bx112_slow_2tracks","stub3_bx112_fast_2tracks","stub3_bx122_slow_2tracks","stub3_bx122_fast_2tracks"]:
    hist_names = [k.GetName() for k in file.Get(dirname).GetListOfKeys()]
    base_hist_name = "Fake"
    up_hist_name = next((name for name in hist_names if name.startswith("Fake") and name.endswith("Up")), None)
    down_hist_name = next((name for name in hist_names if name.startswith("Fake") and name.endswith("Down")), None)

    if base_hist_name not in hist_names or not up_hist_name or not down_hist_name:
        print(f"  Skipping {dir_name}: required histograms not found.")
        continue

    # Get histograms
    h_base = file.Get(dirname).Get(base_hist_name)
    h_up = file.Get(dirname).Get(up_hist_name)
    h_down = file.Get(dirname).Get(down_hist_name)

    # Create canvas and draw
    canvas = ROOT.TCanvas("c", "c", 800, 600)
    h_base.SetLineColor(ROOT.TColor.GetColor("#f89c20"))
    h_up.SetLineColor(ROOT.TColor.GetColor("#964a8b"))
    h_down.SetLineColor(ROOT.TColor.GetColor("#e42536"))

    h_base.SetLineWidth(2)
    h_up.SetLineWidth(2)
    h_down.SetLineWidth(2)

    h_base.SetTitle("")
    h_base.GetXaxis().SetTitle("p_{T} (GeV)")
    h_base.GetYaxis().SetTitle("Events")
    h_base.SetMaximum(1.5*h_base.GetMaximum())
    h_base.SetMinimum(0.0)
    h_base.Draw("HIST")
    h_base.Draw("ESAME")
    h_up.Draw("HIST SAME")
    h_down.Draw("HIST SAME")

    # Add legend
    legend = ROOT.TLegend(0.65, 0.75, 0.88, 0.88)
    legend.AddEntry(h_base, "Background", "l")
    legend.AddEntry(h_up, "Shape up", "l")
    legend.AddEntry(h_down, "Shape down", "l")
    legend.Draw()

    lumixs  = ROOT.TPaveText(0.3, 0.78, 0.5, 0.85, "NDC")
    lumixs.SetTextFont(42)
    lumixs.SetTextSize(0.04)
    lumixs.SetBorderSize(   0 )
    lumixs.SetFillStyle(    0 )
    lumixs.SetTextAlign(   12 )
    lumixs.SetTextColor(    1 )
    lumixs.AddText(dirname)
    lumixs.Draw("same")


    # Save the plot
    output_path = os.path.join(output_dir, f"syst_{dirname}.png")
    canvas.SaveAs(output_path)
    print(f"  Saved plot to: {output_path}")

# Close the file
file.Close()

