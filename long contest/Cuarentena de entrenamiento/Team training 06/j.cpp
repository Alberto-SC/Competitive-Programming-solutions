#include <bits/stdc++.h>

using namespace std;
typedef long long int lli;
const lli mod = 986444681;
const int maxn = 100007;
lli inv[maxn];
lli fact[maxn];
lli invfact[maxn];
void calc(int m){
    inv[0] = inv[1] = 1;
    fact[0] = fact[1] = 1;
    invfact[0] = invfact[1] = 1;
    for(int i = 2; i <= m; ++i) {
        inv[i] = (inv[mod % i]* (mod - (mod/i)))%mod;
        fact[i] = (fact[i - 1]* i)%mod;
        invfact[i] = (invfact[i - 1]* inv[i])%mod;
    }
}
/*
    Lucas Theorem
*/
lli Lucas(lli N,lli R){
	if(R<0||R>N)
		return 0;
	if(R==0||R==N)
		return 1ll;
	if(N>=mod)
		return (1ll*Lucas(N/mod,R/mod)*Lucas(N%mod,R%mod))%mod;
	return (1ll* fact[N]*((invfact[N-R]*invfact[R])%mod))%mod;
}


int main(){
    int n,k;
    calc(100000);
    cin>>n>>k;
    cout<<Lucas(n,k)<<endl;

	return 0;   
}