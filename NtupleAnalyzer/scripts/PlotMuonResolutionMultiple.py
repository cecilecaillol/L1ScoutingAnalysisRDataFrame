import uproot
import numpy as np
import matplotlib.pyplot as plt
import mplhep as hep
from scipy.optimize import curve_fit
from cycler import cycler

# === Gaussian Function ===
def gaussian_norm(x, mu, sigma):
    return 1 / (sigma * np.sqrt(2 * np.pi)) * np.exp(-(x - mu)**2 / (2 * sigma**2))

# === Load ROOT File ===
filename = "output_ZmumuKBMTF/DY.root"
histnames = {
    r"15 < $p_T$ < 25 GeV": "h_reso_pt15to25",
    r"25 < $p_T$ < 35 GeV": "h_reso_pt25to35",
    r"35 < $p_T$ < 45 GeV": "h_reso_pt35to45",
    r"45 < $p_T$ < 55 GeV": "h_reso_pt45to55",
    r"55 < $p_T$ < 65 GeV": "h_reso_ptgt55"
}

# === Plotting Setup ===
plt.style.use(hep.style.CMS)
fig, ax = plt.subplots()

colors = plt.rcParams['axes.prop_cycle'].by_key()['color']
fit_results = []

# === Process Each Histogram ===
with uproot.open(filename) as f:
    for label, histname in zip(histnames.keys(), histnames.values()):
        hist = f[histname]
        values = hist.values()
        edges = hist.axis().edges()
        bin_widths = np.diff(edges)
        centers = (edges[1:] + edges[:-1]) / 2
        errors = np.sqrt(values)  # Poisson errors

        # Normalize histogram
        area = np.sum(values * bin_widths)
        values_norm = values / area
        errors_norm = errors / area

        # Fit Gaussian
        try:
            popt, pcov = curve_fit(gaussian_norm, centers, values_norm, p0=[0, 0.1])
            mu_fit, sigma_fit = popt
            perr = np.sqrt(np.diag(pcov))
            sigma_err = perr[1]
        except RuntimeError:
            mu_fit, sigma_fit, sigma_err = np.nan, np.nan, np.nan

        fit_results.append((label, sigma_fit, sigma_err))

        # Plot histogram
        color = colors[len(fit_results)-1]
        ax.errorbar(centers, values_norm, yerr=errors_norm, fmt='o', label=label, color=color)

        # Plot fit
        x_fit = np.linspace(edges[0], edges[-1], 1000)
        y_fit = gaussian_norm(x_fit, mu_fit, sigma_fit)
        ax.plot(x_fit, y_fit, color=color, linestyle='--')

# === CMS Label ===
hep.cms.label("Preliminary", data=False, com="13.6", loc=0)

# === Fit Results Text Box ===
fit_text = "\n".join(
    [f"{label}: res. = {sigma:.2f}" for label, sigma, _ in fit_results]
)
ax.text(0.65, 0.65, fit_text, transform=ax.transAxes, fontsize=14)

# === Axis Labels ===
ax.set_xlim(-1, 1)
ax.set_xlabel(r"Muon (reco. - gen.) / gen. $p_{T}$")
ax.set_ylabel("Arbitrary units")
ax.legend()

plt.tight_layout()
plt.savefig("muon_resolution_multi.png")
plt.savefig("muon_resolution_multi.pdf")

