""" The same appearence as in Jupyter Notebook,
except bold font for the header and interleaved backround for rows.
"""

from IPython.display import display
import numpy as np
import pandas as pd

df = pd.DataFrame({ 'A' : 1.,
                   'B' : pd.Timestamp('20130102'),
                   'C' : pd.Series(1, index=list(range(4)), dtype='float32'),
                   'D' : np.array([3] * 4, dtype='int32'),
                   'E' : pd.Categorical(["test", "train", "test", "train"]),
                   'F' : 'foo' })
display(df)
