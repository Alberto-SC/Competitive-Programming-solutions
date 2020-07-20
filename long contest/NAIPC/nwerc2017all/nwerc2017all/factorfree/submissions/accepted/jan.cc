#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

int N;
vector<int> a,d,parent;
map<int,set<int>> pos;
vector<int> range_lo, range_hi;

void sieve() {
  int MAX = 10000001;
  d = vector<int>(MAX, 0);
  d[0] = d[1] = 1;
  for (int n=0; n<MAX; n++) {
    if (d[n]) continue;
    d[n] = n;
    for (int m=2*n; m<MAX; m+=n)
      if (!d[m]) d[m] = n;
  }
}

set<int> primes(int n) {
  set<int> p;
  while (n>1) {
    p.insert(d[n]);
    n /= d[n];
  }
  return p;
}

void get_ranges() {
  range_lo = vector<int>(N);
  range_hi = vector<int>(N);
  for (int n=0; n<N; n++) {
    int lo=0, hi=N;
    for (int p : primes(a[n])) {
      auto it = pos[p].find(n);
      if (it != pos[p].begin()) {
	--it;
	int x = 1 + *it;
	if (x <= n && x > lo) lo = x;
	it++;
      }
      it++;
      if (it != pos[p].end()) {
	int x = *it;
	if (x > n && x < hi) hi = x;
      }      
    }
    range_lo[n] = lo;
    range_hi[n] = hi;
  }
}

bool build(int fr, int to, int par) {
  if (to==fr) return true;
  for (int d=0; d<to-fr; d++) {
    int n = (d%2==0 ? fr+d/2 : to-1-d/2);
    int lo = range_lo[n];
    int hi = range_hi[n];
    if (lo <= fr && hi >= to) {
      parent[n] = par;
      if (!build(fr, n, n+1)) return false;
      if (!build(n+1, to, n+1)) return false;
      return true;
    }
  }
  return false;
}

int main() {
  sieve();

  cin >> N;
  a = vector<int>(N);
  for (int n=0; n<N; n++)
    cin >> a[n];

  for (int n=0; n<N; n++)
    for (int p : primes(a[n]))
      pos[p].insert(n);

  get_ranges();

  parent = vector<int>(N);
  bool success = build(0, N, 0);
  if (!success) {
    cout << "impossible" << endl;
  } else {
    bool first = true;
    for (int n=0; n<N; n++) {
      if (first)
	first = false;
      else 
	cout << " ";
      cout << parent[n];
    }
    cout << endl;
  }
  return 0;
}
