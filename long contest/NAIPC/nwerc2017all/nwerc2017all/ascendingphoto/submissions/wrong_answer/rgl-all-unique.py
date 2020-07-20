#!/usr/bin/env python
import bisect

raw_input()
v = map(int, raw_input().split())
s = sorted(v)

res = 0
for i in range(len(v) - 1):
    res += int(bisect.bisect_right(s,v[i]) <> bisect.bisect_left(s,v[i+1]))

print res
