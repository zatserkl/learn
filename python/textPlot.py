# modified from Introduction to Python for Engineers and Scientists

# from __future__ import print_function

import matplotlib.pyplot as plt
import numpy as np


x = np.arange(0, 2*np.pi, .01)
y = np.sin(x)
# plt.figure(figsize=(6, 4))          # to set size this way use before plot
plt.plot(x, y, color='r')
plt.text(0.1, -0.04, '$sin(0) = 0$')
plt.text(1.5, 0.9, '$sin(90) = 1$')
plt.text(2.0, 0, '$sin(180) = 0$')
plt.text(4.5, -0.9, '$sin(270) = -1$')
plt.text(6.0, 0.0, '$sin(360) = 1$')
plt.annotate('$sin(theta)=0$', xy=(3, 0.1), xytext=(5, 0.7),
             arrowprops=dict(facecolor='green', shrink=0.05))
plt.title('Inserting text and annotation in plots')
plt.xlabel('$theta$')
plt.ylabel('$y = sin( theta)$')
plt.grid(True)
# plt.gcf().set_size_inches(6.5, 5)   # gcf: get current figure
plt.show()
