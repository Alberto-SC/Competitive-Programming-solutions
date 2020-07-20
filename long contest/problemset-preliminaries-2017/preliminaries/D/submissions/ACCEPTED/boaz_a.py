"""
Problem solver for problem Bacteria.
Expected output: ACCEPTED
"""

import sys
from collections import deque
instr = sys.stdin

MIN_N = 1
MAX_N = 10**5
MIN_B = 0
MAX_B = 2**60 # Python 'natively' supports very large numbers
MOD_VAL = 10**9 + 7
ERROR_MSG = 'error'

def magic(verbose = False, no_modulo = False):
    if verbose: i = 0
    bc = 1
    do_modulo = False
    for b_string in bs:
        b = int(b_string)
        assert(b >= MIN_B and b <= MAX_B) # Input checking
        bc = bc * 2 # Double the bacteria
        if (not do_modulo and b > bc): # There are not enough bacteria for this experiment
            print(ERROR_MSG)
            return # We are done
        if verbose: 
            i = i + 1
            print("{}: {} - {} = {}".format(i, bc, b, bc - b))
    
        bc = bc - b # Substract bacteria due to experiment
        if bc >= MAX_B:
            # If the number of bacteria >= the number that is needed per experiment, we know for sure that there will always be enough bacteria, as the number of bacteria will double each unit of time.
            # So we can start using modulo to make sure that the number of bacteria fits
            if not no_modulo: do_modulo = True
        if do_modulo: bc = (bc % MOD_VAL + MOD_VAL) % MOD_VAL # Make sure to keep in mind that it can occur that b >= MOD_VAL

    # Print the remaining number of bacteria after the experiments
    if not no_modulo: print("{}".format(bc % MOD_VAL))
    else: print("{}".format(bc))

def read_input():
    input = instr.readline()
    if not input: return None
    inputs = input.split(' ')
    assert(len(inputs) == 1) # Input checking
    global n
    n = int(inputs[0])
    assert(n >= MIN_N and n <= MAX_N) # Input checking
    input = instr.readline()
    global bs
    bs = input.split(' ')
    if len(bs) != n: print(str(len(bs)) + " / " + str(n))
    assert(len(bs) == n) # Input checking

def solve():
    read_input()
    magic()

def main():
    solve()

if __name__ == "__main__":
    main()

#1152921504606846976
#18446744073709551615