import math
epsilon=1e-09,
def power(x, y) : 
    res = 1    
    x = x % p  
    if (x == 0) : 
        return 0
    while (y > 0) : 
        if ((y & 1) == 1) : 
            res = (res * x) 
        y = y >> 1     
        x = (x * x)        
    return res 

a,b = input().split()
a = int(a)
b = int(b)
c = int(pow(a,b))
stri = str(c)
# print(c)
sum = 0
while 1:
    sum = 0
    while(c>0):
        sum  = sum+int(c%10)
        c = int(c//10) 
    x = float(math.log10(sum))
    if x<1.0:
        break
    c = int(sum)
print(int(sum))