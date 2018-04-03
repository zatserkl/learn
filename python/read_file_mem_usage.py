import sys


def yield_line(fname):
    with open(fname) as file:
        line = file.readline()
        while line:
            yield line
            line = file.readline()


# it's better to implement in class
# def stream_line(fname):
#    gen_file = yield_line(fname)


if __name__ == "__main__":

    fname = __file__
    if len(sys.argv) > 1:
        fname = sys.argv[1]

    yield_obj = yield_line(fname)

    print("\ncontent of", __file__)
    key = input("Enter <CR>=Continue, q=Quit ")
    if key.upper() == 'Q':
        print("Goodbye!")
        exit()

    for line in yield_obj:
        print(line.strip('\n'))
