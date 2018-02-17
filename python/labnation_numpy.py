#!/usr/bin/env python

"""Andriy Zatserklyaniy <zatserkl@gmail.com>
"""

import sys
import csv
import numpy as np
import matplotlib.pyplot as plt
import math


def labNation(fname, shiftA=0., scaleA=1., shiftB=0., scaleB=1.):
    """
    Reads file saved by LabNation digital oscilloscope
    """

    # print "shiftA =", shiftA, "scaleA =", scaleA, "shiftB =", shiftB, "scaleB =", scaleB

    with open(fname) as file:
        reader = csv.reader(file)
        header = next(reader)
        line1 = next(reader)

    # print header
    # print line1

    AcquisitionStartTimeInSeconds = float(line1[2]) * 1e6 # us
    SamplePeriodInSeconds = float(line1[3]) * 1e6 # us
    SampleTime = float(line1[4]) * 1e6 # us

    # print "AcquisitionStartTimeInSeconds =", AcquisitionStartTimeInSeconds, "us"
    # print "SamplePeriodInSeconds =", SamplePeriodInSeconds, "us"
    # print "SampleTime =", SampleTime, "us"

    chA, chB = np.loadtxt(fname, delimiter=",", skiprows=1, usecols=(5,6), unpack=True)
    # print chA[:5]
    # print chB[:5]
    # print len(chA), len(chB)

    t = np.ndarray(len(chA), dtype=float)
    for i in xrange(len(chA)):
        t[i] = AcquisitionStartTimeInSeconds + i*SamplePeriodInSeconds

    # print "t[:5] =", t[:5]
    # print "t[0] =", t[0], "t[-1] =", t[-1], "chA[0] =", chA[0], "chA[-1] =", chA[-1]

    # scale and shift the channels

    title = ""
    eps = 1e-15
    if abs(scaleA - 1.) > eps:
        title += "scaleA = " + str(scaleA) + " "
    if abs(shiftA) > eps:
        title += "shiftA = " + str(shiftA) + "V "

    if abs(scaleB - 1.) > eps:
        title += "scaleB = " + str(scaleB) + " "
    if abs(shiftB) > eps:
        title += "shiftB = " + str(shiftB) + "V "

    title = title[:-1]          # remove the trailing whitespace

    chA *= scaleA       # scale first
    chA += shiftA       # shift after scale
    chB *= scaleB
    chB += shiftB

    plt.plot(t, chA, color='r', label="chA")
    plt.plot(t, chB, color='b', label="chB")

    plt.title(title)
    # plt.legend(loc="upper right")             # to avoid clutter
    plt.xlabel("time, ms")
    plt.grid(True)
    plt.show()


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print "Usage:", __file__, "filename [shiftA=-1.] [scaleA=0.25] [shiftB=0.] [scaleB=1.]"
        exit()

    # scale and shift the channel A by default
    shiftA = -1.        # V
    scaleA = 0.25
    shiftB = 0.
    scaleB = 1.

    if len(sys.argv) > 1:
        filename = sys.argv[1]
    if len(sys.argv) > 2:
        shiftA = float(sys.argv[2])
    if len(sys.argv) > 3:
        scaleA = float(sys.argv[3])
    if len(sys.argv) > 4:
        shiftB = float(sys.argv[4])
    if len(sys.argv) > 5:
        scaleB = float(sys.argv[5])

    # print "shiftA =", shiftA, "scaleA =", scaleA, "shiftB =", shiftB, "scaleB =", scaleB

    labNation(filename, shiftA, scaleA, shiftB, scaleB)
