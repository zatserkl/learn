import sys


class Solution:
    def reverse(self, x):
        """
        :type x: int
        :rtype: int
        """
        # work with n = abs(x)

        n = abs(x)
        n_inv = 0

        # convert n into list of decimal digits
        # NB: it will contain digits already in inv order

        n_inv_list = [n % 10]
        n //= 10
        while n:
            n_inv_list.append(n % 10)
            n //= 10

        print("n_inv_list =", n_inv_list)

        # TODO: check the range
        # AZ: test

        return n_inv


def main(n):
    solution = Solution()
    n_inv = solution.reverse(n)
    print("n =", n, "n_inv =", n_inv)


if __name__ == "__main__":
    n = 0
    if len(sys.argv) > 1:
        n = int(sys.argv[1])

    solution = Solution()
    n_inv = solution.reverse(n)
    print("n =", n, "n_inv =", n_inv)
