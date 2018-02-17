from __future__ import division
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import norm

#########################################
# norm.pdf(x) = exp(-x**2/2)/sqrt(2*pi) #
#########################################

x = np.linspace(-10,10, 100)    # 100 points

loc = 0                         # mean

scale = 1.                      # sigma
y = norm.pdf(x, loc, scale)

scale = 3.
y1 = norm.pdf(x, loc, scale)
y2 = norm.pdf((x - loc)/scale) / scale  # the same as previous

plt.plot(x, y)
plt.plot(x, y1)
plt.plot(x, y2, '--')           # superimpose dashed line
plt.show()
