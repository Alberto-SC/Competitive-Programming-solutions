#include <algorithm>
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;
typedef pair<long double,long double> pl;

/**

Intentionally slow: does meet-in-the-middle memoisation for the
toplevel solve_problem instead of properly memoising everything.

**/

long double choosa[201][201];
long double choose(int n,int k){return choosa[n][k];}

int t,n,h;
int table[200];

pl mul_res(pl a,pl b,int u,int v){
  auto const c=choose(u+v,u);
  return {a.first*b.first*c,(a.first*b.second+b.first*a.second)*c};
}

pl cmb_res(pl a,pl b){
  return {a.first*b.first  ,(a.first*b.second+b.first*a.second)};
}

void add_res(pl &a, pl b) {a.first+=b.first; a.second+=b.second;}

pl get_ways(int l,int r){
  static pl gwm[256][256];
  static bool gwh[256][256];

  if (l==r) return {1,0};
  if (l and table[l-1]==table[l]) return {0,0};
  if (gwh[l][r]) return gwm[l][r]; else gwh[l][r]=1;

  int const lo = (l? table[l-1]+1: 1);
  pl res;
  for (int i=l; i<r; i++){
    if (i+1<r and (i+1>=t or table[i]==table[i+1])) continue;

    pl const a=get_ways(l,i), b=get_ways(i+1,r);
    pl const c=i<t
        ? pl{(table[i]-lo+1), (table[i]-lo+1)*(table[i]+lo)/2.L}
        : pl{table[t-1]-lo+1, 0};

    add_res(res, cmb_res(c, mul_res(a,b,i-l,r-i-1)));
  }
  return gwm[l][r]=res;
}

int midway;

pl solve_problem_right(int s,int people){
  if (s>=t) return {powl(n-table[t-1],people),0};
  if (s<midway){
    assert(false);
  }

  pl res=solve_problem_right(s+1,people);
  if (s==0 or table[s]>table[s-1]){
    for (int j=1,k=people-j; j<=people; j++,k--){
      add_res(res, mul_res(get_ways(s,s+j), solve_problem_right(s+j+1,k), j, k));
    }
  }
  return res;
}

pl solve_problem_left(int s,int people){
  if (s>=t) return {powl(n-table[t-1],people),0};
  if (s>=midway){
    static pl spm[256][256];
    static bool sph[256][256];
    if (not sph[s][people]){
      sph[s][people]=1;
      spm[s][people]=solve_problem_right(s,people);
    }
    return spm[s][people];
  }

  pl res=solve_problem_left(s+1,people);
  if (s==0 or table[s]>table[s-1]){
    for (int j=1,k=people-j; j<=people; j++,k--){
      add_res(res, mul_res(get_ways(s,s+j), solve_problem_left(s+j+1,k), j, k));
    }
  }
  return res;
}

int main(){
  for (int i=0; i<=200; i++)
    for (int j=0; j<=200; j++)
      choosa[i][j]=(i==j or j==0? 1: i<j? 0: choosa[i-1][j-1]+choosa[i-1][j]);

  cin>>t>>n>>h;
  midway=h/2;
  for (int i=0; i<t; i++) cin>>table[i], table[i]=min(table[i],n);
  sort(table,table+t);
  pl res=solve_problem_left(0,h);
  printf("%.9Lf\n", res.second/res.first);
}
