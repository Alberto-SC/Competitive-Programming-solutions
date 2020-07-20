def sub(P, Q): return (P[0]-Q[0], P[1]-Q[1])
def dot(P, Q): return P[0]*Q[0] + P[1]*Q[1]
def cross(P, Q): return P[0]*Q[1] - P[1]*Q[0]
def parallel(P, Q):
    return dot(P, Q) >= 0 and cross(P, Q) == 0

def between(P1, Q, P2, P1_closed, P2_closed):
    if parallel(P1, Q): return P1_closed
    if parallel(Q, P2): return P2_closed
    return (cross(P1, Q) > 0) + (cross(Q, P2) > 0) + (cross(P1, P2) < 0) >= 2

seq = [None for _ in range(16)]
grid = [map(int, raw_input().split()) for _ in range(4)]
for i in range(4):
    for j in range(4):
        seq[grid[i][j]-1] = (j, i)
delta = [sub(seq[i+1], seq[i]) for i in range(15)]

ans = 1
lo_dir = hi_dir = delta[0]
lo_closed = hi_closed = True
for at in range(1, 15):
    if between(lo_dir, delta[at], hi_dir, lo_closed, hi_closed):
        lo_dir = hi_dir = delta[at]
        lo_closed = hi_closed = True
    else:
        ans += 1
        new_lo = (-lo_dir[0], -lo_dir[1])
        new_hi = (-hi_dir[0], -hi_dir[1])
        lo_closed = hi_closed = False
        if not between(new_lo, delta[at], new_hi, False, False):
            if between(hi_dir, delta[at], new_lo, True, True):
                new_lo = delta[at]
                lo_closed = True
            else:
                new_hi = delta[at]
                hi_closed = True
        (lo_dir, hi_dir) = (new_lo, new_hi)

print ans
