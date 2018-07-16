# https://hub.packtpub.com/basics-jupyter-notebook-python/

# Andriy Zatserklyaniy <zatserkl@gmail.com> modified Jul 15, 2018

"""Functional programming

Python is a multi-paradigm language; it notably supports imperative,
object-oriented, and functional programming models. Python functions are
objects and can be handled like other objects. In particular, they can be
passed as arguments to other functions (also called higher-order functions).
This is the essence of functional programming.

Decorators provide a convenient syntax construct to define higher-order
functions. Here is an example using the is_even() function.

You can find more information about Python decorators at
https://en.wikipedia.org/wiki/Python_syntax_and_semantics#Decorators
and at http://www.thecodeship.com/patterns/guide-to-python-function-decorators/
"""

# is_even here is an example of some arbitrary function
def is_even(x: int):    # NB: type hint here is no more than a recommendation
    return x % 2 == 0

def show_output(func):
    """
    The show_output() function transforms an arbitrary function func()
    to a new function, named wrapped(),
    that displays the result of the function func()
    """
    def wrapped(*args, **kwargs):
        output = func(*args, **kwargs)
        print("wrapper: The result is:", output)
        return output
    return wrapped

print('is_even(3.14) =', is_even(3))

f = show_output(is_even)
res = f(3)
print('res =', res)

"""
Equivalently, this higher-order function can also be used with a decorator:
"""
@show_output
def square(x):
    return x*x

res = square(3)
print('res =', res)
