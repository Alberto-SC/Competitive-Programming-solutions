#include <bits/stdc++.h>

using namespace std;

long long go(vector<long long> v, long long d){
  if(d < 0) return 0;
  return 7 * v[0] + v[0]*v[0] + v[1]*v[1] + (v[2] + d) * (v[2] + d);
}

int main(){
  int n;
  cin >> n;
  for(int i = 0; i < n; ++i){
    long long a, b, c, d;
    cin >> a >> b >> c >> d;
    vector<long long> v = {a, b, c};
    sort(v.begin(), v.end());
    long long ans = 0;

    //ans = max(ans, go(v, d));

    long long mv = min(d, v[1] - v[0]);
    v[0] += mv;
    d -= mv;
    ans = max(ans, go(v, d));


    mv = min(d/2, v[2] - v[1]);
    v[0] += mv;
    v[1] += mv;
    d -= 2 * mv;
    ans = max(ans, go(v, d));

    mv = d/3;
    v[0] += mv;
    v[1] += mv;
    v[2] += mv;
    d -= 3 * mv;
    //ans = max(ans, go(v, d));

    cout << ans << endl;
  }
}
