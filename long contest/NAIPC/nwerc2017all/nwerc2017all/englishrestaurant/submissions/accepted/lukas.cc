// Solution by lukasP (Lukáš Poláček)
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

#define rep(i, a, b) for (__typeof(b) i = a; i < (b); ++i)

struct Stat { // Contains stats about a random variable
  double sum_, cnt_;
  Stat() : sum_(0), cnt_(0) {}
  double E() {
    if (cnt_ == 0)
      return 0;
    return sum_ / cnt_;
  }
  void AddInfo(double expected, double cnt) {
    sum_ += expected * cnt;
    cnt_ += cnt;
  }
};
ostream &operator<<(ostream &out, Stat a) {
  out << a.sum_ << "/" << a.cnt_ << " = " << a.E();
  return out;
}

int n, g, t;
long double cap_avg(int x, int y, int upper) {
  if (upper > n)
    return 0;
  return (x + y + 1) / 2.0;
}
int main() {
  cin >> n >> g >> t;
  vector<int> c(n + 1);
  rep(i, 0, n) {
    cin >> c[i + 1];
    c[i + 1] = min(c[i + 1], g); // tables larger than g don't make sense
  }
  sort(c.begin() + 1, c.end());
  c.resize(t + n + 1, g); // add virtual tables that catch overflow
  int m = c.size();

  long double b[t + 1][t + 2]; // binomial coefficient
  rep(i, 0, t + 1) {
    b[i][0] = 1;
    b[i][i + 1] = 0;
    rep(j, 1, i + 1) b[i][j] = b[i - 1][j] + b[i - 1][j - 1];
  }

  Stat cont[m][m];
  // cont[i][j] has the statistics of filling up interval [i, j) with customers conditioned upon
  // *no one else* coming to the restaurant. Tables are numbered from 0 in ascending order.
  for (int i = m - 1; i >= 0; i--) {
    cont[i][i].AddInfo(0, 1); // empty interval can be occupied in only one way
    rep(j, i + 1, m) if (i + t >= j) { // only process intervals of length <= t
      rep(k, i, j) {
        // merge [i,k) and [k+1,j) by occupying table k
        long double cnt = cont[i][k].cnt_ * cont[k + 1][j].cnt_ *
                          (c[k + 1] - c[i]) * b[j - i - 1][k - i];
        long double expected = cont[i][k].E() + cont[k + 1][j].E() +
                               cap_avg(c[k + 1], c[i], k + 1);
        cont[i][j].AddInfo(expected, cnt);
      }
    }
  }

  Stat total[m][t + 1];
  // total[i][k] has the statistics of filling up the first i tables with k different groups,
  // conditioned upon no one else coming. Some of the first i tables might be empty.
  rep(i, 0, m) {
    if (i <= t)
      total[i][i] = cont[0][i];
    rep(k, 0, t + 1) if (total[i][k].cnt_ > 0) {
      rep(j, i + 1, m) {
        int new_cnt = k + j - i - 1;
        if (new_cnt > t)
          continue;
        long double cnt =
            total[i][k].cnt_ * cont[i + 1][j].cnt_ * b[new_cnt][k];
        long double expected = total[i][k].E() + cont[i + 1][j].E();
        total[j][new_cnt].AddInfo(expected, cnt);
      }
    }
  }

  printf("%.9lf\n", total[m - 1][t].E());
}
