#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int x,y,z,s,r,m,d;
	cin>>x>>y>>z;
	s=x+y;
	r=x-y;
	d=(x/y);
	m = x*y;
	if(z==s)
		cout<<"+";
	else if(z==r)
		printf("-");
	else if(z == m)
		printf("*");
	else if(z == d)
		printf("/");
	else
		printf("D:");
	return 0;
	
}
