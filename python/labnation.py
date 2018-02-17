#!/usr/bin/env python

"""
Andriy Zatserklyaniy <zatserkl@gmail.com> Dec 24, 2017
Reads LabNation USB oscilloscope data. Two channels at the moment.
"""

from __future__ import print_function   # to work in both Python3 and Python2

import sys
import csv
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


def labNation(fname, shiftA=0., scaleA=1., shiftB=0., scaleB=1., debug=False):
    """
    Reads file saved by LabNation digital oscilloscope
    """
    
    ### nSamples = 2048     # a constant for the LabNation

    if debug:
        print("shiftA =", shiftA, "scaleA =", scaleA, "shiftB =", shiftB, "scaleB =", scaleB)

    df = pd.read_table(fname, delimiter=",")

    keys = df.keys()
    if debug:
        for ikey, key in enumerate(keys): print(ikey, key)

    nAcq = df['AcquisitionID'].count()
    if debug:
        print("nAcq =", nAcq)

    channelsA = []
    channelsB = []

    # for the rolling recording the channel names are ChannelA and ChannelB
    if "ChannelA" in keys and "ChannelB" in keys:
        if "ChannelA" in keys:
            channelsA.append("ChannelA")
        if "ChannelB" in keys:
            channelsB.append("ChannelB")
    else:
        chA_curr = "ChannelA_Acq{0:05d}".format(0)
        chB_curr = "ChannelB_Acq{0:05d}".format(0)
        for key in keys:
            if key == chA_curr:
                channelsA.append(key)
                chA_curr = "ChannelA_Acq{0:05d}".format(len(channelsA))
            elif key == chB_curr:
                channelsB.append(key)
                chB_curr = "ChannelB_Acq{0:05d}".format(len(channelsB))

    # print("len(channelsA) =", len(channelsA), "len(channelsB) =", len(channelsB))
    if debug:
        print("channelsA:", channelsA, "\nchannelsB:", channelsB)

    nSamples = 0
    if len(channelsA) > 0:
        nSamples = len(df[channelsA[0]])
    elif len(channelsB) > 0:
        nSamples = len(df[channelsB[0]])
        
    print(nAcq, "acquisition(s) of", nSamples, "samples")

    if nSamples == 0:
        print("Cannot figure out nSamples: both channels A and B are empty")
        return

    # AcquisitionStartTimeInSeconds: can be a single number or an array in file
    if "AcquisitionStartTimeInSeconds" in keys:
        AcquisitionStartTimeInSeconds = df['AcquisitionStartTimeInSeconds']
    else:
        AcquisitionStartTimeInSeconds = np.zeros(1)     # array with 1 element
        
    SamplePeriodInSeconds = float(df['SamplePeriodInSeconds'][0]) # must use float()
    SampleTime = float(df['SampleTime'][0])

    if debug:
        print("SamplePeriodInSeconds =", SamplePeriodInSeconds)
        print("SampleTime =", SampleTime)
        print("AcquisitionStartTimeInSeconds[:", nAcq, "]:\n", AcquisitionStartTimeInSeconds[:nAcq])
        for iAcq, t0 in enumerate(AcquisitionStartTimeInSeconds[:nAcq]):
            print("AcquisitionStartTimeInSeconds[{0:2d}] = {1:f}".format(iAcq, t0))

    tSample = np.array([ [t0 + i*SamplePeriodInSeconds for i in range(nSamples)]
                         for t0 in AcquisitionStartTimeInSeconds[:nAcq] ])
    if debug:
        print("tSample[0,:10] =", tSample[0,:10])

    #
    # Create an empty float array with shape(dimensions) (nSamples, nAcq)
    #
    chA = np.empty((nSamples, nAcq), dtype=float)
    chB = np.empty((nSamples, nAcq), dtype=float)

    for iAcq in range(nAcq):
        chA[:, iAcq] = df[channelsA[iAcq]]*scaleA + shiftA
        chB[:, iAcq] = df[channelsB[iAcq]]*scaleB + shiftB

    for iAcq in range(nAcq):
        plt.plot(tSample[iAcq], chA[:, iAcq], color='g',
                 label="chA {0}".format(iAcq))
        plt.plot(tSample[iAcq], chB[:, iAcq], color='b',
                 label="chB {0}".format(iAcq))

    title = fname
    eps = 1e-15
    if abs(scaleA - 1.) > eps:
        title += " scaleA = " + str(scaleA)
    if abs(shiftA) > eps:
        title += " shiftA = " + str(shiftA) + "V"

    if abs(scaleB - 1.) > eps:
        title += " scaleB = " + str(scaleB)
    if abs(shiftB) > eps:
        title += " shiftB = " + str(shiftB) + "V"

    plt.title(title)
    # plt.legend(loc="upper right")             # comment out to avoid clutter
    plt.xlabel("time, s")
    plt.grid(True)

    # plt.subplots_adjust(0.05, 0.05, 0.95, 0.95) # left, bottom, right, top
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage:", __file__,
        "filename [shiftA=-1.] [scaleA=0.25] [shiftB=0.] [scaleB=1.]")
        exit()

    # scale and shift the channel A by default
    shiftA = -1.        # V
    scaleA = 0.25
    shiftB = 0.
    scaleB = 1.

    debug = False

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
    if len(sys.argv) > 6:
        debug = bool(sys.argv[6])

    labNation(filename, shiftA, scaleA, shiftB, scaleB, debug)
