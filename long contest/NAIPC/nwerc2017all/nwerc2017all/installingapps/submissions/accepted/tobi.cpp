#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
int n, c, dp[10005][505];
pair<pair<int,int>,int> apps[505];
bool used[10005][505];

int rec(int free, int curApp) {
	if (curApp >= n) return 0;
	if (dp[free][curApp] >= 0) return dp[free][curApp];
	int best = rec(free, curApp + 1);
	if (free >= apps[curApp].first.first && free >= apps[curApp].first.second) {
		int installed = 1 + rec(free - apps[curApp].first.second, curApp + 1);
		if (installed > best) {
			best = installed;
			used[free][curApp] = true;
		}
	}
	return dp[free][curApp] = best;
}

int main() {
	cin >> n >> c;
	FOR(i, 0, n) cin >> apps[i].first.first >> apps[i].first.second;
	FOR(i, 0, n) apps[i].second = i + 1;
	sort(apps, apps+n, [](pair<pair<int,int>,int> a, pair<pair<int,int>,int> b) {
			return a.first.first-a.first.second > b.first.first-b.first.second;
	});
	FOR(j, 0, c+1) FOR(i, 0, n) dp[j][i] = -1;
	cout << rec(c, 0) << endl;
	int i = 0, f = c;
	while (true) {
		if (i >= n) break;
		if (used[f][i]) {
			cout << apps[i].second << " ";
			f -= apps[i].first.second;
		}
		i++;
	}
	return 0;
}
