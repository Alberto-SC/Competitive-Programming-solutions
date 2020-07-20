// Sort according to the install size
#include <algorithm>
#include <tuple>
#include <iostream>
#include <vector>
using namespace std;

#define rep(i, a, b) for (__typeof(b) i = a; i < (b); ++i)

typedef long long ll;
int main() {
  int n, c;
  cin >> n >> c;
  vector<tuple<int, int, int>> a;
  rep(i, 0, n) {
    int d, I;
    cin >> d >> I;
    a.push_back(make_tuple(I, max(d, I), i));
  }
  sort(a.begin(), a.end());

  int used = 0;
  vector<int> res;
  for (const auto& app : a) {
    int d, I, i;
    std::tie(I, d, i) = app;
    if (used + d <= c) {
      used += I;
      res.push_back(i + 1);
    }
  }
  cout << res.size() << endl;
  for (int x : res)
    cout << x << " ";
  cout << endl;
}
