"""
$ python sys_argv.py abc def 345
len(sys.argv) = 4
sys.argv[0] = sys_argv.py
sys.argv[0] = abc
sys.argv[0] = def
sys.argv[0] = 345
"""
import sys

print 'len(sys.argv) =', len(sys.argv)
for i,arg in enumerate(sys.argv):
    # print 'sys.argv[', i, '] =', arg
    # print 'sys.argv[%d] = %s' % (i, arg)      # arguments should be a tuple (if more than 1)
    print "sys.argv[{0}] = {1}".format(i, arg)  # recommended way
