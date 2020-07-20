#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;

	vector<vector<int>> l(n), c(n);
	for (int i = 0; i < n; ++i) {
		int p;
		cin >> p;
		l[i].assign(p, 0);
		c[i].assign(p, 0);
		for (int j = 0; j < p; ++j) {
			cin >> l[i][j];
			int d;
			cin >> d;
			while (d--) {
				int k;
				cin >> k;
				c[i][j] |= (1 << k);
			}
		}
	}

	vector<int> cost(1 << n, 1e9);
	cost[0] = 0;
	for (int m = 0; m < (1 << n); ++m) {
		if (cost[m] > 1e9 - 3) continue;
		for (int i = 0; i < n; ++i) {
			if ((m >> i)&1) continue;
			for (size_t j = 0; j < l[i].size(); ++j) {
				if ((c[i][j]&~m) > 0) continue;
				cost[m|(1<<i)] = min(cost[m|(1<<i)], cost[m] + l[i][j]);
			}
		}
	}

	int ans = 1e9;
	for (int m = 1; m < (1 << n); m += 2) ans = min(ans, cost[m]);
	cout << ans << endl;
}
