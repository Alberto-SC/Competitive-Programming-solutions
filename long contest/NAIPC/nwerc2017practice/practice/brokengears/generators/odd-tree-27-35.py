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

def gen_graph(n=1000, m=2000, max_val=10**6):
  connected = [set() for i in range(n)]
  radii = [randint(1, max_val/2) for i in range(n)]
  edges = []

  def add_edge(a, b):
    if a not in connected[b]:
      connected[a].add(b)
      connected[b].add(a)
      edges.append((a, b, radii[a] + radii[b]))

  # Create a tree structure.
  for i in range(1, n):
    add_edge(i, randint(0, i-1))

  while len(edges) < m:
    a = randint(0, n-1)
    b = randint(0, n-1)
    if a <> b:
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
  (1000, 10**5, 10**5),
  (50, 100, 1000),
  (100, 100, 1000),
  (127, 400, 1000),
  (990, 1200, 10**6),
  (567, 10000, 1000),
  (54321, 10**5, 10**3),
  (41234, 10**5, 10**3),
]

for cid in range(len(cases)):
  fn = cid + 27
  with open('secret/%02d.in' % fn, 'w') as f, open('secret/%02d.ans' % fn, 'w') as o:
    radii, edges, perm = gen_graph(*cases[cid])
    n,m = cases[cid][:2]

    f.write("%d\n" % n)
    f.write("%s\n" % ' '.join([str(x) for x in radii]))
    f.write("%d\n" % m)
    for abw in edges:
      f.write("%d %d %d\n" % tuple(abw))

    o.write("%s\n" % ' '.join([str(x+1) for x in perm]))
