#!/usr/bin/env python3
import math

def sub(a, b):
    x1, y1 = a
    x2, y2 = b
    return (x1 - x2, y1 - y2)

def cross(a, b):
    x1, y1 = a
    x2, y2 = b
    return x1 * y2 - y1 * x2

def eq(a, b):
    x1, y1 = a
    x2, y2 = b
    return x1 == x2 and y1 == y2

def mul(p, d):
    x, y = p
    return (x * d, y * d)

def div(p, d):
    x, y = p
    return (x / d, y / d)

def dist(a, b):
    x1, y1 = a
    x2, y2 = b
    return math.sqrt((x1 - x2)**2 + (y1 - y2)**2)

def sameline(s1, e1, s2, e2):
    v1 = sub(e1, s1)
    v2 = sub(e2, s2)
    d = sub(s2, s1)
    a = cross(v1, v2)
    a1 = cross(v1, d)
    a2 = cross(v2, d)
    return a == 0 and a1 == 0 and a2 == 0

dots = [(x, y) for x in range(4) for y in range(4)]
lines = [(a, b) for a in dots for b in dots]

distinct_lines = []
for s1, e1 in lines:
    if eq(s1, e1): continue
    distinct = True
    for s2, e2 in distinct_lines:
        if sameline(s1, e1, s2, e2): distinct = False
    if distinct:
        distinct_lines.append((s1, e1))

print(len(distinct_lines), "distinct lines")
print(distinct_lines)

P = []

for s1, e1 in lines:
    for s2, e2 in lines:
        if eq(s1, s2) and eq(e1, e2): continue
        v1 = sub(e1, s1)
        v2 = sub(e2, s2)
        a = cross(v1, v2)
        if a == 0: continue
        d = sub(s2, s1)
        a1 = cross(v1, d)
        a2 = cross(v2, d)
        isct = sub(s1, div(mul(v1, a2), a))
        exists = False
        for p in P:
            if dist(p, isct) < 1e-9: exists = True
        if not exists: P.append(isct)

print(len(P), "intersection points")
print(P)
