#################################################
# See the final solution in the numpy_matrix.py #
#################################################

import numpy as np

"""
Solve equation A*x = b
where b is represented by ndarray or matrix

NB: use matmul for the multiplication of matrices (or arrays).
"""


def solve_matrix_matrix():
    A = np.mat("1 -2 1;0 2 -8;-4 5 9")
    print("A:\n", A)

    # define b as matrix: b should be a column vector
    b = np.matrix([0, 8, -9]).T
    print("b is a numpy matrix:\n", b)

    x = np.linalg.solve(A, b)
    print("Solution of the equation A*x = b:\n", x, "\ntype(x) =", type(x))

    # check the solution
    # b1 = A.dot(x)
    # b1 = np.dot(A, x)
    b1 = np.matmul(A, x)
    print('b1 = np.matmul(A, x):\n', b1)


def solve_matrix_array():
    A = np.mat("1 -2 1;0 2 -8;-4 5 9")
    print("A:\n", A)

    # define b as ndarray: b should be a row vector
    b = np.array([0, 8, -9])
    # b = np.matrix([0, 8, -9]).T # if b is matrix, it should be column
    print("b is a numpy array, row vector:\n", b)

    x = np.linalg.solve(A, b) # if b is column matrix, x will be column matrix
    print("Solution of the equation A*x = b:\n", x, "\ntype(x) =", type(x))

    # check the solution
    # b1 = A.dot(x)     # if b is column matrix, x will be column matrix
    b1 = np.dot(A, x.T) # if b is array, x will be array: transpose it
    print('b1 = A.dot(x.T):\n', b1)
    b1 = np.matmul(A, x.T)
    # b1 = A.dot(x.T) # if b is array, x will be array: transpose it
    print('b1 = np.matmul(A, x.T):\n', b1)


print("\nSolve equation A*x = b")
print("where we use dot-product A.dot(x)")

print("\ndefine b as a np.matrix")

solve_matrix_matrix()

print("\ndefine b as a np.array")

solve_matrix_array()
