import time
from functools import lru_cache

# NB: the Fibonacci sequence here is for n = 0, 1, 2, ...
# while usually n is counted from 1
# See http://mathworld.wolfram.com/FibonacciNumber.html
#
# 0 1 2 3 4 5
# 1 1 2 3 5 8

def fibonacci_direct(n):
    if n < 2:
        return 1
    return fibonacci_direct(n-1) + fibonacci_direct(n-2)


print("\nElapsed time for", fibonacci_direct.__name__);
start_time = time.clock()
fibonacci_direct(20)
stop_time = time.clock()
print(stop_time - start_time, 'seconds');

def fibonacci_cache(n):
    cache = {0:0, 1:1}  # provides cache for fibonacci
    def fibonacci(n):
        if n < 2:
            return 1
        if not n in cache:
            cache[n] = fibonacci(n-1) + fibonacci(n-2)
        return cache[n]
    return fibonacci(n)


print("\nElapsed time for", fibonacci_cache.__name__);
start_time = time.clock()
fibonacci_cache(20)
stop_time = time.clock()
print(stop_time - start_time, 'seconds');

# Uses functools.lru_cache for automatic keeping of recent results of fibonacci
# https://stackoverflow.com/questions/43432956/how-a-decorator-works-when-the-argument-is-recursive-function

from functools import lru_cache

@lru_cache(None)
def fibonacci(n):
    if n < 2:
        return 1
    return fibonacci(n-1) + fibonacci(n-2)

print("\nElapsed time for", fibonacci.__name__, 'direct that uses functools.lru_cache');
start_time = time.clock()
fibonacci(20)
stop_time = time.clock()
print(stop_time - start_time, 'seconds');
