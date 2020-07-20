#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

int main(){
  string s; cin>>s; int const n=s.length();
  vector<int> v; for (auto &i: s) v.push_back(i-'0');

  set<int> zero={-1,n};
  for (int i=0; i<n; i++) if (v[i]==0) zero.insert(i);

  for (int i=0; i<n; i++){
    while (v[i]>=2){
      int pl=0;
      auto it=zero.upper_bound(i);
      pl+=*it-i; if (*it<n) v[*it]++, zero.erase(it--); else --it;
      pl+=*it-i; if (*it>=0) v[*it]++, zero.erase(it);
      if (not --v[i]) zero.insert(i);
      if (not --v[i+pl]) zero.insert(i+pl);
    }
  }
  for (int i=0; i<n; i++) cout<<v[i];
  cout<<endl;
}
