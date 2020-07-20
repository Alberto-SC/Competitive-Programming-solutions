#include <bits/stdc++.h>
using namespace std;

struct app {
	int before, after, index;

	bool operator<(const app &a) const {
		return before-after > a.before-a.after;
	}
};

const int N = 510, oo = 0x3f3f3f3f;
int dp[N][N], pred[N][N];

int main() {
	int n, c; cin >> n >> c;
	vector<app> apps(n);
	for (auto &a: apps) cin >> a.before >> a.after;
	for (int i = 0; i < n; i++) apps[i].index = i+1;
	sort(begin(apps),end(apps));
	
	memset(dp,0x3f,sizeof dp);
	dp[0][0] = 0;
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (dp[i][j] == oo) continue;

			if (dp[i][j] < dp[i+1][j]) dp[i+1][j] = dp[i][j], pred[i+1][j] = 0;
			
			if (dp[i][j] + max(apps[i].before,apps[i].after) > c) continue;
			
			if (dp[i][j] + apps[i].after < dp[i+1][j+1]) {
				dp[i+1][j+1] = dp[i][j] + apps[i].after;
				pred[i+1][j+1] = 1;
			}
		}
	
	int j = n;
	while (dp[n][j] == oo) j--;
	
	vector<int> res;
	for (int i = n; i > 0; i--) {
		if (pred[i][j]) res.push_back(i-1), j--;
	}
	reverse(begin(res),end(res));

	cout << res.size() << endl;
	for (int i: res) cout << apps[i].index << " ";
	cout << endl;
}
