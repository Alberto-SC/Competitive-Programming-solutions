#!/usr/bin/env python

def trin(x):
    return '0' if x == 0 else str(x) if x < 3 else trin(x/3) + str(x%3)

print "\n".join(map(lambda _: trin(int(raw_input())), range(int(raw_input()))))
