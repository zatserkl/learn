from __future__ import division

# at this stage in the book we haven't actually installed matplotlib,
# comment this out if you need to
from matplotlib import pyplot as plt

##########################
#                        #
# FINDING KEY CONNECTORS #
#                        #
##########################

users = [
    { "id": 0, "name": "Hero" },
    { "id": 1, "name": "Dunn" },
    { "id": 2, "name": "Sue" },
    { "id": 3, "name": "Chi" },
    { "id": 4, "name": "Thor" },
    { "id": 5, "name": "Clive" },
    { "id": 6, "name": "Hicks" },
    { "id": 7, "name": "Devin" },
    { "id": 8, "name": "Kate" },
    { "id": 9, "name": "Klein" },
    { "id": 10, "name": "Jen" }
]

friendships = [(0, 1), (0, 2), (1, 2), (1, 3), (2, 3), (3, 4),
               (4, 5), (5, 6), (5, 7), (6, 8), (7, 8), (8, 9)]

# adding friends

# first give each user an empty list
for user in users:
    user["friends"] = []                # add one more item into dictionary

# fill up friends
#
# this is my version of the data structure, different from the book one:
# I save just index, not a complete user in the list of friends
#
for i,j in friendships:
    users[i]['friends'].append(j)
    users[j]['friends'].append(i)

def number_of_friends(user):
    return len(user['friends'])

for i,user in enumerate(users):
    print i, len(user['friends'])

total_connections = sum(number_of_friends(user) for user in users)
print 'total_connections =', total_connections

total_connections = sum(number_of_friends(user)
                        for user in users) # 24

print 'total_connections =', total_connections

num_users = len(users)
avg_connections = total_connections / num_users
print 'num_users =', num_users, 'avg_connections =', avg_connections

################################
#                              #
# DATA SCIENTISTS YOU MAY KNOW #
#                              #
################################

# list of friends by id: list of tuples
num_friends_by_id = [(user['id'], number_of_friends(user)) for user in users]

print 'num_friends_by_id sorted:', sorted(num_friends_by_id, key=lambda(id,n): n, reverse=True)

def fof(id):
    """ works fine, returns all friends of friends with duplication:
    fof(0)
    In [48]: fof(0)
    Out[48]: [0, 2, 3, 0, 1, 3]
    """
    fall = []
    for friend in users[id]['friends']:
        fall.extend(users[friend]['friends'])
    return fall

print 'fof(0) =', fof(0)

def fofset(id):
    """Returns friends of friends using set.
    1) No duplication.
    2) No id and its direct friends in the list
    """
    fall = set()
    for friend_id in users[id]['friends']:
        # print '\t friend_id =', friend_id
        for fof in users[friend_id]['friends']:
            # print '\t\t adding fof =', fof
            fall.add(fof)
    # print 'fall:', fall
    # remove from the set id and its friends
    fall.remove(id)
    for friend_id in users[id]['friends']:
        # print 'friend_id =', friend_id
        if friend_id in fall: fall.remove(friend_id)
    return list(fall)

print 'fofset(3) =', fofset(3)

def friends_of_friend_ids_bad(user):
    # foaf is short for "friends of friend"
    return [fid
            for id in user['friends']
            for fid in users[id]['friends']]    # NB: no indent because this is a list comprehension

print 'friends_of_friend_ids_bad(users[0]) =', friends_of_friend_ids_bad(users[0])

def friends_of_friend_ids_bad(user_id):
    # foaf is short for "friends of friend"
    return [fid
            for id in users[user_id]['friends']
            for fid in users[id]['friends']]    # NB: no indent because this is a list comprehension

print 'friends_of_friend_ids_bad(0) =', friends_of_friend_ids_bad(0)

def friends_of_friend_ids_set(user_id):
    # foaf is short for "friends of friend"
    return list(set(
        [fid
            for id in users[user_id]['friends']
            for fid in users[id]['friends']]    # NB: no indent because this is a list comprehension
    ))

print 'friends_of_friend_ids_set(0) =', friends_of_friend_ids_set(0)

print [friend for friend in users[0]['friends']]
print [friend for friend in users[1]['friends']]
print [friend for friend in users[2]['friends']]

from collections import Counter

def not_the_same(user, other_user):
    return user['id'] != other_user['id']

def not_friends_az(user, other_user):
    """other_user is not a friend if he's not in user['friends'], that is 
    he is not_the_same for every user in user['friends']
    """
    for friend_id in user['friends']:
        if not not_the_same(users[friend_id], other_user): return False
    return True

def not_friends(user, other_user):
    """other_user is not a friend if he's not in user['friends'], that is 
    he is not_the_same for every user in user['friends']
    """
    return all(not_the_same(users[friend_id], other_user) for friend_id in user['friends'])

# def friends_of_friend_ids(user):
#     return Counter(id
#                    for friend_id in user['friends']         # for each of my friends
#                    for id in users[friend_id]['friends']    # count *their* friends
#                    if not_the_same(user, users[id])         # who aren't me
#                    and not_friends_az(user, users[id]))        # and aren't my friends

def friends_of_friend_ids(user):
    return Counter(id
                   for friend_id in user['friends']         # for each of my friends
                   for id in users[friend_id]['friends']    # count *their* friends
                   if not_the_same(user, users[id])         # who aren't me
                   and not_friends(user, users[id]))        # and aren't my friends

print 'friends_of_friend_ids(users[3]) =', friends_of_friend_ids(users[3])

#
# pairs of (id, interest)
#
interests = [
    (0, "Hadoop"), (0, "Big Data"), (0, "HBase"), (0, "Java"),
    (0, "Spark"), (0, "Storm"), (0, "Cassandra"),
    (1, "NoSQL"), (1, "MongoDB"), (1, "Cassandra"), (1, "HBase"),
    (1, "Postgres"), (2, "Python"), (2, "scikit-learn"), (2, "scipy"),
    (2, "numpy"), (2, "statsmodels"), (2, "pandas"), (3, "R"), (3, "Python"),
    (3, "statistics"), (3, "regression"), (3, "probability"),
    (4, "machine learning"), (4, "regression"), (4, "decision trees"),
    (4, "libsvm"), (5, "Python"), (5, "R"), (5, "Java"), (5, "C++"),
    (5, "Haskell"), (5, "programming languages"), (6, "statistics"),
    (6, "probability"), (6, "mathematics"), (6, "theory"),
    (7, "machine learning"), (7, "scikit-learn"), (7, "Mahout"),
    (7, "neural networks"), (8, "neural networks"), (8, "deep learning"),
    (8, "Big Data"), (8, "artificial intelligence"), (9, "Hadoop"),
    (9, "Java"), (9, "MapReduce"), (9, "Big Data")
]

def data_scientists_who_like(target_interest):
    return [id for id,interest in interests
            if interest == target_interest]

print "data_scientists_who_like('Hadoop') =", data_scientists_who_like('Hadoop')

#
#   defaultdict is in collections
#
from collections import defaultdict

#   link from interest to users
user_ids_by_interest = defaultdict(list)                        # defaultdict(<type 'list'>, {})

for id,interest in interests:
    user_ids_by_interest[interest].append(id)

print 'user_ids_by_interest =', user_ids_by_interest

# link from user to interests
interests_by_user_id = defaultdict(list)                        # defaultdict(<type 'list'>, {})

for id,interest in interests:
    interests_by_user_id[id].append(interest)

print 'interests_by_user_id =', interests_by_user_id

def most_common_interests_with_az(user_id):
    """my version
    """
    return Counter(id
                   for interest in interests_by_user_id[user_id]
                   for id in user_ids_by_interest[interest]
                   if id != user_id
                  )

print 'most_common_interests_with_az(0) =', most_common_interests_with_az(0)

# this book version does not work
def most_common_interests_with_orig(user_id):
    return Counter(interested_user_id
                   for interest in interests_by_user_id["user_id"]
                   for interested_user_id in user_ids_by_interest[interest]
                   if interested_user_id != user_id)

def most_common_interests_with(user_id):
    return Counter(interested_user_id
                   for interest in interests_by_user_id[user_id]
                   for interested_user_id in user_ids_by_interest[interest]
                   if interested_user_id != user_id)

# NB: the order of the fields in output Counter({1: 2, 5: 1, 8: 1, 9: 3}) may vary from call to call
print 'most_common_interests_with(0)    =', most_common_interests_with(0)

###########################
#                         #
# SALARIES AND EXPERIENCE #
#                         #
###########################

salaries_and_tenures = [(83000, 8.7), (88000, 8.1),
                        (48000, 0.7), (76000, 6),
                        (69000, 6.5), (76000, 7.5),
                        (60000, 2.5), (83000, 10),
                        (48000, 1.9), (63000, 4.2)]

print 'salaries_and_tenures =', salaries_and_tenures

#--AZ plot salaries vs tenures
salaries,tenures = zip(*salaries_and_tenures)
plt.plot(tenures,salaries, 'ro')                # 'ro' = 'red o'

# I can also sort data points wrt tenures, plot will be the same (if don't connect with lines)
salaries,tenures = zip(*sorted(salaries_and_tenures, key=lambda(x,y):y))

plt.clf()                                       # 'cl'ear 'f'igure
plt.plot(tenures,salaries, 'ro')                # 'ro' = 'red o'
plt.axis([0, 1.10*max(tenures), 0.90*min(salaries), 1.10*max(salaries)])
plt.show()

# bucket the tenures

def tenure_bucket(tenure):
    if tenure < 2: return 'less than two'
    if tenure < 5: return 'less than five'
    return 'more than five'

salary_by_tenure_bucket = defaultdict(list)

for salary, tenure in salaries_and_tenures:
    salary_by_tenure_bucket[tenure_bucket(tenure)].append(salary)

# average_salary_by_bucket = {
#     salary_by_tenure_bucket.key: sum(salary_by_tenure_backet[tenure]/len(salary_by_tenure_backet[tenure])
#                                      for tenure in salary_by_tenure_bucket}

average_salary_by_bucket = {
    tenure:sum(salary)/len(salary)
    # for tenure, salary in salary_by_tenure_bucket.iteritems()   # list.iteritems(): returns iterator
    for tenure, salary in salary_by_tenure_bucket.items()         # list.items(): returns list, the result here is the same
}

print 'average_salary_by_bucket =', average_salary_by_bucket
