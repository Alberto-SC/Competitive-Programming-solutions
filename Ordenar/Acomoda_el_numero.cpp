#include <iostream>
#include <stdio.h>
using namespace std;

inline void getInt(int &n)  
{
  n = 0;
  int ch = getchar_unlocked();
  int sign = 1;
 
  while (ch<'0' || ch>'9')  
  {
    if (ch == '-')
    {
      sign = -1;
    }
    ch = getchar_unlocked();
  }
 
  while (ch >= '0' && ch <= '9')
  {
    n = (n << 3) + (n << 1) + ch - '0';  
    ch = getchar_unlocked();
  }
  
  n *= sign;  
}

int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int i,a0,s = 0,n,p = 0;
	getInt(n);
	getInt(a0);
	for(i = 1;i<n;i++){
		getInt(s);
		if(a0 > s)
		p++;
	}
	cout<<p;
	return 0;
}
