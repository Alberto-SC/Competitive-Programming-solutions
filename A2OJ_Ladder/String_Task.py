import re
str = input()
str = str.lower()
F = ""
str = re.sub('[aeiouy]', '',str)
for i in range(len(str)):
	F = F+"."+str[i]
print(F)