

t = int(input())
for i in range(t):
	s = input();
	if len(s) >10:
		print('{0}{1}{2}'.format(s[0], len(s)-2, s[len(s)-1]))
	else:
		print(s)