#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

bool go(
    map<int,vector<int>> &gears,
    vector<map<int,int>> const &edge,
    vector<pair<int,int>> &result,
    int v,
    int x=0,
    int p=-1){

  if (not gears.count(v) or gears.at(v).empty()){
    return false;
  }
  result[x]={gears.at(v).back(),v}; gears.at(v).pop_back();
  for (auto y: edge.at(x)){
    if (result[y.first].first==-1){
      if (not go(gears,edge,result,y.second-v,y.first,x)){
        return false;
      }
    }
    else if (result[y.first].second+result[x].second!=y.second){
      return false;
    }
  }
  return true;
}

int main(){
  int n; cin>>n;

  map<int,vector<int>> gears;
  for (int i=0; i<n; i++){
    int x; cin>>x;
    gears[x].emplace_back(i);
  }

  int m; cin>>m;
  vector<map<int,int>> edge(n);
  for (int i=0; i<m; i++){
    int a,b,w; cin>>a>>b>>w; --a,--b;
    edge[a][b]=w;
    edge[b][a]=w;
  }

  vector<int> gear_keys;
  transform(
      gears.begin(),
      gears.end(),
      back_inserter(gear_keys),
      // [](auto i){return i.first;});
      // to make old c++11 compilers happy
      [](pair<int,vector<int>> i){return i.first;});
  for (auto x: gear_keys){
    cerr<<"trying "<<x<<endl;
    auto tmp=gears;
    vector<pair<int,int>> result(n,{-1,-1});
    if (go(gears,edge,result,x)){
      for (int i=0; i<n; i++){
        cout<<result[i].first+1<<(i+1==n?'\n':' ');
      }
      return 0;
    }
  }
  cout<<"impossible"<<endl;
}
