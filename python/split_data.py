from __future__ import division
import random

def split_data(data, prob):
    result = [], []     # tuple is immutable, but you can modify referenced content
    # random.seed(0)    # comment out for production
    for row in data:
        result[0 if random.random() < prob else 1].append(row)
    return result

#
# code to generate 20 elements of data
#
# for i in range(20):
#     char = chr(ord('A') + i)
#     li1 = (i+1)*10
#     li2 = (i+1)*100
#     print "[%2d, '%s', [%d, %d]]," % (i, char, li1, li2)

# data = [
#     [ 0, 'A', [10, 100]],
#     [ 1, 'B', [20, 200]],
#     [ 2, 'C', [30, 300]],
#     [ 3, 'D', [40, 400]],
#     [ 4, 'E', [50, 500]],
#     [ 5, 'F', [60, 600]],
#     [ 6, 'G', [70, 700]],
#     [ 7, 'H', [80, 800]],
#     [ 8, 'I', [90, 900]],
#     [ 9, 'J', [100, 1000]],
#     [10, 'K', [110, 1100]],
#     [11, 'L', [120, 1200]],
#     [12, 'M', [130, 1300]],
#     [13, 'N', [140, 1400]],
#     [14, 'O', [150, 1500]],
#     [15, 'P', [160, 1600]],
#     [16, 'Q', [170, 1700]],
#     [17, 'R', [180, 1800]],
#     [18, 'S', [190, 1900]],
#     [19, 'T', [200, 2000]]]

N = 60
print 'Use', N, 'rows'
data = []
for i in range(N):
    char = chr(ord('A') + i)
    li1 = (i+1)*10
    li2 = (i+1)*100
    row = list([i, char, list([li1, li2])])
    data.append(row)

prob = 2/3
list1, list2 = split_data(data, prob)

print 'len(list1) =', len(list1)
# for i,row in enumerate(list1): print i, row
for i,row in enumerate(list1):
    print i, row
    if i > 2: break
print '\nlen(list2) =', len(list2)
# for i,row in enumerate(list2): print i, row
for i,row in enumerate(list2):
    print i, row
    if i > 2: break

print '\nratio =', len(list1) / (len(list1) + len(list2)), 'while prob =', prob
