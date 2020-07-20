import sys

r = map(int, sys.stdin.read().split()[1:])
n = len(r)
r = list(reversed(sorted(r[1:]))) + [r[0]]

k = 1
while k < n:
    k *= 2

p = [[] for _ in range(2*n)]

for i in range(n):
    if k + i < 2*n:
        p[k+i].append((i, 1.0))
    else:
        p[k-n+i].append((i, 1.0))

for u in range(n-1, 0, -1):
    o = p[u]
    for (w, l) in [(2*u, 2*u+1), (2*u+1, 2*u)]:
        for (i, qi) in p[w]:
            tot = 0
            for (j, qj) in p[l]:
                tot += qj*r[i]/(r[i]+r[j])
            o.append((i, qi*tot))

for (i, qi) in p[1]:
    if i == n-1:
        print '%.12lf' % qi
