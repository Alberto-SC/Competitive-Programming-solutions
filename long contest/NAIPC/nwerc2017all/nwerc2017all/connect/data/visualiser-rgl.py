#!/usr/bin/env python
from math import hypot
import matplotlib.pyplot as plt
import matplotlib.patheffects as path_effects
import sys

if len(sys.argv) < 2 or len(sys.argv) > 3:
  print >> sys.stderr, 'Usage:', sys.argv[0], 'data.in [picture.png] [< data.ans]'
  sys.exit(1)

file_in = open(sys.argv[1])
file_out = sys.argv[2] if len(sys.argv) > 2 else None

v = [None for i in range(16)]
for y in range(4):
    p = map(int, file_in.readline().split())
    for x in range(4):
        v[p[x]-1] = (float(x), float(y))

nums = plt.figure().add_subplot(111)
for i in range(16):
    nums.text(v[i][0], 3 - v[i][1], '%d' % (i + 1))

ren = int(raw_input())
res = map(lambda s: map(float, raw_input().split()), range(ren+1))
print 'answer =',len(res)-1

x = []
y = []
for i in res:
    x += [i[0]]
    y += [i[1]]
plt.plot(x, y, '-o', path_effects = [path_effects.SimpleLineShadow(), path_effects.Normal()])

if file_out:
  plt.savefig(file_out)
else:
  plt.show()
