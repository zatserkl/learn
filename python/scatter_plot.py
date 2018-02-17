# Introduction to Python for Engineers and Scientists.pdf

import matplotlib.pyplot as pl
import numpy as np
x = np.random.rand(1000)
y = np.random.rand(1000)
pl.scatter(x,y)
pl.title('Scatter Chart')
pl.xlabel('$x$')                # $...$ italizes and removes spaces (if any)
pl.ylabel('$y$')
pl.show()
