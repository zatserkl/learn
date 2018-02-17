# -*- coding: utf-8 -*-         # set UTF-8 encoding

"""https://work.caltech.edu/homework/hw2.pdf
Run a computer simulation for flipping 1,000 virtual fair coins. 
Flip each coin independently 10 times. Focus on 3 coins as follows: 
c1 is the first coin flipped, 
crand is a coin chosen randomly from the 1,000, and 
cmin is the coin which had the minimum frequency of heads 
(pick the earlier one in case of a tie). 
Let ν1, νrand, and νmin be the fraction of heads obtained for the 
3 respective coins out of the 10 tosses.
Run the experiment 100,000 times in order to get a full distribution of 
ν1, νrand, and νmin (note that crand and cmin will change from run to run).
"""

from __future__ import division
import random
import matplotlib.pyplot as plt
import numpy as np
from collections import Counter

Ncoins = 1000
Nflips = 10
# Nrepeat = 100000      # NB: takes too long
Nrepeat = 1000

random.seed(0)

c1 = []
crand = []
cmin = []
for irepeat in range(Nrepeat):
    coins = [sum([random.choice([0,1]) for _ in range(Nflips)]) for _ in range(Ncoins)]
    c1.append(coins[0])
    crand.append(coins[random.randint(0,Ncoins-1)])
    cmin.append(min(coins))
    # print "c1 = {} crand = {} cmin = {}".format(c1, crand, cmin)
    # if irepeat > 0 and irepeat % (irepeat // 10) == 0: print 'irepeat =', irepeat
    if irepeat % 100 == 0: print irepeat,  # NB: ending comma to suppress CR
print '\n'

# scale to one flip: divide by 10

c1 = map(lambda x: x/10., c1)
crand = map(lambda x: x/10., crand)
cmin = map(lambda x: x/10., cmin)

for i in range(10): print '{:30.18f}   {:30.18f}   {:30.18f}'.format(c1[i], crand[i], cmin[i])

print "max(c1) = {} max(crand) = {}".format(max(c1), max(crand))

c1_count = Counter(c1).values()
crand_count = Counter(crand).values()
cmin_count = Counter(cmin).values()
print "c1_count\n", c1_count
print "crand_count\n", crand_count
print "cmin_count\n", cmin_count

print '\nCounter(crand):\n', Counter(crand)
crand_counter = Counter(crand)
for k in sorted(crand_counter): print k, crand_counter[k],
print '\n'

plt.figure()
plt.suptitle("Selected coins out of {}".format(Ncoins), fontsize=14)

xmin = 0
#-- xmax = 11
xmax = 1.1
nbins = 22
xbins = np.linspace(xmin, xmax, nbins+1)
xbins -= (xbins[1] - xbins[0]) / 1e12      # subtract the eps from each bin position: important if xbins are fractions like 3/10, 6/10, 7/10

plt.subplot(311)
plt.hist(c1, bins=xbins)
plt.text(0.05, 0.80, 'c1: the first coin', transform=plt.gca().transAxes)
#-- plt.xlim([0, 11])
plt.xlim([0, 1.1])

plt.subplot(312)
yval, xval, patches = plt.hist(crand, bins=xbins)
plt.text(0.05, 0.80, 'crand: the random coin', transform=plt.gca().transAxes)
#-- plt.xlim([0, 11])
plt.xlim([0, 1.1])

print 'crand yval:\n', yval, '\ncrand xval:\n', xval, '\ncrand patches:\n', patches

plt.subplot(313)
cmin_yval, xval, patches = plt.hist(cmin, bins=xbins)
plt.text(0.05, 0.80, 'cmin: the coin with minimum # of heads', transform=plt.gca().transAxes)
#-- plt.xlim([0, 11])
plt.xlim([0, 1.1])

#
# average of cmin
#
cmin_average = sum(cmin_yval*xval[:-1]) / sum(cmin_yval) # NB: the first bin is not exact zero because of eps shift
print '\ncmin_average = {:0.18f}'.format(cmin_average)

cmin_average_correct = sum(cmin_yval*(xval[:-1] + (xval[1] - xval[0]) / 1e12)) / sum(cmin_yval)
print 'cmin_average corrected for the eps shift of xbins is {:0.18f}'.format(cmin_average_correct)

plt.text(0.95, 0.90, "average = {:0.4f}".format(cmin_average), transform=plt.gca().transAxes, \
         ha='right', va='top', bbox={'fill':False})

plt.show()
