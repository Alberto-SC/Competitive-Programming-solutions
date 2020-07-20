//Solution by lukasP (Lukáš Poláček)
//Complexity O(NC)
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstdio>
using namespace std;

#define rep(i, a, b) for (__typeof(b) i = a; i < (b); ++i)

inline int encode_pair(int cnt, int cap) { return cap + (cnt << 20); }
inline int encode_pair(const pair<int, int> &inp) {
  return encode_pair(inp.first, inp.second);
}
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
  vector<int> cur(c + 1, -1); cur[0] = 0;
  unordered_map<int, tuple<int, int, int>> prev;
  prev[encode_pair(0, 0)] = make_tuple(-1, -1, -1);
  int best_num = 0;
  pair<int, int> last = {0, 0};
  for (const auto &x : a) {
    int dif, d, I, idx;
    tie(dif, d, idx) = x;
    I = dif + d;
    for (int i = c - max(d, I); i >= 0; i--)
      if (cur[i] >= 0) {
        if (best[i] + 1 > best[i + I]) {
          best[i + I] = best[i] + 1;
          cur[i + I]++;
          prev[encode_pair(cur[i + I], i + I)] = make_tuple(cur[i], i, idx);
          if (best[i + I] > best_num) {
            best_num = best[i + I];
            last = {cur[i + I], i + I};
          }
        }
      }
  }

  vector<int> res;
  while (last.second > 0) {
    const auto &pr = prev[encode_pair(last)];
    res.push_back(get<2>(pr));
    last = make_pair(get<0>(pr), get<1>(pr));
  }
  cout << res.size() << endl;
  reverse(res.begin(), res.end());
  for (int x : res)
    cout << x + 1 << " ";
  cout << endl;
}
