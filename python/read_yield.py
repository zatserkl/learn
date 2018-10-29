# Andriy Zatserklyaniy <zatserkl@gmail.com> Oct 28, 2018

# write large file

# python read_yield.py large_file.txt 100000000

import sys


def write_large_file(ofname, n=100):
    with open(ofname, 'w') as ofile:
        for i in range(n):
            ofile.write('{0:9d}\n'.format(i))

    print('Wrote integer numbers from 0 to', n, 'into file', ofname)


def read_large_file(ifname):
    """Yields line-by-line to avoid read the whole file into memory
    """
    with open(ifname) as ifile:
        for line in ifile:
            yield line

if __name__ == '__main__':

    print('sys.len(argv) =', len(sys.argv))
    for iarg, arg in enumerate(sys.argv):
        print(iarg, '\t', arg)

    ofname = 'large_file.txt'
    if len(sys.argv) > 1:
        ofname = sys.argv[1]

    n = 100000000               # for 1000000000 bytes = 954M
    if len(sys.argv) > 2:
        n = int(sys.argv[2])

    print('Write', n, 'integers into output file', ofname)
    write_large_file(ofname, n)

    print('\nRead that file\n')

    ifname = ofname

    # create generator object
    lines = read_large_file(ifname)

    line = next(lines)  # use next to read the next line from generator
    number = int(line)

    print('the first number:', number)

    print('read next numbers')

    for line in lines:
        number = int(line)

    print('the last number is', number)

    input('Look at memory consumption, press <CR> to see read in one object')

    # with open(ifname) as ifile:
    #     for line in ifile:
    #         number = int(line)

    file = open(ifname)
    lines = file.readlines()

    number = lines[-1]
    print('the last number is', number)

    input('Look at memory consumption, and press <CR> to quit')
