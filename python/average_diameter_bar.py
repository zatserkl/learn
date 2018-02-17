# What Is The Distance Between Two Random Points In A Square.mp4
# https://www.youtube.com/watch?v=i4VqXRRXi68

# See these supplementary discussions:
# http://stackoverflow.com/questions/26412084/getting-the-cumulative-distribution-function-for-sqrtx-from-the-cumulative-dis
# http://math.stackexchange.com/questions/1512756/what-is-the-distribution-of-the-sqrt-of-a-random-variable-with-exponential-distr
# http://math.stackexchange.com/questions/305997/does-the-square-of-uniform-distribution-have-density-function

from __future__ import division
import random, math
import matplotlib.pyplot as plt
from collections import defaultdict, Counter
import sys

def calcAverage(N=10000):

    if N > 10000: print 'Be patient: Python is an interpreter'

    random.seed(0)

    x1 = [random.random() for _ in range(N)]
    y1 = [random.random() for _ in range(N)]
    x2 = [random.random() for _ in range(N)]
    y2 = [random.random() for _ in range(N)]

    r = []
    for i in range(len(x1)):
        r.append(math.sqrt((x1[i] - x2[i])**2 + (y1[i] - y2[i])**2))

    print 'average distance between', N, 'random points in (0,1) is', sum(r) / len(r)

    r2 = []
    for i in range(len(x1)):
        r2.append((x1[i] - x2[i])**2 + (y1[i] - y2[i])**2)

    print 'average square distance between', N, 'random points in (0,1) is', sum(r2) / len(r2)

def plotSum(N=1000):
    """Plot some distributions
    """
    random.seed(0)

    x1 = [random.random() for _ in range(N)]
    y1 = [random.random() for _ in range(N)]
    x2 = [random.random() for _ in range(N)]
    y2 = [random.random() for _ in range(N)]

    # diffx = []
    # for i in range(len(x1)):
    #     diffx.append(x1[i] - x2[i])

    diffx = [x1i - x2i for x1i,x2i in zip(x1,x2)]

    for i in range(5): print x1[i], x2[i], x1[i] - x2[i], '=', diffx[i]

    xmin = -1.
    xmax = 1.
    nbins = 20
    width = (xmax - xmin) / nbins

    hist_dx = defaultdict(int)

    for i in range(len(x1)):
        dx = x1[i] - x2[i]
        bin = int((dx - xmin) / width)	# distance in bins from xmin
        if bin < 0: bin = -1		# underflow bin
        if bin >= nbins: bin = nbins	# overflow bin
        hist_dx[bin] += 1

    print hist_dx
    for bin in hist_dx: print bin, hist_dx[bin]

    print 'Create figure and plot'
    plt.figure()
    # plt.plot([width*t for t in hist_dx.keys()], hist_dx.values(), marker='.', linestyle='None')
    plt.bar([xmin+width*bin for bin in hist_dx.keys()], hist_dx.values(), width=width)
    plt.xlim(xmin, xmax)
    plt.title('Distribution for dx')
    plt.xlabel('x[i] - x[j]')
    plt.show()

    #
    # average of square of dx
    #

    xmin2 = 0.
    xmax2 = 1.
    nbins2 = 10
    width2 = (xmax2 - xmin2) / nbins2
    
    hist_dx2 = defaultdict(int)

    for i in range(len(x1)):
        dx = x1[i] - x2[i]
        dx = dx**2
        bin = int((dx - xmin2) / width2)	# distance in bins from xmin
        if bin < 0: bin = -1			# underflow bin
        if bin >= nbins2: bin = nbins2		# overflow bin
        hist_dx2[bin] += 1

    print hist_dx2
    for bin in hist_dx2: print bin, hist_dx2[bin]

    print 'Create figure and plot'
    plt.figure()
    plt.bar([xmin2+width2*bin for bin in hist_dx2.keys()], hist_dx2.values(), width=width2)
    plt.xlim(xmin2, xmax2)
    plt.title('Distribution for dx**2')
    plt.xlabel('(x[i] - x[j])**2')
    plt.show()


    #
    # average of sqrt(dx**2 + dy**2)
    #

    xmin = 0.
    xmax = 2.
    nbins = 20
    width = (xmax2 - xmin2) / nbins2
    
    hist_sqrt = defaultdict(int)

    for i in range(len(x1)):
        dx = x1[i] - x2[i]
        dy = y1[i] - y2[i]
        r = math.sqrt(dx*dx + dy*dy)
        bin = int((r - xmin2) / width2)		# distance in bins from xmin
        if bin < 0: bin = -1			# underflow bin
        if bin >= nbins: bin = nbins		# overflow bin
        hist_sqrt[bin] += 1

    print hist_sqrt
    for bin in hist_sqrt: print bin, hist_sqrt[bin]

    print 'Create figure and plot for r = sqrt(dx*dx + dy*dy)'
    plt.figure()
    plt.bar([xmin+width*bin for bin in hist_sqrt.keys()], hist_sqrt.values(), width=width)
    plt.xlim(xmin, xmax)
    plt.title('Distribution for r = sqrt(dx*dx + dy*dy)')
    plt.xlabel('r = sqrt(dx*dx + dy*dy)')
    plt.show()
    
if __name__ == '__main__':
    N = 10000
    if len(sys.argv) > 1:
        N = int(sys.argv[1])
        print 'use', N, 'points'
    plotSum(N)

    
