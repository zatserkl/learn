import numpy
import scipy
import matplotlib.pyplot as plt

x = numpy.linspace(0, 1, 11)    # 11 points (0 and 1 included) to dx = 0.1
y = numpy.sin(x*numpy.pi/2)     # let's this will be data

#
# fit
#
line_par = numpy.polyfit(x, y, deg=1)       # line is an array

print 'line_par =', line_par    

#
# plot
#
plt.figure()

#--NB marker:  '.'
#
plt.plot(x, y, '.', x, numpy.polyval(line_par, x), '-')
plt.title('straight line fit example')
plt.show()
