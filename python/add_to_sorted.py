def increasing_order():
    print('\nincreasing_order')

    pairs = [('two', 2), ('three', 3), ('one', 1), ('six', 6)]
    psort = sorted(pairs, key=lambda x: x[1])
    print('psort:', psort)

    p = ('four', 4)
    # p = ('zero',0)

    n = 0
    while p[1] > psort[n][1]:
        n += 1
        if n >= len(psort):
            break

    print('n =', n)

    psort.insert(n, p)
    print('psort:', psort)
    del psort[0]            # removes the first item
    # psort.pop()           # removes the last item
    print('psort:', psort)


def decreasing_order():
    print('\ndecreasing_order')

    pairs = [('two', 2), ('three', 3), ('one', 1), ('six', 6)]
    psort = sorted(pairs, key=lambda x: x[1], reverse=True)
    print('initial psort:', psort)

    p = ('four', 4)
    # p = ('zero',0)

    n = 0
    while p[1] < psort[n][1]:
        n += 1
        if n >= len(psort):
            break

    psort.insert(n, p)

    print('n =', n)

    print('final psort:  ', psort)
    # del psort[0]            # removes the first item
    psort.pop()           # removes the last item
    print('resized psort:', psort)

    for p in psort:
        print('p:', p[0], p[1])


increasing_order()
decreasing_order()
