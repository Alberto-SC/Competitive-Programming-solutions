#include <unordered_map>/*{{{*/
#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
#include <sstream>
#include <cassert>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <set>
using namespace std;/*}}}*/

enum JudgeCode:int{
  judge_error=1,
  correct=42,
  wrong_answer=43,
};

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

struct Validator{
  vector<vector<size_t>> children;
  vector<set<int32_t>> factors;

  bool go(size_t x,size_t l,size_t r, map<int32_t,size_t> &f){
    if (l == r) return true;
    bool valid = true;

    // Check for clashes
    for (auto i : factors[x]){
      if (f.count(i)){
        cout<<"Answer ["<<x+1<<"] has factor "<<i<<" in common with index ["<<f[i]+1<<"]"<<endl;
        return false;
      }else{
        f[i] = x;
      }
    }

    // Recurse.
    for (auto i : children[x]) {
      if (i<x){
        valid = valid and go(i,l,x,f);
      }else{
        valid = valid and go(i,x+1,r,f);
      }
    }

    // Remove changes.
    for (auto i : factors[x]){
      f.erase(i);
    }

    return valid;
  }
};

int main(int argc, char **argv){
  if (argc<3){
    cerr<<"usage: "<<argv[0]<<" testcase.in testcase.ans < team.out"<<endl;
    return judge_error;
  }
  else if (argc>3){
    cerr<<"warning: ignoring "<<argc-3<<" extra arguments"<<endl;
  }
  ifstream canonical_input(argv[1]);
  ifstream canonical_output(argv[2]);
  auto &team_output = cin;

  size_t n; assert(canonical_input>>n);
  vector<int32_t> v(n);
  for (size_t i = 0; i < n; i++) {
    canonical_input>>v[i];
  }
  int max_v = accumulate(v.begin(), v.end(), 0, [](int a,int b){return max(a,b);});

  // Read expected answer.
  string first_token;
  assert(canonical_output>>first_token);

  if (first_token == "impossible") {
    // Impossible.
    string team_token;
    if (not (team_output>>team_token)){
      cout<<"Bad output: unable to read 'impossible' from team"<<endl;
      return wrong_answer;
    }
    if (team_token=="impossible"){
      return correct;
    }else{
      cout<<"Wrong answer: expected 'impossible', team output "<<team_token<<endl;
      return wrong_answer;
    }
  }

  // Read team answer
  vector<int32_t> team_answer(n), roots;
  vector<vector<size_t>> children(n);
  for (size_t i = 0; i < n; i++) {
    if (not (cin>>team_answer[i])){
      cout<<"Missing "<<i+1<<"-th number"<<endl;
      return wrong_answer;
    }
    if (team_answer[i] < 0 or team_answer[i] > n){
      cout<<"Index "<<team_answer[i]<<" out of bounds [1,"<<n<<"]"<<endl;
      return wrong_answer;
    }
    if (team_answer[i] == 0){
      roots.push_back(i);
    }else{
      children[team_answer[i]-1].push_back(i);
    }
  }

  // Validate tree structure.
  if (roots.size() != 1) {
    cout<<"Expected 1 root but got {";
    for (size_t i = 0; i < roots.size(); i++) {
      cout<<(i == 0? "": " ")<<roots[i]+1;
    }
    cout<<"}"<<endl;
    return wrong_answer;
  }
  for (size_t i = 0; i < n; i++) {
    if (children[i].size() > 2){
      cout<<"Team has "<<children[i].size()<<" children for index "<<i+1<<endl;
      return wrong_answer;
    }
    if (children[i].size() == 2 and (children[i][0]<i) == (children[i][1]<i)){
      cout<<"Team has two children on the same side for index "<<i+1<<endl;
      return wrong_answer;
    }
  }

  // Generate factors.
  Factors f(max_v);
  vector<set<int32_t>> factors(n);
  for (size_t i = 0; i < n; i++) {
    factors[i] = f.get(v[i]);
  }

  // Validate tree factor-uniqueness.
  map<int32_t,size_t> factors_used;
  Validator validator{children,factors};
  return validator.go(roots[0],0,n,factors_used) ? correct : wrong_answer;
}
