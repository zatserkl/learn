""" https://leetcode.com/problems/two-sum/description/
Given an array of integers, return indices of the two numbers such that
they add up to a specific target.

You may assume that each input would have exactly one solution, and you may
not use the same element twice.

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
"""

# import numpy as np


class Solution:
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        print(nums, target)
        # index = np.argsort(nums)  # indices of sorted elements
        index = [x[0] for x in sorted(enumerate(nums), key=lambda x: x[1])]
        print("index:", index)
        for i in index:
            print(nums[i], end=',')
        print()
        n1 = 0  # index of element in indices
        n2 = len(index) - 1
        while n2 > n1:
            print(nums[index[n1]], nums[index[n2]])
            sum = nums[index[n1]] + nums[index[n2]]
            if sum == target:
                return index[n1], index[n2]
            if sum > target:
                n2 -= 1
            else:
                n1 += 1
        return -1, -1

    def twoSumHash(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        hash = {}
        for i in range(len(nums)):
            complement = target - nums[i]
            if complement in hash:
                return i, hash[complement]  # success
            hash[nums[i]] = i
        return -1, -1           # no match


# nums = [2, 7, 11, 15]
# target = 9
# nums = [3, 3]
# target = 6
nums = [3, 2, 4]
target = 6

solution = Solution()
n1, n2 = solution.twoSum(nums, target)
print("twoSum: n1, n2:", n1, n2)
n1, n2 = solution.twoSumHash(nums, target)
print("twoSumHash: n1, n2:", n1, n2)

if n2 > 0:
    print("solution: n1, n2:", n1, n2)
else:
    print("no solution")
