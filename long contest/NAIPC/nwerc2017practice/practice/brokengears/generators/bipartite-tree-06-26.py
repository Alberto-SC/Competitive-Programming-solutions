#!/usr/bin/env python
from random import randint, seed, shuffle
seed(4354326)

#
# The important thing for generating really hard cases
# is to make sure that vertices with even distance from
# root (including itself) constitute exactly half of the
# graph.
#
# This stops simple algebraic approaches from working and
# forces the team to choose a good landmark vertex to go
# from instead.
#

def gen_graph(n=1000, m=2000, max_val=10**6, colourfn=None):
  connected = [set() for i in range(n)]
  colours = [None for i in range(n)]
  radii = [randint(1, max_val/2) for i in range(n)]
  edges = []

  def get_colour(a, b=None):
    if colours[a] is None:
      if colourfn is not None:
        colours[a] = colourfn(a)
        assert colours[a] <> colourfn(b)
      else:
        assert b is not None and colours[b] is not None
        colours[a] = not colours[b]
    return colours[a]

  def compatible(a, b):
    if colourfn is not None:
      return colourfn(a) <> colourfn(b)
    if colours[a] is not None and colours[b] is not None:
      return colours[a] <> colours[b]
    return True

  def add_edge(a, b):
    assert get_colour(a, b) <> get_colour(b, a)
    if a not in connected[b]:
      connected[a].add(b)
      connected[b].add(a)
      edges.append((a, b, radii[a] + radii[b]))

  # Create a tree structure.
  if colourfn is None:
    colours[0] = True
  for i in range(1, n):
    while colours[i] is None:
      j = randint(0, i-1)
      if compatible(i, j):
        add_edge(i, j)
        break

  while len(edges) < m:
    a = randint(0, n-1)
    b = randint(0, n-1)
    if a <> b and compatible(a, b):
      add_edge(a, b)

  perm = list(range(n)) ; shuffle(perm)
  iperm = [None for i in range(n)]
  for i in range(n):
    iperm[perm[i]] = i

  germ = list(range(n))# ; shuffle(germ)
  igerm = [None for i in range(n)]
  for i in range(n):
    igerm[germ[i]] = i

  edges = [sorted([perm[a]+1, perm[b]+1]) + [w] for a,b,w in edges]
  radii = [radii[i] for i in germ]
  return (radii, edges, [igerm[i] for i in iperm])

cases = [
  (5, 6, 10),
  (1000, 10**5, 10**5, lambda i: i%2 == 1),
  (50, 100, 1000),
  (100, 100, 1000),
  (100, 400, 1000),
  (100, 900, 10**6),
  (500, 10000, 1000),
  (1000, 10**5, 10**3),
  (10000, 10**5, 10**3),
  (20000, 10**5, 500, lambda i: i%2 == 1),
  (20000, 10**5, 500, lambda i: i%2 == 0),
  (50000, 10**5, 5000, lambda i: i%2 == 0),
  (50000, 10**5, 5000, lambda i: (i%6) in [1,4,5]),
  (100, 110, 100000, lambda i: (i % 2) == 1),
  (100, 110, 100000, lambda i: (i % 2) == 1),
  (100, 110, 100000, lambda i: (i % 2) == 1),
  (498, 504, 100000, lambda i: (i % 2) == 1),
  (577, 590, 100000, lambda i: (i % 2) == 1),
  (613, 800, 100000, lambda i: (i % 2) == 1),
  (39999, 40007, 100000, lambda i: (i % 2) == 1),
  (49997, 51234, 100000, lambda i: (i % 2) == 1)
]

for cid in range(len(cases)):
  fn = cid + 6
  with open('secret/%02d.in' % fn, 'w') as f, open('secret/%02d.ans' % fn, 'w') as o:
    radii, edges, perm = gen_graph(*cases[cid])
    n,m = cases[cid][:2]

    f.write("%d\n" % n)
    f.write("%s\n" % ' '.join([str(x) for x in radii]))
    f.write("%d\n" % m)
    for abw in edges:
      f.write("%d %d %d\n" % tuple(abw))

    o.write("%s\n" % ' '.join([str(x+1) for x in perm]))
