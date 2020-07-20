#!/usr/bin/env python3
from sys import stdin
import re
import sys

MIN_N = 1
MAX_N = 100

integer = "(0|-?[1-9]\d*)"
line = stdin.readline()
oneint = re.compile(integer + "\n")

assert oneint.match(line)

n = int(line)

assert MIN_N <= n and n <= MAX_N

sys.exit(42)
