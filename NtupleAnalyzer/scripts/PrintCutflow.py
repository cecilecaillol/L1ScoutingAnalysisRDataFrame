import ROOT
import os

ROOT.gROOT.SetBatch(True)

# Mass points
#mass_points = list(range(1000, 6001, 500))
#mass_points = list(range(1000, 5501, 500))
#mass_points = list(range(1000, 5001, 500))
mass_points = list(range(1000, 4001, 500))
#mass_points = list(range(1000, 3501, 500))
#mass_points = list(range(4000, 6001, 500))

# Store normalized bin contents
cutflow_data = {mass: [] for mass in mass_points}

# Read histograms
for mass in mass_points:
    #filename = f"out_GluinoBall{mass}.root"
    filename = f"out_ZPrimeTo2TauPrime_ratio3p0_{mass}.root"
    if not os.path.isfile(filename):
        print(f"File {filename} not found. Skipping.")
        continue

    file = ROOT.TFile.Open(filename)
    hist = file.Get("h_cutflow")
    if not hist:
        print(f"Histogram 'h_cutflow' not found in {filename}. Skipping.")
        continue

    norm = hist.GetBinContent(1)
    for i in range(1, 26):  # ROOT bins are 1-indexed
        content = hist.GetBinContent(i)
        normed = content / norm if norm != 0 else 0
        cutflow_data[mass].append(normed)

    file.Close()

# Format to LaTeX scientific notation
def format_latex_scientific(x):
    if x == 0:
        return "$0$"
    exponent = int(f"{x:.2e}".split("e")[1])
    base = float(f"{x:.2e}".split("e")[0])
    return f"${base:.3g}\\times 10^{{{exponent}}}$"

# Create LaTeX table
latex = []
latex.append("\\begin{tabular}{c|" + "l" * len(mass_points) + "}")
latex.append(" & " + " & ".join([f"{mass} \GeV" for mass in mass_points]) + " \\\\")
latex.append("\\hline")

for bin_idx in range(25):
    #row = [f"{bin_idx + 1}"]
    row=[]
    if bin_idx==0: row=["All"]
    elif bin_idx==1: row=["Reco track"]
    elif bin_idx==2: row=["$d_{xy}<1$"]
    elif bin_idx==3: row=["At least 3 stubs"]
    elif bin_idx==4: row=["Quality"]
    elif bin_idx==5: row=["$>1$ BX"]
    elif bin_idx==6: row=["3 stubs"]
    elif bin_idx==7: row=["$\pt>50\GeV$"]
    elif bin_idx==8: row=["2nd track"]
    elif bin_idx==9: row=["stub3\_bx124\_slow"]
    elif bin_idx==10: row=["stub3\_bx124\_fast"]
    elif bin_idx==11: row=["stub3\_bx123\_slow"]
    elif bin_idx==12: row=["stub3\_bx123\_fast"]
    elif bin_idx==13: row=["stub3\_bx122\_slow"]
    elif bin_idx==14: row=["stub3\_bx122\_fast"]
    elif bin_idx==15: row=["stub3\_bx112\_slow"]
    elif bin_idx==16: row=["stub3\_bx112\_fast"]
    elif bin_idx==17: row=["4 stubs"]
    elif bin_idx==18: row=["stub4\_bx124"]
    elif bin_idx==19: row=["stub4\_bx123"]
    elif bin_idx==20: row=["stub4\_bx1234"]
    elif bin_idx==21: row=["stub4\_bx1222"]
    elif bin_idx==22: row=["stub4\_bx1122"]
    elif bin_idx==23: row=["stub4\_bx1112"]
    for mass in mass_points:
        if mass in cutflow_data and bin_idx < len(cutflow_data[mass]):
            value = cutflow_data[mass][bin_idx]
            formatted = format_latex_scientific(value)
        else:
            formatted = "---"
        row.append(formatted)
    latex.append(" & ".join(row) + " \\\\")
latex.append("\\hline")
latex.append("\\end{tabular}")

# Write LaTeX to file
with open("cutflow_table.tex", "w") as f:
    for line in latex:
        f.write(line + "\n")

print("Formatted LaTeX table written to cutflow_table.tex")

