#define _GLIBCXX_DEBUG
#include <array>
#include <iostream>
#include <vector>
using namespace std;
int main() {
	int h, w, mod = 1e9 + 7;
	cin >> h >> w;
	if(h == 1) return cout << (w == 1 ? 1 : 0) << endl, 0;
	--h, --w; // dp[i][j]: # trees height max h-i with rightmost branch height at least j
	array<vector<int>, 2> dp;
	for(auto &d : dp) d.assign(h + 2, 0), d[0] = 1;
	for(int i : {0, 1})
		for(int k = 1; k <= w; ++k)
			for(int j    = h - i; j >= 0; --j)
				dp[i][j] = (dp[i][j + 1] + (j >= 1 ? dp[i][j - 1] : 0)) % mod;
	return cout << (dp[0][0] - dp[1][0] + mod) % mod << endl, 0;
}
