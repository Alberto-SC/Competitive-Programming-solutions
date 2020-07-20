//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
#include <complex>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

typedef complex<double> cd;
int main() {
  int n; scanf("%d", &n);
  vector<cd> points(n);
  rep(i,0,n) {
    int x, y;
    scanf("%d %d", &x, &y);
    points[i] = cd(x, y);
  }

  double best = 0;
  int res = 0;
  rep(k,3,9) {
    double mi = 1e7, ma = 0;
    rep(i,0,n) {
      double ang = fmod(arg(points[i]) + 2 * M_PI, 2 * M_PI / k) - M_PI / k;
      double radius = cos(ang) * abs(points[i]);
      mi = min(radius, mi);
      ma = max(radius, ma);
    }
    double score = (mi / ma) * (mi / ma);
    if (score > best) {
      best = score;
      res = k;
    }
  }

  printf("%d %.9lf\n", res, best);
}
