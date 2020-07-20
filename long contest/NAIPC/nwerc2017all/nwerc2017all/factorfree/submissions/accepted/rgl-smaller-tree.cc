#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <map>
#include <set>
using namespace std;

/**
  General idea:
    - keep a "todo list" of indices of coprime items in the range.

    - keep a dependency list of how many factors an item has to go before it can
      be added to the list.

    - whenever we choose a new subroot, delete it from the list and then create
      a second such pair of lists for the *smaller* subtree (size < N/2). Use
      these lists to update the larger half in O(size) time too.

    - charge the work against the smaller half. time complexity is
      T(N) = N/2 + 2*T(N/2) -> O(NlogN).
*/

template <class C>/*{{{*/
struct ArrayVector {
  C *beg, *last;
  C const* begin() const {return beg;}
  C const* end() const {return last;}
  void push_back(C const &x){*(last++)=x;}
};/*}}}*/

struct Factors{/*{{{*/
  vector<int32_t> f;

  void sieve(int32_t const n){
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

  // Gives an iterator range for unique prime factors of X.
  ArrayVector<int> get(int x,int id) const{
    static int val[20];
    ArrayVector<int> v{val,val};
    if (x==1) v.push_back(4+id*2);
    else for (int last=-1; x>1;){
      int q=((x&1)==0? 2: f[x/2]);
      if (q!=last) v.push_back(q), last=q;
      x/=last;
    }
    return v;
  }
} factors;/*}}}*/

unordered_map<int,int> answer;
unordered_map<int,int> factors_remaining;
vector<int> v;

int sz(pair<int const*,int const*> const &p){
  return (p.second-p.first+1);
}

bool solve(
    int const l,
    int const r,
    int const p,
    unordered_map<int,pair<int const*,int const*>> &ranges,
    unordered_set<int> &todo){
  // Choose any centre point.
  if (l>=r) return true;

  if (todo.empty()) return false;
  int const centre=*todo.begin(); todo.erase(centre);
  answer[centre]=p;

  // find the smaller half and count primes in it.
  unordered_map<int,pair<int const*,int const*>> smaller;
  unordered_set<int> todo_smaller;

  bool const left_smaller=(centre-l <= r-centre);
  auto &a=(left_smaller? smaller: ranges);
  auto &b=(left_smaller? ranges: smaller);
  auto &todo_a=(left_smaller? todo_smaller: todo);
  auto &todo_b=(left_smaller? todo: todo_smaller);

  if (left_smaller){
    for (int i=l; i<centre; i++)
      for (int j: factors.get(v[i],i)){
        if (not a.count(j)){
          a[j]={ranges[j].first,ranges[j].first-1};
        }
        ++a[j].second;
        ++b[j].first;
        if (b[j].first<=b[j].second and *b[j].first==centre) ++b[j].first;
      }
  }else{
    for (int i=centre+1; i<r; i++)
      for (int j: factors.get(v[i],i)){
        if (not b.count(j)){
          b[j]={ranges[j].second+1,ranges[j].second};
        }
        --a[j].second;
        --b[j].first;
        if (a[j].first<=a[j].second and *a[j].second==centre) ++a[j].second;
      }
  }

  // Shift items across the "todo" list into subtrees.
  for (auto const i: smaller){
    pair<int const*,int const*> now_small = i.second;
    pair<int const*,int const*> now_large = ranges[i.first];

    if (sz({a[i.first].first,b[i.first].second})==1){
      ++factors_remaining[*a[i.first].first];
      todo.erase(*a[i.first].first);
    }

    if (sz(now_small)==1){
      --factors_remaining[*now_small.first];
      if (factors_remaining[*now_small.first]==0)
        todo_smaller.insert(*now_small.first);
    }
    if (sz(now_large)==1){
      --factors_remaining[*now_large.first];
      if (factors_remaining[*now_large.first]==0)
        todo.insert(*now_large.first);
    }
  }

  return solve(l,centre,centre,a,todo_a) and solve(centre+1,r,centre,b,todo_b);
}

int main(){
  int n; cin>>n;
  v.resize(n); for (auto &i: v) cin>>i;

  // Create the factors map.
  int const max_v=max(n*2+2,accumulate(v.begin(),v.end(),0,[](int a,int b){return max(a,b);}));
  factors.sieve(max_v);

  vector<vector<int>> items(max_v+1);
  for (int i=0; i<n; i++){
    for (auto j: factors.get(v[i],i)){
      ++factors_remaining[i];
      items[j].push_back(i);
    }
  }

  unordered_map<int,pair<int const*,int const*>> ranges;
  unordered_set<int> todo;
  for (int i=0; i<=max_v; i++){
    if (not items[i].empty()){
      ranges[i]={&items[i].front(),&items[i].back()};
      if (items[i].size()==1){
        if (not --factors_remaining[items[i][0]]) todo.insert(items[i][0]);
      }
    }
  }

  if (not solve(0,n,-1,ranges,todo)){
    cout<< "impossible" <<endl;
  }else{
    for (int i=0; i<n; i++){
      cout<<answer[i]+1<<(i+1==n? '\n': ' ');
    }
  }
}
