#!/usr/bin/env python

def flatzip(a,b):
    for i,j in zip(a,b):
        yield i ; yield j

def next_power_of_two(n):
    n = n-1
    for i in [1,2,4,8,16]:
        n |= n >> i
    return n+1

n = int(raw_input())
nn = next_power_of_two(n)
slack = nn - n

# v = map(float, raw_input())
v = map(lambda x: float(raw_input()), range(n))

v = sorted(v[1:])[::-1] + v[:1]
v = v[:n-slack] + [i for i in flatzip([0]*slack, v[n-slack:])]

p = [1.0 for i in range(nn)]
rnd = 1
while 2**rnd <= nn:
    r = [0.0 for i in range(nn)]
    s = 2**(rnd-1)
    for i in range(0,nn,2*s):
        for j in range(0,s):
            for k in range(0,s):
                if v[i+j] + v[i+k+s] > 0:
                    happen = p[i+j] * p[i+k+s]
                    win = v[i+j] / (v[i+j] + v[i+k+s])
                    r[i+j] += happen * win
                    r[i+k+s] += happen * (1-win)
    rnd+=1
    p = r
print p[-1]
