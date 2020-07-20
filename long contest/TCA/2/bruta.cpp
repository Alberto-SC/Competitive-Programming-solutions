#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli n,k;
lli DP[100];
lli solve(lli s,lli mask){
    if(s == n)return __builtin_popcountll(mask);
    if(s>n)return 0;
    if(DP[s]!= -1)return DP[s];
    lli &x = DP[s];
    for(int i =2;i<=k;i++){
        if((mask>>i) &1)continue;
        lli aux = mask ;
        aux|=1<<i;
        x = min(solve((s+i)-1,aux),x);
    }
    return x;
}


int main(){
    cin>>n>>k;
    // memset(DP,100,sizeof(DP));
    solve(1,0);
    for(int i = 0;i<n;i++)cout<<DP[i]<<" ";
    cout<<endl;
    cout<<DP[n]<<endl;
    return 0;
}