from __future__ import print_function
import numpy as np
import matplotlib.pyplot as plt

Ndata = 15
Naver = 5       # must be odd

if Naver % 2 == 0:
    Naver += 1

# data = np.zeros(Ndata)
data = np.ones(Ndata)
data[Ndata//2] = 10.

weights = np.ones(Naver) / Naver

print("len(np.convolve(weights, data)) =", len(np.convolve(weights, data)))

data_aver = np.convolve(weights, data)

plt.plot(data_aver, marker='o', linestyle='None')
# plt.plot(data, marker='+', linestyle='None')          # need to be shifted by Naver//2 = 2 points

lentot = len(np.convolve(weights, data))
title = "Convolution with delta function\nNdata = {0}, Naver = {1}, len(np.convolve(weights, data)) = {2}".format(Ndata, Naver, lentot)
plt.title(title)
plt.xlabel("point No.")
plt.show()
