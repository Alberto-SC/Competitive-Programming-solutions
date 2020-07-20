#!/usr/bin/env python

n = int(raw_input())
v = map(int, raw_input().split())

dups = filter(lambda (i,j): i==j, zip(v[:-1], v[1:]))
good1 = set(zip(v[:-1], v[1:])) ; v = sorted(v)
good2 = set(zip(v[:-1], v[1:]))

print (n-1) - len(good1 & good2) - (len(dups) - len(set(dups)))
