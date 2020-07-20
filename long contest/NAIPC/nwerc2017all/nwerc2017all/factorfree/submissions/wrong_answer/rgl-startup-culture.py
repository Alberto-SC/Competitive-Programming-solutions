#!/usr/bin/env python

#
# Bad: outputs a flat tree with one root
# and N-1 children direct children.
#

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

solved = False
for i in range(n):
    if lef[i] <= 0 and rgt[i] >= n:
        for j in range(n):
            a[j] = i+1
        solved = True
        a[i] = 0
        break

if solved:
    print ' '.join(map(str, a))
else:
    print 'impossible'
