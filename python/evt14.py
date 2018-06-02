from __future__ import division
from pandas import *                    # for read_csv
import matplotlib.pyplot as plt
import numpy as np                      # for np.linspace
from scipy.optimize import curve_fit

def funGauss(x, *par):
    """This function is used in fitGauss for fitting and in the main for plotting
    """
    return par[0] * np.exp(-0.5 * ((x - par[1])/par[2])**2)

def fitGauss_curve_fit(x, y, ey):
    """
    Fit Gaussian using curve_fit
    """

    # estimate initial parameters

    ampl = max(y)
    mean = np.sum(x*y) / np.sum(y)
    sigma = np.sqrt( np.sum(y * (x - mean)**2) / np.sum(y) )

    popt0 = [ampl, mean, sigma]

    try:
        popt, pcov = curve_fit(funGauss, x, y, popt0, ey, True)
    except RuntimeError as e:
        print('***Exception RuntimeError:', e)
        return [], []   # parameters and errors
    # except OptimizeWarning as e:
    #     print '***Exception OptimizeWarning:', e
    #     return [], []   # parameters and errors
    
    perr = np.sqrt(np.diag(pcov))       # from curve_fit documentation
    return popt, perr

####################
#       main       #
####################

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

print(d[:5])

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

xmin = -0.010   # lower boundary of the first channel
xmax =  0.010   # upper boundary of the last channel
nbins = 20      # the number of bins

xbins = np.linspace(xmin, xmax, nbins+1)  # NB: bin width = (xmax - xmin) / nbins. Cf in ROOT: 100 bins from 0 to 100.

print('xbins:\n', xbins)
print('xmin =', xmin, 'xmax =', xmax, 'nbins =', nbins)

plt.subplot(211)
plt.title('Channel 1')
plt.hist(d['w1'][:512], xbins)
plt.text(0.05, 0.75, 'channel 1', transform=plt.gca().transAxes, bbox={'fill':False})  # bbox draws box around the text
plt.grid()

plt.subplot(212)
plt.title('Channel 2')
yval, xval, patches = plt.hist(d['w2'][:512], xbins)    # we need return values for the fit
plt.text(0.05, 0.75, 'channel 2', transform=plt.gca().transAxes, bbox={'fill':False})
plt.grid()

###########################################################################
# fit the second channel - to avoid complication with pure graphical part #
###########################################################################

yerr = 1. + np.sqrt(yval)       # here 1. is min uncertainty

width = xval[1] - xval[0]
popt, perr = fitGauss_curve_fit(xval[:-1]+width/2, yval, yerr)  # evaluate in the bin center

if len(popt) == 0:
    #
    # fit failed, plot everything and exit
    #
    plt.show()
    exit()
    
print(u'Const = {:g} \u00B1 {:g}'.format(popt[0], perr[0]))
print(u'Mean  = {:g} \u00B1 {:g}'.format(popt[1], perr[1]))
print(u'Sigma = {:g} \u00B1 {:g}'.format(popt[2], perr[2]))

# plot the fit function
xfun = np.linspace(xmin, xmax, 100)             # 100 points
plt.plot(xfun, funGauss(xfun, *popt), 'r-')     # NB: *pop

text_par = "Const\t%0.3g $\pm$ %0.3g\nMean\t%0.3g $\pm$ %0.3g\nSigma\t%0.3g $\pm$ %0.3g" \
           % (popt[0], perr[0], popt[1], perr[1], popt[2], perr[2])
plt.text(0.60, 0.95, text_par, transform=plt.gca().transAxes, va='top', bbox={'fill':False})

print('the number of events in histogram sum(yval) =', sum(yval))
print('the number of events under the function is sqrt(2*pi)*A*sigma/width =', np.sqrt(2*np.pi)*popt[0]*popt[2]/width)

plt.show()
