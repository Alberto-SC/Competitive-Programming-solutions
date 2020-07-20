DP = {}

DP[1] = 1
DP[2] = 2
for i in range (3,10007):    
    DP[i] = DP[i-1]+DP[i-2]

t = int(input())
for i in range (0,t):
    n = int(input())
    print(DP[n])
