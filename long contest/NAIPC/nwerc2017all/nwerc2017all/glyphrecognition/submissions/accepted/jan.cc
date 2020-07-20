#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int main() {

  int N;
  cin >> N;
  vector<double> xs(N),ys(N);
  for (int i=0; i<N; i++)
    cin >> xs[i] >> ys[i];

  double best_factor = 0.0;
  int best_k = 0;
  for (int k=3; k<=8; k++) {
    double min_area=1e99, max_area=0.0;
    for (int i=0; i<N; i++) {
      double x=xs[i], y=ys[i];
      double B = sqrt(x*x+y*y);
      double a = atan2(y,x) + 2*M_PI;
      while (a > 2*M_PI/k) a -= 2*M_PI/k;
      double b = M_PI*(k-2)/k/2;
      double c = M_PI - a - b;
      double C = B * sin(c) / sin(b);
      double area = k * C * C * sin(2*M_PI/k);
      min_area = min(min_area, area);
      max_area = max(max_area, area);
    }
    double factor = min_area / max_area;
    if (factor > best_factor) {
      best_factor = factor;
      best_k = k;
    }
  }
  cout << setprecision(8) << best_k << " " << best_factor << endl;
  return 0;
}
