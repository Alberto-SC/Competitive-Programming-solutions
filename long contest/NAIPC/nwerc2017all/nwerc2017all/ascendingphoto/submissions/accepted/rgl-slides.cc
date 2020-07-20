#include <bits/stdc++.h>
using namespace std;

// Implementation of the algorithm described in the solution slides.

struct bimap{
  vector<int> fwd;
  priority_queue<pair<int,int>> rev;
  bimap(int n):fwd(n,-1){}
  void put(int x,int y) {fwd[x]=y; rev.emplace(y,x);}
  void clear() {while (not rev.empty()) fwd[rev.top().second]=-1, rev.pop();}
  bool count(int x) const {return x!=-1 and fwd[x]!=-1;}
  int max(){
    while (rev.top().first!=fwd[rev.top().second]) rev.pop();
    return rev.top().first;
  }
};

struct cell{
  int val,idx,pre;
  bool operator<(cell const &a)const{return val!=a.val?val<a.val:idx!=a.idx?idx<a.idx:pre<a.pre;}
};

int main(){
  ios::sync_with_stdio(false);

  int n; cin>>n;
  vector<cell> v;
  for (int i=0,p=-1,x; cin>>x; i++) if (!i or v.back().val!=x) v.push_back({x,(int)v.size(),p}), p=x;
  sort(v.begin(),v.end());
  vector<int> where(v.size()+1,-1);
  for (int i=0; i<v.size(); i++) where[v[i].idx]=i;

  bimap avail(v.size());
  vector<int> dp(v.size());
  auto const update=[&](int i,int j){
    avail.put(j,dp[j]+(v[j].pre==v[i].val and v[j].idx!=v[i].idx+1));
  };

  for (int i=v.size(); i--;)
    if (v[i].val==v.back().val)
      dp[i]=0;
    else if (v[i].val!=v[i+1].val and (i==0 or v[i].val!=v[i-1].val))
      for (int j=i+1; j<v.size() and v[j].val==v[i+1].val; j++)
        dp[i]=max(dp[i],dp[j]+(v[j].idx==v[i].idx+1));
    else{
      // either initialise the dp table from scratch or reuse one from the last iteration..
      if (v[i].val!=v[i+1].val)
        for (int j=(avail.clear(),i+1); j<v.size() and v[j].val==v[i+1].val; j++)
          update(i,j);
      else
        for (int j: {where[v[i].idx+1], where[v[i+1].idx+1]})
          if (avail.count(j))
            update(i,j);
      dp[i]=avail.max();
    }

  int res=dp[0];
  for (int i=1; i<v.size() and v[i].val==v[0].val; i++) res=max(res,dp[i]);
  cout<<v.size()-1-res<<endl;
}
