#include <iostream>
#include <string>
#include <vector>
using namespace std;

constexpr bool debug_enabled=true;
bool debug=false;

int main(int argc,char **argv){
  for (int i=1; i<argc; i++){
    if (string(argv[i])=="-d"){
      debug=true;
    }
  }

  string s; cin>>s; int const n=s.length();
  vector<int> v; for (auto &i: s) v.push_back(i-'0');
  long long iterations=0;
  for (int i=0; i<n;){
    if (v[i]>=2){
      ++iterations;
      if (debug_enabled and debug){
        for (int i=0; i<n; i++){
          cerr<<v[i];
        }
        cerr<<endl;
      }
      if (i+1<n) ++v[i+1];
      v[i]-=2;
      if (i>0) ++v[i-1], --i;
    }
    else ++i;
  }
  cerr<<"iterations: "<<iterations<<endl;
  for (int i=0; i<n; i++){
    cout<<v[i];
  }
  cout<<endl;
}
