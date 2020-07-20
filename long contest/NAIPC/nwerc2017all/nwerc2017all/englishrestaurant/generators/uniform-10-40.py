#!/usr/bin/env python
from random import randint, seed

seed(471613413)

def gen_case(n, g, t, max_table=None):
  if max_table is None:
    max_table = 100
    return map(lambda _: randint(1, randint(g, max_table)), range(n))
  else:
    if isinstance(max_table, int):
      mtv = max_table
      max_table = lambda _: randint(1, mtv)
    return map(max_table, range(n))

cases = [
  (20, 100, 50),        # 10
  (50, 100, 50),        # 11
  (20, 30, 50),         # 12
  (50, 50, 10),         # 13
  (50, 50, 50),         # 14
  (10, 100, 50),        # 15
  (40, 1, 4),           # 16
  (30, 30, 50),         # 17
  (50, 67, 24),         # 18
  (2, 100, 50),         # 19
  (2, 100, 1),          # 20
  (50, 100, 50, 1),     # 21
  (37, 100, 50, 2),     # 22
  (44, 100, 50, 3),     # 23
  (100, 200, 100, 200), # 24
  (100, 200, 90, 200),  # 25
  (99, 199, 50, 200),   # 26
  (90, 200, 90, 200),   # 27
  (1, 140, 50, 200),    # 28
  (99, 140, 1, 170),    # 29
  (50, 200, 67, 150),   # 30
  (100, 7, 75, 20),     # 31
  (100, 199, 100, 1),   # 32
  (90, 1, 100, lambda i: 2 if i == 57 else 1), # 33
  (90, 2, 100, lambda i: 2 if i <= 57 else 1), # 34
  (98, 70, 100, lambda i: 2 if i <= 10 else 60 if i <= 12 else 1), # 35
  (98, 177, 87, lambda i: randint(5, 10) if i <= 70 else randint(95, 99)) # 36
]

for tid,ch in enumerate(cases):
  tn = 10 + tid
  with open('secret/%02d.in' % tn, 'w') as fi:
    fi.write("%d %d %d\n" % (ch[:3]))
    fi.write("%s\n" % (' '.join(map(str, gen_case(*ch)))))
