from __future__ import division
from pandas import *                    # for read_csv
import matplotlib.pyplot as plt

"""Read and plot event
Data format: 3 space separated columns
of time (ns) and voltages (V) for two channels
t       w1      w2
0 0.00260925 0.00521851
0.1997 0.00311279 0.00471497
0.3984 0.00361633 0.00421143
0.5967 0.00411987 0.00370789
0.795 0.00421143 0.0032196
0.9928 0.0032196 0.00291443
1.191 0.00221252 0.00221252
...
"""

fname = "evt14.dat"

# read data file using pandas' read_csv with space as a delimiter
# assign names to the DataFrame column

d = read_csv(fname, delim_whitespace=True, names=['t', 'w1', 'w2'])

print d[:5]

plt.figure()
plt.gcf().suptitle('Traces', fontsize=14)       # suptitle: the global title. NB: default font size is too small.

#
# make two plots on the same figure
#

plt.subplot(211)         # 211 = (rows, columns, subplotNumber)
plt.title('Channel 1')
plt.scatter(d['t'][800:900], d['w1'][800:900], color='r', marker='.')
plt.text(0.05, 0.75, 'channel 1', transform=plt.gca().transAxes, bbox={'fill':False})  # bbox draws a box around the text
plt.grid()

plt.subplot(212)
plt.title('Channel 2')
plt.scatter(d['t'][800:900], d['w2'][800:900], color='b', marker='.')
plt.text(0.05, 0.75, 'channel 2', transform=plt.gca().transAxes, bbox={'fill':False})
plt.grid()

#
# plot histogram of the noise: the first 512 samples
#

plt.figure()
plt.gcf().suptitle('Noise in the first 512 samples', fontsize=14)       # suptitle: the global title

# book histogram in the same way as in Root

import numpy as np      # for np.linspace

xmin = -0.010   # lower boundary of the first channel
xmax =  0.010   # upper boundary of the last channel
nbins = 20      # the number of bins

xbins = np.linspace(xmin, xmax, nbins+1)  # NB: bin width = (xmax - xmin) / nbins. Cf in ROOT: 100 bins from 0 to 100.

print xbins
print 'xmin =', xmin, 'xmax =', xmax, 'nbins =', nbins

plt.subplot(211)
plt.title('Channel 1')
plt.hist(d['w1'][:512], xbins)
plt.text(0.05, 0.75, 'channel 1', transform=plt.gca().transAxes, bbox={'fill':False})  # bbox draws box around the text
plt.grid()

plt.subplot(212)
plt.title('Channel 2')
yval, xval, patches = plt.hist(d['w2'][:512], xbins)            # we need return values for the fit
plt.text(0.05, 0.75, 'channel 2', transform=plt.gca().transAxes, bbox={'fill':False})
plt.grid()

#-- plt.show()

###########################################################################
# fit the second channel - to avoid complication with pure graphical part #
###########################################################################

from scipy.optimize import curve_fit

# fit function

fun = lambda x, *par: par[0] * np.exp(-0.5 * ((x - par[1])/par[2])**2)           # uses array NB: *par
# fun = lambda x, ampl, mean, sigma: ampl * np.exp(-0.5 * ((x - mean)/sigma)**2) # uses separate arguments

width = (xmax - xmin) / nbins
print 'width =', width, 'xval[1] - xval[0] =', xval[1] - xval[0]

yerr = 1. + np.sqrt(yval)       # here 1. is min uncertainty
# yerr = np.full(len(yerr), 10.)       # set all errors to 1

print 'width =', width, 'len(xval) =', len(xval), 'len(yval) =', len(yval), 'len(patches) =', len(patches)
# for i in range(len(yval)): print i, xval[i], yval[i], 'yerr:', yerr[i]

ampl = np.max(yval)
mean = np.sum(xval[:nbins]*yval) / np.sum(yval)                                 # NB: dimension of xval is nbins+1
sigma = np.sqrt( np.sum(yval*(xval[:nbins] - mean)**2) / np.sum(yval) )
print 'ampl =', ampl, 'mean =', mean, 'sigma =', sigma

#-- popt0 = [10., 0., 1.]               # suppose to be a bad fit
popt0 = [ampl, mean, sigma]

try:
    popt, pcov = curve_fit(fun, xval[:-1]+width/2, yval, popt0, yerr, True) # evaluate in the bin center
except RuntimeError as e:
    print '***Exception RuntimeError:', e
    print 'Terminated'
    plt.show()          # plot whatever we have
    exit()              # if in the function: return
    
perr = np.sqrt(np.diag(pcov))           # from curve_fit documentation

# print 'popt =', popt
# print 'perr =', perr

# Python and Matplotlib Essentials for Scientists and Engineers.pdf, p.11-3
print 'Const = {:g} \u00B1 {:g}'.format(popt[0], perr[0])
print 'Mean  = {:g} \u00B1 {:g}'.format(popt[1], perr[1])
print 'Sigma = {:g} \u00B1 {:g}'.format(popt[2], perr[2])

# plot the fit function
xfun = np.linspace(xmin, xmax, 100)     # 100 points
plt.plot(xfun, fun(xfun, *popt), 'r-')  # NB: *pop

text_par = "Const\t%0.3g $\pm$ %0.3g\nMean\t%0.3g $\pm$ %0.3g\nSigma\t%0.3g $\pm$ %0.3g" \
           % (popt[0], perr[0], popt[1], perr[1], popt[2], perr[2])
plt.text(0.60, 0.95, text_par, transform=plt.gca().transAxes, va='top', bbox={'fill':False})

print 'the number of events in histogram sum(yval) =', sum(yval)
print 'the number of events under the function is sqrt(2*pi)*A*sigma/width =', np.sqrt(2*np.pi)*popt[0]*popt[2]/width

plt.show()
