#include <bits/stdc++.h>

using namespace std;

typedef long long int lli;
#define endl "\n"

lli gauss(lli n){
	return (n*(n+1)/2)-1;
}

int main(){
	lli n,k; cin >> n >> k;
	lli l=1, r=k-1, m, sum, ans;
    if(n == 1)return cout<<0<<endl,0;
    if(n<=k)return cout<<1<<endl,0;
    lli max = (k*(k-1))/2+1;
	if(n>max)return cout<<-1<<endl,0;
    while(l<r){
		m = (r+l)>>1;
        sum = (gauss(k))-(gauss(k-m))-(m-1);
		if(sum>=n)r = m;
		else
			l = m+1;
	}
    return cout<<l<<endl,0;
}
