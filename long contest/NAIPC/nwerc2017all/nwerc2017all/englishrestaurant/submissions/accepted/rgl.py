#!/usr/bin/env python
from functools import wraps

def memoize(function):
    memo = {}
    @wraps(function)
    def cache(*args):
        if args in memo: return memo[args]
        rv = function(*args)
        memo[args] = rv
        return rv
    return cache

@memoize
def choose(a,b):
    assert a>=0 and b>=0
    if b == 0 or a == b: return 1
    if a < b: return 0
    return choose(a-1,b) + choose(a-1,b-1)

def mul_res(a,b,u,v):
    c = choose(u+v,u)
    return [a[0]*b[0]*c,(a[1]*b[0]+b[1]*a[0])*c]

def cmb_res(res, b):
    res[1] = res[1]*b[0] + b[1]*res[0]
    res[0] *= b[0]

def up_res(res, ways, tot):
    res[0] += ways
    res[1] += tot

@memoize
def get_ways(l,r):
    have = r-l
    if l == r: return [1,0]
    if l > 0 and table[l-1] == table[l]: return [0,0]

    lo = (1 if l == 0 else table[l-1]+1)

    res = [0, 0]
    for i in range(l, r):
        if i+1<r and (i+1>=t or table[i] == table[i+1]):
            continue

        u = i-l
        v = r-(i+1)
        a = get_ways(l, i)
        b = get_ways(i+1, r)
        if i < t:
            ways = (table[i]-lo)+1
            mean = (table[i]+lo)/2.0
            c = [ways, ways*mean]
        else:
            c = [table[-1]-lo+1, 0]
        c_orig = c[:]
        cmb_res(c, mul_res(a,b,u,v))
        up_res(res, *c)
    return res

@memoize
def solve_problem(s,people_left):
    if s>=t:
        unused_vals = n - table[-1]
        r = [unused_vals**people_left, 0]
        return r
    else:
        res = solve_problem(s+1,people_left)
        if s == 0 or table[s] > table[s-1]:
            for j in range(1,people_left+1):
                during = get_ways(s,s+j)
                after  = solve_problem(s+j+1, people_left-j)
                rec = mul_res(during, after, j,people_left-j)
                up_res(res, *rec)
        return res

t,n,h = map(int, raw_input().split())
table = sorted(list(map(lambda i: min(n, int(i)), raw_input().split()))[:t])

ans = solve_problem(0,h)
if False: print(ans)
assert ans[0] == n**h
print('%.12f' % (ans[1] / ans[0]))
