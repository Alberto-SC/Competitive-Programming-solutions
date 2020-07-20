#!/usr/bin/env python
from sys import exit

s = raw_input()

assert 1 <= len(s) <= 10**6
for i in s:
  assert i in '012'

exit(42)
