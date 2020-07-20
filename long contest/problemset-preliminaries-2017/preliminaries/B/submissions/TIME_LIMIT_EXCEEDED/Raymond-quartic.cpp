// Solution to: Bonsai
// Using the standard recursion for Catalan numbers.
// Runtime: O(W^4)

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <cassert>

#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <list>
#include <set>
#include <map>
#include <string>

#include <iostream>
#include <sstream>

#include <utility>
#include <functional>
#include <limits>
#include <numeric>
#include <algorithm> 

using namespace std;

#define MaxHW 2001
#define MOD 1000000007
int h, w;
long long dp[MaxHW][MaxHW]; // dp[i][j] = number of Bonsai trees of height i and weight j


int main () {
	cin >> h >> w;
	
	// Initialise DP array
	for (int i = 1; i <= h; i++)
	for (int j = 1; j <= w; j++) {
		dp[i][j] = 0;
	}
	dp[1][1] = 1;
	
	// Start DP
	for (int j = 1; j <= w; j++)
	for (int i = 2; i <= h; i++) {
		// dp[i][j] = sum_{k=1}^{j-1} ( sum_{l=1}^i dp[l][k]*dp[i-1][j-k] + sum_{l=1}^{i-2} dp[i][k]*dp[l][j-k]
		// i.e. in order to make a tree of weight j and height at most i
		// we take a tree of height at most i and weight k, and to the
		// first branch point we attach a tree of height at most i - 1
		// and weight j - k.
		for (int k = 1; k <= j-1; k++) {
			for (int l = 1; l <= i; l++) {
				dp[i][j] += dp[l][k]*dp[i-1][j-k];
				dp[i][j] %= MOD;
			}	
			for (int l = 1; l <= i-2; l++) {
				dp[i][j] += dp[i][k]*dp[l][j-k];
				dp[i][j] %= MOD;
			}
		}
	}
	
	cout << dp[h][w] << '\n';
	return 0;
}
