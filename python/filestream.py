import sys


class FileStream:
    def __init__(self, fname):
        self.fname = fname
        self.gen_stream = self.__stream(self.fname)

    def __stream(self, fname):
        with open(fname) as filestream:
            line = filestream.readline()
            while line:
                yield line
                line = filestream.readline()

    def get_line(self):
        """ Catch StopIteration in calling routine to get end-of-stream.
        See https://stackoverflow.com/questions/4741243/how-to-pick-just-one-item-from-a-generator-in-python
        """
        return next(self.gen_stream)    # will raise StopIteration at end


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

    # yield_obj = yield_line(fname)
    filestream = FileStream(fname)

    print("\ncontent of", __file__)
    key = input("Enter <CR>=Continue, q=Quit ")
    if key.upper() == 'Q':
        print("Goodbye!")
        exit()

    # for line in yield_obj:
    #     print(line.strip('\n'))

    nlines_max = 80
    nlines = 0

    while True:
        nlines += 1
        if nlines > nlines_max:
            break
        line = ""
        try:
            line = filestream.get_line()
        except StopIteration:
            print("End-of-stream")
            break

        print(line.strip('\n'))
