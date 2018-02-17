import matplotlib.pyplot as plt
import random
# from collections import Counter   # another way is to use Counter

mean = 0.
sigma = 1.
gnumbers = [random.gauss(mean, sigma) for i in range(1000)]

plt.figure()
plt.hist(gnumbers)
plt.show()              # you don't need this statement in IPython
