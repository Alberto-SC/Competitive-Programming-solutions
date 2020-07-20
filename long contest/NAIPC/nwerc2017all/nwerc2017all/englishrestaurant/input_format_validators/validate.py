#!/usr/bin/env python3
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"
threeint = re.compile(integer + " " + integer + " " + integer + "\n")
manyint = re.compile("(" + integer + " )*" + integer + "\n")

line = stdin.readline()
assert threeint.match(line)
n, g, t = map(int, line.split())
assert 1 <= n <= 100
assert 1 <= g <= 200
assert 1 <= t <= 100

line = stdin.readline()
assert manyint.match(line)
c = list(map(int, line.split()))
assert len(c) == n
for x in c:
    assert 1 <= x <= 200

assert len(stdin.readline()) == 0
sys.exit(42)
