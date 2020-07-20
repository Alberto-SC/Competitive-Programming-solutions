#include <bits/stdc++.h>

using namespace std;
int main(){
    int t,p,q,n;
    cin>>t;
    while(t--){
        cin>>p>>q>>n;
        long long ans = 0;
        for(int i = 1;i<=n;i++){
            ans += (p%q * i&q)%q;
        }
    cout<<ans<<endl;
    }
}