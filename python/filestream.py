import sys


class FileStream:
    """ Creates generator for the file content.
    The method next_line returns the next line from the generator.
    Calling rountine should catch StopIteration in case of EOF.
    """
    def __init__(self, fname):
        self.fname = fname
        self.gen_stream = self.__stream(self.fname)

    def __stream(self, fname):
        """ Create generator for lines
        """
        with open(fname) as filestream:
            line = filestream.readline()
            while line:
                yield line
                line = filestream.readline()

    def next_line(self):
        """ Returns the next line from the generator.
        Raises StopIteration at EOF. Catch it in the calling routine.
        """
        return next(self.gen_stream)    # will raise StopIteration at EOF


def yield_line(fname):
    """ Standalone function
    """
    with open(fname) as file:
        line = file.readline()
        while line:
            yield line
            line = file.readline()


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
            line = filestream.next_line()
        except StopIteration:
            print("End-of-stream")
            break

        print(line.strip('\n'))
