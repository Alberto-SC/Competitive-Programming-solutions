#include <algorithm>
#include <iostream>
#include <utility>
#include <numeric>
#include <cassert>
#include <vector>
#include <cmath>
#include <set>
using namespace std;
typedef long long ll;
typedef long double ld;

#define EPS (1e-12L)
#define BOUND 100
#define N 4

struct vec2{/*{{{*/
  long double x,y;

  bool const operator<(vec2 const &o)const{return x!=o.x? x<o.x: y<o.y;}
  bool const operator==(vec2 const &o)const{return x==o.x and y==o.y;}

  vec2 const operator-(vec2 const o)const{return {x-o.x,y-o.y};}
  vec2 const operator+(vec2 const o)const{return {x+o.x,y+o.y};}
  vec2 const operator*(ld const o)const{return {x*o,y*o};}

  long double dot(vec2 const o)const{return x*o.x+y*o.y;}
  long double cross(vec2 const o)const{return y*o.x-x*o.y;}

  long double length()const{return hypotl(x,y);}
  void normalise(){auto const l=length(); if (l) x/=l, y/=l;}

  friend ostream& operator<<(ostream& s, vec2 const &v){
    return s<<"("<<v.x<<","<<v.y<<")";
  }
}/*}}}*/;

vec2 extrude(vec2 const o, vec2 d){
  ld const f1=(fabsl(d.x) < EPS? 1e30L: ((d.x>0? BOUND: -BOUND)-o.x)/d.x);
  ld const f2=(fabsl(d.y) < EPS? 1e30L: ((d.y>0? BOUND: -BOUND)-o.y)/d.y);
  return o+d*min(f1,f2);
}

bool in_range(vec2 p, pair<vec2,vec2> r){
  r.first.normalise();
  r.second.normalise();

  vec2 bisection=r.first+r.second;
  if (p.dot(bisection) < 0) return false;

  ld const u=p.cross(r.first);
  ld const v=p.cross(r.second);
  if (fabsl(u) < EPS or fabsl(v) < EPS) return true;
  return ((u<0) != (v<0));
}

struct Solution{
  int cost;
  set<pair<vec2,vec2>> ranges;
  bool corner;
};

int main(){
  static vec2 v[N*N];
  for (int i=0; i<N; i++)
    for (int j=0; j<N; j++){
      int id; cin>>id; --id;
      v[id].x=j; v[id].y=N-1-i;
    }

  vector<Solution> angles(N*N, {N*N+1,{{{0.,0.},{0.,0.}}},true});
  angles[1]={1, {{v[1]-v[0],v[1]-v[0]}}};

  for (int i=1; i+1<N*N; i++){
    int const cost=angles[i].cost;
    for (auto const dirn: angles[i].ranges){
      if (in_range(v[i+1]-v[i], dirn)){
        if (angles[i+1].cost  > cost) angles[i+1]={cost, {}, false};
        if (angles[i+1].cost == cost) angles[i+1].ranges.insert({v[i+1]-v[i], v[i+1]-v[i]});
      }else{
        if (angles[i+1].cost  > cost+1) angles[i+1]={cost+1, {}, true};
        if (angles[i+1].cost == cost+1){
          angles[i+1].ranges.emplace(v[i+1]-v[i], v[i+1]-extrude(v[i],dirn.first));
          angles[i+1].ranges.emplace(v[i+1]-v[i], v[i+1]-extrude(v[i],dirn.second));
        }
      }
    }
  }
  cout<<angles[N*N-1].cost<<endl;
}
