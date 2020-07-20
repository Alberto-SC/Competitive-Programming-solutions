#!/usr/bin/env python3

n = int(input())

dn = 0
up = 4 * 10**9 + 1

def get(x):
    return (x/4.0)**2

for it in range(1000):
    a = (dn*2+up)/3.0
    b = (dn+up*2)/3.0
    if abs(get(a)-n) < abs(get(b)-n):
        up = b
    else:
        dn = a

print('%.8f' % up)
