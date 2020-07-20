#!/usr/bin/env python

v = map(lambda i: ord(i) - ord('0'), raw_input())
n = len(v)

zero_before =[-1]
zero_after = [n] + filter(lambda x: v[x] == 0, range(n-1,-1,-1))

i = 0
for i in range(n):
  while v[i] >= 2:
    pl = 0
    for j in [zero_before, zero_after]:
      assert(j[-1] == -1 or j[-1] == n or v[j[-1]] == 0)
      pl += j[-1] - i
      if len(j) > 1:
        v[j[-1]] += 1
        j.pop()
    for j in reversed(sorted([i,i+pl])):
      if 0 <= j < n:
        v[j] -= 1
        if v[j] == 0:
          zero_after += [j]
  while zero_after[-1] <= i:
    zero_before += [zero_after[-1]]
    zero_after.pop()

print ''.join(map(str, v))
