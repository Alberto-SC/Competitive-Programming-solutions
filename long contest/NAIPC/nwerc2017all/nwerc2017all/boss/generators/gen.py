#!/usr/bin/env python
import random
import os

random.seed(20172018)

def write(tc, n):
  tcprefix = './secret/%02d' % tc

  if not os.path.exists('./secret/'):
    os.makedirs('./secret/')

  f = open(tcprefix + '.in', 'w')
  f.write(str(n) + '\n')
  f.close()
  f = open(tcprefix + '.ans', 'w')
  f.write(str(max(1, n - 2)) + '\n')
  f.close()

def gen_old():
  for i in range(1, 21):
    if i == 4 or i == 7: continue
    write(i)
  write(100000000)
  write(100000000 - 1)
  a = 10
  for i in range(1, 7):
    for j in range(5):
      n = random.randint(a, 10 * a)
      write(n)
      write(a)
      write(a - 1)
    a *= 10

if __name__ == "__main__":
  values = set(range(1, 11) + [random.randint(11, 100) for i in range(20)] + [100])
  values.remove(4)
  values.remove(7)
  tc = 1
  for i in sorted(values):
    write(tc, i)
    tc += 1
