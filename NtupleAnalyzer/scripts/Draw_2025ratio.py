import uproot
import matplotlib.pyplot as plt
import mplhep as hep

# Apply CMS style
plt.style.use(hep.style.CMS)

# Input ROOT files
file1 = "output_2025/ZeroBias_2025D_part15.root"
file2 = "output_2025/Selection_2025D_part15.root"

directories = [
    "stub4_bx1112", "stub4_bx1122", "stub4_bx1222", "stub4_bx123",
    "stub4_bx124", "stub4_bx1234", "stub3_bx112_slow", "stub3_bx112_fast",
    "stub3_bx122_slow", "stub3_bx122_fast", "stub3_bx123_slow", "stub3_bx123_fast",
    "stub3_bx124_slow", "stub3_bx124_fast"
]

ratios = []

# Open files with uproot
with uproot.open(file1) as f1, uproot.open(file2) as f2:
    for d in directories:
        h1 = f1[f"{d}/data_obs"]
        h2 = f2[f"{d}/data_obs"]

        # Compute integrals
        integral1 = h1.to_hist().values().sum()
        integral2 = h2.to_hist().values().sum()

        ratio = integral1 / integral2 if integral2 != 0 else float("nan")
        print(integral1,integral2,ratio)
        ratios.append(ratio)

# Plot
fig, ax = plt.subplots(figsize=(12,6))
ax.bar(range(len(directories)), ratios, tick_label=directories)
ax.set_ylabel("ZeroBias / Selection")
ax.set_xlabel("Category")
plt.xticks(rotation=45, ha="right")
#plt.title("")
plt.tight_layout()

# Add CMS label
hep.cms.label(ax=ax, data=True, year=2025)

plt.savefig("ratio_2025.png")

