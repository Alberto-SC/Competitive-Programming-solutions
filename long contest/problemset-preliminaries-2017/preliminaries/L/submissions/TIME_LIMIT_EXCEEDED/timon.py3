from itertools import groupby, product
from functools import reduce
from operator import mul, mod

def egcd(a, b):
	if a == 0: return (b, 0, 1)
	g, y, x = egcd(b % a, a)
	return (g, x - (b // a) * y, y)

def crt(xs, ms):
	pos, prod = 0, reduce(mul, ms)
	for x, m in zip(xs, ms):
		p = prod // m
		pos += (x % m) * (egcd(p, m)[1] % m) * p
	return pos % prod, prod

def solve(xs, ms):
	pos, prod = crt(xs, ms)
	for x in xs:
		pos += prod * max(0, (x - pos + prod - 1) // prod)
	return pos

# Read input.
n = int(input())
xds = [tuple(map(int, input().split())) for _ in range(n)]
xds = sorted(xds, key=lambda xd: xd[1])

# Group by prime and residue class.
byprime = lambda ls: groupby(ls, lambda xd: xd[1])
byclass = lambda ls: groupby(ls, lambda xd: xd[0] % xd[1])
gather = lambda ls: reduce(lambda c, v: (max(c[0], v[0]),c[1]+1), ls, (0, 0))
vs = [[(p,)+gather(vs2) for _, vs2 in byclass(vs1)] for p, vs1 in byprime(xds)]

# Solve over all possible groups.
best = (0, 0)
for prod in product(*vs):
	primes, positions, counts = zip(*prod)
	best = min(best, (-sum(counts), solve(positions, primes)))

print(str.format("{} {}", best[1], -best[0]))
