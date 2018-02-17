# errorbar example

# Python and Matplotlib Essentials for Scientists and Engineers.pdf, p. 10-5

import numpy as np
import matplotlib.pyplot as plt

# generate some fake data
x = np.arange(10) + 2*np.random.randn(10)
y = np.arange(10) + 2*np.random.randn(10)

# generate fake errors for the data
xerr = 2*np.random.random(10)
yerr = 2*np.random.random(10)

plt.errorbar(x,y,xerr=xerr,yerr=yerr,fmt='bo')
plt.show()
