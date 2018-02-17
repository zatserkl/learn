import os
import sys

indent = 0

def print_dir(path):
    global indent               # needed to modify global variable indent
    indent_curr = ' '*indent
    dir_old = os.getcwd()
    os.chdir(path)
    items = os.listdir(os.getcwd())
    if indent > 0: print indent_curr,           # comma to suppress <LF>
    print '.. os.getcwd() =', os.getcwd()
    # print '.. items:', items
    for item in items:
        indent_curr = ' '*indent
        if indent > 0: print indent_curr,       # comma to suppress <LF>
        print item
        if os.path.isdir(item):
            indent += 4
            print_dir(item)
            indent -= 4
    os.chdir(dir_old)

if __name__ == '__main__':
    dir_curr = '.'
    if len(sys.argv) > 1: dir_curr = sys.argv[1]
    # print 'dir_curr =', dir_curr
    print_dir(dir_curr)
