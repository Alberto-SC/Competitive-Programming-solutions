#!/usr/bin/python3
import sys
import random

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

def seq(n, offset=0):
	assert n % 2 == 1 and n > 2
	k = (n + 2) // 2
	l1, l2 = list(range(offset, k+offset)), list(range(1+offset, k+offset))
	for i in range(0, len(l1), 2):
		if i + 1 < len(l1):
			l1[i], l1[i + 1] = l1[i + 1], l1[i]
	for i in range(0, len(l2), 2):
		if i + 1 < len(l2):
			l2[i], l2[i + 1] = l2[i + 1], l2[i]
	return l1 + list(reversed(l2))

ps = list(primes())

n = int(input())
a = seq(n)
assert max(a) < len(ps)

# a = seq(697001, 1) + [0] + seq(1000000 - 697001 - 2, 1)

# a = seq(697001)
# v = a[150000]
# a = a[:150000] + seq(1000000 - 697001, v) + a[150001:]

sys.stderr.write(str.format("[{} {}] \subseteq [0, {})\n", min(a), max(a), len(ps)))

print(len(a))
print(' '.join(map(lambda i: str(ps[i]), a)))
