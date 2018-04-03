# modified example from https://wiki.python.org/moin/Generators

nmax = 5

# Generator expression: like list comprehension
doubles = (2*n for n in range(nmax))    # parenthesis () instead of brackets []

# print("list of doubles:", list(doubles))

while True:
    try:
        number = next(doubles)  # raises StopIteration if no default value
    except StopIteration:
        print("caught StopIteration")   # StopIteration e returns empty string
        break
    print(number)
