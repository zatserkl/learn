# Modified from book NumPy, 3rd Edition.pdf

#################################
# Use ndarray instead of matrix #
#################################

import numpy as np

A = np.array(np.mat("3 -2;1 0")) # use mat() interface for convenience
print("A:\n", A)

eigenvalues, eigenvectors = np.linalg.eig(A) # NB: eigenvalues is ndarray, eigenvectors is matrix

print('\neigenvalues:\n', eigenvalues,
      '\ntype(eigenvalues) =', type(eigenvalues))
print('\neigenvectors (column vectors):\n\n', eigenvectors,
      '\ntype(eigenvectors) =', type(eigenvectors))

print()

eigenvec1 = eigenvectors[:, 0]
print('eigenvec1 = eigenvectors[:, 0]:\n', eigenvec1)

eigenvec2 = eigenvectors[:, 1]
print('eigenvec2 = eigenvectors[:, 1]:\n', eigenvec2)

print("\nCheck eigenvectors and eigenvalues: A * evec / eval\n")

print('Check eigenvec1: np.dot(A, eigenvec1) / eigenvlues[0]:\n',
      np.dot(A, eigenvec1) / eigenvalues[0])

print('Check eigenvec2: np.dot(A, eigenvec2) / eigenvlues[1]:\n',
      np.dot(A, eigenvec2) / eigenvalues[1])

