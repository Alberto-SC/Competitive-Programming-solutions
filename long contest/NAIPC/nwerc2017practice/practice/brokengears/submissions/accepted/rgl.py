#!/usr/bin/env python

def eval_formula(x,m,c): return m*x+c
def lave_formula(y,m,c): return (y-c)/m

# Read the gears.
n = int(raw_input())
gears = map(int, raw_input().split())

def get_gear_map(gears):
  res = dict()
  for i,v in enumerate(gears):
    if v not in res:
      res[v] = set()
    res[v].add(i+1)
  return res

# Read the edges.
edges = [dict() for i in range(n)]
m = int(raw_input())
for i in range(m):
  a,b,w = map(int, raw_input().split())
  edges[a-1][b-1] = w
  edges[b-1][a-1] = w

# Create the formulae.
formulae = [set() for i in range(n)]
formulae[0].add((1,0))
todo = [0]
while len(todo) > 0:
  x = todo.pop()
  for y,w in edges[x].items():
    if len(formulae[y]) == 0:
      todo.append(y)
    for f in formulae[x]:
      formulae[y].add((-f[0], w-f[1]))

# Get the possible values:
found = False
for sgn in [-1,1]:
  f = filter(lambda i: i[0] == sgn, [a for b in formulae for a in b])
  if len(f) > 0:
    gear0 = lave_formula(max(gears), *max(f))
    avail = get_gear_map(gears)

    answers = []
    found = True
    for i,form in enumerate(formulae):
      gear = None
      for j in form:
        if gear is None:
          gear = eval_formula(gear0, *j)
        elif gear <> eval_formula(gear0, *j):
          gear = -1
      if gear not in avail or len(avail[gear]) == 0:
        found = False
        break
      answers += [avail[gear].pop()]

    if found:
      print ' '.join(map(str, answers))
      break

if not found:
  print 'impossible'
