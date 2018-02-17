###################################################################
# This is the final solution: use array for the matrix operations #
###################################################################

"""
See https://docs.scipy.org/doc/numpy-dev/user/numpy-for-matlab-users.html

NumPy matrix operations: use arrays and dot(A, B) for multiplication.
NB: for ndarray all operations (*, /, +, - etc.) are elementwise

The vector is considered as a row or a column depending on context.
dot(A,v) treats v as a column vector, while dot(v,A) treats v as a row vector.
NB: attribute Transpose does not change the ndarray vector.

To use convenient interface like mat("1 -2 1;0 2 -8;-4 5 9")
use casting A = np.array(np.mat("1 -2 1;0 2 -8;-4 5 9"))

Solve equation A*x = b
where all variables are represented by ndarray.
"""

import numpy as np


def solve_matrix_array():
    A = np.array(np.mat("1 -2 1;0 2 -8;-4 5 9")) # convenient mat interface
    print("A:\n", A)
    print("type(A) =", type(A))

    b = np.array([0, 8, -9])
    print("b is a numpy array:\n", b)
    print("type(b) =", type(b))


    x = np.linalg.solve(A, b) # b will be treated as a column vector
    print("Solution of the equation A*x = b:\n", x, "\ntype(x) =", type(x))

    # check the solution
    b1 = np.dot(A, x) # x will be treated as a column vector
    print('b1 = np.dot(A, x):\n', b1)
    print("type(b1) =", type(b1))


print("\nSolve equation A*x = b")
print("where we use dot-product np.dot(A, x)")

print("\ndefine b as a ndarray: it will be treated row- or column-wise "
      "depending on context")

solve_matrix_array()
