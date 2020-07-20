#include <algorithm>
#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <map>
using namespace std;
typedef uint32_t ll;

ll solve(vector<string> const &s, map<string,vector<string>> const &dict){
  ll res=1ull;
  for (string const &i: s)
    res*=(dict.count(i) == 0 ? 0ull : dict.at(i).size());
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

  ll good_count=solve(s,good);
  ll all_count=solve(s,all);
  if (all_count==1){
    bool first=true;
    for (string const &i: s){
      if (first) first=false; else cout<<" "; cout<<all[i].front();
    }
    cout<<(good_count?"correct":"incorrect")<<endl;
  }else{
    cout<<good_count<<" correct"<<endl;
    cout<<all_count-good_count<<" incorrect"<<endl;
  }
}
