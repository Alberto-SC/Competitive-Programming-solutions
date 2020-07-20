//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

typedef long long ll;
int main() {
  int n; cin >> n;
  auto sq = [](ll x) { return x * x; };
  rep(k,0,n) {
    int a, b, c, d; cin >> a >> b >> c >> d;
    vector<ll> all = {a, b, c};
    sort(all.begin(), all.end());
    ll ma = 0;
    rep(i,0,4) rep(j,0,4) {
      int rest = d - i - j;
      if (rest < 0) continue;
      vector<ll> cur = {all[0] + i, all[1] + j, all[2] + rest};
      ll score = sq(cur[0]) + sq(cur[1]) + sq(cur[2]) + 7 * *min_element(cur.begin(), cur.end());
      ma = max(score, ma);
    }
    cout << ma << endl;
  }
}
