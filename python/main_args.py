import sys

def hello(name):
    print(name)


if __name__ == "__main__":

    print('\nlen(sys.argv) =', len(sys.argv))
    print()

    for i in range(len(sys.argv)):
        print("{0:d}\t {1:s}".format(i, sys.argv[i]))

    print()

    for i, arg in enumerate(sys.argv):
        print("{0:d}\t {1:s}".format(i, sys.argv[i]))

    print("")   # print() will print empty parentheses in Python 2

    if len(sys.argv) > 1:
        print("Hello {0}!".format(sys.argv[1]))
    else:
        print("Usage: {0:s} name\n".format(sys.argv[0]))
