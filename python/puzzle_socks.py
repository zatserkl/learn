""" https://www.youtube.com/watch?v=GuqcnrtdUCc

Can You Solve The Missing Sock Puzzle?

A statistician keeps a simple wardrobe. He only purchases pairs of black socks 
and white socks, and he keeps all of the socks in a pile in the drawer.
Recently one of the socks was lost in the laundry. 
The socks NOW have a mathematical property. If you select two socks at random from 
the drawer, the socks will match in color exactly 50% of the time. The 
statistician owns more than 200 socks but less than 250 socks, and there are 
more black socks than white socks. How many socks of each color are there? 
And which color sock was lost in the laundry?
"""
from __future__ import division

for N in range(201, 250):
   for n1 in range(0, (N+1+1)//2):  # it's enough to run to the middle
       n2 = N - n1
       p1 = (n1/N)*(n1-1)/(N-1)     # probability to match color of n1
       p2 = (n2/N)*(n2-1)/(N-1)     # probability to match color of n2
       p = p1 + p2                  # sum of mutually excluded probabilities
       if abs(p - 0.5) < 0.0001:
           print n1, n2, p
