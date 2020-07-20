#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <map>
#include <set>
using namespace std;

#ifdef DEBUG
#define DBG(x) {x;}
#else
#define DBG(x)
#endif

#define MAXN 1000000
#define MAXV 10000000

template <class C>
struct ArrayVector {
  C *beg, *last;
  C const* begin() const {return beg;}
  C const* end() const {return last;}
  void push_back(C const &x){*(last++)=x;}
};

struct Factors{
  vector<int32_t> f;

  Factors(int32_t const n){
    f.assign((n+1)/2+1,-1);
    for (int32_t i=3; i<=n; i+=2){
      if (f[i/2]!=-1) continue;
      f[i/2]=i;
      if (i<=n/i){
        for (int32_t j=i*i; j<=n; j+=i+i){
          if (f[j/2]==-1){
            f[j/2]=i;
          }
        }
      }
    }
  }

  ArrayVector<int> get(int x) const{
    static int val[20];
    ArrayVector<int> v{val,val};
    for (int last=-1; x>1;){
      int q=((x&1)==0? 2: f[x/2]);
      if (q!=last) v.push_back(q), last=q;
      x/=last;
    }
    return v;
  }
};

pair<int,int> span[MAXN];
int answer[MAXN];
vector<int> v;

long long iterations=0;

bool solve(int l,int r,int p=-1){
  if (r<=l) return true;
  for (int j=l; j<=min(l+10,r-1); j++){
    DBG(++iterations);
    if (span[j].first<=l and span[j].second>=r){
      answer[j]=p;
      return solve(l,j,j) and solve(j+1,r,j);
    }
  }
  for (int j=r; j-->max(r-10,l);){
    DBG(++iterations);
    if (span[j].first<=l and span[j].second>=r){
      answer[j]=p;
      return solve(l,j,j) and solve(j+1,r,j);
    }
  }
  for (int j=l; j<=r-1; j++){
    DBG(++iterations);
    if (span[j].first<=l and span[j].second>=r){
      answer[j]=p;
      return solve(l,j,j) and solve(j+1,r,j);
    }
  }
  return false;
}

int main(){
  ios::sync_with_stdio(false);

  int n; cin>>n;
  v.resize(n); for (auto &i: v) cin>>i;

  // Create the factors map.
  Factors f(accumulate(v.begin(),v.end(),0,[](int a,int b){return max(a,b);}));

  // Find the first non-coprime neighbours in each direction.
  {
    static int when[MAXV+1];
    for (int i=0; i<n; i++){
      span[i].first=0;
      for (auto j: f.get(v[i])){
        if (when[j]!=0) span[i].first=max(span[i].first,when[j]);
        when[j]=i+1;
      }
    }
    for (int i=n; i--;){
      span[i].second=n;
      for (auto j: f.get(v[i])){
        if (when[j]>i+1) span[i].second=min(span[i].second,when[j]-1);
        when[j]=i+1;
      }
    }
  }

  DBG(
    set<int> roots;
    for (int i=n; i--;)
      if (span[i].first==0 and span[i].second==n)
        roots.insert(i);
    cerr<<"roots: "<<roots.size()<<endl;
  )

  if (not solve(0,n)){
    cout<< "impossible" <<endl;
  }else{
    DBG(cerr<<"iterations: "<<iterations<<endl);
    for (int i=0; i<n; i++){
      cout<<answer[i]+1<<(i+1==n? '\n': ' ');
    }
  }
}
