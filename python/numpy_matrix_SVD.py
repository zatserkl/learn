# Modified from book NumPy, 3rd Edition.pdf

import numpy as np

A = np.array(np.mat("4 11 14;8 7 -2"))
print("A:\n", A)

U, Sigma, V = np.linalg.svd(A, full_matrices=False)

"""U and V are orthogonal matrices: their columns are set of orthonormal vectors
"""

print('U:\n', U)
print('Sigma:\n', Sigma)
print('V:\n', V)

print("Product U * np.diag(Sigma) * V = np.dot(U, np.dot(np.diag(Sigma),V))\n",
      np.dot(U, np.dot(np.diag(Sigma),V)))

#
# Play with matrix
#

print("\nGet singular values from eigenvectors and sqrt(eigenvalues)"
      "of Atransposed*A matrix")

ATA = np.dot(A, A.T)
print('ATA = np.dot(A, A.T):\n', ATA)

# Eigenvalues and eigenvectors of the ATA

print("\nEigenvalues and eigenvectors of ATA")

eigenvalues, eigenvectors = np.linalg.eig(ATA)

print("\neigenvalues:\n", eigenvalues)
print("type(eigenvalues) =", type(eigenvalues))
print("\neigenvectors (column vectors): the same as matrix U\n", eigenvectors)
print("type(eigenvalues) =", type(eigenvalues))
print("NB: different sign of the first column\nThis is the SVD sign ambiguity\n")

print("np.sqrt(eigenvalues):\n", np.sqrt(eigenvalues))

print("The matrix V is unitary: V*V.T = np.dot(V, V.T)\n", np.dot(V, V.T))

