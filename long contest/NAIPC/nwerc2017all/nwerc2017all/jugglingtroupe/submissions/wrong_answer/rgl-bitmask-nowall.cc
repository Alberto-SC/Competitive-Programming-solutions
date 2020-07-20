#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
using namespace std;

constexpr bool debug_enabled=true;
bool debug=false;

#define MAXN 100000
static uint64_t v[3][MAXN/64+3];

int main(int argc,char **argv){
  for (int i=1; i<argc; i++){
    if (string(argv[i])=="-d"){
      debug=true;
    }
  }

  string s; cin>>s; int const n=s.length();
  for (uint64_t a=1,b=1,i=0; i<s.size(); i++){
    if (s[i]>='1') v[0][a]|=b;
    if (s[i]>='2') v[1][a]|=b;
    if ((i&63)==63) ++a, b=1ll; else b<<=1ll;
  }
  int const nn=(n+63)/64;

  for (;;){
    if (debug_enabled and debug){
      for (uint64_t i=0; i<n; i++){
        for (uint64_t j=3; j--;)
          if ((v[j][i/64+1]&(1ll<<(i%64ll)))!=0)
            {cerr<<j+1; goto good;}
        cerr<<'0';
        good: continue;
      }
      cerr<<endl;
    }

    bool change=false;
    for (int i=1; i<=nn; i++) change|=!!v[1][i];
    if (not change) break;

    static uint64_t w[3][MAXN/64+3];
    for (int i=1; i<=nn; i++){
      w[0][i]=(v[1][i]<<1ll)|((v[1][i-1]&(1ll<<63ll))!=0 ? (1ll<<0ll) : 0ll);
      w[1][i]=(v[2][i])|(v[0][i]&~v[1][i]);
      w[2][i]=(v[1][i]>>1ll)|((v[1][i+1]&(1ll<<0ll))!=0 ? (1ll<<63ll) : 0ll);
    }
    for (int i=1; i<=nn; i++){
      v[0][i]=(w[0][i]|w[1][i]|w[2][i]);
      v[1][i]=(w[0][i]&w[1][i])|(w[0][i]&w[2][i])|(w[1][i]&w[2][i]);
      v[2][i]=(w[0][i]&w[1][i]&w[2][i]);
    }
  }

  for (uint64_t i=0; i<n; i++){
    cout<<((v[0][i/64+1]&(1ll<<(i%64)))!=0);
  }
  cout<<endl;
}
