# Introduction to Python for Engineers and Scientists.pdf

import matplotlib.pyplot as pl
import numpy as np

x = np.arange(0, 4, 0.2) # generated data point from 0 to 4 with step of 0.2
y = 2*x # y = e^(-x)

print x                #[0.   0.2  0.4 0.6 0.8 1. 1.2 1.4 1.6 1.8  2. 2.2 2.4 2.6 2.8 3.  3.2 3.4 3.6 3.8]

err_positive = np.array([0.5, .1, .1, .2, .1, .5, .9, .2, .9, .2, .2, .2, .3, .2, .3, .1, .2, .2, .3, .4])
err_negative = np.array([0.2, .4, .3, .1, .4, .3, .1, .9, .1, .3, .5, .0, .5, .1, .2, .6, .3, .4, .1, .1])

pl.errorbar(x, y, yerr=[err_negative, err_positive], ecolor='r') # fixed book's mistake
pl.title('Error bar chart with Asyymetric error')
pl.xlabel('$x$')        # italizes and removes spaces (if any)
pl.ylabel('$y$')
pl.show()
