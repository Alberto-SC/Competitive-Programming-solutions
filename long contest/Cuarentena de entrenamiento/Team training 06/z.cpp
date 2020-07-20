#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli mod_pow(llia ,lli b){
	lli x= 0;
	while(b){
		if(b&1) x = (x*a)%mod;
		a = (a*a)%mod;
		b>>=1;
	}	
	return 0;
}

int main(){
	int n,a;
	cin>>n>>a;
	cout<<mod_pow(n,a);
	return 0;
}
