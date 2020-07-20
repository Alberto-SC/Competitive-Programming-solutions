#!/usr/bin/env python3

n,c = map(int,input().split())

apps = list(map(lambda i: list(map(int,input().split())), range(n)))
for i in range(n):
    apps[i][0] = max(apps[i][0], apps[i][1])
    apps[i] += [i+1]
apps = sorted(apps, key=lambda x: x[1]-x[0])

dp = list(map(lambda i: [(c+1 if i > 0 else 0), None, None], range(len(apps)+1)))
for i in range(len(apps)):
    for j in range(i,-1,-1):
        if dp[j][0] + apps[i][0] <= c and dp[j][0] + apps[i][1] < dp[j+1][0]:
            dp[j+1] = [dp[j][0] + apps[i][1], i, dp[j]]

res = len(apps)
while dp[res][0] > c: res -= 1
res = dp[res]

answer = []
while res[1] is not None:
    answer += [apps[res[1]][2]]
    res = res[2]

print(len(answer))
print(' '.join(map(str, answer[::-1])))
