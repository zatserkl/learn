"""Python 3 code
Unpack tuple, the output of plt.xlim() into arguments of np.linspace
"""
import numpy as np
import matplotlib.pyplot as plt

def ret2():
    return 1, 2

def take2(a, b):
    print (a, b)

take2(*ret2())
take2(*(1,2))

t = (10, 20)
take2(*t)

take2(*(ret2()))

# np.linspace and plt.xlim in Python 3

np.linspace(*(ret2()), 10)

x = np.linspace(0., 3., 10)
y = np.sin(x)

plt.plot(x, y)

t = np.linspace(*(plt.xlim()), 5)
print(t)
