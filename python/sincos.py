import matplotlib.pyplot as plt
from math import sin, cos

t = [0.01*x for x in range(int(12.5*100))]

plt.figure()
plt.plot(t, map(lambda(x): sin(x)+cos(x), t), color='black')
plt.plot(t, map(sin, t))
plt.plot(t, map(cos, t), color='r')
plt.show()
