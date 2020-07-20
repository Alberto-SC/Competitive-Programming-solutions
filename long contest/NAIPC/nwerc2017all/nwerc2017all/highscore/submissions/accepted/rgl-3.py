#!/usr/bin/env python

#
# s'(a+1,b,c) = s + 2a+1 + 7
# s'(a,b,c+1) = s + 2c+1
# s'' = 2(c-a) - 7
#         c-a <= 3
#

for tc in range(int(raw_input())):
    v = map(int, raw_input().split())
    v[:3] = sorted(v[:3])

    res = 0
    for i in range(min(3,v[3])+1):
        w = [v[0]+i, max(v[0]+i,v[1]), max(v[0]+i,v[2])]
        w[2] += sum(v) - sum(w)
        if w[2] >= max(w[1], v[2]):
            res = max(res, w[0]**2+w[1]**2+w[2]**2+7*w[0])
    print res
