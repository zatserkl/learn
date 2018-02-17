#! /usr/bin/env python

import sys

if len(sys.argv) < 2:
    print 'Usage:', sys.argv[0], 'file_to_check'
    exit()

fname = sys.argv[1]

with open(fname) as fp:
    for i, line in enumerate(fp):
        if "\xe2" in line:
            print i, '\t', repr(line)
