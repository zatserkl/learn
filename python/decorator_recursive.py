""" See details about functools.wraps and caching with lru_cache at Answer #3
https://stackoverflow.com/questions/43432956/how-a-decorator-works-when-the-argument-is-recursive-function
"""

import time
from functools import wraps
from functools import lru_cache


# def rclock(func):
#     top = True
#     @wraps(func)
#     def clocked(*args):
#         nonlocal top
#         if top:
#             top = False
#             t0 = time.perf_counter()
#             result = func(*args) 
#             elapsed = time.perf_counter() - t0
#             name = func.__name__
#             arg_str = ', '.join(repr(arg) for arg in args)
#             print('[%0.8fs] %s(%s) -> %r' % (elapsed, name, arg_str, result))
#         else:
#             result = func(*args)
#             top = True
#         return result
#     return clocked


def clock(func):
    @wraps(func)  # provide doc of decorated function, not the decorator one
    def clocked(*args):
        ''' Clocking decoration wrapper '''
        t0 = time.perf_counter()
        result = func(*args) 
        elapsed = time.perf_counter() - t0
        name = func.__name__
        arg_str = ', '.join(repr(arg) for arg in args)
        print('[%0.8fs] %s(%s) -> %r' % (elapsed, name, arg_str, result))
        return result
    return clocked


@lru_cache(None)
@clock
def factorial(n):
    ''' Recursive factorial '''
    return 1 if n < 2 else n * factorial(n-1)

# Here because of use @wraps(func) in decorator-function 'clock'
# the factorial.__doc__ will return doc of decorated function 'factorial',
# not the doc of the decorator-function 'clock'

print("factorial.__name__, factorial.__doc__:")
print(factorial.__name__, factorial.__doc__)
print()

for n in range(3, 7):
    print('%d! = %d' % (n, factorial(n)))
for n in range(3, 7):
    print('%d! = %d' % (n, factorial(n))) 
