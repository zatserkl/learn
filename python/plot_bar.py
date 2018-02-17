import matplotlib.pyplot as plt
from collections import Counter

grades = [83,95,91,87,70,0,85,82,100,67,73,77,0]

# bin to decimals

#
# "You can assign lambdas to variables, although most people will tell you that
# you should just use def instead" -- Data Science from Scratch.pdf, p. 18
#
# decile = lambda(grade): grade // 10 * 10        # not recommended in general
# def decile(grade): return grade // 10 * 10      # recommended

# histogram = Counter([decile(grade) for grade in grades])                  # use function decile
histogram = Counter([(lambda(x): x // 10 * 10)(grade) for grade in grades]) # use lambda directly

plt.figure()
plt.bar(histogram.keys(), histogram.values(), width=8)
plt.axis([0, 1.10*max(histogram.keys()), 0, 1.10*max(histogram.values())])
plt.xticks([10 * i for i in range(11)])
plt.xlabel("Decile")
plt.ylabel("# of Students")
plt.title("Distribution of Exam 1 Grades")
plt.show()                                              # this statement is not needed in IPython
