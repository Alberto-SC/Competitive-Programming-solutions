#!/usr/bin/env python

print "\n".join(map(lambda _: bin(int(raw_input()))[2:], range(int(raw_input()))))
