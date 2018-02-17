with open("contents.txt", "r") as file:
    for line in file:
        line = line.strip().replace(':', ' -').replace(' PDF', '')
        print line
        for c in line:
            if ord(c) > 128: print '-->', c, ord(c)
