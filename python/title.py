#!/usr/bin/env python

from __future__ import print_function   # to work with both Python 3 and 2
import sys


"""
Example of input:
title LONG TERM COARSENING IN RENÉ 80 Ni-BASE SUPERALLOY

Output:
Long Term Coarsening In René 80 Ni-Base Superalloy
"""

if len(sys.argv) < 2:
    print('Usage: {:s} title'.format(sys.argv[0]))
else:
    s_input = ' '.join(sys.argv[1:])
    print(s_input.title())
