#!/usr/bin/env python

raw_input()
sentence = set(raw_input().split())

good = dict()
bad = dict()

for i in range(int(raw_input())):
    a,b,c = raw_input().split()
    if a not in good:
        good[a] = []
        bad[a] = []
    if c == 'correct':
        good[a] += [b]
    bad[a] += [b]

def go(d):
    res = 1
    for i in sentence:
        res *= len(d[i])
    return res

def get(d):
    return map(lambda x: d[x][0], sentence)

gc = go(good)
tc = go(bad)
if tc == 1:
    print ' '.join(get(good if gc == 1 else bad))
    print ('correct' if gc == 1 else 'incorrect')
else:
    print gc, 'correct'
    print tc-gc, 'incorrect'
