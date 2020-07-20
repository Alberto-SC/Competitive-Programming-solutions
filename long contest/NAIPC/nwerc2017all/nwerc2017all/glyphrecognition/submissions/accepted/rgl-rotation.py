#!/usr/bin/env python
from math import atan2, cos, hypot, pi, sin

p = [map(float, raw_input().split()) for i in range(int(raw_input()))]

def get_cost(sides):
  def get_size(i):
    v = [(cos(a), sin(a)) for a in [t*pi*2/sides-atan2(i[1], i[0]) for t in range(sides)]]
    return hypot(*i) /\
        max([0.0 if (a[1]<0)==(b[1]<0) else a[0]+(b[0]-a[0])*(a[1]/(a[1]-b[1])) \
            for a,b in zip(v, v[1:]+v[:1])])
  return (min(map(get_size, p)) / max(map(get_size, p)))**2

print '{1:d} {0:.8f}'.format(*max([(get_cost(i), i) for i in range(3,9)]))
