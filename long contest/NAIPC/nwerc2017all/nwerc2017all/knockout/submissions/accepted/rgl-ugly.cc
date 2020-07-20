#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long double ld;

ld p[15][15000];
ld s[15000];

int bracket(int person,int round){return person>>round;}

int main(){
  int n; cin>>n;
  int n2=1,rounds=0; while (n2<n) n2*=2, ++rounds;
  fill(p[0],p[0]+n2,1);
  for (int i=n; i--;) cin>>s[i];
  sort(s,s+n-1,[](ld a,ld b){return b<a;});
  for (int i=0; i<n2-n; i++) swap(s[n2-1-i*2],s[n-1-i]);

  for (int round=0; round<rounds; round++) for (int i=n2; i--;) for (int j=i; j--;)
    if (s[i]+s[j] and bracket(i,round+0)!=bracket(j,round+0) and bracket(i,round+1)==bracket(j,round+1))
      p[round+1][i]+=p[round][i]*p[round][j]*s[i]/(s[i]+s[j]),
      p[round+1][j]+=p[round][i]*p[round][j]*s[j]/(s[i]+s[j]);

  cout.precision(12);
  cout<<fixed<<p[rounds][n2-1]<<endl;
}
