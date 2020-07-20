#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll go(vector<ll> v, ll d) {
  return 7 * v[0] + v[0]*v[0] + v[1]*v[1] + (v[2] + d) * (v[2] + d);
}

int main(){
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    vector<ll> v = {a, b, c};
    sort(v.begin(), v.end());
    ll ans = 0;

    for (int i = 0; i <= min(1000LL, d); ) {
      ans = max(ans, go(v, d - i));
      ++v[0], ++i;
      if (v[0] > v[1])
        ++v[1], ++i;
      if (v[1] > v[2])
        ++v[2], ++i;
    }

    cout << ans << endl;
  }
}
