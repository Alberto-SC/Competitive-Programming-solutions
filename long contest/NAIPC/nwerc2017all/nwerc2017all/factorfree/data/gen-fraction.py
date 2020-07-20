#!/usr/bin/python3
import sys
import random

sys.setrecursionlimit(1000100)

A_MAX = 5000000
N_MAX = 1000000

def primes(A=A_MAX):
	sieve = [True] * (A + 1)
	sieve[0] = sieve[1] = False
	for i in range(2, A+1):
		if not sieve[i]:
			continue;
		yield i
		for j in range(i*i, A+1, i):
			sieve[j] = False

def seq(n, f, offset=0):
	if n <= 1:
		return [offset] * n
	l = int((n - 1) * f)
	r = n - 1 - l
	if random.random() < 0.5:
		l, r = r, l
	return seq(l, f, offset+1) + [offset] + seq(r, f, offset+1)

ps = list(primes())

n = int(input())
f = float(input())

a = seq(n, f)
if max(a) >= len(ps):
	a = seq((n - 1) // 2, f, 1) + [0] + seq(n - (n - 1) // 2 - 1, f, 1)

assert 0 <= max(a) < len(ps)

print(len(a))
print(' '.join(map(lambda i: str(ps[i]), a)))
