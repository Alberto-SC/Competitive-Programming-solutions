#include <iostream>
#include <vector>
using namespace std;
int main() {
	int n;
	cin >> n;
	vector<vector<pair<int, int>>> thms(n);
	for(auto &t : thms) {
		int ps;
		cin >> ps;
		t.resize(ps, {0, 0});
		for(auto &p : t) {
			int deps, d;
			cin >> p.first >> deps;
			while(deps--) cin >> d, p.second |= 1 << d;
		}
	}
	int inf = 1e9, ans = inf;
	vector<int> dp(1 << n, inf);
	dp[0] = 0;
	for(int m = 0; m < (1 << n); ++m) {
		if(dp[m] == inf) continue;
		if(m & 1) ans = min(ans, dp[m]);
		for(int i = 0; i < n; ++i)
			if((m & (1 << i)) == 0)
				for(auto &p : thms[i])
					if((m & p.second) == p.second)
						dp[m | (1 << i)] = min(dp[m | (1 << i)], dp[m] + p.first);
	}
	cout << ans << endl;
	return 0;
}
