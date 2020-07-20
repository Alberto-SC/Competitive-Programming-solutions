#!/usr/bin/env python
from random import randint, seed

seed(654123)

def trin(x):
    return '0' if x == 0 else str(x) if x < 3 else trin(x/3) + str(x%3)

for fn in range(5, 9):
  with open('secret/%02d.in' % fn, 'w') as f, open('secret/%02d.ans' % fn, 'w') as o:
    n = randint(1, 10**6)
    f.write("%d\n" % n)
    for i in range(n):
      v = randint(0, 3**20-1)
      f.write("%d\n" % v)
      o.write("%s\n" % trin(v))
