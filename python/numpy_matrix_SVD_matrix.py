#######################################################################
# Use the version with ndarray instead of matrix: numpy_matrix_SVD.py #
#######################################################################

# Modified from book NumPy, 3rd Edition.pdf

import numpy as np

A = np.matrix("4 11 14;8 7 -2")
print("A:\n", A)

U, Sigma, V = np.linalg.svd(A, full_matrices=False)

print('U:\n', U)
print('Sigma:\n', Sigma)
print('V:\n', V)

print("Product U * np.diag(Sigma) * V\n", U * np.diag(Sigma) * V)

#
# Eigenvalues and eigenvectors exist for square matrix only
#

# print('\nEigenvalues and eigenvectors:\n')

# eigenvalues, eigenvectors = np.linalg.eig(A) # NB: eigenvalues is ndarray, eigenvectors is matrix

# print('eigenvalues:\n', eigenvalues,
#       '\ntype(eigenvalues) =', type(eigenvalues))
# print('eigenvectors (column vectors):\n', eigenvectors,
#       '\ntype(eigenvectors) =', type(eigenvectors))

# eigenvec1 = eigenvectors[:, 0]
# print('eigenvec1 = eigenvectors[:, 0]:\n', eigenvec1)

# eigenvec2 = eigenvectors[:, 1]
# print('eigenvec2 = eigenvectors[:, 1]:\n', eigenvec2)

#
# Play with matrix
#

print("\nGet singular values from eigenvectors and sqrt(eigenvalues)"
      "of Atransposed*A matrix")

A2 = np.matmul(A, A.T)
print('A2 = np.matmul(A, A.T):\n', A2)

# Eigenvalues and eigenvectors of the A2

print('\nEigenvalues and eigenvectors of A2 = A*A.T:\n', A2)

eigenvalues, eigenvectors = np.linalg.eig(A2) # NB: eigenvalues is ndarray, eigenvectors is matrix

print('eigenvalues:\n', eigenvalues)
print('eigenvectors (column vectors): the same as matrix U\n', eigenvectors)
print("NB: different sign of the first column\nThis is the SVD sign ambiguity\n")

print("np.sqrt(eigenvalues):\n", np.sqrt(eigenvalues))

print("The maatrix V is unitary: V*V.T:\n", V*V.T)
