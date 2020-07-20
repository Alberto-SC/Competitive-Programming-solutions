#!/usr/bin/env python3
from sys import stdin
import re
import sys

MAX_N = 500
MAX_C = 10000

integer = "(0|-?[1-9]\d*)"
oneint = re.compile(integer + "\n")
twoint = re.compile(integer + " " + integer + "\n")

line = stdin.readline()
assert twoint.match(line)
n, c = list(map(int, line.split()))
assert 1 <= n <= MAX_N and 1 <= c <= MAX_C

for i in range(n):
    line = stdin.readline()
    assert twoint.match(line)
    a, b = list(map(int, line.split()))
    assert 1 <= a <= MAX_C and 1 <= b <= MAX_C

assert len(stdin.readline()) == 0
sys.exit(42)
