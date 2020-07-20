#include <algorithm>
#include <iostream>
#include <numeric>
using namespace std;

int main(){
  long long n,v[4];
  for (cin>>n; n--;){
    for (auto &i: v) cin>>i;
    sort(v,v+3);

    long long res=0;
    for (long long i=0; i<=min(1000ll,v[3]); i++){
      long long w[3]={v[0]+i,max(v[0]+i,v[1]),max(v[0]+i,v[2])};
      w[2]+=accumulate(v,v+4,0ll)-accumulate(w,w+3,0ll);
      if (w[2]>=max(w[1],v[2])){
        res=max(res,w[0]*w[0]+w[1]*w[1]+w[2]*w[2]+7*w[0]);
      }
    }
    cout<<res<<endl;
  }
}
