#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
const lli mod = 1e9 + 7;
#define endl '\n'
lli powmod(lli a,lli b){
    lli x = 1;
    while(b){
        if(b&1)x = (a*x)%mod;
        a = (a*a)%mod;
        b>>=1;
    }
    return x;
}

vector<lli> ac(40);
vector<lli> acc(60);
vector<lli> pow7(23);
vector<lli> big(40);
lli inv2  = powmod(2, mod - 2);
lli gauss(lli n){
    return (((n%mod)*((n+1))%mod)*inv2)%mod;
}
lli solve(lli block,lli n){
    if(block <= 1)return acc[n];
    lli ans = ac[block-2];
    n-=pow7[block-1];
    lli b2 = n/pow7[block-1];
    ans+= ac[block-2]*(gauss(b2+1)-1);
    ans%=mod;
    if(ans<0)ans+=mod;
    lli x = big[block-1]*gauss(b2);
    ans+= x;
    ans%=mod;
    if(ans<0)ans+=mod;
    lli diff = n- pow7[block-1]*b2;
    lli nblock = lower_bound(pow7.begin(),pow7.end(),diff)-pow7.begin();
    ans+= solve(nblock,diff)*(b2+2);
    ans%=mod;
    if(ans<0)ans+=mod;
    lli z = big[block-1]-gauss((pow7[block-1]-1)-diff);
    z = ((z%mod)*((b2+1)%mod))%mod;
    if(z<0)z+=mod;
    ans+= z;
    ans%=mod;
    if(ans<0)ans+=mod;
    return ans;
}
long long pas[1004][1004];
int main(){
    int t;
    lli n;
    pow7[0] = 0;
    pow7[1] = 7;
	ac[0] = 0;
	ac[1] = 21 * 21;
    big[0] = 0;
    big[1] = 21;
	int ff = 1;
	for (int i = 2; i <= 22; i++) {
		pow7[i] = pow7[i-1]*7;
		ac[i] = ((ac[i - 1]%mod)*(28%mod))%mod;
        lli x = ((pow7[i]%mod)*((pow7[i]-1)%mod))%mod;
        x*=inv2;
        x%=mod;
        big[i] = x;
        if(x<0)x+=mod;
        x*=21;
        x%=mod;
        if(x<0)x+=mod;
        ac[i]+=x;
        ac[i]%=mod;
    }

    memset(pas,0, sizeof(pas));
    pas[1][1]=1;
    for (int i=2; i <=49; i++) {
        for (int j = 1; j <= i; j++) {
            pas[i][j]=(pas[i-1][j]+pas[i-1][j-1])%7;
        }
    }
    int acu = 0;
    for (int i = 2; i <= 49; i++) {
        int cont=0;
        for (int j = 1; j <= i; j++) {
            if (pas[i][j] % 7 == 0){
              cont++;
            }
        }
        acu+=cont;
        acc[i] = acu;
    }
    scanf("%d",&t);
    int cont = 1;
    for(int i = 0;i<t;i++){
        scanf("%lld",&n);
        n++;
        lli block;
        block = lower_bound(pow7.begin(),pow7.end(),n)-pow7.begin();
        printf("Case %u: %lld\n",cont++,solve(block,n));
    }
    return 0;
}
