import uproot
import numpy as np
import matplotlib.pyplot as plt
import mplhep as hep
import matplotlib.ticker as mticker

plt.style.use(hep.style.CMS)
hep.style.use("CMS")

# === File and structure ===
filename = "datacard_ZmumuKBMTF.root"  # Replace with your actual file
directories = ["OS", "nstub_OS"]

# === Helper function to extract histogram data ===
def get_hist_data(hist):
    values = hist.values(flow=False)
    errors = hist.errors(flow=False)
    edges = hist.axis().edges()
    centers = (edges[:-1] + edges[1:]) / 2
    return centers, values, errors, edges

# === Loop over each directory ===
with uproot.open(filename) as file:
    for dir_name in directories:
        group = file[dir_name]

        # Load histograms
        h_data = group["data_obs"]
        h_dy = group["DYall"]
        h_fake = group["Fake"]

        # Get values and errors from ROOT
        x, y_data, yerr_data, edges = get_hist_data(h_data)
        _, y_dy, yerr_dy, _ = get_hist_data(h_dy)
        _, y_fake, yerr_fake, _ = get_hist_data(h_fake)

        # Stack values
        y_stack = y_dy + y_fake

        # Combine stat uncertainties in quadrature
        y_stack_err = np.sqrt(yerr_dy**2 + yerr_fake**2)

        # Plot
        fig, ax = plt.subplots()

        # Plot stacked filled histograms
        mc_weights = [y_fake, y_dy]
        mc_labels = ["Nonprompt", r"Z/$\gamma*\rightarrow\mu\mu$"]

        #ax.hist(
        #    [x, x], bins=edges, weights=mc_weights, stacked=True,
        #    label=mc_labels, histtype='stepfilled', edgecolor='black'
        #)
        ax.hist(
          [x, x], bins=edges, weights=mc_weights, stacked=True,
          label=mc_labels, histtype='stepfilled', edgecolor='black',
          color=["#f89c20", "#5790fc"]
        )

        # Plot shaded stat. uncertainty band for stacked MC
        #ax.fill_between(
        #    x, y_stack - y_stack_err, y_stack + y_stack_err,
        #    step="mid", color="gray", alpha=0.5,
        #    label="MC stat. unc."
        #)
        x_fill = edges[:-1]
        x_fill_next = edges[1:]

        ax.fill_between(
          edges,
          np.append(y_stack - y_stack_err, y_stack[-1] - y_stack_err[-1]),
          np.append(y_stack + y_stack_err, y_stack[-1] + y_stack_err[-1]),
          step="post", color="gray", alpha=0.5,
          label="MC stat. unc."
        )

        # Plot data with error bars
        ax.errorbar(x, y_data, yerr=yerr_data, fmt='o',
                    label='Data', color="black", markersize=10)

        # CMS label
        hep.cms.label("", data=True, com=13.6, lumi=3.7, loc=0)

        # Axis labels
        ax.yaxis.set_major_formatter(mticker.ScalarFormatter(useMathText=True))
        ax.ticklabel_format(axis='y', style='sci', scilimits=(0, 0))
        ax.get_yaxis().get_offset_text().set_x(-0.12)
        ax.xaxis.set_major_locator(mticker.MaxNLocator(integer=True))
        ax.set_xlim(edges[0], edges[-1])
        ax.set_xlabel(r"$m_{\mu\mu}$ (GeV)", fontsize=32)  # # Change this to your variable name
        if dir_name=="nstub_OS": ax.set_xlabel(r"$N_\mathrm{stubs}$", fontsize=32)
        ax.set_ylabel("Events", fontsize=32)
        ymax = max(np.max(y_data + yerr_data), np.max(y_stack + y_stack_err)) * 1.6
        if dir_name=="nstub_OS": ax.set_ylim(0, ymax)
        #if dir_name=="OS": ax.set_xlim(50, 150)
        if dir_name=="nstub_OS": 
           ax.text(
              0.02, 0.98,             # (x, y) position in axes coordinates (0-1 range)
              r"$m_{\mu\mu}>70$ GeV",       # The text
              transform=ax.transAxes, # Use axes coordinates instead of data coordinates
              fontsize=32,
              verticalalignment='top',
              horizontalalignment='left'
           )

        # Legend
        ax.legend(fontsize=30,loc='upper right',)

        plt.tight_layout()
        plt.savefig("validation_"+dir_name+".png")
        plt.savefig("validation_"+dir_name+".pdf")

