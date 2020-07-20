#!/usr/bin/env pypy
from random import randint, seed, shuffle
from bisect import bisect_left

seed(314151617181)

def shuffled(arr):
  arr = arr[:]
  shuffle(arr)
  return arr

def shuffish(arr):
  arr = arr[:]
  for i in range(len(arr) / 10):
    a = randint(0, len(arr)-1)
    b = randint(0, len(arr)-1)
    arr[a], arr[b] = arr[b], arr[a]
  return arr

cases = [
  # Basic cases
  [(0, 10**5)],
  [(i,i+1) for i in range(10**5,0,-1)],
  shuffled([(i,i+1) for i in range(10**5,0,-1)]),

  # sqrt(N) based cases
  shuffled([         range(i/3,i/3+505)  for i in range(0, 10**5, 499)]),
  shuffled([shuffled(range(i/3,i/3+504)) for i in range(0, 10**5, 502)]),
           [shuffled(range(i/3,i/3+503)) for i in range(0, 10**5, 503)],
  shuffled([shuffish(range(i/3,i/3+502)) for i in range(0, 10**5, 504)]),
  shuffish([shuffish(range(i/3,i/3+499)) for i in range(0, 10**5, 505)])
]

def make_case_interesting(c):
  c = [range(*i) if isinstance(i, tuple) else i for i in c]

  unique_values = set()
  for i in c:
    for j in i:
      unique_values.add(j)
  unique_values = sorted(unique_values)

  mapped_values = set()
  while len(mapped_values) < len(unique_values):
    mapped_values.add(randint(1, 10**9))
  mapped_values = sorted(mapped_values)

  res = []
  for i in c:
    res += [bisect_left(unique_values, j) for j in i]
  return [mapped_values[i] for i in res]

for tid,tinf in enumerate(cases):
  tn = tid + 15
  with open('secret/%02d.in' % tn, 'w') as fi:
    data = make_case_interesting(tinf)
    fi.write("%d\n" % len(data))
    fi.write("%s\n" % ' '.join(map(str, data)))
