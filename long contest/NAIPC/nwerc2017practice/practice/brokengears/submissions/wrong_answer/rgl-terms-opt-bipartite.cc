#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

// O(N)

struct Formula{
  long long m=0,c=0;
  Formula(long long m=0,long long c=0):m(m),c(c){}

  long long eval(long long x){return m*x+c;}
  long long lave(long long y){return (y-c)/m;}
  bool operator==(Formula const &o)const{return m==o.m and c==o.c;}
  bool operator!=(Formula const &o)const{return m!=o.m or c!=o.c;}
  Formula operator+(Formula const &o)const{return {m+o.m,c+o.c};}
};

vector<pair<int,int>> edge[1000002];
bool did[1000002];
Formula f[1000002];

bool go(int x){
  did[x]=true;
  for (auto y: edge[x]){
    Formula const ff={-f[x].m, y.second-f[x].c};
    if (not did[y.first]){
      f[y.first]=ff;
      if (not go(y.first)) return false;
    }
    else if (f[y.first]!=ff) return false;
  }
  return true;
}

int main(){
  int n; cin>>n;

  uint64_t sum_of_gears=0;
  int max_gear=0;
  vector<int> gears;
  unordered_map<int,vector<int>> gear_map;
  for (int i=0; i<n; i++){
    int x; cin>>x;
    gear_map[x].emplace_back(i);
    gears.push_back(x);
    sum_of_gears+=x;
    max_gear=max(max_gear,x);
  }

  int m; cin>>m;
  for (int i=0; i<m; i++){
    int a,b,w; cin>>a>>b>>w; --a,--b;
    edge[a].emplace_back(b,w);
    edge[b].emplace_back(a,w);
  }

  f[0]={1,0};
  if (not go(0)){
    cout<<"impossible"<<endl;
    return 0;
  }

  int big[2]={};
  for (int i=n; i--;){
    if (f[big[0]].m<=0 or f[i].m>0 and (f[i].c>f[big[0]].c)) big[0]=i;
    if (f[big[1]].m>=0 or f[i].m<0 and (f[i].c>f[big[1]].c)) big[1]=i;
  }

  vector<int> result(n);
  Formula total=accumulate(f,f+n,Formula{});
  cerr<<"total fn = "<<total.m<<"x + "<<total.c<<endl;
  for (int largest: big){
    int x=f[largest].lave(max_gear);
    cerr<<"trying "<<x<<endl;

    if (total.eval(x)!=sum_of_gears){
      continue;
    }

    auto tmp=gear_map;
    for (int i=0; i<n; i++){
      int y=f[i].eval(x);
      if (not tmp.count(y) or tmp[y].empty()){
        goto bad;
      }
      result[i]=tmp[y].back();
      tmp[y].pop_back();
    }

    good:
      for (int i=0; i<n; i++){
        cout<<result[i]+1<<(i+1==n?'\n':' ');
      }
      return 0;
    bad:
      continue;
  }
  cout<<"impossible"<<endl;
}
