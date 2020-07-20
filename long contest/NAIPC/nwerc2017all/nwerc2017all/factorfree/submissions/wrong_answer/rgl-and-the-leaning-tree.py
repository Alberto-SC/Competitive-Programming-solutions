#!/usr/bin/env python

#
# Bad: outputs a heap structure regardless of
# what the actual answer is.
#

n = int(raw_input())
v = map(int, raw_input().split())
a = [0] * n

print ' '.join(map(str, map(lambda x: x/2, range(1,n+1))))
