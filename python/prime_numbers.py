# Andriy Zatserklyaniy <zatserkl@gmail.com> Jan 7, 2019


def prime_numbers(limit):
    """Computes prime numbers that not exceed limit
    """

    primes = [2]

    for i in range(2, limit+1):
        is_prime = True
        for prime in primes:
            if i % prime == 0:
                is_prime = False
                break

        if is_prime:
            primes.append(i)

    return primes


if __name__ == '__main__':

    limit = 15
    primes = prime_numbers(limit)
    print(primes)
