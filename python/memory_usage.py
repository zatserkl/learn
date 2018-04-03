# memory usage and decorator example

# https://stackoverflow.com/questions/938733/total-memory-used-by-python-process
# Answer #1
# AZ: To work with Python 3 I replaced get_memory_info() --> memory_info()

import time
import os
import psutil


def elapsed_since(start):
    return time.strftime("%H:%M:%S", time.gmtime(time.time() - start))


def get_process_memory():
    process = psutil.Process(os.getpid())
    return process.memory_info().rss    # AZ: get_memory_info --> memory_info


def track(func):
    """ Decorator
    """
    def wrapper(*args, **kwargs):
        mem_before = get_process_memory()
        start = time.time()
        result = func(*args, **kwargs)      # function call
        elapsed_time = elapsed_since(start)
        mem_after = get_process_memory()
        print("{}: memory before: {:,}, after: {:,}, consumed: {:,}; exec time: {}".format(
            func.__name__,
            mem_before, mem_after, mem_after - mem_before,
            elapsed_time))
        return result                       # returns result of function call
    return wrapper


# function to decorate

@track
def list_create(n):
    """ AZ: I expect that it will use 4*n bytes, but it's not the case...
    """
    print("list_create: n =", n)
    # x = [1] * n
    x = list(range(n))      # 40,505,344 for n = 1000000
    # x = range(n)          # 40,960
    return x


# stand-alone function

def list_create1(n):
    """ AZ: I expect that it will use 4*n bytes, but it's not the case...
    """
    print("list_create1: n =", n)
    # x = [1] * n
    x = list(range(n))      # 40,505,344 for n = 1000000
    # x = range(n)          # 40,960
    return x


# main calls the decorated function

print("\nWith decorator\n")

list_create(1000000)

print("\nWith menory_profiler\n")

from memory_profiler import memory_usage    # AZ: installed with conda

# https://github.com/pythonprofilers/memory_profiler/issues/114
args = (1000000,)
print(memory_usage((list_create1, args)))

print("\nWith decorator again\n")

list_create(1000000)
