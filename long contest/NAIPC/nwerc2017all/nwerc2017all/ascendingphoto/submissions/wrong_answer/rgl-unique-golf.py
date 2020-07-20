#!/usr/bin/env python
from bisect import bisect_left, bisect_right

n,v = raw_input(), map(int, raw_input().split())
s = sorted(v)

print sum([int(a<>b and bisect_right(s,a) <> bisect_left(s,b)) for a,b in zip(v[:-1],v[1:])])
