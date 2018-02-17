"""Illustration of the Central Limit Theorem
Andriy Zatserklyaniy <zatserkl@fnal.gov> Feb 4, 2017
"""

from __future__ import division
import random, math
import matplotlib.pyplot as plt

N = 10000       # the number of sums
n = 12          # the number of randoms in each sum

#
# Central Limit Theorem
# ---------------------
# If x1, x2, ..., xN are independent and identically distributed random variables with
# mean     = mean0
# variance = var0
# then the sum x1 + x2 + ... + xn has
# mean =     n * mean0
# variance = n * variance0
# (we can use notation variance = sigma**2 above)
#
# Apply the Central Limit Theorem to sum of uniformely distributed random numbers in (0,1)
# Uniform distribution in (0,1) has
# mean0 = 0.5
# sigma = sqrt(1/12)
#
# The SUM of n numbers tends (as n goes to infinity) to have normal distribution with
# mean  = mean0 * n        = 0.5 * n
# sigma = sigma0 * sqrt(n) = sqrt(1/12) * sqrt(n) = sqrt(n/12)
#

#
# In our case the distribution of SUM of n=12 numbers has
# mean  = 12 * 0.5 = 6
# sigma = sqrt(12) * sqrt(1/12) = 1
#

random.seed(0)

x = [sum([random.random() for _ in range(n)]) for _ in range(N)]
mean = sum(x) / N
print 'mean =', mean
var = sum((xi-mean)**2 for xi in x) / (N-1)
print 'var =', var, 'sqrt(var) =', math.sqrt(var)
print 'n*1/12 = ', n*1/12, 'sqrt(n*1/12) =', math.sqrt(n*1/12)

plt.figure()
plt.hist(x)

plt.title("Distribution of %d sums of %d random numbers from range (0, 1)" % (N, n)) 

textLeft = "$\mu$ = %0.2f\n$\sigma$ = %0.2f" % (mean, math.sqrt(var))
plt.text(0.05, 0.95, textLeft, transform=plt.gca().transAxes, bbox={'fill':False}, va='top')

textRight = "$\sqrt{12}*\sqrt{1/12}$ = %0.2f" % (math.sqrt(12/12))
plt.text(0.95, 0.95, textRight, transform=plt.gca().transAxes, bbox={'fill':False}, va='top', ha='right')

plt.show()
