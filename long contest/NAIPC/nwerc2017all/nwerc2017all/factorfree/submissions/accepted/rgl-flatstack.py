#!/usr/bin/env python
import sys

n = int(raw_input())
v = map(int, raw_input().split())
prime_factor = [i for i in range(max(v) + 1)]
for i in range(2, len(prime_factor)):
    if prime_factor[i] == i:
        for j in range(i*i, len(prime_factor), i):
            if prime_factor[j] == j:
                prime_factor[j] = i
def get_factors(x):
  res = set()
  while x > 1:
    res.add(prime_factor[x])
    x /= prime_factor[x]
  return res
v = map(get_factors, v)
a = [0] * n

lef = [0 for i in v]
rgt = [n for i in v]
factor_when = dict()
for i in range(n):
    for j in v[i]:
        if j in factor_when:
            f = factor_when[j]
            lef[i] = max(lef[i], f+1)
            rgt[f] = min(rgt[f], i)
        factor_when[j] = i

factor_when = None

def solve(l, r, p=-1):
    if l+1 == r: a[l] = p+1
    if l+1 >= r: return True

    global stack
    for i in range(r-l):
        for z in set((l+i,r-1-i)):
            if lef[z] <= l and rgt[z] >= r:
                a[z] = p+1
                stack += [[l,z,z]]
                stack += [[z+1,r,z]]
                return True
    return False

stack = [[0,n,-1]]
while len(stack) > 0:
  s = stack.pop()
  if not solve(*s):
    print 'impossible'
    sys.exit(0)

print ' '.join(map(str, a))
