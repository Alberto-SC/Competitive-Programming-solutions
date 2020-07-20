#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

struct App {int prep,stable,id;};
vector<App> apps;
int cap;

int get_score(vector<bool> const &used){
  int res=0;
  int remain=cap,least_left=cap;
  for (int i=0; i<apps.size(); i++)
    if (used[i] and apps[i].prep<=remain){
      least_left=min(least_left,remain-apps[i].prep);
      remain-=apps[i].stable;
      ++res;
    }
  return res*cap*30+remain*2+least_left;
}

void simulate(vector<bool> const &used,vector<int> &into){
  int remain=cap;
  for (int i=0; i<apps.size(); i++)
    if (used[i] and apps[i].prep<=remain){
      remain-=apps[i].stable;
      into.push_back(apps[i].id);
    }
}

constexpr int macro_gens=1001;
constexpr int gen_size=1024;
constexpr int survivors=32;
constexpr int mutation_size=5;

vector<bool> go(){
  vector<vector<bool>> sp(gen_size,vector<bool>(apps.size()));
  for (auto &i: sp) i[rand()%i.size()]=1, i[rand()%i.size()]=1;

  for (int macro=0; macro<=macro_gens; macro++){
    static pair<int,int> good[1024];
    for (int i=0; i<gen_size; i++){
      good[i]={get_score(sp[i]),i};
    }
    sort(good,good+gen_size, greater<pair<int,int>>());
    if (macro==macro_gens) return sp[good[0].second];

    for (int ii=survivors; ii<gen_size; ii++){
      int const i=good[ii].second;
      sp[i]=sp[good[rand()%survivors].second];
      for (int j=1+(rand()%mutation_size); j--;){
        int const id=rand()%sp[i].size();
        sp[i][id]=not sp[i][id];
        if (id>0 and sp[i][id] and apps[id-1].prep==apps[id].prep) sp[i][id-1]=true;
      }
    }
  }
  return sp[0];
}

int main(){
  int n; cin>>n>>cap;
  srand(234565432);

  apps.resize(n);
  for (int i=0; i<n; i++){
    apps[i].id=i+1;
    cin>>apps[i].prep>>apps[i].stable;
    apps[i].prep=max(apps[i].prep,apps[i].stable);
  }
  sort(apps.begin(),apps.end(),[](App const &a,App const &b){
    return a.stable+b.prep < b.stable+a.prep
       or (a.stable+b.prep == b.stable+a.prep and a.stable<b.stable);
  });

  vector<int> res;
  simulate(go(),res);

  cout<<res.size()<<endl;
  for (int i=0; i<res.size(); i++) cout<<res[i]<<(i+1<res.size()?' ':'\n');
}
