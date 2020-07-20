// Solution by lukasP (Lukáš Poláček)
// Doesn't sort the input
#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
#include <iostream>
#include <cstdio>
using namespace std;

#define rep(i, a, b) for (__typeof(b) i = a; i < (b); ++i)

typedef vector<int> vi;
typedef pair<int, double> pid;
double calc_prod(const vector<pid> &opponents, const pid& me) {
  return accumulate(
      opponents.begin(), opponents.end(), 0.0,
      [me](double sum, const pid &opponent) {
        return sum + (double)me.first / (me.first + opponent.first) * opponent.second;
      }) * me.second;
}
int main() {
  int n, m;
  scanf("%d", &n);
  for (m = 1; m * 2 <= n; m *= 2);
  vi r(n);
  rep(i, 0, n) scanf("%d", &r[i]);
  // sort(r.begin() + 1, r.end());

  vector<vector<pid>> leaves;
  int rest = n - m;
  rep(i, 0, m - rest) leaves.emplace_back(1, pid(r[i], 1.));
  int cnt = m - rest;
  while ((int)leaves.size() < m) {
    double prob = (double)r[cnt] / (r[cnt] + r[cnt + 1]);
    leaves.push_back({{r[cnt], prob}, {r[cnt + 1], 1 - prob}});
    cnt += 2;
  }

  while (leaves.size() > 1) {
    vector<vector<pid>> new_leaves;
    for (size_t i = 0; i < leaves.size(); i += 2) {
      vector<pid> leaf;
      for (const auto &x : leaves[i])
        leaf.emplace_back(x.first, calc_prod(leaves[i + 1], x));
      for (const auto &x : leaves[i + 1])
        leaf.emplace_back(x.first, calc_prod(leaves[i], x));
      new_leaves.push_back(leaf);
    }
    swap(leaves, new_leaves);
  }
  printf("%.9lf\n", leaves[0][0].second);
}
