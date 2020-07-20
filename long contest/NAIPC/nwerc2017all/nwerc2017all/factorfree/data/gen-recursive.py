#!/usr/bin/env python3
from random import randint,choice,shuffle
import sys

MAX_VAL = 10**7
N_MAX = 5*10**5
sys.setrecursionlimit(N_MAX * 2)

n = 10**6

primes = []
prime_factor = [None for i in range(MAX_VAL + 1)]
for i in range(2, len(prime_factor)):
    if prime_factor[i] is None:
        primes += [i]
        for j in range(i*i, len(prime_factor), i):
            prime_factor[j] = i

def go(l, r, v, d):
  if l >= r: return

  if r - l <= 20:
    assert(r - l > 2)

    if (r - l) % 2 == 1:
      centre = (l+r) // 2
      v[centre] = primes[d]
      v[l:centre] = primes[d+1:d+1+centre-l]
      v[centre+1:r] = primes[d+1:d+1+centre-l]
      return
    else:
      centre = l
  else:
    if d == 99999:
      border = (r-l-1) // 2
    else:
      border = min(randint(10, 21), r-l-10)
    centre = l + border if randint(1,2) == 1 else r - 1 - border

  assert(l <= centre < r)

  v[centre] = primes[d]
  todo.append((l, centre+0, v, d+1))
  todo.append((centre+1, r, v, d+1))

shuffle(primes)
v = [1 for i in range(n)]
todo = [(0, len(v), v, 0)]
while len(todo) > 0:
    go(*todo.pop())

print(n)
print(' '.join(map(str, v)))
