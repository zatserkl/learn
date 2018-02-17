# NumPy, 3rd Edition.pdf, p.77

"""Simple Moving Average as an example of convolution
"""

from __future__ import print_function
import numpy as np
import matplotlib.pyplot as plt

fname = "moving_average.csv"

N = 5

weights = np.ones(N) / N
print("Weights", weights)

# NB: comma in usecols=(6,) because just one column is specified
# AZ: in my python works without that comma as well
# c = np.loadtxt('data.csv', delimiter=',', usecols=(6,), unpack=True)
c = np.loadtxt(fname, delimiter=',', usecols=(6), unpack=True)
print(c)

# sma_all = np.convolve(weights, c)     # how many in total?
# print("len(sma_all) =", len(sma_all)) # len(sma_all) = 34
print("len(np.convolve(weights, c)) =", len(np.convolve(weights, c)))

#
# The total convolution adds N-1 = 4 points in the beginning and in the end
#

sma = np.convolve(weights, c)[N-1:-N+1] # discard the first and the last 4 points

# NB: sma[0] here is the first point built on the 100% data points.
# It is shifted on N-1 points wrt to the original data,
# so they will plot data starting from c[N-1] point.

print("len(c) =", len(c), "len(sma) =", len(sma)) # len(c) = 30, len(sma) = 34

t = np.arange(N - 1, len(c))    # threw away N-1 = 4 elements

# len(c)        = 30
# len(sma_all)  = 34
# len(sma)      = 26

# For the plot they discard the first 4 points:
# The first point is c[N-1], so c[4]
# So, there is no symmetry for the beginning and for the end.
# Of course, this is arbitrary, it's up to you...

plt.plot(t, c[N-1:], lw=1.0, label="Data")
plt.plot(t, sma, '--', lw=2.0, label="Moving average")
plt.title("5 Day Moving Average")
plt.xlabel("Days")
plt.ylabel("Price ($)")
plt.grid()
plt.legend()
plt.show()
