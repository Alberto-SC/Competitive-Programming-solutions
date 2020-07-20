#include <cassert>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

double C(int n, int k) {
  if (n < k) return 0.0;
  double ret = 1.0;
  for (int i = 1; i <= k; i++)
    ret *= (n-i+1.0)/(i);
  return ret;
}

vector<double> c;
int N, G, T;

double E(const pair<double, double>& x) {
  return (x.first == 0.0 ? 0.0 : x.second/x.first);
}

double avg(int i, int k) {
  if (k > N) return 0.0;
  if (c[i] == c[k])
    return c[k];
  return (c[i]+1+c[k])/2.0;
}

map<tuple<int,int,int>,pair<double,double>> m;

// X(i, j, r) is the expected number of people sitting in [1..N] \cap
// [i+1..j] given that exactly r groups are seated in [i+1..j] and the
// group sizes are uniformly random in [c[i]+1..c[j]].
//
// the return value is a pair <denom, numerator> of the expectation
// that is computed
pair<double, double> X(int i, int j, int r) {
  if (m.count(make_tuple(i,j,r)) > 0) return m[make_tuple(i,j,r)];

  // default is 0 ways of getting 0
  pair<double, double> f = {0.0, 0.0};

  // if we are seating 0 people, just return 1 way of getting a 0
  if (r == 0)
    return m[make_tuple(i,j,r)] = {1.0, 0.0};

  // when there are fewer people than tables in the range, some table
  // must be empty, so condition on the RIGHTMOST table (k-th) being
  // empty
  if (r < j-i) {
    for (int k = max(j-r, i+1); k <= j; k++) {
      f.first  += C(r, j-k)*X(i, k-1, r-(j-k)).first*X(k, j, j-k).first;
      f.second += C(r, j-k)*X(i, k-1, r-(j-k)).first*X(k, j, j-k).first*
	(E(X(i, k-1, r-(j-k))) + E(X(k, j, j-k)));
    }
  } else {
    // r == j-i and therefore we have exactly as many tables as
    // people. we cannot condition on a table being empty. instead we
    // condition on the k-th table being the *last* occupied. So
    // among, the j-i random variables representing the group sizes
    // (the last of which we set aside), we condition on some k-i-1
    // among the j-i-1 being less than or equal to c[k-1] and the rest
    // being greater than c[k], and finally the last one being
    // somewhere in the range c[i]+1..c[k].
    for (int k = i+1; k <= j; k++) {
      f.first  += C(j-i-1, k-i-1)*X(i, k-1, k-1-i).first*X(k, j, j-k).first*(c[k]-c[i]);
      f.second += C(j-i-1, k-i-1)*X(i, k-1, k-1-i).first*X(k, j, j-k).first*(c[k]-c[i])*
	(E(X(i, k-1, k-1-i)) + avg(i, k) + E(X(k, j, j-k)));
    }
  }

  return m[make_tuple(i,j,r)] = f;
}

int main() {
  cin >> N >> G >> T;

  c.resize(N+T+1);
  c[0] = 0;
  for (int i = 0; i < N; i++) {
    cin >> c[i+1];
    c[i+1] = min(c[i+1], double(G));
  }
  for (int i = 0; i < T; i++)
    c[N+1+i] = G;
  sort(c.begin(), c.end());

  auto F = X(0, N+T, T); // F.first must be equal to G^T
  fprintf(stderr, "map size: %lu\n", m.size());
  printf("%.9lf\n", E(F));
  return 0;
}
