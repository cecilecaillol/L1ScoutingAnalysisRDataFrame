import matplotlib.pyplot as plt

# Layer (Y-axis) names and positions
layers = ["MB1", "MB2", "MB3", "MB4"]
y_positions = range(1, len(layers) + 1)

# Vertical line (X-axis) names and positions
bx_labels = ["BX1", "BX2", "BX3", "BX4"]
x_positions = range(1, len(bx_labels) + 1)

# Example circle positions (configurable): (x_index, y_index)
#circle_positions = [(1, 1), (2, 2), (3, 3), (4, 4)] #1234
#circle_positions = [(1, 1), (1, 2), (2, 3), (2, 4)] #1122
#circle_positions = [(1, 1), (1, 2), (1, 3), (2, 4)] #1112
#circle_positions = [(1, 1), (2, 2), (1, 3), (1, 4)] #1211
circle_positions = [(1, 1), (1, 2), (2, 3), (1, 4)] #1121

fig, ax = plt.subplots(figsize=(4, 4))
fig.patch.set_edgecolor("black")
fig.patch.set_linewidth(1.0)
fig.patch.set_facecolor("white")

# --- Draw horizontal layers ---
for y, label in zip(y_positions, layers):
    ax.hlines(y, x_positions[0] - 0.5, x_positions[-1] + 0.5, colors="black", linewidth=0.8)
    ax.text(x_positions[0] - 0.7, y, label, va="center", ha="right", fontsize=15)

# --- Draw vertical dashed lines ---
for x, label in zip(x_positions, bx_labels):
    ax.vlines(x, y_positions[0] - 0.5, y_positions[-1] + 0.5, colors="black", linestyles="dashed")
    ax.text(x, y_positions[0] - 0.7, label, ha="center", va="top", fontsize=15)

# --- Draw filled circles at specified intersections ---
for (x, y) in circle_positions:
    ax.plot(x, y, "o", color="red", markersize=10)

# --- Add double-headed arrow (BX separation = 25 ns) ---
y_arrow = y_positions[-1] + 0.7  # place arrow above top labels
ax.annotate(
    "",
    xy=(x_positions[0], y_arrow),
    xytext=(x_positions[1], y_arrow),
    arrowprops=dict(arrowstyle="<->", color="blue"),
)
ax.text((x_positions[0] + x_positions[1]) / 2, y_arrow + 0.1, "25 ns",
        ha="center", va="bottom", fontsize=15, color="blue")

# --- Add double-headed arrow (MB3-MB4 separation ~1m) ---
x_arrow = x_positions[-1] + 0.6  # place arrow to the right of BX4
ax.annotate(
    "",
    xy=(x_arrow, y_positions[2]),   # MB3
    xytext=(x_arrow, y_positions[3]),  # MB4
    arrowprops=dict(arrowstyle="<->", color="blue"),
)
ax.text(x_arrow + 0.1, (y_positions[2] + y_positions[3]) / 2, "~1 m",
        ha="left", va="center", fontsize=15, color="blue", rotation=90)

# --- Add general label below the plot ---
ax.text((x_positions[0] + x_positions[-1]) / 2, y_positions[0] - 1.3, "BX1112 background",
        ha="center", va="top", fontsize=18, fontweight="bold")

# --- Formatting ---
ax.set_xlim(x_positions[0] - 1, x_positions[-1] + 1)
ax.set_ylim(y_positions[0] - 1, y_positions[-1] + 1)
ax.set_xticks([])
ax.set_yticks([])
ax.set_frame_on(False)

#plt.savefig("BX1234_diagram.png")
#plt.savefig("BX1234_diagram.pdf")
#plt.savefig("BX1122_diagram.png")
#plt.savefig("BX1122_diagram.pdf")
#plt.savefig("BX1112_diagram.png")
#plt.savefig("BX1112_diagram.pdf")
plt.savefig("BX1121_diagram.png")
plt.savefig("BX1121_diagram.pdf")
#plt.savefig("BX1211_diagram.png")
#plt.savefig("BX1211_diagram.pdf")

