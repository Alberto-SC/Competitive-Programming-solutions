// Solution to: Bonsai
// This is simply a less clever version (edits by Mees) of Raymond-fast, with
// almost all code copied.  Because it has to recompute partial sums, the
// complexity is a factor higher.
// 
// Runtime: O(W^3)

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
long long dpA[MaxHW][MaxHW]; // dpA[i][j] = number of Bonsai trees of left-height i and weight j, never exceeding height h
long long dpB[MaxHW][MaxHW]; // dpB[i][j] = number of Bonsai trees of left-height i and weight j, never exceeding height h-1


int main () {
	cin >> h >> w;

	// Edge case added by Ragnar
	if( h==1 && w==1 ){
		cout << 1 << endl;
		return 0;
	}
	
	// Initialise DP array
	for (int i = 1; i <= h; i++)
	for (int j = 1; j <= w; j++) {
		dpA[i][j] = dpB[i][j] = 0;
	}
	dpA[1][1] = dpB[1][1] = 1;
	
	// Start DP
		// dpA[i][j] = sum_{k=i-1}^h     dpA[k][j-1]
		// dpB[i][j] = sum_{k=i-1}^{h-1} dpB[k][j-1]
		// i.e. in order to make a tree of weight j and left-height i
		// we take a tree of left-height k at least i and weight j-1,
		// and we attach a branch on the left, making the new tree have
		// exactly left-height i.
	for (int j = 2; j <= w; j++) {
		//long long sumA = dpA[h][j-1];
		//long long sumB = dpB[h-1][j-1];
		for (int i = h; i >= 2; i--) {
            for(int k = i-1; k <= h; k++) {
                dpA[i][j] += dpA[k][j-1];
                dpA[i][j] %= MOD;
            }

            /*
			sumA += dpA[i-1][j-1];
			sumA %= MOD;
			dpA[i][j] += sumA;
			dpA[i][j] %= MOD;	
            */
		}
		for (int i = h-1; i >= 2; i--) {
            for(int k = i-1; k <= h-1; k++) {
                dpB[i][j] += dpB[k][j-1];
                dpB[i][j] %= MOD;
            }
            /*
			sumB += dpB[i-1][j-1];
			sumB %= MOD;
			dpB[i][j] += sumB;
			dpB[i][j] %= MOD;	
            */
		}
	}
	
	// The answer now is sum_{i=1}^h dpA[i][w] - dpB[i][w]
	long long ans = 0;
	for (int i = 1; i <= h; i++) {
		ans += MOD + dpA[i][w] - dpB[i][w];
		ans %= MOD;
	}
	
	cout << ans << '\n';
	return 0;
}
