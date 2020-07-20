#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct App {
  int i, d, s;
};

bool operator< (App a, App b) {
  return a.d-a.s > b.d-b.s;
}

int main() {
  int N,C;
  cin >> N >> C;
  vector<App> apps(N);
  for (int n=0; n<N; n++) {
    apps[n].i = n + 1;
    cin >> apps[n].d >> apps[n].s;
  }
  sort(apps.begin(), apps.end());

  vector<int> dp(C+1, -9999);
  dp[0] = 0;
  vector<vector<int>> use(N+1, vector<int>(C+1));
  int sol = 0;
  int sol_c = 0;
  for(int n=0; n<N; n++) {
    App a = apps[n];
    for (int c = C - max(a.d, a.s); c>=0; c--) {
      if (dp[c]!=-9999 && dp[c] + 1 > dp[c + a.s]) {
	dp[c + a.s] = dp[c] + 1;
	use[dp[c]+1][c + a.s] = n;
      }
      if (dp[c + a.s] > sol) {
	sol = dp[c + a.s];
	sol_c = c + a.s;
      }
    }
  }

  cout << sol << endl;
  vector<App> installs;
  while (sol_c > 0) {
    App a = apps[use[sol][sol_c]];
    installs.push_back(a);
    sol_c -= a.s;
    sol--;
  }
  reverse(installs.begin(), installs.end());
  bool first = true;
  for (App a : installs) {
    if (first)
      first = false;
    else
      cout << " ";
    cout << a.i;
  }
  cout << endl;
  return 0;
}
