#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long double ld;

// Bug: doesn't guard against p[v][i] = NaN from division by zero.

ld p[13][4096];
ld s[4096];

void rec(int l,int r,int v=0){
  if (l+1==r) {p[v][l]=1; return;}
  int m=(l+r)/2;
  rec(l,m,v+1);
  rec(m,r,v+1);

  for (int i=l; i<m; i++)
    for (int j=m; j<r; j++)
      p[v][i]+=p[v+1][i]*p[v+1][j]*s[i]/(s[i]+s[j]),
      p[v][j]+=p[v+1][i]*p[v+1][j]*s[j]/(s[i]+s[j]);
}

int main(){
  int n; cin>>n;
  int n2=1; while (n2<n) n2*=2;
  for (int i=n; i--;) cin>>s[i];
  sort(s,s+n-1,[](ld a,ld b){return b<a;});
  for (int i=0; i<n2-n; i++) swap(s[n2-1-i*2],s[n-1-i]);
  n=n2;

  rec(0,n);
  cout.precision(8);
  cout<<fixed<<p[0][n-1]<<endl;
}
