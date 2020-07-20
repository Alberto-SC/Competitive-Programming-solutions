#!/usr/bin/env python

#
# Issue: makes 2-3 choices every iteration about what move to make next. Over
# time these snowball into a huge number, even though most of the arcs in the
# list turn out to be the same.
#

n = 4
bounds = 1000000.0
eps = 1e-11

v = [[0,0] for i in range(n*n)]
for i in range(n):
    for j,x in zip(range(n), map(int, raw_input().split())):
        v[x-1] = (j, 3-i)

def v_sub(a, b): return (a[0]-b[0], a[1]-b[1])
def v_add(a, b): return (a[0]+b[0], a[1]+b[1])
def v_mul(a, b): return (a[0]*b, a[1]*b)
def v_len(a): return (a[0]**2+a[1]**2)**0.5

def in_arc(r, a, b):
    bi = v_add(v_mul(a,v_len(b)), v_mul(b,v_len(a)))
    if abs(r[0]) + abs(r[1]) < eps: return True
    if bi[0]*r[0] + bi[1]*r[1] < 0: return False
    ca = a[1]*r[0] - a[0]*r[1]
    cb = b[1]*r[0] - b[0]*r[1]
    if abs(ca) < eps or abs(cb) < eps: return True
    return ca * cb < 0

def extrude(p, dirn, bound):
    scale = 1e30
    for dim in [0,1]:
        if abs(dirn[dim]) > eps:
            scale = min(scale, ((bound if dirn[dim] > 0 else -bound) - p[dim]) / dirn[dim])
    return v_add(p, v_mul(dirn, scale))

answers = [[2**30, []] for i in range(n*n)]
answers[1] = [1, [[extrude(v[0], v_sub(v[1], v[0]), bounds) for _ in range(2)]]]

def update_answer(a, cost, b):
    if a[0] < cost: return
    if a[0] > cost:
        a[0] = cost
        a[1] = []
    a[1] += [b]

for i in range(2,n*n):
    for a,b in answers[i-1][1]:
        covered = in_arc(v_sub(v[i], v[i-1]), v_sub(a, v[i-1]), v_sub(b, v[i-1]))

        x = extrude(v[i], v_sub(v[i], a), bounds)
        y = extrude(v[i], v_sub(v[i], v[i-1]), bounds)
        z = extrude(v[i], v_sub(v[i], b), bounds)

        if covered:
            update_answer(answers[i], answers[i-1][0] + 0, (y, y))
        if True:
            update_answer(answers[i], answers[i-1][0] + 1, (y, x))
            update_answer(answers[i], answers[i-1][0] + 1, (y, z))

print answers[-1][0]
