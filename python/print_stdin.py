#!/Users/zatserkl/anaconda/bin/python

import sys, re

def printre():
    """The command line parameter provides regular expession
    The script accepts lines and after end of input (Ctrl-D)
    prints lines that match the regular expression
    Example:
code$ python print_stdin.py '^m'
len(sys.argv) = 2
abb
mcp
more
ggg
mix
bbb
^D      matches: mcp
	matches: more
	matches: mix    
    """
    print 'len(sys.argv) =', len(sys.argv)

    if len(sys.argv) > 1:
        # print sys.argv[1]
        regex = sys.argv[1]                     # NB: variable regex has global scope
    else:
        print 'Usage: ', __name__, 'regex'
        return

    for line in sys.stdin:                                          # line includes newline character
        # if re.search(regex, line): print '\tmatches:', line,      # ending comma to suppress <CR>
        if re.search(regex, line): print '\tmatches:', line.strip() # strip newline character

if __name__ == '__main__':
    printre()
