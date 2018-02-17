# Andriy Zatserklyaniy <zatserkl@gmal.com> Jul 5, 2017


import json
from pandas import Series, DataFrame
import pandas as pd


"""Loop over batch dataset
"""

fname_batch = "batch_log100.json"
 
with open(fname_batch) as file_batch:
    header = json.loads(file_batch.readline())  # header is of type dict
    json_batch = [json.loads(line) for line in file_batch]

D = int(header['D'])
T = int(header['T'])

print "header['D'] =", D, "head['T'] =", T

df_batch = DataFrame(json_batch)
print "df_batch[:10]\n", df_batch[:10]

print "\nLoop over transactions\n"

for index, row in df_batch.iterrows():
    # print index and type of the event in the beginning of the line
    print index, row['event_type'], '\t',

    # row is either purchase or befriend/unfriend event
    if pd.notnull(row['id1']):
        print row['id1'], row['id2'],
    else:
        print row['id'], row['amount'],

    # finish line with the timestamp
    print '\t', row['timestamp']
