# http://www.python-course.eu/recursive_functions.php

# TODO: does not work at the moment

from timeit import Timer
# from fibo import fib


memo = {0:0, 1:1}
def fibm(n):
    if not n in memo:
        memo[n] = fibm(n-1) + fibm(n-2)
    return memo[n]


t1 = Timer("fib(10)","from fibo import fib")

for i in range(1,41):
	s = "fibm(" + str(i) + ")"
	t1 = Timer(s,"from fibo import fibm")
	time1 = t1.timeit(3)
	s = "fibi(" + str(i) + ")"
	t2 = Timer(s,"from fibo import fibi")
	time2 = t2.timeit(3)
	print("n=%2d, fib: %8.6f, fibi:  %7.6f, percent: %10.2f" % (i, time1, time2, time1/time2))
