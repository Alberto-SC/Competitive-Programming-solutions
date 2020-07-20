#include <iostream>
#include <vector>
#include <map>
using namespace std;

#define MAXN 1000000
constexpr bool debug_enabled=true;
bool debug=false;

vector<int> places[MAXN+1];
int dp[MAXN+1];

void renumber(vector<int> &v){
  map<int,int> all; for (auto const &i: v) all[i];
  int indices=0; for (auto &i: all) i.second=indices++;
  for (int i=0; i<v.size(); i++) v[i]=all[v[i]], places[v[i]].push_back(i);
}

int main(int argc,char **argv){
  if (debug_enabled){
    for (int i=1; i<argc; i++){
      if (string(argv[i])=="-d"){
        debug=true;
      }
    }
  }

  vector<int> h;
  int n; cin>>n;
  for (int i=0; i<n; i++){
    int x; cin>>x; if (h.empty() or h.back()!=x) h.push_back(x);
  }
  renumber(h);

  vector<int> occurrences(h.size());
  for (auto const &i: h) occurrences[i]++;

  for (int i=h.size(); i--;) if (places[i].size()){
    int const q=places[i].size();

    for (int j: places[i]){
      if (places[i+1].empty()){
        dp[j]=q-1;
      }else{
        dp[j]=(1<<29);

        for (int k: places[i+1]){
          if (q==1){
            dp[j]=min(dp[j],dp[k]+(k!=j+1));
          }else{
            dp[j]=min(dp[j],dp[k]+(k==j+1 or k==0 or h[k-1]!=i)+(q-1));
          }
        }
      }
    }
  }

  if (debug){
    for (int i=0; places[i].size(); i++){
      cerr<<"    "<<i<<":";
      for (auto j: places[i]) cerr<<"\t"<<j<<"["<<dp[j]<<"]";
      cerr<<endl;
    }
  }

  int res=(1<<29);
  for (int i: places[0]) res=min(res,dp[i]);
  cout<<res<<endl;
}
