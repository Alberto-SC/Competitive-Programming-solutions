#!/usr/bin/env python

prime_factor = [set() for i in range(200001)]
for i in range(2, len(prime_factor)):
    if len(prime_factor[i]) == 0:
        prime_factor[i].add(i)
        for j in range(i*2, len(prime_factor), i):
            prime_factor[j].add(i)

n = int(raw_input())
v = map(lambda i: prime_factor[i], map(int, raw_input().split()))
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

def solve(l, r, p):
    if l+1 == r: a[l] = p+1
    if l+1 >= r: return True

    for i in range(r-l):
        for z in set((l+i,r-1-i)):
            if lef[z] <= l and rgt[z] >= r:
                a[z] = p+1
                return solve(l,z,z) and solve(z+1,r,z)
    return False

if solve(0,n,n):
    print ' '.join(map(str, a))
else:
    print 'impossible'
