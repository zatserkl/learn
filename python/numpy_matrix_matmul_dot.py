##############################
# Use matrix and np.matmul() #
##############################

# Book: NumPy, 3rd Edition.pdf

import numpy as np

print("\nUse matrix and np.matmul()\n")

A = np.mat("1 -2 1;0 2 -8;-4 5 9")
print('A:\n', A)

b = np.mat([0, 8, 9]).T # needs to be a column vector
print('b:\n', b)

x = np.linalg.solve(A, b)
print('x:\n', x)

print('Check np.matmul(A, x):\n', np.matmul(A, x))

############################
# Use ndarray and np.dot() #
############################

print("\nUse ndarray and np.dot()\n")

A = np.array(np.mat("1 -2 1;0 2 -8;-4 5 9"))
print('A:\n', A)

b = np.array([0, 8, 9])
print('b:\n', b)

x = np.linalg.solve(A, b)
print('x:\n', x)

print('Check np.dot(A, x):\n', np.dot(A, x))
