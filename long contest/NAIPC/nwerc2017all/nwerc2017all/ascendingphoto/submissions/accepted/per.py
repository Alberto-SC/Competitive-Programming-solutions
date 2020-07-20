raw_input()
H = map(int, raw_input().split())
H = [H[i] for i in range(len(H)) if not i or H[i] != H[i-1]]
n = len(H)

idx = {}
count = {}
for (i, h) in enumerate(sorted(set(H))):
    idx[h] = i

for i in range(n):
    H[i] = idx[H[i]]
    if H[i] not in count:
        count[H[i]] = 0
    count[H[i]] += 1
L = max(H)+2

cuts = n-1

cands = [set() for _ in range(L)]
for i in range(1, n):
    if H[i] == H[i-1]+1:
        cands[H[i]].add(i)
forced = [v for v in range(L) if len(cands[v]) == 1]
while forced:
    v = forced.pop()
    if not cands[v]: continue
    cuts -= 1
    i = cands[v].pop()
    for d in [-1, 1]:
        if i+d in cands[v+d] and count[v+d/2] > 1:
            cands[v+d].remove(i+d)
            if len(cands[v+d]) == 1:
                forced.append(v+d)

print cuts - len([v for v in range(L) if len(cands[v]) > 1])
