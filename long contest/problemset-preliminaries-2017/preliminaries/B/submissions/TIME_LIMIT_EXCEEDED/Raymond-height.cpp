// Solution to: Bonsai
// Using recursion on the height.
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
long long dp[MaxHW][MaxHW]; // dp[i][j] = number of Bonsai trees of height at most i and weight j


int main () {
	cin >> h >> w;
	
	// Initialise DP array
	for (int i = 1; i <= h; i++)
	for (int j = 1; j <= w; j++) {
		dp[i][j] = 0;
		if (j == 1)
			dp[i][j]= 1;
	}
	
	// Start DP
	for (int i = 2; i <= h; i++) 
	for (int j = 1; j <= w; j++) {
		// In order to make a tree of height at most i and weight j, we take a number of trees
		// of height at most i-1 and weights adding up to j-1.
		long long dp2[j]; // dp2[m] = number of compositions of trees of height i-1 and weight m
		
		// Initialise
		for (int m = 0; m <= j-1; m++)
			dp2[m] = 0;
		dp2[0] = 1; 
		
		// DP for the products
		for (int m = 1; m <= j-1; m++) {
			for (int l = 1; l <= m; l++) {
				dp2[m] += dp[i-1][l] * dp2[m-l];
				dp2[m] %= MOD;
			}
		}
		
		dp[i][j] = dp2[j-1];
	}
	

	
	cout << (MOD + dp[h][w] - dp[h-1][w]) % MOD << '\n';
	return 0;
}
