import matplotlib.pyplot as plt
import numpy as np
import ternary

#---------------------------------

inp_name = "test3d.dat"

#---------------------------------

fig, tax = ternary.figure(scale=1)

tax.gridlines(multiple=0.10, color="grey")
tax.boundary(linewidth=2.0)
tax.get_axes().axis('off')
tax.clear_matplotlib_ticks()
tax.ticks(axis='lbr', linewidth=1, multiple=0.1, offset=0.02, tick_formats="%2.1f")

tax.top_corner_label("$S_1$")
tax.left_corner_label("$P_2$")
tax.right_corner_label("$P_3$")

axs = tax.scatter(np.genfromtxt(inp_name), marker='.', color='grey', s=2, picker=10)
axs.set_aspect(1.0)
axs.set_clip_on(False)

plt.savefig("test3d.png", bbox_inches='tight')
#                         ^^^^^^^^^^^^^^^^^^^ Needed to show corner labels
