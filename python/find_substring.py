# https://stackoverflow.com/questions/4664850/find-all-occurrences-of-a-substring-in-python

def findall(s, p):
    '''Yields all the positions of
    the pattern p in the string s.'''
    i = s.find(p)
    while i != -1:
        yield i
        i = s.find(p, i+1)

s = "abcdefghidefklmdefxyz"
pattern = "def"

# print(findall(s, pattern))

alist = findall(s, pattern)
print(alist)

for x in alist:
    print(x)

for x in findall(s, pattern):
    print(x)
