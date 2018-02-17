#!/usr/bin/env python

# based on https://stackoverflow.com/questions/39795518/detect-if-key-is-down-mac-python
# to restore the terminal see Answer #2 at https://stackoverflow.com/questions/8757915/how-to-turn-console-echo-back-on-after-tty-setcbreak

import sys,tty
import termios

# get the current attributes of sys.stdin
fd = sys.stdin.fileno()
old_attributes = termios.tcgetattr(fd)

tty.setcbreak(sys.stdin)

key_code_q = 113
print "press q to quit"

key = 0
while key != key_code_q:
    key = ord(sys.stdin.read(1))  # key captures the key-code
    if key == key_code_q:
        print "you pressed q ( key =", key_code_q, ")"
        break
    else:
        print "you pressed", key
        pass

# restore old attributes of the sys.stdin
termios.tcsetattr(sys.stdin, termios.TCSADRAIN, old_attributes)

# sys.exit(0)
