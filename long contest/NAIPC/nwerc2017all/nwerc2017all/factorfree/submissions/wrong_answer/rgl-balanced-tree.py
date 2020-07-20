#!/usr/bin/env python

#
# Bad: outputs a balanced tree regardless of
# what the actual answer is.
#

n = int(raw_input())
v = map(int, raw_input().split())
a = [0] * n

def go(l,r,p=0):
    if l == r: return
    m = (l+r) / 2
    a[m] = p
    go(l,m,m+1)
    go(m+1,r,m+1)

go(0,n)
print ' '.join(map(str, a))
