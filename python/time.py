import datetime
import math


doc = """
To convert srt --> datetime: strptime NB: method name starts from 'strp'
To convert datetime --> str: strftime NB: method name starts from 'strf'
"""
print(doc)

time1_str = "2017-06-13 11:33:01"
time2_str = "2017-06-13 11:33:03"

datetime1 = datetime.datetime.strptime(time1_str, '%Y-%m-%d %H:%M:%S')
datetime2 = datetime.datetime.strptime(time2_str, '%Y-%m-%d %H:%M:%S')

# convert back to check
print("time1_str:                    ", time1_str)
print("convert datetime1 back to str:",
      datetime.datetime.strftime(datetime1, "%Y-%m-%d %H:%M:%S"))

deltat = datetime2 - datetime1
print("deltat as a timedelta object:", deltat)

deltat_seconds = math.ceil(deltat.total_seconds())  # total_seconds() ret float
print("deltat_seconds =", deltat_seconds)
