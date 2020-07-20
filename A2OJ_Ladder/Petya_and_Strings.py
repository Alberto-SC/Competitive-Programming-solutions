s1 = input()
s2 = input()
s1 = s1.lower()
s2 = s2.lower()
i = 0
for i in range(len(s1)):
	if s1[i] == s2[i]: 
		continue
	elif s1[i] < s2[i]: 
		i = -1 
		break
	elif s1[i] > s2[i]: 
		i = 1 
		break
if i == -1 or  i == 1:
	print(i)
else:
	print(0)