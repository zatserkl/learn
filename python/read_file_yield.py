def yield_line(file):
    with open(fname) as file:
        line = file.readline()
        while line:
            yield line
            line = file.readline()


fname = __file__
print("\ncontent of", __file__, "\n")
for line in yield_line(fname):
    print(line.strip('\n'))

# you may also get a list from the yield:
# yield_obj = yield_line(fname)
# print(list(yield_obj))
#
# NB: the next call will print an empty list:
# print(list(yield_obj))
