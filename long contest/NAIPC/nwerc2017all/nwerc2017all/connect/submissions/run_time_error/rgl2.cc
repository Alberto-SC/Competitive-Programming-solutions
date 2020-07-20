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

// #define DEBUG
#define EPS (1e-12L)
#define BOUND 1000000
#define N 4

#ifdef DEBUG
#define DBG(x) {x;}
#else
#define DBG(x)
#endif

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
  assert(fabsl(d.x) >= 1e-9L or fabsl(d.y) >= 1e-9L);
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

pair<vec2,bool> find_ray_intersection(vec2 a,vec2 ad, vec2 b,vec2 bd){
  b=b-a;

  // ad*T = b+bd*S
  // ---
  // ad.x*T = b.x+bd.x*S
  // ad.y*T = b.y+bd.y*S
  // ---
  // ad.x*ad.y*T = ad.y*(b.x+bd.x*S)
  // ad.x*ad.y*T = ad.x*(b.y+bd.y*S)
  // S*(ad.y*bd.x-ad.x*bd.y) = ad.x*b.y - ad.y*b.x

  // Codirectional
  if (fabsl(ad.cross(bd)) < EPS){
    if (fabsl((b-a).cross(ad)) < EPS) {
      // Colinear
      if ((b-a).dot(ad) >= 0) return {b,true};
      if ((a-b).dot(bd) >= 0) return {a,true};
    }
    return {{},false};
  }

  // Find an intersection. Is it on line B?
  ld const s=(ad.x*b.y-ad.y*b.x) / (ad.y*bd.x-ad.x*bd.y);
  if (s < 0) return {{},false};

  vec2 v=b+bd*s;

  // And how about line A?
  if (v.dot(ad) < 0) return {{},false};
  return {a+v,true};
}

pair<vec2,bool> find_triangle_intersection(vec2 a,vec2 ad, vec2 b,pair<vec2,vec2> bd){
  DBG(cerr<<"find_triangle_intersection "<<a<<" "<<ad<<" | "<<b<<" .. "<<bd.first<<" "<<bd.second);

  if (in_range(a-b, bd)){
    DBG(cerr<<" => "<<a<<" (inside)"<<endl);
    return {a,true};
  }

  auto const u=find_ray_intersection(a,ad, b,bd.first);
  if (u.second and in_range(u.first-b, bd)){
    DBG(cerr<<" => "<<u.first<<" (edge 1)"<<endl);
    return u;
  }

  auto const v=find_ray_intersection(a,ad, b,bd.second);
  if (v.second and in_range(v.first-b, bd)){
    DBG(cerr<<" => "<<v.first<<" (edge 2)"<<endl);
    return v;
  }

  auto const w=extrude(a,ad);
  if (in_range(w-b, bd)){
    DBG(cerr<<" => "<<w<<" (extruded)"<<endl);
    return {w,true};
  }

  DBG(cerr<<" => false"<<endl);
  return {{},false};
}

struct Solution{
  int cost;
  set<pair<vec2,vec2>> ranges;
  bool corner;
};


int main(int argc,char **argv){
  vec2 v[N*N];
  for (int i=0; i<N; i++)
    for (int j=0; j<N; j++){
      int id; cin>>id; --id;
      v[id].x=j; v[id].y=N-1-i;
    }

  vector<Solution> angles(N*N, {600,{{{0.,0.},{0.,0.}}},true});
  angles[1]={1, {{v[1]-v[0],v[1]-v[0]}}};

  for (int i=1; i<N*N; i++){
    int const cost=angles[i].cost;
    DBG(cerr<<endl);
    for (auto const dirn: angles[i].ranges){
      DBG(cerr<<i+1<<": "<<(angles[i].corner)<<" | "<<dirn.first<<" "<<dirn.second<<endl);
      if (i+1==N*N) continue;

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

  DBG(cerr<<"---"<<endl);

  cout<<angles[N*N-1].cost<<endl;
  vector<vec2> answer={v[N*N-1]};
  for (int i=N*N-1; i>0; --i){
    DBG(cerr<<endl);
    for (auto const y: angles[i].ranges){
      DBG(cerr<<i+1<<": "<<(angles[i].corner)<<" | "<<y.first<<" "<<y.second<<endl);
      if (not angles[i].corner){
        // assert(in_range(y.first, *angles[i-1].ranges.begin()));
        // assert(in_range(y.second, *angles[i-1].ranges.begin()));
        angles[i-1].ranges={{{v[i]-v[i-1]},{v[i]-v[i-1]}}};
        goto good;
      }
      else{
        vec2 me=(y.first+y.second)*-1;
        for (auto const z: angles[i-1].ranges){
          pair<vec2,bool> p=find_triangle_intersection(v[i],me, v[i-1],z);
          if (p.second){
            if ((p.first-v[i-1]).length() > 1e-9L){
              angles[i-1].ranges.clear();
              angles[i-1].ranges.insert({p.first-v[i-1], p.first-v[i-1]});
            }
            answer.push_back(p.first);
            goto good;
          }
        }
      }
    }
    assert(false);
    good: continue;
  }
  answer.push_back(v[0]);
  DBG(cerr<<"answer size: "<<answer.size()<<endl);
  assert(answer.size() == (size_t)(angles[N*N-1].cost+1));

  if (argc>1){
    cout.precision(16);
    for (int i=answer.size(); i--;)
      cout<<answer[i].x<<" "<<answer[i].y<<endl;
  }
}
