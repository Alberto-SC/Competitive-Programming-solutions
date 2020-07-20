#!/usr/bin/env python

for tc in range(int(raw_input())):
    v = map(int, raw_input().split())
    v[:3] = sorted(v[:3])

    res = 0
    for a in range(11):
        for b in range(11):
            for c in range(11):
                if a + b + c <= v[3]:
                    w = sorted([v[0]+a, v[1]+b, v[2]+c])
                    w[2] += v[3] - a - b - c
                    res = max(res, w[0]**2+w[1]**2+w[2]**2+7*w[0])
    print res
