#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef double ld;

ld p[14][5000];
ld s[5000];
int n2=1;

void rec(int l,int r,int v=0){
  if (l+1==r) {p[v][l]=1; return;}
  int m=(l+r)/2;
  rec(l,m,v+1);
  rec(m,r,v+1);

  for (int i=0; i<n2; i++)
    for (int j=0; j<n2; j++)
      if (l<=i and i<m and m<=j and j<r)
        if (p[v+1][i] or p[v+1][j])
          p[v][i]+=p[v+1][i]*p[v+1][j]*s[i]/(s[i]+s[j]),
          p[v][j]+=p[v+1][i]*p[v+1][j]*s[j]/(s[i]+s[j]);
}

int main(){
  int n; cin>>n; while (n2<n) n2*=2;
  for (int i=n; i--;) cin>>s[i];
  sort(s,s+n-1,[](ld a,ld b){return b<a;});
  for (int i=0; i<n2-n; i++) swap(s[n2-1-i*2],s[n-1-i]);

  rec(0,n2);
  cout.precision(8);
  cout<<fixed<<p[0][n2-1]<<endl;
}
