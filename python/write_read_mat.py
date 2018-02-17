
import scipy.io

# saving
A = [10, 20, 30, 40]
data={'A':A}                                    # dict;name-->object
print "data['A']:\n", data['A']

scipy.io.savemat(__file__ + ".mat", mdict=data)

# loading
data = scipy.io.loadmat(__file__ + ".mat")      # --> dict
A = data['A']                                   # get matrix 'A' from the dict
print "A:\n", A
