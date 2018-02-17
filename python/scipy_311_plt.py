import numpy as np
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt

# Let's create a function to model and create data
def func(x, a, b):
    return a * x + b

# Generating clean data
x = np.linspace(0, 10, 100)
y = func(x, 1, 2)

# Adding noise to the data
np.random.seed(0)
yn = y + 0.9 * np.random.normal(size=len(x))

# Executing curve_fit on noisy data
popt, pcov = curve_fit(func, x, yn)

#popt returns the best fit values for parameters of the given model (func)
print popt

# Plot out the current state of the data and model
ym = func(x, popt[0], popt[1])

#
# create a subplot in the new figure
#
fig = plt.figure()
# ax = fig.add_subplot(111)

# ax.plot(x, y, c='k', label='Function')
# ax.scatter(x, yn)
# ax.plot(x, ym, c='r', label='Best fit')
# ax.legend(loc='upper left')
plt.plot(x, y, c='k', label='Function')
plt.scatter(x, yn)
plt.plot(x, ym, c='r', label='Best fit')
plt.legend(loc='upper left')

#
# text to plot: fit parameters
#
text = 'a = %f\nb = %f' %(popt[0], popt[1])

# ax.text(0.05, 0.65, text, transform=ax.transAxes)

# alternative method: get current axes with plt.axes and use their transform

# axes = plt.axes()
plt.text(0.05, 0.65, text, transform=plt.axes().transAxes)       # in one line

fig.savefig('scipy_311.pdf', bbox_inches='tight')

plt.show()      #--AZ--
