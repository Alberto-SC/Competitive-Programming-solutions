#include <algorithm>
#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <map>
using namespace std;
typedef uint64_t ll;

// Super efficient recursive generator.
// Made even more efficient by implementing meet-in-the-middle to
// really crank up the performance.

ll solve(
    vector<string>::const_iterator s,
    vector<string>::const_iterator t,
    map<string,vector<string>> const &dict){
  if (s==t) return 1ull;
  if (not dict.count(*s)) return 0ull;
  ll res=0ull;
  for (auto const &i: dict.at(*s)){
    res+=solve(s+1,t,dict);
  }
  return res;
}

int main(){
  int n; cin>>n; vector<string> s(n); for (auto &i: s) cin>>i;
  int m; cin>>m; map<string,vector<string>> good,all;
  while (m--){
    string a,b,c; cin>>a>>b>>c;
    if (c=="correct") good[a].push_back(b);
    all[a].push_back(b);
  }

  ll const good_count=
      solve(s.begin(),s.begin()+s.size()/2,good) *
      solve(s.begin()+s.size()/2,s.end(),good);
  ll const all_count=
      solve(s.begin(),s.begin()+s.size()/2,all) *
      solve(s.begin()+s.size()/2,s.end(),all);
  if (all_count==1){
    bool first=true;
    for (string const &i: s){
      if (first) first=false; else cout<<" "; cout<<all[i].front();
    }
    cout<<endl<<(good_count?"correct":"incorrect")<<endl;
  }else{
    cout<<good_count<<" correct"<<endl;
    cout<<all_count-good_count<<" incorrect"<<endl;
  }
}
