# http://www.python-course.eu/recursive_functions.php

# TODO: does not work at the moment


from timeit import Timer

def ifib(n):
    a, b = 0, 1
    for i in range(n):
        a, b = b, a + b
    return a

def fib(n):
    if n < 2:
        return 1
    return fib(n-1) + fib(n-2)


memo = {0:0, 1:1}
def fibm(n):
    if not n in memo:
        memo[n] = fibm(n-1) + fibm(n-2)
    return memo[n]


t1 = Timer("fib(10)")

for i in range(1,41):
	s = "fibm(" + str(i) + ")"
	t1 = Timer(s)
	time1 = t1.timeit(3)
	s = "fibi(" + str(i) + ")"
	t2 = Timer(s)
	time2 = t2.timeit(3)
	print("n=%2d, fib: %8.6f, fibi:  %7.6f, percent: %10.2f" % (i, time1, time2, time1/time2))
