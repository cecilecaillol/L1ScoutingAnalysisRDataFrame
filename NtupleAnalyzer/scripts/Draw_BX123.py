import matplotlib.pyplot as plt

# Layer (Y-axis) names and positions
layers = ["MB1", "MB2", "MB3", "MB4"]
y_positions = range(1, len(layers) + 1)

# Vertical line (X-axis) names and positions
bx_labels = ["BX1", "BX2", "BX3", "BX4"]
x_positions = range(1, len(bx_labels) + 1)

# Example sets of circle positions for 2 diagrams
#circle_sets = [ #fast
#    [(1, 1), (2, 2), (3, 4)],
#    [(1, 1), (2, 3), (3, 4)],
#]
circle_sets = [ #slow
    [(1, 1), (2, 2), (3, 3)],
    [(2, 2), (3, 3), (4, 4)],
]

def draw_diagram(ax, circle_positions):
    # --- Draw horizontal layers ---
    for y, label in zip(y_positions, layers):
        ax.hlines(y, x_positions[0] - 0.5, x_positions[-1] + 0.5,
                  colors="black", linewidth=0.8)
        ax.text(x_positions[0] - 0.7, y, label,
                va="center", ha="right", fontsize=15)

    # --- Draw vertical dashed lines ---
    for x, label in zip(x_positions, bx_labels):
        ax.vlines(x, y_positions[0] - 0.5, y_positions[-1] + 0.5,
                  colors="black", linestyles="dashed")
        ax.text(x, y_positions[0] - 0.7, label,
                ha="center", va="top", fontsize=15)

    # --- Draw filled circles ---
    for (x, y) in circle_positions:
        ax.plot(x, y, "o", color="red", markersize=10)

    # --- Add double-headed arrow (BX separation = 25 ns) ---
    y_arrow = y_positions[-1] + 0.7
    ax.annotate("", xy=(x_positions[0], y_arrow), xytext=(x_positions[1], y_arrow),
                arrowprops=dict(arrowstyle="<->", color="blue"))
    ax.text((x_positions[0] + x_positions[1]) / 2, y_arrow + 0.1, "25 ns",
            ha="center", va="bottom", fontsize=15, color="blue")

    # --- Add double-headed arrow (MB3-MB4 separation ~1m) ---
    x_arrow = x_positions[-1] + 0.6
    ax.annotate("", xy=(x_arrow, y_positions[2]), xytext=(x_arrow, y_positions[3]),
                arrowprops=dict(arrowstyle="<->", color="blue"))
    ax.text(x_arrow + 0.1, (y_positions[2] + y_positions[3]) / 2, "~1 m",
            ha="left", va="center", fontsize=15, color="blue", rotation=90)

    # --- Formatting ---
    ax.set_xlim(x_positions[0] - 1, x_positions[-1] + 1)
    ax.set_ylim(y_positions[0] - 1, y_positions[-1] + 1)
    ax.set_xticks([])
    ax.set_yticks([])
    ax.set_frame_on(False)


# Create 1x2 grid of subplots
fig, axes = plt.subplots(1, 2, figsize=(10, 5))

# Draw each diagram
for ax, circles in zip(axes.flat, circle_sets):
    draw_diagram(ax, circles)

# Single label below both plots
fig.text(0.5, 0.02, "BX123 slow", ha="center", va="center",
         fontsize=15, fontweight="bold")

plt.tight_layout(rect=[0, 0.05, 1, 1])  # leave space for bottom label
plt.savefig("BX123_slow.png")
plt.savefig("BX123_slow.pdf")

