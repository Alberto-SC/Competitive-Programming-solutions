#include <bits/stdc++.h>

#define maxn 1010

#define ll long long

#define pb push_back

#define pii pair<int,int>

#define mod 1000000007 

#define debug(args...)// fprintf(stderr,args)

using namespace std;





int v[110];

ll dp[2][110];

int s;




ll get(int ok,int pos){



	if(pos == s) return 1;



	if(dp[ok][pos]+1)

		return dp[ok][pos];



	ll ans = 0;

	

	for(int d=0;d<7;d++){

		if(ok == 0 && d > v[pos]) break;

		ans += get(ok || (d < v[pos]), pos+1) * (d+1);

		ans %= mod;

	}



	return dp[ok][pos] = ans;

	

}



main(){

	int nt;

	scanf("%d",&nt);
	int u = 0;

	while(nt--){

		u++;
		ll n;

		scanf("%lld",&n);

		s = 0;
		ll n0 = n;

		while(n){

			v[s] = n%7;

			n /= 7;

			s++;

		}

		reverse(v,v+s);

		memset(dp,-1,sizeof(dp));
		ll tot = (n0+2);
		tot %= mod;
		tot *= ((n0+1)%mod);
		tot %= mod;
		tot *= (mod+1)/2;
		tot %= mod;
		

		printf("Case %lld: %lld\n",tot,(tot-get(0,0)+mod)%mod);

	}

}