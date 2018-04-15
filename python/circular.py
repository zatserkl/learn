import collections


nmax = 100000
buf = collections.deque(maxlen=nmax)
for i in range(nmax):
    buf.append([n for n in range(1000)])
    if i % 1000 == 0:
        print("filled", i)

print("len(buf) =", len(buf))
print("sum(buf[0]) =", sum(buf[0]))

sum_tot = 0
for i in range(len(buf)):
    sum_tot += sum(buf[i])

print("sum_tot =", sum_tot)
input("\nLook at memory usage.\nPress <Enter> to continue")
