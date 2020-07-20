#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
typedef long long ll;

template <class C> struct vec2{
  C x,y;

  template <class T> vec2<decltype(C{}*T{})> const operator-(vec2<T> const o)const{return {x-o.x,y-o.y};}
  template <class T> vec2<decltype(C{}*T{})> const operator+(vec2<T> const o)const{return {x+o.x,y+o.y};}

  template <class T> decltype(C{}*T{}) dot(vec2<T> const o)const{return x*o.x+y*o.y;}
  template <class T> decltype(C{}*T{}) cross(vec2<T> const o)const{return y*o.x-x*o.y;}
};
typedef vec2<ll> ivec2;
typedef vec2<long double> fvec2;

static bool colinear(ivec2 const a,ivec2 const b,ivec2 const c){
  return (b-a).cross(c-a)==0;
}

static bool intersect(pair<ivec2,ivec2> a, pair<ivec2,ivec2> b, fvec2 &res){
  auto const ad=a.second-a.first, bd=b.second-b.first;
  if (ad.cross(bd)==0) return false;

  long double const u = (a.first.x-b.first.x) * bd.y;
  long double const v = (a.first.y-b.first.y) * bd.x;
  long double const w = (ad.x*bd.y-ad.y*bd.x);
  long double const T = (v-u)/w;

  res={a.first.x+ad.x*T,a.first.y+ad.y*T};
  if ((res-a.second).dot(ad) < 1e-9L) return false;
  if ((res-b.first).dot(bd) > 1e-9L) return false;
  return true;
}

int main(int argc,char **argv){
  ivec2 v[16];
  for (int i=0; i<4; i++)
    for (int j=0; j<4; j++){
      int id; cin>>id; --id;
      v[id].x=j; v[id].y=3-i;
    }

  vector<bool> iss;
  vector<ivec2> seg;
  for (int i=0; i<16; i++){
    bool straight=false;
    while (seg.size()>=2 and colinear(seg[seg.size()-2],seg[seg.size()-1],v[i])){
      iss.pop_back();
      seg.pop_back();
      straight=true;
    }
    seg.push_back(v[i]);
    iss.push_back(straight);
  }

  bool skip=false;
  vector<fvec2> res;
  for (int i=0; i<seg.size();){
    fvec2 tmp;

    if (not skip){
      res.push_back(fvec2{}+seg[i]);
    }

    if (i+3<seg.size() and not iss[i+2] and intersect(
        {seg[i+0],seg[i+1]},
        {seg[i+2],seg[i+3]},
        tmp)){
      res.push_back(tmp);
      skip=true;
      i+=2;
    }else{
      skip=false;
      i++;
    }
  }
  cout.precision(8);
  cout<<res.size()-1<<endl;
  if (argc>1) for (auto i: res) cout<<i.x<<" "<<i.y<<endl;
}
