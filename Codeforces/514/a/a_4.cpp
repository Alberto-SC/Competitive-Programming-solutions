#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,l,a,t,li;
    cin>>n>>l>>a;
    if(n==0)return cout<<l/a<<endl,0;
    vector<pair<int,int>>pairs(n);
    for(int i = 0;i<n;i++){
        cin>>t>>li;
        pairs[i]={t,li};
    }
    sort(pairs.begin(),pairs.end());
    int ans =0;
    pairs.push_back({l,0});
    ans= (pairs[n].first - (pairs[n-1].first + pairs[n-1].second))/a;
    
    cout<<ans<<endl;
    return 0;
}