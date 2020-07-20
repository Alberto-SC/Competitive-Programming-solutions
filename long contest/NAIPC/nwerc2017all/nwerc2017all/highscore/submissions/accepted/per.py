
def solve(a, b, c, d):
    if a < b: (a, b) = (b, a)
    if a < c: (a, c) = (c, a)
    if b < c: (b, c) = (c, b)
    ans = a*a + b*b + c*c
    for i in range(c, c+min(d+1, 4)):
        x = max(0, i-a)+max(0, i-b)+max(0, i-c)
        if x > d: break
        ans = max(ans, 7*i + (max(a, i)+d-x)**2 + max(b, i)**2 + max(c, i)**2)
    return ans

n = int(raw_input())
print '\n'.join(map(str, [solve(a, b, c, d) for (a, b, c, d) in [map(int, raw_input().split()) for _ in [0]*n]]))
