# NumPy, 3rd Edition.pdf, p.148

import numpy as np
import numpy.linalg as linalg


A = np.mat([[1, -2, 1], [0, 2, -8], [-4, 5, 9]], dtype=float)
print "A\n", A

b = np.array([0, 8, -9])
print "b\n", b

x = np.linalg.solve(A, b)
print "Solution\n", x
