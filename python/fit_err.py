"""Example of curve_fit
Andriy Zatserklyaniy <zatserkl@fnal.gov> Feb 3, 2017
"""

from __future__ import division
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import numpy as np

x = np.array([0.0,      2.0,    4.0,    6.0,    8.0])
y = np.array([0.,       1.5,    1.5,    3.0,    1.0])
#
# Smaller sigma for the last point makes slope much steeper
#
ey = np.array([1.0,     1.0,    1.0,    0.5,    3.0])     # popt: 0.214, 0.4399
# ey = np.array([1.0,     1.0,    1.0,    0.5,    0.5])   # popt: 1.255, 0.0838

plt.figure()
plt.grid()

plt.errorbar(x, y, yerr=ey, fmt='bo')

xmin = np.min(x)
xmax = np.max(x)
xrange = xmax - xmin
plt.gca().set_xlim(xmin - 0.05*xrange, xmax + 0.05*xrange)

ymin = np.min(y - ey)
ymax = np.max(y + ey)
yrange = ymax - ymin
plt.gca().set_ylim(ymin - 0.05*yrange, ymax + 0.05*yrange)

#########
#  fit  #
#########


# fitfun = lambda x, *p: p[0] + p[1]*x      # ok, but bounds lambda with name
def fitfun(x, *p): return p[0] + p[1]*x     # mathematicians call this model


popt0 = 0., 1.

#
# Change of absolute_sigma from default False to True:
#
# Parameters popt are the same, but pcov are different.
# Use True for errors as actual sigma
#

try:
    popt, pcov = curve_fit(fitfun, x, y, popt0, ey, absolute_sigma=True)    # set absolute_sigma to True, because our errors are sigmas
    # popt, pcov = curve_fit(fitfun, x, y, popt0, ey, absolute_sigma=False) # default absolute_sigma
except RuntimeError as e:
    print("***Exception RuntimeError:", e)
    print("Terminated")
    plt.show()      # plot whatever we have
    exit()

perr = np.sqrt(np.diag(pcov))           # from curve_fit documentation

print("popt:", popt)
print('pcov:\n', pcov)
print('Result: p0 =', popt[0], '+-', perr[0], 'p1 =', popt[1], '+-', perr[1])

##################################
#   plot the fitted function     #
#   in general way: 100 points   #
##################################

xmin, xmax = plt.xlim()
xfitfun = np.linspace(xmin, xmax, 100)
#-- xfitfun = np.linspace(*(plt.xlim()), 100)   # does not work in Python 2
yfitfun = fitfun(xfitfun, *popt)
plt.plot(xfitfun, yfitfun, 'r-')

###############################
#  text box with fit results  #
###############################

textBox = "p0 = %0.3f $\pm$ %0.3f\np1 = %0.3f $\pm$ %0.3f" % (popt[0], perr[0], popt[1], perr[1])
plt.text(0.05, 0.95, textBox, transform=plt.gca().transAxes, bbox={'fill':False}, va='top')

plt.title("Fit error bar data")

plt.show()

"""Output with absolute_sigma = True

popt: [ 0.21404399  0.43993232]
pcov:
[[ 0.65143821 -0.11759728]
 [-0.11759728  0.02707275]]
Result: p0 = 0.214043986989 +- 0.807117224561 p1 = 0.43993231931 +- 0.164538003846

Output with absolute_sigma = False

popt: [ 0.21404399  0.43993232]
pcov:
[[ 0.29338602 -0.05296189]
 [-0.05296189  0.01219266]]
Result: p0 = 0.214043986989 +- 0.541651198022 p1 = 0.43993231931 +- 0.110420400149
"""
