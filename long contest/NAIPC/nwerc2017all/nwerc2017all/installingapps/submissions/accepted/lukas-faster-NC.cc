//Solution by lukasP (Lukáš Poláček)
//Complexity O(NC)
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

  vector<int> best(c + 1, 0);
  vector<vector<tuple<int, int, int>>> prev(c + 1);
  prev[0].push_back(make_tuple(-1, -1, -1));
  pair<int, int> last = {0, 0};
  for (const auto &x : a) {
    int dif, d, I, idx;
    tie(dif, d, idx) = x;
    I = dif + d;
    for (int i = c - max(d, I); i >= 0; i--)
      if (!prev[i].empty()) {
        if (best[i] + 1 > best[i + I]) {
          best[i + I] = best[i] + 1;
          prev[i + I].emplace_back(i, (int)prev[i].size() - 1, idx);
          if (best[i + I] > best[last.first])
            last.first = i + I;
        }
      }
  }

  last.second = prev[last.first].size() - 1;
  vector<int> res;
  while (last.first > 0) {
    const auto &pr = prev[last.first][last.second];
    res.push_back(get<2>(pr));
    last = make_pair(get<0>(pr), get<1>(pr));
  }
  cout << res.size() << endl;
  reverse(res.begin(), res.end());
  for (int x : res)
    cout << x + 1 << " ";
  cout << endl;
}
