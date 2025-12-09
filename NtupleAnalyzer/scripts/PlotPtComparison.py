import uproot
import matplotlib.pyplot as plt
import mplhep as hep

# Set CMS style
plt.style.use(hep.style.CMS)

# Open the ROOT file
file = uproot.open("out_HSCP4000.root")

# Extract histograms
h_before = file["h_ptbefore"]
h_after = file["h_ptafter"]

# Convert to numpy arrays
values_before, edges_before = h_before.to_numpy()
values_after, edges_after = h_after.to_numpy()

# Create the figure
fig, ax = plt.subplots()

# Plot both histograms
hep.histplot(values_before, edges_before, label="Before smearing", histtype='step', color='blue', ax=ax)
hep.histplot(values_after, edges_after, label="After smearing", histtype='step', color='red', ax=ax)

# CMS label
hep.cms.label(ax=ax, label="Preliminary", data=False, com=13.6)  
# Adjust lumi/year to your dataset

# Legend
ax.legend()

# Axis labels
ax.set_xlabel("pT [GeV]")
ax.set_ylabel("Events")

plt.tight_layout()
plt.savefig("ptsmearing.png")

