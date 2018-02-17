# Original from https://github.com/CoreyMSchafer/code_snippets/tree/master/Generators
# uses custom memory profile module mem_profile
#
# modified for standard Python modules with help of Answer #1 from
# http://stackoverflow.com/questions/41191412/no-module-named-mem-profile

"""Demo on generator
"""

import resource
import time
import random

names = ['John', 'Corey', 'Adam', 'Steve', 'Rick', 'Thomas']
majors = ['Math', 'Engineering', 'CompSci', 'Arts', 'Business']

print "Memory (Before): {}Mb".format(resource.getrusage(resource.RUSAGE_SELF).ru_maxrss/2**20)

def people_list(num_people):
    result = []
    for i in xrange(num_people):
        person = {
            'id': i,
            'name': random.choice(names),
            'major': random.choice(majors)
        }
        result.append(person)
    return result

def people_generator(num_person):
    for i in xrange(num_people):
        person = {
            'id': i,
            'name': random.choice(names),
            'major': random.choice(majors)
        }
        yield person

N = 1000000

t1 = time.clock()
people_list(N)
print "Memory (After people_list): {}Mb".format(resource.getrusage(resource.RUSAGE_SELF).ru_maxrss/2**20)
t2 = time.clock()
print "Took {} seconds".format(t2 - t1)

t1 = time.clock()
people_generator(N)
print "Memory (After people_generator): {}Mb".format(resource.getrusage(resource.RUSAGE_SELF).ru_maxrss/2**20)
t2 = time.clock()
print "Took {} seconds".format(t2 - t1)

