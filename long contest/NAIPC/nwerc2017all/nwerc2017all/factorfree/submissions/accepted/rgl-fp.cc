#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <map>
#include <set>
using namespace std;

#define MAXV 10000000

struct Factors{
  vector<int32_t> f;

  Factors(int32_t const n){
    f.assign(n+1,-1);
    for (int32_t i=2; i<=n; i++){
      if (f[i]!=-1) continue;
      f[i]=i;
      if (i<=n/i){
        for (int32_t j=i*i; j<=n; j+=i){
          if (f[j]==-1){
            f[j]=i;
          }
        }
      }
    }
  }

  set<int> get(int x){
    set<int> res;
    while (x>1) res.insert(f[x]), x/=f[x];
    return res;
  }
};

pair<int,int> span[MAXV];
int answer[MAXV];
vector<int> v;

// T(N) = max(X + T(X) + T(N-1-X) | 0 <= X*2 <= N) = O(N log N)
bool solve(int l,int r,int p=-1){
  if (r<=l) return true;
  for (int i=0; l+i<=r-1-i; i++){
    for (int j: {l+i,r-1-i}){
      if (span[j].first<=l and span[j].second>=r){
        answer[j]=p;
        return solve(l,j,j) and solve(j+1,r,j);
      }
    }
  }
  return false;
}

int main(){
  int n; cin>>n;
  v.resize(n); for (auto &i: v) cin>>i;

  // Create the factors map.
  Factors f(accumulate(v.begin(),v.end(),0,[](int a,int b){return max(a,b);}));

  // Find the first non-coprime neighbours in each direction.
  {
    map<int,int> when;
    for (int i=0; i<n; i++){
      span[i].first=0;
      for (auto j: f.get(v[i])){
        if (when.count(j)) span[i].first=max(span[i].first,when[j]);
        when[j]=i+1;
      }
    }
    when.clear();
    for (int i=n; i--;){
      span[i].second=n;
      for (auto j: f.get(v[i])){
        if (when.count(j)) span[i].second=min(span[i].second,when[j]);
        when[j]=i;
      }
    }
  }

  if (not solve(0,n)){
    cout<< "impossible" <<endl;
  }else{
    for (int i=0; i<n; i++){
      cout<<answer[i]+1<<(i+1==n? '\n': ' ');
    }
  }
}
