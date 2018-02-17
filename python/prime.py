import sys

"""Prints dividers of the number
"""

if len(sys.argv) > 1:
    n = int(sys.argv[1])
    for i in range(2, n):
        if n % i == 0: print i
else:
    print 'Usage:', sys.argv[0], 'N'
