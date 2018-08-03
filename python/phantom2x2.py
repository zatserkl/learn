# Andriy Zatserklyaniy <zatserkl@gmail.com> Aug 3, 2018

"""
Working example of Machine Learning approach to pCT image reconstruction.
"""

import numpy as np
import matplotlib.pyplot as plt
from collections import defaultdict
# % matplotlib inline


class Track:
    """
    Track consists of measured energy Edet and list of voxels' coordinates.
    The coordinates are the same for voxel weight and for voxel derivatives.
    Class Track has a global pointer to Phantom and to the Phantom filled
    by derivatives.
    """
    phantom_w = None
    phantom_d = None
    Einc = None  # incident energy

    def __init__(self, Edet, voxels):
        self.Edet = Edet  # Energy detector meausurement for this event
        self.voxels = voxels[:]  # use list copy

    def __repr__(self):
        s = 'Edet ' + str(Edet) + ' voxels'
        for voxel in self.voxels:
            s += ' ' + str(voxel)
        return s
    
    def loss(self):
        """
        --> Debug-purpose function
        Just calculates loss: not terrible useful w/o derivatives
        :return: loss function J
        """
        dE = self.Einc - self.Edet
        for voxel in self.voxels:
            row, col = voxel
            dE -= Track.phantom_w[row, col]
        return dE
    
    def loss_der(self):
        """
        --> Mainstream function
        Calculates the loss function and modifies derivatives
        :return: loss function
        NB: modifies phantom_d passed by references
        """
        dE = self.Einc - self.Edet
        for voxel in self.voxels:
            row, col = voxel
            dE -= Track.phantom_w[row, col]

        # modify derivative for this voxel
        for voxel in self.voxels:
            Track.phantom_d[row, col] = -dE  # minus because loss = (y - h(w))
        return dE

    def print(self):
        print(self.Edet, end='\t')
        for row_col in self.voxels:
            row, col = row_col
            # print('Track.phantom_w[row, col] =', Track.phantom_w[row, col])
            # print(Track.phantom_w[row, col], end='\t')  # print voxel value
            print(row_col, end='\t')                      # voxel coordinates
        print()


def print_phantom(phantom):
    for row in range(phantom.shape[0]):
        for col in range(phantom.shape[1]):
            print('{:8.2f}'.format(phantom[row, col]), end=' ')
        print()


N = 2
phantom_v = np.zeros((N, N))  # true values

phantom_w = np.zeros((N, N))  # weights
phantom_d = np.zeros((N, N))  # derivatives

# incident energy
Einc = 100  # MeV

#
# initialize Track global variables
#
Track.phantom_w = phantom_w
Track.phantom_d = phantom_d
Track.Einc = Einc

# set the phantom density (in terms of energy loss)
phantom_v[1, 1] = 10  # loss 10 MeV

print('"real" phantom\n')
print_phantom(phantom_v)

tracks = []
# the track energy will be measured later
tracks.append(Track(Einc, [(0, 0), (0, 1)]))
tracks.append(Track(Einc, [(1, 0), (1, 1)]))
tracks.append(Track(Einc, [(0, 0), (1, 0)]))
tracks.append(Track(Einc, [(0, 1), (1, 1)]))
tracks.append(Track(Einc, [(0, 0)]))
tracks.append(Track(Einc, [(1, 0), (0, 1)]))
tracks.append(Track(Einc, [(1, 1)]))
tracks.append(Track(Einc, [(1, 0)]))
tracks.append(Track(Einc, [(0, 0), (1, 1)]))
tracks.append(Track(Einc, [(0, 1)]))

# measure the energy
for track in tracks:
    Elost = 0
    for voxel in track.voxels:
        row, col = voxel
        Elost += phantom_v[row, col]
    track.Edet = Einc - Elost

print('\nMeasured tracks:')

for track in tracks:
    track.print()

###############################################

# Cost function
def costFunction(tracks, phantom_w, phantom_d):
    """
    Returns cost function.
    The derivatives phantom_d will be changed in-place as passed by reference
    """
    J = 0.  # cost function
    # clear derivatives
    phantom_d = np.zeros((phantom_d.shape[0], phantom_d.shape[1]))

    for track in tracks:
        loss = track.loss_der()  # calcs loss function J and modifies phantom_d
        J += loss * loss
    
    phantom_d /= len(tracks)
    return J / len(tracks) / 2


J = costFunction(tracks, phantom_w, phantom_d)
print('\nInitial Cost function J =', J)

print('\n"real" phantom\n')
print_phantom(phantom_v)

print('\nInitial "weights" phantom: should be empty\n')
print_phantom(phantom_w)

print('\n"derivatives" phantom\n')
print_phantom(phantom_d)

# introduce the correction
phantom_w -= phantom_d

print('\n"weights" phantom after correction\n')
print_phantom(phantom_w)

#
# the next iteration
#
print('\nThe next iteration')
print('------------------\n')

J = costFunction(tracks, phantom_w, phantom_d)
print('Cost function J =', J)

print('\n"weights" phantom\n')
print_phantom(phantom_w)

print('\n"derivatives" phantom\n')
print_phantom(phantom_d)

# introduce the correction
phantom_w -= phantom_d

print('\n"weights" phantom after correction\n')
print_phantom(phantom_w)

