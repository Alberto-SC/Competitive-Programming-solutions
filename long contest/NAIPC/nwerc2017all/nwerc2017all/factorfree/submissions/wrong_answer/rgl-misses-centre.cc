#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

#define MAXN 1000000

vector<int> df;
vector<set<int>> factors;
void gen_factors(int const max_v){
  df.resize(max_v+1);
  factors.resize(max_v+1);
  for (long long i=2; i<=max_v; i++){
    if (df[i]==0) for (long long j=i*i; j<=max_v; j+=i) df[j]=i;
  }
  for (int i=2; i<=max_v; i++){
    if (df[i]==0) factors[i].insert(i);
    else{
      factors[i]=factors[i/df[i]];
      factors[i].insert(df[i]);
    }
  }
}

pair<int,int> span[MAXN];
int answer[MAXN];
vector<int> v;

// T(N) = max(X + T(X) + T(N-1-X) | 0 <= X*2 <= N) = O(N log N)
bool solve(int l,int r,int p=-1){
  if (r<=l) return true;
  for (int i=0; l+i<r-1-i or l+i<=r-1-i and (r-l)<=6; i++){
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
  int n,maxi=1; cin>>n;
  v.resize(n); for (auto &i: v) cin>>i, maxi=max(i,maxi);

  // Create the factors[] map.
  gen_factors(maxi);

  // Find the first non-coprime neighbours in each direction.
  {
    map<int,int> when;
    for (int i=0; i<n; i++){
      span[i].first=0;
      for (auto j: factors[v[i]]){
        if (when.count(j)) span[i].first=max(span[i].first,when[j]);
        when[j]=i+1;
      }
    }
    when.clear();
    for (int i=n; i--;){
      span[i].second=n;
      for (auto j: factors[v[i]]){
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
