#include <iostream>
#include <string>
#include <vector>
using namespace std;

constexpr bool debug_enabled=true;
bool debug=false;

vector<int> go(vector<int> v){
  vector<int> r(v.size());
  for (int i=0; i<v.size(); i++){
    if (i) r[i-1]+=v[i]/2;
    if (i+1<v.size()) r[i+1]+=v[i]/2;
    r[i]+=v[i]%2;
  }
  return r;
}

int main(int argc, char **argv){
  for (int i=1; i<argc; i++){
    if (string(argv[i])=="-d"){
      debug=true;
    }
  }

  string s; cin>>s; int const n=s.length();
  vector<int> v; for (auto &i: s) v.push_back(i-'0');
  for (;;){
    if (debug_enabled and debug){
      for (int i=0; i<n; i++){
        cerr<<v[i];
      }
      cerr<<endl;
    }
    vector<int> r=go(v);
    if (v==r) break;
    v=r;
  }
  for (int i=0; i<n; i++){
    cout<<v[i];
  }
  cout<<endl;

}
