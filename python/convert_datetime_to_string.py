from datetime import datetime, timedelta
from collections import Counter, deque, defaultdict

dt = datetime(1990, 1, 1, 0, 0, 0)
b = defaultdict(int)
b[dt] = 100
print b
time = b.keys()[0]
print time.strftime("%d/%b/%Y:%H:%M:%S")

print "\nConvert from string to datetime"

time_str = "2017-06-13 11:33:01"
print "Convert", time_str, "to datatime object"

datetime_object = datetime.strptime(time_str, '%Y-%m-%d %H:%M:%S')
time_str_back = datetime_object.strftime("%Y-%m-%d %H:%M:%S")

print "Convert back from datatime to str: time_str_back =", time_str_back

print "time_str == time_str_back:", time_str == time_str_back
