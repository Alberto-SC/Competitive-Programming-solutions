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
	lb = (0 if l == 0 else c[l-1])
	rb = min(g, c[r])
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
c = [v for v in sorted(map(int, str.split(input())))]
nCk = precompute_nCk(100+1)
num, den = table(100, 100), table(100, 100)

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

dpn, dpd = table(100, 100), table(100, 100)
for i in range(t-1, -1, -1):
	for j in range(n-1, -1, -1):
		if t-i <= n-j:
			dpn[i][j], dpd[i][j] = num[j][j+t-i-1], den[j][j+t-i-1]
		else:
			dpn[i][j], dpd[i][j] = fradd(dpn[i+1][j], dpd[i+1][j], 0, min(g, c[n-1]) - (0 if j == 0 else c[j-1]))

for i in range(t-1, -1, -1):
	for j in range(n-1, -1, -1):
		for ni in range(i+1, t):
			for ns in range(j+(ni-i)+1, n):
				s, w = 0, nCk[t-i][t-ni]
				s, w = fradd(s, w, num[j][j+(ni-i)-1], den[j][j+(ni-i)-1])
				s, w = fradd(s, w, dpn[ni][ns], dpd[ni][ns])
				dpn[i][j] += s
				dpd[i][j] += w

ansn, ansd = 0, max(0, g-c[n-1])**t
for l in range(n):
	ansn += dpn[0][l]
	ansd += dpd[0][l]
	if c[n-1] < g:
		for tt in range(1, t):
			s, w = 0, nCk[t][tt]
			s, w = fradd(s, w, dpn[tt][l], dpd[tt][l])
			s, w = fradd(s, w, 0, (g-c[n-1])**tt)
			ansn += s
			ansd += w
print("{:.12f}".format(ansn / ansd))
