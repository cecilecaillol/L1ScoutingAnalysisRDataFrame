import ROOT
import os
import numpy as np
import matplotlib.pyplot as plt
import mplhep as hep

# Avoid ROOT popups
ROOT.gROOT.SetBatch(True)

# Use CMS style
plt.style.use(hep.style.CMS)

is_mu = True  # set False for MET-based triggers

# MASS range
mass_values = range(1000, 6001, 500)
means = []

for mass in mass_values:
    path = f"/eos/cms/store/group/cmst3/group/slowmuons/HSCPtauPrime_{mass}/KBMTFsim_HLT/total.root"
    if not os.path.isfile(path):
        print(f"File not found: {path}")
        means.append(np.nan)
        continue

    f = ROOT.TFile.Open(path)
    if not f or f.IsZombie():
        print(f"Could not open file: {path}")
        means.append(np.nan)
        continue

    tree = f.Get("Events")
    if not tree:
        print(f"No 'Events' tree in file: {path}")
        means.append(np.nan)
        f.Close()
        continue

    # Draw into a temporary histogram (values 0 or 1)
    if is_mu:
        tree.Draw("HLT_IsoMu24||HLT_Mu50>>temp(2,-0.5,1.5)", "", "goff")
    else:
        tree.Draw(
            "HLT_PFMET120_PFMHT120_IDTight||"
            "HLT_PFHT500_PFMET100_PFMHT100_IDTight||"
            "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60||"
            "HLT_MET105_IsoTrk50>>temp(2,-0.5,1.5)", "", "goff"
        )

    temp_hist = ROOT.gDirectory.Get("temp")
    mean_val = temp_hist.GetMean()
    print(f"MASS {mass}: Mean trigger efficiency = {mean_val:.4f}")
    means.append(mean_val)

    f.Close()

# --- Plotting with mplhep ---
fig, ax = plt.subplots(figsize=(9, 6))

# marker + line
#ax.plot(mass_values, means, "o-", markersize=6, label=r"Nonres. $\tau'$ pair")
ax.plot(np.array(mass_values) / 1000, means, "o-", markersize=9, label=r"Nonres. $\tau'$ pair")


ax.set_xlabel(r"$m_{\tau'}$ (TeV)")
if is_mu:
    ax.set_ylabel("Single muon HLT efficiency")
else:
    ax.set_ylabel("MET-based HLT efficiency")

ax.set_ylim(0.00, 1.00)
ax.set_xlim(1, 6)

#hep.cms.label(ax=ax, llabel="Work in Progress", rlabel="13.6 TeV")
hep.cms.label("Preliminary", data = False, com="13.6")

ax.legend()

if is_mu:
    plt.savefig("eff_IsoMu24.png", dpi=300, bbox_inches="tight")
    plt.savefig("eff_IsoMu24.pdf", dpi=300, bbox_inches="tight")
else:
    plt.savefig("eff_METHLT.png", dpi=300, bbox_inches="tight")
    plt.savefig("eff_METHLT.pdf", dpi=300, bbox_inches="tight")


