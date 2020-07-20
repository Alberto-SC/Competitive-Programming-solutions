#include <bits/stdc++.h>
using namespace std;

int main(){
  int n; cin>>n;
  vector<pair<int,int>> h(n);
  for (int i=0; i<n; i++) cin>>h[i].first, h[i].second=i;

  sort(h.begin(),h.end());
  for (int i=0; i<n; i++) h[i].first=h[i].second, h[i].second=i;
  sort(h.begin(),h.end());

  int res=0;
  for (int i=0; i+1<h.size(); i++)
    if (h[i].second+1!=h[i+1].second)
      ++res;

  cout<<res<<endl;
}
