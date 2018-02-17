# Demo of subplots (plt.gca()) and text (transAxes, bbox, color)

# Python and Matplotlib Essentials for Scientists and Engineers.pdf, p. 10-6
# Modified: Andriy Zatserklyaniy, Jan 31, 2017

import numpy as np
import matplotlib.pyplot as plt

def func(x):
    return np.sin(2*np.pi*x)

x1 = np.arange(0.0,4.0,0.1)
x2 = np.arange(0.0,4.0,0.01)

y1 = func(x1)
y2 = func(x2)
y1n = y1 + 0.1*np.random.randn(len(x1))

# plt.figure()

plt.subplot(211)
plt.plot(x1,y1,'b.',x2,y2,'r:')
plt.text(0.05, 0.75, 'function sin(x)', transform=plt.gca().transAxes, bbox={'fill':False})
#
# without the box around but two text lines
#
# plt.text(0.05, 0.75, 'function sin(x) #1', transform=plt.gca().transAxes, verticalalignment='bottom')
# plt.text(0.05, 0.75, 'function sin(x) #2', transform=plt.gca().transAxes, verticalalignment='top')

plt.subplot(212)
plt.plot(x1,y1n,'b.',x2,y2,'r:')
plt.text(0.05, 0.75, 'function sin(x) with noise', transform=plt.gca().transAxes, color='r', bbox={'fill':False, 'color':'r'})

plt.show()
