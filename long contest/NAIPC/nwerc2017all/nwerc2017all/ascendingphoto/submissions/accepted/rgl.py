#!/usr/bin/env python
from bisect import bisect_left

n = int(raw_input())
v = map(int, raw_input().split())
v = map(lambda j: v[j], filter(lambda i: i==0 or v[i] <> v[i-1], range(n)))

v_values = sorted(set(v))
v = map(lambda i: bisect_left(v_values, i), v)

places = [set() for i in v_values]
for i in range(len(v)):
  places[v[i]].add(i)

dp = [2**29 for i in v]
for i in places[-1]:
  dp[i] = len(places[-1]) - 1

for cr,nx in zip(places[-2::-1], places[-1:0:-1]):
  if len(cr) == 1:
    z = cr.copy().pop()
    dp[z] = min(map(lambda i: dp[i] + int(i<>z+1), nx))
  else:
    best = sorted([[dp[k] + int(k-1 not in cr) + (len(cr)-1), k] for k in nx])[:2]
    for i in cr:
      dp[i] = 2**29
      for k in best:
        if k[1] <> i+1:
          dp[i] = min(dp[i], k[0])
      if i+1 in nx:
        dp[i] = min(dp[i], dp[i+1] + len(cr))

print min([dp[i] for i in places[0]])
