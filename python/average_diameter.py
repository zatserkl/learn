# What Is The Distance Between Two Random Points In A Square.mp4
# https://www.youtube.com/watch?v=i4VqXRRXi68

# See these supplementary discussions:
# http://stackoverflow.com/questions/26412084/getting-the-cumulative-distribution-function-for-sqrtx-from-the-cumulative-dis
# http://math.stackexchange.com/questions/1512756/what-is-the-distribution-of-the-sqrt-of-a-random-variable-with-exponential-distr
# http://math.stackexchange.com/questions/305997/does-the-square-of-uniform-distribution-have-density-function

from __future__ import division
import random
import math
import matplotlib.pyplot as plt
from collections import defaultdict, Counter
import sys


def calcAverage(N=10000):

    if N > 10000:
        print('N > 1000. Be patient: Python is an interpreter')

    random.seed(0)

    x1 = [random.random() for _ in range(N)]
    y1 = [random.random() for _ in range(N)]
    x2 = [random.random() for _ in range(N)]
    y2 = [random.random() for _ in range(N)]

    r = []
    for i in range(len(x1)):
        r.append(math.sqrt((x1[i] - x2[i])**2 + (y1[i] - y2[i])**2))

    print('average distance between', N,
          'random points in (0,1) is', sum(r) / len(r))

    r2 = []
    for i in range(len(x1)):
        r2.append((x1[i] - x2[i])**2 + (y1[i] - y2[i])**2)

    # print('average square distance between', N, 'random points in (0,1) is', sum(r2) / len(r2))
    print(('average square distance between {} '
           'random points in (0,1) is {}').format(N, sum(r2) / len(r2)))


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

    diffx = [x1i - x2i for x1i, x2i in zip(x1, x2)]     # list comprehension

    print('Create figure and plot')
    plt.figure()
    plt.hist(diffx, bins=20)                            # actual plot command
    plt.title('Distribution for dx')
    plt.xlabel('x[i] - x[j]')
    plt.show()

    #
    # average of square of dx
    #

    dx2 = [(x1i - x2i)**2 for x1i, x2i in zip(x1, x2)]

    print('Create figure and plot for dx**2')
    plt.figure()
    plt.hist(dx2, bins=20)
    plt.title('Distribution for dx**2')
    plt.xlabel('(x[i] - x[j])**2')
    plt.show()

    #
    # average of r2 = dx**2 + dy**2
    #

    r2 = []

    for i in range(len(x1)):
        dx = x1[i] - x2[i]
        dy = y1[i] - y2[i]
        r2.append(dx*dx + dy*dy)

    print('Create figure and plot for r = dx*dx + dy*dy')
    plt.figure()
    plt.hist(r2, bins=20)
    plt.title('Distribution for r2 = dx*dx + dy*dy')
    plt.xlabel('r2 = dx*dx + dy*dy')
    plt.show()

    #
    # average of r = sqrt(dx**2 + dy**2)
    #

    r = []

    for i in range(len(x1)):
        dx = x1[i] - x2[i]
        dy = y1[i] - y2[i]
        r.append(math.sqrt(dx*dx + dy*dy))

    print('Create figure and plot for r = dx*dx + dy*dy')
    plt.figure()
    plt.hist(r, bins=20)
    plt.title('Distribution for r = sqrt(dx*dx + dy*dy)')
    plt.xlabel('r = sqrt(dx*dx + dy*dy)')
    plt.show()


if __name__ == '__main__':

    N = 10000

    if len(sys.argv) > 1:
        N = int(sys.argv[1])

    print('use', N, 'points')
    plotSum(N)
