#include <cmath>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<double> c;
int N, G, T;
double denom;

double rec(int t, vector<int> &occ, double curr) {
  if (t == T)
    return curr/denom;
  double tot = 0.0;
  for (int i = 1; i <= G; i++) {
    bool placed = false;
    for (int j = 0; j < occ.size(); j++) {
      if (occ[j] == 0 && c[j] >= i) {
	occ[j] = i;
	tot += rec(t+1, occ, curr+i);
	occ[j] = 0;
	placed = true;
	break;
      }
    }
    if (!placed)
      tot += rec(t+1, occ, curr);
  }
  return tot;
}

int main() {
  cin >> N >> G >> T;
  c.resize(N);
  for (int i = 0; i < N; i++)
    cin >> c[i];
  sort(c.begin(), c.end());
  vector<int> occ(c.size(), 0);
  denom = pow(G, T);
  cout << setprecision(9) << rec(0, occ, 0.0) << endl;
  return 0;
}
