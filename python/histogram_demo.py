# histogram example

# Python and Matplotlib Essentials for Scientists and Engineers.pdf, p. 10-7

import matplotlib.pyplot as plt
import numpy as np

np.random.seed(0)

x = np.random.randn(500)

##########################################
# simplest histogram: just specify nbins #
##########################################

plt.figure()
plt.title('Simplest histogram with 10 bins')

plt.hist(x,bins=10) # it is unclear how many bins to order if you don't know limits

###########################################
# more sofisticated: xmin, xmax and width #
###########################################

plt.figure()
plt.title('Histogram with xmin, xmax and width')

# NB: code np.floor and np.cell are good for integer x value only!
# Q: do we really need cell and floor?
# A: just to round axis ends
#
# width = 0.5
# histmin = np.floor(min(x))
# histmax = np.ceil(max(x))+width         # max + width (a room for the last bin)
#
# bins = np.arange(histmin,histmax,width)         # np.arange

#
# range = max-min technique
#
width = 0.5                                     # start from width and xmin, xmax
xmin_data = min(x)
xmax_data = max(x)

xrange = xmax_data - xmin_data                  # get the range

xmin = xmin_data - 0.05*xrange
if xmin < 0 and xmin_data > 0: xmin = 0         # zero is a special point

xmax = xmax_data + 0.05*xrange + width          # NB: add width: room for the last bin

# do we need to round xmin and xmax?
# -- not, really, the matplotlib rounds them well

bins = np.arange(xmin,xmax,width)               # np.arange

print 'len(bins) =', len(bins), 'bins:\n', bins

plt.hist(x,bins=bins)

plt.show()
