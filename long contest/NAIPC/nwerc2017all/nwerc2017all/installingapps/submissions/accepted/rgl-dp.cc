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
    return a.stable+b.prep < b.stable+a.prep;
  });

  vector<pair<int,int>> dp(n+1,{cap+1,-1}),bt;
  dp[0]={0,-1};
  for (int i=0; i<app.size(); i++){
    for (int j=i; j>=0; --j){
      if (dp[j].first+app[i].prep<=cap and dp[j].first+app[i].stable<dp[j+1].first){
        dp[j+1]={dp[j].first+app[i].stable,bt.size()};
        bt.push_back({app[i].id,dp[j].second});
      }
    }
  }

  int answer=n; while (dp[answer].first>cap) --answer;
  vector<int> res;
  for (int i=dp[answer].second; ~i; i=bt[i].second)
    res.push_back(bt[i].first);

  cerr<<"backtracking cells used: "<<fixed<<setprecision(2)<<bt.size()*100.L/(n*(n+1)/2)<<"%"<<endl;
  cout<<res.size()<<endl;
  for (int i=res.size(); i--;) cout<<res[i]<<(i?' ':'\n');
}
