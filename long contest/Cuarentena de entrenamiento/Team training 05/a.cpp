#include<bits/stdc++.h>

using namespace std;

int main(){
  int n,t,d,ld = 0,lt = 0,mx = -1;
  cin>>n;
  for(int i = 0;i<n;i++){
    cin>>t>>d;
    if(i == 0){ld = d; lt = t;continue;}
    mx = max(mx,(d-ld)/(t-lt));
    ld = d;
    lt = t;
  }
  cout<<mx<<endl;
  return 0;
}