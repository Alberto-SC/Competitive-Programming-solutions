#!/usr/bin/python3

"""
	Literal transcription of my C++ solution.
"""

def fradd(a, b, p, q):
	return a*q + b*p, b*q

def table(n, m):
	return [[0] * m for _ in range(n)]

def n2(n):
	return n * (n + 1) // 2

def rfrac(l, r, c, g):
	lb = min(g, 0 if l == 0 else c[l-1])
	rb = min(g, c[r])
	if c[r] > 200:
		return 0, rb - lb
	return n2(rb) - n2(lb), rb - lb

def precompute_nCk(n):
	nCk = table(n, n)
	for i in range(n):
		nCk[0][i] = 0
		nCk[i][0] = 1
	for i in range(1, n):
		for j in range(1, n):
			nCk[i][j] = nCk[i-1][j-1] + nCk[i-1][j]
	return nCk

n, g, t = map(int, str.split(input()))
c = [v for v in sorted(map(lambda s: min(g, int(s)), str.split(input())))]
c = c + [300 for _ in range(t)]
n += t
assert len(c) == n
nCk = precompute_nCk(200+3)
num, den = table(200, 200), table(200, 200)

for r in range(n):
	num[r][r], den[r][r] = rfrac(r, r, c, g)
	for l in range(r-1, -1, -1):
		for k in range(l, r+1):
			s, w = 0, nCk[r-l][k-l]
			a, b = rfrac(l, k, c, g)
			s, w = fradd(s, w, a, b)
			if l < k:
				s, w = fradd(s, w, num[l][k-1], den[l][k-1])
			if k < r:
				s, w = fradd(s, w, num[k+1][r], den[k+1][r])
			num[l][r] += s
			den[l][r] += w



dpn, dpd = table(200, 200), table(200, 200)
for i in range(t-1, -1, -1):
	for j in range(n-1, -1, -1):
		if t-i <= n-j:
			dpn[i][j], dpd[i][j] = num[j][j+t-i-1], den[j][j+t-i-1]

for i in range(t-1, -1, -1):
	for j in range(n-1, -1, -1):
		for ni in range(i+1, t):
			for ns in range(j+(ni-i)+1, n):
				s, w = 0, nCk[t-i][t-ni]
				s, w = fradd(s, w, num[j][j+(ni-i)-1], den[j][j+(ni-i)-1])
				s, w = fradd(s, w, dpn[ni][ns], dpd[ni][ns])
				dpn[i][j] += s
				dpd[i][j] += w

ansn, ansd = 0, 0, #max(0, g-c[n-1])**t
for l in range(n):
	ansn += dpn[0][l]
	ansd += dpd[0][l]
print("{:.12f}".format(ansn / ansd))
