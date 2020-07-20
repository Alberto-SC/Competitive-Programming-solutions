#!/usr/bin/env python
from sys import exit

#
# Verify that the graph:
#  - is connected
#

n = int(raw_input()) ; assert 1 <= n <= 10**5
ignore_radii = raw_input()
m = int(raw_input()) ; assert n-1 <= m <= 10**5

edges = [set() for i in range(n)]
seen_edges = set()

for edge_id in range(m):
  a,b,weight = map(int, raw_input().split())
  assert 1 <= a < b <= n
  assert 1 <= weight <= 10**8
  assert (a,b) not in seen_edges
  seen_edges.add((a,b))
  edges[a-1].add(b-1)
  edges[b-1].add(a-1)

colour = [None for i in range(n)]
colour[0] = True
todo = set([0])
while len(todo) > 0:
  x = todo.pop()
  for y in edges[x]:
    if colour[y] is None:
      colour[y] = not colour[x]
      todo.add(y)

for i in colour:
  assert i is not None, 'Graph is not connected'

exit(42)
