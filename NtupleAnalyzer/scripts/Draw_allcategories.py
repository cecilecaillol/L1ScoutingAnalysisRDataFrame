import matplotlib.pyplot as plt

# Layer (Y-axis) names and positions
layers = ["MB1", "MB2", "MB3", "MB4"]
y_positions = range(1, len(layers) + 1)

# Vertical line (X-axis) names and positions
bx_labels = ["BX1", "BX2", "BX3", "BX4"]
x_positions = range(1, len(bx_labels) + 1)

# --- Example dictionary of categories (truncated for brevity) ---

categories = {
    "BX1112": [
        [(1, 1), (1, 2), (1, 3), (2, 4)],
    ],
    "BX1122": [
        [(1, 1), (1, 2), (2, 3), (2, 4)],
    ],
    "BX1222": [
        [(1, 1), (2, 2), (2, 3), (2, 4)],
    ],
    "BX1234": [
        [(1, 1), (2, 2), (3, 3), (4, 4)],
    ],
    "BX123": [
        [(1, 1), (1, 2), (2, 3), (3, 4)],
        [(1, 1), (2, 2), (2, 3), (3, 4)],
        [(1, 1), (2, 2), (3, 3), (3, 4)],
    ],
    "BX124": [
        [(1, 1), (1, 2), (2, 3), (4, 4)],
        [(1, 1), (2, 2), (2, 3), (4, 4)],
        [(1, 1), (2, 2), (4, 3), (4, 4)],
        [(1, 1), (1, 2), (3, 3), (4, 4)],
        [(1, 1), (3, 2), (3, 3), (4, 4)],
        [(1, 1), (3, 2), (4, 3), (4, 4)],
    ],
    "BX112slow": [
        [(1, 1), (1, 2), (2, 3)],
        [(1, 2), (1, 3), (2, 4)],
    ],
    "BX112fast": [
        [(1, 1), (1, 2), (2, 4)],
        [(1, 1), (1, 3), (2, 4)],
    ],
    "BX122slow": [
        [(1, 1), (2, 2), (2, 3)],
        [(1, 2), (2, 3), (2, 4)],
    ],
    "BX122fast": [
        [(1, 1), (2, 2), (2, 4)],
        [(1, 1), (2, 3), (2, 4)],
    ],
    "BX123slow": [
        [(1, 1), (2, 2), (3, 3)],
        [(1, 2), (2, 3), (3, 4)],
    ],
    "BX123fast": [
        [(1, 1), (2, 2), (3, 4)],
        [(1, 1), (2, 3), (3, 4)],
    ],
    "BX124slow": [
        [(1, 1), (2, 2), (4, 3)],
        [(1, 2), (2, 3), (4, 4)],
        [(1, 1), (3, 2), (4, 3)],
        [(1, 2), (3, 3), (4, 4)],
    ],
    "BX124fast": [
        [(1, 1), (2, 2), (4, 4)],
        [(1, 1), (2, 3), (4, 4)],
        [(1, 1), (3, 2), (4, 4)],
        [(1, 1), (3, 3), (4, 4)],
    ],
    ## ... fill in all 14 categories with 1-6 sets each
}

def format_label(cat_name: str) -> str:
    """Convert category name (used for filename) into a nice display label."""
    label = cat_name
    if "124" in label:
        label = label.replace("124", "124/134")
    if label.endswith("fast"):
        label = label.replace("fast", " fast")
    if label.endswith("slow"):
        label = label.replace("slow", " slow")
    return label

def draw_single_diagram(ax, circle_positions):
    """Draw one diagram in a given Axes."""
    # --- Draw horizontal layers ---
    for y, layer_label in zip(y_positions, layers):
        ax.hlines(y, x_positions[0] - 0.5, x_positions[-1] + 0.5,
                  colors="black", linewidth=0.8)
        ax.text(x_positions[0] - 0.7, y, layer_label, va="center",
                ha="right", fontsize=15)

    # --- Draw vertical dashed lines ---
    for x, bx_label in zip(x_positions, bx_labels):
        ax.vlines(x, y_positions[0] - 0.5, y_positions[-1] + 0.5,
                  colors="black", linestyles="dashed")
        ax.text(x, y_positions[0] - 0.7, bx_label, ha="center",
                va="top", fontsize=15)

    # --- Draw filled circles ---
    for (x, y) in circle_positions:
        ax.plot(x, y, "o", color="red", markersize=8)

    # --- Double-headed arrow (BX separation = 25 ns) ---
    y_arrow = y_positions[-1] + 0.7
    ax.annotate(
        "", xy=(x_positions[0], y_arrow), xytext=(x_positions[1], y_arrow),
        arrowprops=dict(arrowstyle="<->", color="blue")
    )
    ax.text((x_positions[0] + x_positions[1]) / 2, y_arrow + 0.1, "25 ns",
            ha="center", va="bottom", fontsize=15, color="blue")

    # --- Double-headed arrow (MB3-MB4 separation ~1m) ---
    x_arrow = x_positions[-1] + 0.6
    ax.annotate(
        "", xy=(x_arrow, y_positions[2]), xytext=(x_arrow, y_positions[3]),
        arrowprops=dict(arrowstyle="<->", color="blue")
    )
    ax.text(x_arrow + 0.1, (y_positions[2] + y_positions[3]) / 2, "~1 m",
            ha="left", va="center", fontsize=15, color="blue", rotation=90)

    # --- Formatting ---
    ax.set_xlim(x_positions[0] - 1, x_positions[-1] + 1)
    ax.set_ylim(y_positions[0] - 1, y_positions[-1] + 1)
    ax.set_xticks([])
    ax.set_yticks([])
    ax.set_frame_on(False)


# --- Main loop over categories ---
for cat_name, diagrams in categories.items():
    n = len(diagrams)

    # ---- Layout logic ----
    if n == 4:
        ncols, nrows = 2, 2  # special case
    else:
        ncols = min(n, 3)
        nrows = (n + ncols - 1) // ncols  # ceil division

    # ---- Create figure and axes ----
    fig, axes = plt.subplots(nrows, ncols, figsize=(4*ncols, 4*nrows))

    # --- Thin frame around figure ---
    fig.patch.set_edgecolor("black")
    fig.patch.set_linewidth(1.0)
    fig.patch.set_facecolor("white")

    # Flatten axes safely into list
    if isinstance(axes, plt.Axes):
        axes = [axes]
    else:
        axes = axes.flatten()

    # Draw each diagram
    for i, circle_positions in enumerate(diagrams):
        draw_single_diagram(axes[i], circle_positions)

    # Hide unused subplots
    for j in range(len(diagrams), len(axes)):
        axes[j].axis("off")

    # Add pretty label
    fig.text(0.5, 0.02, format_label(cat_name), ha="center", va="bottom",
             fontsize=18, fontweight="bold")

    fig.patch.set_edgecolor("black")
    fig.patch.set_linewidth(1.0)
    fig.patch.set_facecolor("white")


    plt.tight_layout(rect=[0, 0.05, 1, 1])  # leave space for label
    plt.savefig(f"{cat_name}_diagram.png")
    plt.savefig(f"{cat_name}_diagram.pdf")
    plt.close()

print("All diagrams saved.")

