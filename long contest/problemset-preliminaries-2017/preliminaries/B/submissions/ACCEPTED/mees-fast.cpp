// Solution to: Bonsai
// By: Mees de Vries
//
// Expected answer: ACCEPTED
// Yet another DP. "Runs around the outside of the tree." Makes more sense in
// the parentheses formulation.

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <climits>

using namespace std;

#define PRIME 1000000007

// Let us reformulate the question to make it more clear: instead of trees of
// height h and weight w, we will look at balanced strings of parentheses of
// depth at most h-1 and length at most 2*w-2. Then we will do DP: C[i,j] will
// contain the strings of parens of length i of current depth j which never go
// deeper than depth d, mod our big prime.
long long num(long long l, long long d) {
    vector<vector<long long>> C(l+1, vector<long long>(d+1, 0));
    C[0][0] = 1;
    for(int i = 1; i <= l; i++) {
        C[i][0] = C[i-1][1];
        C[i][d] = C[i-1][d-1];
        for(int j = 1; j < d; j++) {
            C[i][j] = (C[i-1][j-1] + C[i-1][j+1]) % PRIME;
        }
    }

    return C[l][0];
}

int main() {
    long long h, w; cin >> h >> w;

    // Taking heights 1 and 2 as special cases, to avoid problems with h-2 later.
    if(h == 1) {
        cout << (w==1?1:0) << endl;
        return 0;
    }
    if(h == 2) {
        cout << (w>1?1:0) << endl;
        return 0;
    }

    cout << (num(2*w-2, h-1) - num(2*w-2, h-2) + PRIME) % PRIME << endl;
    return 0;
}
