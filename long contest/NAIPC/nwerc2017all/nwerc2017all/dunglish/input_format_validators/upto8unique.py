#!/usr/bin/env python
import collections, sys

n = int(raw_input())     ; assert 1 <= n <= 20
s = raw_input().split()  ; assert len(s) == n

m = int(raw_input())     ; assert 1 <= m <= 10**5

translations = collections.defaultdict(set)
for i in range(m):
    a,b,c = raw_input().split()
    assert len(a) <= 20, 'source word length is %d' % (len(a))
    assert len(b) <= 20, 'target word length is %d' % (len(b))
    assert c in ('correct', 'incorrect'), '%s is neither correct nor incorrect' % (c)
    assert b not in translations[a], '%s already has %s as a translation' % (a, b)
    assert len(translations[a]) < 8, '%s already has %d translations' % (a, len(translations[a]))
    translations[a].add(b)

for i in set(s):
    assert i in translations, '%s has no translations' % (i)

sys.exit(42)
