# Andriy Zatserklyaniy <zatserkl@gmail.com> Jan 7, 2019

import sys


def prime_numbers(limit):
    """Computes prime numbers that don't exceed limit
    """

    primes = [2]  # add 1 at the end

    for i in range(2, limit+1):
        is_prime = True
        for prime in primes:
            if i % prime == 0:
                is_prime = False
                break

        if is_prime:
            primes.append(i)

    primes.insert(0, 1)  # finally add 1

    return primes


if __name__ == '__main__':

    limit = 15
    if len(sys.argv) > 1:
        limit = int(sys.argv[1])

    primes = prime_numbers(limit)
    print(primes)
