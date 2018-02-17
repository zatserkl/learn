# https://stackoverflow.com/questions/292095/polling-the-keyboard-detect-a-keypress-in-python

import sys
import select

def pressEnter():
    i,o,e = select.select([sys.stdin],[],[],0.0001)
    for s in i:
        if s == sys.stdin:
            input = sys.stdin.readline()
            return True
    return False

while not pressEnter():
    print "Press Enter"
    pass
