# Andriy Zatserklyaniy <zatserkl@gmail.com> Jul 4, 2018

# The fastest Python's solution to date


class Solution(object):
    def reverseWords(self, s):
        """
        :type s: str
        :rtype: str
        """
        s_list = s.split()
        return ' '.join(s_list[::-1])


def call_fun(s):
    solution = Solution()
    output = solution.reverseWords(s)
    print(s, '-->', output)


call_fun('the sky is blue')
call_fun(' ')
