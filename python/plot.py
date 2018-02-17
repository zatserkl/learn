"""See Python and Matplotlib Essentials for Scientists and Engineers.pdf
"""

import matplotlib.pyplot as plt

x = range(5)
y = [xi**2 for xi in x]

plt.figure()

# fig = plt.figure()    # create a figure pointed by fig
# fig.number            # get number of the figure pointed by fig
# plt.gcf().number      # get number of the curent figure
# plt.figure(1)         # make figure No. 1 current
# plt.clf()             # clear current figure

plt.plot(x, y, marker='o', color='black', label='square', linestyle='None')

plt.title('y vs x')
plt.xlabel('x')
plt.ylabel('y')

# plt.legend(loc=1, numpoints=1) # loc=1 is the default location, default numpoints=2 in the legend
plt.legend(loc=2, numpoints=1)   # loc=2 is the top left corner

plt.grid(True)          # turn on gridlines

plt.show()
