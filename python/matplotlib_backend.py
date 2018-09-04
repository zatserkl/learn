# from https://matplotlib.org/faq/howto_faq.html

import matplotlib

"""
The statement

matplotlib.use('Agg')

should be used before import maptlotlib.pyplot
otherwise, you will get a warning on it:

UserWarning:
This call to matplotlib.use() has no effect because the backend has already
been chosen; matplotlib.use() must be called *before* pylab, matplotlib.pyplot,
or matplotlib.backends is imported for the first time.
"""
matplotlib.use('Agg')  # PNG backend. Should be before import matplotlib.pyplot


import matplotlib.pyplot as plt


plt.plot([1, 2, 3])
plt.savefig('matplotlib_backend')
