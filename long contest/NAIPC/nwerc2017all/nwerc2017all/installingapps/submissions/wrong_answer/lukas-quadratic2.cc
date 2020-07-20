//Solution by lukasP (Lukáš Poláček)
//Complexity O(N^2)
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

#define rep(i, a, b) for (__typeof(b) i = a; i < (b); ++i)

int main() {
  int n, c;
  cin >> n >> c;
  vector<tuple<int, int, int>> a;
  rep(i, 0, n) {
    int d, I;
    cin >> d >> I;
    a.push_back(make_tuple(I - d, d, i));
  }

  sort(a.begin(), a.end());

  vector<int> best(n + 1, c + 10);
  best[0] = 0;
  vector<vector<tuple<int, int>>> prev(n + 1);
  prev[0].push_back(make_tuple(-1, -1));
  int most = 0;
  for (const auto &x : a) {
    int dif, d, I, idx;
    tie(dif, d, idx) = x;
    I = dif + d;
    for (int i = most; i >= 0; i--)
      // Should be: best[i] + max(d, I) <= c
      if (best[i] + I <= c) {
        if (best[i + 1] > best[i] + I) {
          best[i + 1] = best[i] + I;
          prev[i + 1].emplace_back((int)prev[i].size() - 1, idx);
          most = max(most, i + 1);
        }
      }
  }

  vector<int> res;
  int idx = 0;
  for (; most > 0; most--) {
    const auto &pr = prev[most][idx];
    res.push_back(get<1>(pr));
    idx = get<0>(pr);
  }
  cout << res.size() << endl;
  reverse(res.begin(), res.end());
  for (int x : res)
    cout << x + 1 << " ";
  cout << endl;
}
