#!/usr/bin/env python
from math import sin,cos,pi,hypot

p = map(lambda i: map(float, raw_input().split()), range(int(raw_input())))
res = [0, -1]

def pip(p, v):
    ans = False
    for a,b in zip(v, v[1:] + v[:1]):
        if (a[1] < p[1]) <> (b[1] < p[1]):
            if a[0] + (b[0] - a[0]) * (p[1] - a[1]) / (b[1] - a[1]) < p[0]:
                ans = not ans
    return ans

def fit(v):
    res = []
    for i in p:
        l = hypot(*i)
        r = l * 2
        for it in range(100):
            m = (l+r) / 2.0
            if pip(i, map(lambda q: [q[0]*m,q[1]*m], v)):
                r = m
            else:
                l = m
        res += [r]
    return min(res) / max(res)

for vertices in range(3, 8+1):
    v = []
    for i in range(vertices):
        theta = i * 2*pi / vertices
        v += [[cos(theta), sin(theta)]]
    res = max(res, [fit(v), vertices])

print '%d %.8f' % (res[1], res[0]**2)
