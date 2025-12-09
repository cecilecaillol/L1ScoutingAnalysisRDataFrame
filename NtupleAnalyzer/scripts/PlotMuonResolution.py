import uproot
import numpy as np
import matplotlib.pyplot as plt
import mplhep as hep
from scipy.optimize import curve_fit

# === Gaussian Function ===
def gaussian_norm(x, mu, sigma):
    return 1 / (sigma * np.sqrt(2 * np.pi)) * np.exp(-(x - mu)**2 / (2 * sigma**2))

# === Load ROOT Histogram ===
filename = "output_ZmumuKBMTF/DY.root"
histname = "h_reso"

with uproot.open(filename) as f:
    hist = f[histname]
    values = hist.values()
    edges = hist.axis().edges()
    bin_widths = np.diff(edges)
    centers = (edges[1:] + edges[:-1]) / 2
    errors = np.sqrt(values)  # Poisson errors

area = np.sum(values * bin_widths)
values_norm = values / area
errors_norm = errors / area

# === Fit Gaussian ===
popt, pcov = curve_fit(gaussian_norm, centers, values_norm, p0=[centers[np.argmax(values_norm)], 1.0])
mu_fit, sigma_fit = popt
perr = np.sqrt(np.diag(pcov))

# === Plotting ===
plt.style.use(hep.style.CMS)

fig, ax = plt.subplots()

# Histogram
ax.errorbar(centers, values_norm, yerr=errors_norm, fmt='o', label="DY simulation", color="black")

# Fit curve
x_fit = np.linspace(edges[0], edges[-1], 1000)
y_fit = gaussian_norm(x_fit, *popt)
ax.plot(x_fit, y_fit, label="Gaussian fit", color="red")

# CMS label
hep.cms.label("", data=False, com="13.6", loc=0)

# Fit parameters text
fit_text = (
    r"$\sigma = {:.2f}$".format(sigma_fit)
)
ax.text(0.65, 0.75, fit_text, transform=ax.transAxes, fontsize=28)

# Labels
ax.set_xlim(-1, 1)
ax.set_xlabel(r"Muon (reco. - gen.) / gen. $p_{T}$", fontsize=28)
ax.set_ylabel("Arbitrary units", fontsize=28)
ax.legend(fontsize=25)

plt.tight_layout()
plt.savefig("muon_resolution.png")
plt.savefig("muon_resolution.pdf")

