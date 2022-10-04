#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long int  lli;
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);
const lli M = 1e6;
const lli mod = 1e9+7;
vector<lli> fact(M+1, 1), inv(M+1, 1), invfact(M+1, 1);
lli ncr(lli n, lli r){
	if(r < 0 || r > n||r<0) return 0;
	return fact[n] * invfact[r] % mod * invfact[n - r] % mod;
}
void calc(){
   	for(lli i = 2; i <= M; ++i){
		fact[i] = (lli)fact[i-1] * i % mod;
		inv[i] = mod - (lli)inv[mod % i] * (mod / i) % mod;
		invfact[i] = (lli)invfact[i-1] * inv[i] % mod;
	}
}



int  main(){__
	lli t= 1,n,m,k;
    cin>>t;
    calc();
    while(t--){
        cin>>n>>m>>k;
        vector<lli> nums(n);
        for(auto &c:nums)cin>>c;
        sort(nums.begin(),nums.end());
        lli ans = 0;
        lli last = -1;
        for(lli i = 0;i<n;i++){
            lli x = nums[i];
            lli idx = lower_bound(nums.begin(),nums.end(),x+k+1)-nums.begin();
            (ans+= ncr((idx-i)-1,m-1))%=mod;
        }
        cout<<ans<<endl;
    }
    return 0;
}  
