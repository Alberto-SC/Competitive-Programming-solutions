#include <bits/stdc++.h>
using namespace std;

int main(){
  int n; cin>>n;
  vector<int> h(n); for (auto &i: h) cin>>i;

  int res=0;
  for (int i=0; i+1<h.size(); i++) res+=(h[i+1]<h[i]);
  cout<<res<<endl;
}
