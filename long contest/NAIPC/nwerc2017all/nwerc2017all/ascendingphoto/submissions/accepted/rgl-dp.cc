#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

vector<vector<int>> places;
vector<int> dp;

void renumber(vector<int> &v){
  map<int,int> all; for (auto const &i: v) all[i];
  int indices=0; for (auto &i: all) i.second=indices++;
  places.resize(indices);
  for (int i=0; i<v.size(); i++) v[i]=all[v[i]], places[v[i]].push_back(i);
}

int main(){
  int n; cin>>n; vector<int> h;
  for (int i=0; i<n; i++){
    int x; cin>>x; if (h.empty() or h.back()!=x) h.push_back(x);
  }
  renumber(h);

  dp.resize(h.size()+1);
  for (int i=places.size(); i--;){
    if (i+1==places.size()){
      for (int j: places[i]) dp[j]=places[i].size()-1;
    }else if (places[i].size()==1){
      for (int j: places[i]){
        dp[j]=(1<<29);
        for (int k: places[i+1])
          dp[j]=min(dp[j],dp[k]+(k!=j+1));
      }
    }else{
      static vector<pair<int,int>> best;
      for (int k: places[i+1]){
        best.emplace_back(dp[k]+(k==0 or h[k-1]!=i)+(places[i].size()-1),k);
        while (best.size()>2){
          if (best.back()<best[0]) swap(best.back(),best[0]);
          if (best.back()<best[1]) swap(best.back(),best[1]);
          best.pop_back();
        }
      }
      for (int j: places[i]){
        dp[j]=(1<<29);
        for (auto k: best) if (k.second!=j+1) dp[j]=min(dp[j],k.first);
        if (j+1<h.size() and h[j+1]==i+1) dp[j]=min(dp[j],dp[j+1]+(int)places[i].size());
      }
      best.clear();
    }
  }

  int res=(1<<29);
  for (int i: places[0]) res=min(res,dp[i]);
  cout<<res<<endl;
}
