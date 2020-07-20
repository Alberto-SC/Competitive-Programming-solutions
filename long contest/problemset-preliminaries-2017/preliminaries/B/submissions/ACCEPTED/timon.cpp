#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr ll MOD = 1e9+7;

int main() {
	int H, W;
	cin >> H >> W;
	
	if (H == 1) { cout << int(W == 1) << endl; return 0; }

	vector<vector<ll>> dp(W, vector<ll>(H, 0LL));
	fill(dp[0].begin(), dp[0].end(), 1LL);

	for (int w = 1; w < W; ++w)
		for (int h = 1; h < H; ++h)
			for (int i = 0; i < w; ++i)
				dp[w][h] = (dp[w][h] + dp[i][h-1] * dp[w-1-i][h]) % MOD;

	cout << ((MOD + dp[W-1][H-1] - dp[W-1][H-2]) % MOD) << endl;

	return 0;
}
