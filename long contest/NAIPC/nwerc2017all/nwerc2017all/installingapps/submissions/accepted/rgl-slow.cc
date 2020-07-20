#include <bits/stdc++.h>
using namespace std;

struct App {int prep,stable,id;};

int main(){
  int n,cap; cin>>n>>cap;

  vector<App> app(n);
  for (int i=0; i<n; i++){
    app[i].id=i+1;
    cin>>app[i].prep>>app[i].stable;
    app[i].prep=max(app[i].prep,app[i].stable);
  }
  sort(app.begin(),app.end(),[](App const &a,App const &b){
    return(a.stable+b.prep  < b.stable+a.prep)
        or(a.stable+b.prep == b.stable+a.prep and a.stable < b.stable);
  });

  vector<pair<int,int>> dp(cap+1,{-1,-1}),bt;
  dp[0]={0,-1};
  for (int i=0; i<app.size(); i++){
    for (int st=cap-app[i].prep; st>=0; --st){
      if (dp[st].first+1>dp[st+app[i].stable].first){
        dp[st+app[i].stable]={dp[st].first+1,bt.size()};
        bt.push_back({app[i].id,dp[st].second});
      }
    }
  }

  int answer=cap;
  for (int i=cap; i--;) if (dp[i]>dp[answer]) answer=i;
  vector<int> res;
  for (int i=dp[answer].second; ~i; i=bt[i].second)
    res.push_back(bt[i].first);

  cerr<<"backtracking cells used: "<<fixed<<setprecision(2)<<bt.size()*100.L/(cap*n)<<"%"<<endl;
  cout<<res.size()<<endl;
  for (int i=res.size(); i--;) cout<<res[i]<<(i?' ':'\n');
}
