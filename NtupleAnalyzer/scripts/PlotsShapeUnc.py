import uproot
import numpy as np
import matplotlib.pyplot as plt
import mplhep as hep
import re

# Use CMS style
plt.style.use(hep.style.CMS)

# CMS-friendly palette
colors = {
    "nominal": "#5790fc",   # blue
    "up": "#f89c20",        # orange
    "down": "#d62728"       # CMS red
}

# Input ROOT file
filename = "datacard.root"
file = uproot.open(filename)

# Directories to process
dirs = [
    "stub4_bx1112","stub4_bx1122","stub4_bx1222","stub4_bx123","stub4_bx124","stub4_bx1234",
    "stub3_bx112_slow","stub3_bx112_fast","stub3_bx122_slow","stub3_bx122_fast",
    "stub3_bx123_slow","stub3_bx123_fast","stub3_bx124_slow","stub3_bx124_fast",
    "stub4_bx1112_2tracks","stub4_bx1122_2tracks","stub4_bx1222_2tracks",
    "stub3_bx112_slow_2tracks","stub3_bx112_fast_2tracks","stub3_bx122_slow_2tracks","stub3_bx122_fast_2tracks"
]

# Loop over directories
for d in dirs:
    dir_content = file[d]
    keys = dir_content.keys()

    # Find nominal histogram
    nominal_key = [k for k in keys if re.fullmatch(r"Fake;.*", k) or k.startswith("Fake")][0]
    nominal_root = dir_content[nominal_key]  # TH1 object
    nominal = nominal_root.to_hist()

    # Bin edges, centers, values, and errors
    bin_edges = nominal.axes[0].edges
    x_centers = nominal.axes[0].centers
    y_nom = nominal.values()
    err_nom = np.sqrt(nominal_root.member("fSumw2"))[1:-1]  # skip underflow/overflow

    # Find Up and Down histograms
    up_key = [k for k in keys if re.match(r"Fake.*Up", k)][0]
    down_key = [k for k in keys if re.match(r"Fake.*Down", k)][0]
    up = dir_content[up_key].to_hist()
    down = dir_content[down_key].to_hist()

    # Values for Up/Down
    y_up = up.values()
    y_down = down.values()

    # Ratios and ratio errors
    ratio_nom = np.ones_like(y_nom)
    ratio_up = y_up / y_nom
    ratio_down = y_down / y_nom
    err_ratio_nom = err_nom / y_nom  # fractional

    # Create figure with ratio subplot
    fig, (ax, rax) = plt.subplots(
        2, 1,
        gridspec_kw={"height_ratios": (3, 1)},
        sharex=True
    )

    # --- Top panel ---
    # Nominal as step + error bars
    ax.step(bin_edges, np.r_[y_nom, y_nom[-1]], where="post", color=colors["nominal"], label="Nominal")
    ax.errorbar(x_centers, y_nom, yerr=err_nom, fmt="o", color=colors["nominal"])
    # Up/Down as steps with same bin edges
    ax.step(bin_edges, np.r_[y_up, y_up[-1]], where="post", color=colors["up"], label="Up variation")
    ax.step(bin_edges, np.r_[y_down, y_down[-1]], where="post", color=colors["down"], label="Down variation")

    ax.set_ylabel("Entries")
    ax.set_ylim(bottom=0)
    ax.legend()

    # CMS label
    hep.cms.label(ax=ax, data=True, lumi=3.7, com=13.6)

    # Add directory name
    ax.text(0.22, 0.92, d, transform=ax.transAxes, fontsize=18, ha='left', va='top')

    # --- Ratio panel ---
    rax.axhline(1.0, color="black", linestyle="--", linewidth=1)
    # Nominal uncertainty band
    #rax.fill_between(bin_edges[:-1], 1 - err_ratio_nom, 1 + err_ratio_nom,
    #                 step="post", color=colors["nominal"], alpha=0.3)

    # Nominal ratio uncertainty band
    ratio_err_low = 1 - err_ratio_nom
    ratio_err_high = 1 + err_ratio_nom

    # Extend arrays to match bin_edges length
    ratio_err_low_ext = np.r_[ratio_err_low, ratio_err_low[-1]]
    ratio_err_high_ext = np.r_[ratio_err_high, ratio_err_high[-1]]

    rax.fill_between(
      bin_edges,
      ratio_err_low_ext,
      ratio_err_high_ext,
      step="post",
      color=colors["nominal"],
      alpha=0.3
    )

    # Up/Down ratios
    rax.step(bin_edges, np.r_[ratio_up, ratio_up[-1]], where="post", color=colors["up"])
    rax.step(bin_edges, np.r_[ratio_down, ratio_down[-1]], where="post", color=colors["down"])

    rax.set_ylabel("Ratio")
    rax.set_xlabel(r"$p_T$ (GeV)")
    rax.set_ylim(0.0, 2.0)

    # Save plot
    plt.tight_layout()
    plt.savefig(f"{d}_shape.png")
    plt.close()

