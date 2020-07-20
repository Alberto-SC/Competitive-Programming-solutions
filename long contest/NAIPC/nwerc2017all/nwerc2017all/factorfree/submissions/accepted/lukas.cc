// Solution by lukasP (Lukáš Poláček)
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

#define rep(i, a, b) for (__typeof(b) i = a; i < (b); ++i)

typedef vector<int> vi;
bool rec(int start, int end, vi &par, const vi &left, const vi &right,
         int parent) {
  if (start > end) {
    if (start == end)
      par[start] = parent;
    return true;
  }
  for (int i = 0; end - i >= start + i; i++) {
    int pos = end - i;
    if (left[pos] < start && right[pos] > end) {
      par[pos] = parent;
      return rec(start, pos - 1, par, left, right, pos) &&
             rec(pos + 1, end, par, left, right, pos);
    }
    pos = i + start;
    if (left[pos] < start && right[pos] > end) {
      par[pos] = parent;
      return rec(start, pos - 1, par, left, right, pos) &&
             rec(pos + 1, end, par, left, right, pos);
    }
  }
  return false;
}
int main() {
  vi div(10000001, -1);
  unordered_map<int, int> ord;
  rep(i, 2, div.size()) if (div[i] == -1) {
    div[i] = i;
    int sz = ord.size();
    ord[i] = sz;
    for (size_t j = 2 * i; j < div.size(); j += i)
      div[j] = i;
  }
  vector<vi> divisible(ord.size());

  int n;
  scanf("%d", &n);
  vi a(n);
  vi left(n, -1), right(n, n);
  rep(i, 0, n) {
    scanf("%d", &a[i]);
    int q = a[i];
    while (q > 1) {
      int d = div[q];
      while (q % d == 0)
        q /= d;

      auto &divis = divisible[ord[d]];
      if (!divis.empty()) {
        left[i] = max(left[i], divis.back());
        right[divis.back()] = min(right[divis.back()], i);
      }
      divis.push_back(i);
    }
  }

  vi par(n, -5);
  if (rec(0, n - 1, par, left, right, -1)) {
    rep(i, 0, par.size()) printf("%d ", par[i] + 1);
    printf("\n");
  } else {
    printf("impossible\n");
  }
}
