import sys
import random

MAX_DIGS = 18

case_no = 1

def next_file():
    global case_no
    f = open('%02d.in' % case_no, 'w')
    case_no += 1
    return f

def write_case(A):
    f = next_file()
    f.write('%d\n' % A)
    f.close()

random.seed(42)

for i in range(0, MAX_DIGS+1):
    write_case(10**i)
    if i > 0:
        for j in range(0, 1+i/10):
            write_case(random.randint(1, 10**i))

write_case((10**9-1)**2)
